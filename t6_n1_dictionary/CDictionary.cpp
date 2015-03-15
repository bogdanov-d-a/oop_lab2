#include "stdafx.h"
#include "CDictionary.h"

CDictionary::CDictionary(std::string const& fileName):
	m_hasUnsyncedChanges(false),
	m_fileName(fileName)
{
	assert(!m_fileName.empty());
}

CDictionary::LoadFromFileResult CDictionary::LoadFromFile()
{
	assert(!m_hasUnsyncedChanges);
	assert(m_dict.empty());

	std::ifstream fileStream(m_fileName);
	if ((fileStream.rdstate() & std::ifstream::failbit) != 0)
	{
		return LoadFromFileResult::OPEN_ERROR;
	}

	std::string curLine;
	while (std::getline(fileStream, curLine))
	{
		std::string key;
		std::string value;

		if (!ParseLine(curLine, key, value))
		{
			m_dict.clear();
			return LoadFromFileResult::DATA_CORRUPTED;
		}

		AddPair(key, value, true);
	}

	return LoadFromFileResult::SUCCESS;
}

void CDictionary::AddPair(std::string key, std::string const& value, bool fromFile)
{
	assert(CheckKey(key));
	ToLower(key);

	m_dict[key] = { value, fromFile };
	if (!fromFile)
	{
		m_hasUnsyncedChanges = true;
	}
}

bool CDictionary::ParseLine(std::string const& line, std::string &key, std::string &value)
{
	assert(key.empty());
	assert(value.empty());

	const size_t startElemIndex = line.find("[");
	const size_t delimiterIndex = line.find(fileDelimiter);

	const bool startElemOnStart = (startElemIndex == 0);
	const bool delimiterFound = (delimiterIndex != std::string::npos);

	if (!startElemOnStart || !delimiterFound)
	{
		return false;
	}

	const bool keyPresent = (delimiterIndex > 1);
	const bool valuePresent = (delimiterIndex + fileDelimiter.length() < line.length());

	if (!keyPresent || !valuePresent)
	{
		return false;
	}

	key = line.substr(1, delimiterIndex - 1);
	value = line.substr(delimiterIndex + fileDelimiter.length());
	return true;
}

bool CDictionary::FindValue(std::string key, std::string &value) const
{
	assert(value.empty());
	assert(CheckKey(key));
	ToLower(key);

	Dict::const_iterator findResult = m_dict.find(key);
	if (findResult != m_dict.cend())
	{
		value = findResult->second.value;
		return true;
	}
	else
	{
		return false;
	}
}

bool CDictionary::SyncWithFile(bool fullRewrite)
{
	std::ofstream fileStream;
	const bool needSync = (!fullRewrite && m_hasUnsyncedChanges);

	if (needSync)
	{
		fileStream.open(m_fileName, std::ios_base::app);
		if ((fileStream.rdstate() & std::ifstream::failbit) != 0)
		{
			return SyncWithFile(true);
		}
	}

	if (fullRewrite)
	{
		fileStream.open(m_fileName);
		if ((fileStream.rdstate() & std::ifstream::failbit) != 0)
		{
			return false;
		}
	}

	if (needSync || fullRewrite)
	{
		std::for_each(m_dict.begin(), m_dict.end(),
			[&fileStream, fullRewrite](Dict::value_type &dictValue)
		{
			if (fullRewrite || !dictValue.second.synched)
			{
				fileStream << "[" << dictValue.first << fileDelimiter << dictValue.second.value << "\n";
				dictValue.second.synched = true;
			}
		});
	}

	m_hasUnsyncedChanges = false;
	return true;
}

const std::string CDictionary::fileDelimiter("] ");

bool CDictionary::CheckKey(std::string const& key)
{
	return (key.find(fileDelimiter) == std::string::npos);
}

bool CDictionary::HasUnsyncedChanges()
{
	return m_hasUnsyncedChanges;
}

void CDictionary::ToLower(std::string &str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
}
