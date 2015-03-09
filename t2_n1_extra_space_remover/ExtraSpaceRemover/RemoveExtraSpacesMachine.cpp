#include "stdafx.h"
#include "RemoveExtraSpacesMachine.h"

CRemoveExtraSpacesMachine::CRemoveExtraSpacesMachine(charCallback_t callback)
{
	m_state = state_t::START_POSITION;
	assert(callback != nullptr);
	m_callback = callback;
}

void CRemoveExtraSpacesMachine::SendChar(char c)
{
	switch (m_state)
	{
	case state_t::START_POSITION:
		if (c != SPACE_CHAR)
		{
			m_callback(c);
			m_state = state_t::NOTHING_PENDING;
		}
		break;

	case state_t::NOTHING_PENDING:
		if (c == SPACE_CHAR)
		{
			m_state = state_t::SPACE_PENDING;
		}
		else
		{
			m_callback(c);
		}
		break;

	case state_t::SPACE_PENDING:
		if (c != SPACE_CHAR)
		{
			m_callback(SPACE_CHAR);
			m_callback(c);
			m_state = state_t::NOTHING_PENDING;
		}
	}
}

std::string CRemoveExtraSpacesMachine::RemoveExtraSpaces(std::string const& arg)
{
	std::string result;
	CRemoveExtraSpacesMachine machine([&result](char c){ result.push_back(c); });
	std::for_each(arg.begin(), arg.end(), [&machine](char c){ machine.SendChar(c); });
	return result;
}
