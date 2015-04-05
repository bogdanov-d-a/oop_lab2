#pragma once

typedef std::function<void(char)> SendCharFunction;
typedef std::function<void(std::string const&)> SendStringFunction;
typedef std::set<std::string> StringSet;

void SplitWords(std::istream &input, SendCharFunction whitespaceCallback, SendStringFunction wordCallback);
std::string ToLower(std::string const& str);
void FilterStream(std::istream &input, std::ostream &output, StringSet const& filterSet);
