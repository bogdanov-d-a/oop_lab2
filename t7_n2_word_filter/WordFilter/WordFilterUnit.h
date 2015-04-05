#pragma once

typedef std::set<std::string> StringSet;

void FilterStream(std::istream &input, std::ostream &output, StringSet const& filterSet);
