#include "stdafx.h"
#include "ParseURLUnit.h"

bool ParseURL::ParseURL(std::string const& url, Protocol &protocol,
	int &port, std::string &host, std::string &document)
{
	assert(host.empty());
	assert(document.empty());

	std::string remains;
	if (!SplitURLProtocol(url, protocol, remains))
	{
		return false;
	}

	if (!ParseURLRemains(remains, protocol, port, host, document))
	{
		return false;
	}

	return true;
}

bool ParseURL::SplitURLProtocol(std::string const& url,
	Protocol &protocol, std::string &remains)
{
	assert(remains.empty());

	std::string delimiter("://");
	size_t delimiterIndex = url.find(delimiter);

	const bool delimiterFound = (delimiterIndex != std::string::npos);
	const bool noDataBeforeDelimiter = (delimiterIndex == 0);
	const bool noDataAfterDelimiter = (delimiterIndex + delimiter.length() >= url.length());
	
	if (!delimiterFound || noDataBeforeDelimiter || noDataAfterDelimiter)
	{
		return false;
	}

	if (!StringToProtocol(url.substr(0, delimiterIndex), protocol))
	{
		return false;
	}

	remains = url.substr(delimiterIndex + delimiter.length());
	return true;
}

bool ParseURL::StringToProtocol(std::string protocolStr, Protocol &protocol)
{
	std::transform(protocolStr.begin(), protocolStr.end(), protocolStr.begin(), tolower);

	if (protocolStr == "http")
	{
		protocol = Protocol::HTTP;
		return true;
	}

	if (protocolStr == "https")
	{
		protocol = Protocol::HTTPS;
		return true;
	}

	if (protocolStr == "ftp")
	{
		protocol = Protocol::FTP;
		return true;
	}

	return false;
}

bool ParseURL::ParseURLRemains(std::string const& remains, Protocol protocol,
	int &port, std::string &host, std::string &document)
{
	assert(host.empty());
	assert(document.empty());

	const size_t colonIndex = remains.find(":");
	const size_t slashIndex = remains.find("/");

	const bool colonFound = (colonIndex != std::string::npos);
	const bool slashFound = (slashIndex != std::string::npos);

	const bool noHost = (colonIndex == 0 || slashIndex == 0);
	const bool noPortAfterColon = (colonFound && slashFound && slashIndex == colonIndex + 1);

	if (noHost || noPortAfterColon)
	{
		return false;
	}

	const bool portSpecified = (colonFound && (!slashFound || colonIndex < slashIndex));

	if (portSpecified)
	{
		const size_t portLength = (slashFound ? slashIndex - colonIndex - 1 : std::string::npos);
		if (!StringToPort(remains.substr(colonIndex + 1, portLength), port))
		{
			return false;
		}
	}
	else
	{
		port = GetDefaultPort(protocol);
	}

	const size_t hostLength = Min(colonIndex, slashIndex);
	host = remains.substr(0, hostLength);

	if (slashFound && slashIndex + 1 < remains.length())
	{
		document = remains.substr(slashIndex + 1, std::string::npos);
	}

	return true;
}

int ParseURL::GetDefaultPort(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return 80;
	case Protocol::HTTPS:
		return 443;
	case Protocol::FTP:
		return 21;
	default:
		assert(false);
		return 0;
	}
}

bool ParseURL::StringToPort(std::string const& portStr, int &port)
{
	try
	{
		port = std::stoi(portStr);
		return (port >= 1 && port <= 65535);
	}
	catch (std::invalid_argument const& e)
	{
		(void)e;
		return false;
	}
}

size_t ParseURL::Min(size_t a, size_t b)
{
	return ((a <= b) ? a : b);
}
