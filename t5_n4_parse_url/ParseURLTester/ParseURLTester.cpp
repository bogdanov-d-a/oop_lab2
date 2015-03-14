// ParseURLTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../ParseURL/ParseURLUnit.h"

bool RunValidURLTest(std::string const& url, ParseURL::Protocol protocol,
	int port, std::string const& host, std::string const& document)
{
	ParseURL::Protocol resultProtocol;
	int resultPort;
	std::string resultHost;
	std::string resultDocument;

	if (!ParseURL::ParseURL(url, resultProtocol, resultPort, resultHost, resultDocument))
	{
		return false;
	}

	return (
		(protocol == resultProtocol) &&
		(port == resultPort) &&
		(host == resultHost) &&
		(document == resultDocument)
	);
}

bool RunInvalidURLTest(std::string const& url)
{
	ParseURL::Protocol resultProtocol;
	int resultPort;
	std::string resultHost;
	std::string resultDocument;

	return !ParseURL::ParseURL(url, resultProtocol, resultPort, resultHost, resultDocument);
}

BOOST_AUTO_TEST_CASE(TaskExample)
{
	BOOST_CHECK(RunValidURLTest(
		"http://www.mysite.com/docs/document1.html?page=30&lang=en#title",
		ParseURL::Protocol::HTTP,
		80,
		"www.mysite.com",
		"docs/document1.html?page=30&lang=en#title"
	));
}

BOOST_AUTO_TEST_CASE(EmptyString)
{
	BOOST_CHECK(RunInvalidURLTest(""));
}

BOOST_AUTO_TEST_CASE(NoDelimiter)
{
	BOOST_CHECK(RunInvalidURLTest("http/host:1/doc"));
}

BOOST_AUTO_TEST_CASE(NoProtocol)
{
	BOOST_CHECK(RunInvalidURLTest("://host:1/doc"));
}

BOOST_AUTO_TEST_CASE(NoAddress)
{
	BOOST_CHECK(RunInvalidURLTest("ftp://"));
}

BOOST_AUTO_TEST_CASE(UnknownProtocol)
{
	BOOST_CHECK(RunInvalidURLTest("github-windows://openRepo/repo"));
}

BOOST_AUTO_TEST_CASE(RandomCaseProtocol)
{
	BOOST_CHECK(RunValidURLTest(
		"HttPS://github.com/bogdanov-d-a",
		ParseURL::Protocol::HTTPS,
		443,
		"github.com",
		"bogdanov-d-a"
	));
}

BOOST_AUTO_TEST_CASE(HostFormatError)
{
	BOOST_CHECK(RunInvalidURLTest("http:///host/doc"));
	BOOST_CHECK(RunInvalidURLTest("http://:host/doc"));
}

BOOST_AUTO_TEST_CASE(ColonAndNoPort)
{
	BOOST_CHECK(RunInvalidURLTest("http://host:/doc"));
}

BOOST_AUTO_TEST_CASE(FakePort)
{
	BOOST_CHECK(RunValidURLTest(
		"ftp://host/doc:123",
		ParseURL::Protocol::FTP,
		21,
		"host",
		"doc:123"
	));
}

BOOST_AUTO_TEST_CASE(RealPort)
{
	BOOST_CHECK(RunValidURLTest(
		"ftp://host:123/doc",
		ParseURL::Protocol::FTP,
		123,
		"host",
		"doc"
	));
}

BOOST_AUTO_TEST_CASE(SlashAndNoDoc)
{
	BOOST_CHECK(RunValidURLTest(
		"https://host/",
		ParseURL::Protocol::HTTPS,
		443,
		"host",
		""
	));
}

BOOST_AUTO_TEST_CASE(BadPortFormat)
{
	BOOST_CHECK(RunInvalidURLTest("http://host:-1/doc"));
	BOOST_CHECK(RunInvalidURLTest("http://host:port/doc"));
	BOOST_CHECK(RunInvalidURLTest("http://host:65536/doc"));
}
