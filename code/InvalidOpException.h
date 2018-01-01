

#pragma once
#include <exception>
#include <string.h>
using namespace std;
class InvalidOpException : public exception{
private:
char* info;
public:
	InvalidOpException(char* info){
		this->info = info;
	}
	
virtual const char* what() const  throw(){
		return info;
	}
	
};

