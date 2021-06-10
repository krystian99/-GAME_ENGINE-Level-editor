#pragma once
#include <string>

class Error {
public:
	Error(std::string str_l) : str{ str_l } {}
	std::string what() const { return str; }
private:
	std::string str;
};