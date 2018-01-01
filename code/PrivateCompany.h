#pragma once
#include "Company.h"

using namespace std;

class PrivateCommpany : public Company{
public:
	PrivateCommpany (string name, string department, double paperValue, int numOfPapers);
	virtual Company& operator+(const Company& other) const; //add two companies. throws InvalidOpException
	virtual void print(ostream& os) const;
};

