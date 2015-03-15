// Dictionary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CDictionary.h"

bool LoadDictionary(CDictionary &dict)
{
	CDictionary::LoadFromFileResult result = dict.LoadFromFile();
	
	if (result == CDictionary::LoadFromFileResult::OPEN_ERROR)
	{
		std::cout << "Could not load dictionary; new one will be created on sync\n";
	}
	else if (result == CDictionary::LoadFromFileResult::DATA_CORRUPTED)
	{
		std::cout << "Dictionary file is corrupted; program will now halt\n";
	}

	return (result != CDictionary::LoadFromFileResult::DATA_CORRUPTED);
}

void RequestNewValue(CDictionary &dict, std::string const& key)
{
	assert(CDictionary::CheckKey(key));
	std::cout << "Word \"" << key << "\" is unknown. Enter translation or blank line to cancel.\n";

	std::string value;
	if (!std::getline(std::cin, value) || value.empty())
	{
		std::cout << "Ignored word \"" << key << "\".\n";
	}
	else
	{
		dict.AddPair(key, value);
		std::cout << "Word \"" << key << "\" has been saved as \"" << value << "\".\n";
	}
}

bool HandleUserRequest(CDictionary &dict, std::string const& str)
{
	if (str == "...")
	{
		return true;
	}

	if (!CDictionary::CheckKey(str))
	{
		std::cout << "<" << CDictionary::fileDelimiter << "> substring is not allowed\n";
		return false;
	}

	std::string value;
	if (dict.FindValue(str, value))
	{
		std::cout << value << "\n";
	}
	else
	{
		RequestNewValue(dict, str);
	}
	return false;
}

void InteractWithUser(CDictionary &dict)
{
	std::string curLine;
	while (std::getline(std::cin, curLine))
	{
		if (HandleUserRequest(dict, curLine))
		{
			return;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		assert(argc > 0);
		std::cout << "Usage: " << argv[0] << " <file name>\n";
		return 1;
	}

	const std::string fileName(argv[1]);
	CDictionary dict(fileName);

	if (!LoadDictionary(dict))
	{
		return 2;
	}

	InteractWithUser(dict);

	if (dict.HasUnsyncedChanges())
	{
		std::cout << "Dictionary has been modified. Enter Y or y to sync with file before exit.\n";

		char answer;
		std::cin >> answer;

		if (answer == 'Y' || answer == 'y')
		{
			if (dict.SyncWithFile())
			{
				std::cout << "All changes has been saved. Goodbye.\n";
			}
			else
			{
				std::cout << "Could not write data to dictionary file; all unsaved data is lost\n";
				return 3;
			}
		}
	}

	return 0;
}
