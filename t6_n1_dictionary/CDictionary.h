#pragma once

class CDictionary
{
public:
	enum class LoadFromFileResult
	{
		SUCCESS,
		OPEN_ERROR,
		DATA_CORRUPTED
	};
	static const std::string fileDelimiter;

	CDictionary(std::string const& fileName);
	LoadFromFileResult LoadFromFile();
	void AddPair(std::string const& key, std::string const& value, bool fromFile = false);
	bool FindValue(std::string const& key, std::string &value) const;
	bool SyncWithFile(bool fullRewrite = false);
	static bool CheckKey(std::string const& key);
	bool HasUnsyncedChanges();

private:
	typedef struct
	{
		std::string value;
		bool synched;
	}
	DictValue;
	typedef std::map<std::string, DictValue> Dict;

	Dict m_dict;
	bool m_hasUnsyncedChanges;
	std::string m_fileName;

	static bool ParseLine(std::string const& line, std::string &key, std::string &value);
};
