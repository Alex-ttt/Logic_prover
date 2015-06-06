#pragma once
#include <string>

using std::string;

class BAN_Exception {
private:
	string msg;

public:
	BAN_Exception(const string &m) : msg(m) {}
	string getMessage() const {
		return msg;	
	}; 
};