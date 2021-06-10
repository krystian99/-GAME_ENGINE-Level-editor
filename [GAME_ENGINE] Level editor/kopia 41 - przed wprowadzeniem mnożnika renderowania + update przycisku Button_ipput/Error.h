#pragma once
#include <string>

class Error
{
public:
	static const std::string & throw_Message(const std::string & str) { return str; }
};