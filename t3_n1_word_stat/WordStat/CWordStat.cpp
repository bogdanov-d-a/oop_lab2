#include "stdafx.h"
#include "CWordStat.h"

bool CWordStat::IsWordChar(char c)
{
	return (
		(c != ' ') &&
		(c != '\t') &&
		(c != '\n')
	);
}

CWordStat::CWordStat(Dict &dict):
	m_workComplete(false),
	m_dict(dict)
{
	m_dict.clear();
};

CWordStat::~CWordStat()
{
	if (!m_workComplete)
	{
		EndDataStream();
	}
}

void CWordStat::SendChar(char c)
{
	assert(!m_workComplete);

	if (IsWordChar(c))
	{
		m_buffer.push_back(ToLower(c));
	}
	else
	{
		FlushBuffer();
	}
}

void CWordStat::EndDataStream()
{
	assert(!m_workComplete);
	FlushBuffer();
	m_workComplete = true;
}

void CWordStat::AddToDict(std::string const& str)
{
	assert(!str.empty());

	Dict::iterator findResult = m_dict.find(str);
	if (findResult != m_dict.end())
	{
		++findResult->second;
	}
	else
	{
		m_dict[str] = 1;
	}
}

void CWordStat::FlushBuffer()
{
	if (!m_buffer.empty())
	{
		AddToDict(m_buffer);
		m_buffer.clear();
	}
}

char CWordStat::ToLower(char c)
{
	return std::tolower(c, locale);
}

std::locale CWordStat::locale("rus_rus.866");
