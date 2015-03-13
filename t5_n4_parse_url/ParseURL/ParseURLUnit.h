#pragma once

namespace ParseURL
{
	enum class Protocol
	{
		HTTP,
		HTTPS,
		FTP
	};

	bool ParseURL(std::string const& url, Protocol &protocol,
		int &port, std::string &host, std::string &document);
	bool SplitURLProtocol(std::string const& url,
		Protocol &protocol, std::string &remains);
	bool StringToProtocol(std::string protocolStr, Protocol &protocol);
	bool ParseURLRemains(std::string const& remains, Protocol protocol,
		int &port, std::string &host, std::string &document);
	int GetDefaultPort(Protocol protocol);
	bool StringToPort(std::string const& portStr, int &port);
	size_t Min(size_t a, size_t b);
}
