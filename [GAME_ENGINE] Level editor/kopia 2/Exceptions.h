#pragma once
class Error {
public:
	Error(const char * str_l) : str{ str_l } {}
	const char * what() const { return str; }
private:
	const char * str;
};