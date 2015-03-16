#pragma once

namespace WordFilter
{
	typedef std::function<void(char)> SendCharFunction;
	typedef std::function<void(std::string const&)> SendStringFunction;
	typedef std::set<char> CharSet;
	typedef std::set<std::string> StringSet;

	const CharSet whitespaceSet = {
		' ', '\t', '\n', ':', ',', '-', '!', '.', '?', ';', '/', '\\',
		'%', '^', '*', '+', '=', '(', ')', '[', ']', '{', '}', '<', '>'
	};

	void SplitWords(std::istream &istream,
		SendCharFunction whitespaceCallback, SendStringFunction wordCallback);
	void FilterText(std::istream &istream,
		std::ostream &ostream, StringSet const& filterSet);
	void FlushBuffer(std::string &buffer, SendStringFunction wordCallback);
	void ToLower(std::string const& source, std::string &target);
	std::string ToLower(std::string const& str);
}
