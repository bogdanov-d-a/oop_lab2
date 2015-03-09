#pragma once

class CRemoveExtraSpacesMachine
{
public:
	typedef std::function<void(char)> charCallback_t;

	CRemoveExtraSpacesMachine(charCallback_t callback);
	void SendChar(char c);
	static std::string RemoveExtraSpaces(std::string const& arg);

protected:
	enum class state_t
	{
		START_POSITION,
		SPACE_PENDING,
		NOTHING_PENDING
	};

	static const char SPACE_CHAR = ' ';

	state_t m_state;
	charCallback_t m_callback;
};
