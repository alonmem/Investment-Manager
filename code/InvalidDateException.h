#pragma once

#include <exception>
#include <string>
using namespace std;
class InvalidDateExcetion : public exception{
private:
char* info;
public:
	InvalidDateExcetion(char* info){
		this->info = info;
	}
	
	virtual const char* what() const  throw(){
		return info;
	}
	
};
