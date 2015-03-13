#pragma once

class CWordStat
{
public:
	typedef std::map<std::string, size_t> Dict;

	CWordStat(Dict &dict);
	~CWordStat();
	void SendChar(char c);
	void EndDataStream();

private:
	static std::locale locale;

	bool m_workComplete;
	std::string m_buffer;
	Dict &m_dict;

	void AddToDict(std::string const& str);
	void FlushBuffer();
	static bool IsWordChar(char c);
	static char ToLower(char c);
};
