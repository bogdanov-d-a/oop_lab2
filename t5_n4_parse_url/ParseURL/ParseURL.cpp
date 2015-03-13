// ParseURL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ParseURLUnit.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::string curUrl;
	while (std::getline(std::cin, curUrl))
	{
		ParseURL::Protocol protocol;
		int port;
		std::string host;
		std::string document;

		if (ParseURL::ParseURL(curUrl, protocol, port, host, document))
		{
			std::cout << curUrl << "\n";
			std::cout << "HOST: " << host << "\n";
			std::cout << "PORT: " << port << "\n";
			std::cout << "DOC: " << document << "\n";
		}
	}

	return 0;
}
