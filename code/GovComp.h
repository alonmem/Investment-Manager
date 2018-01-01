#pragma once
#include "Company.h"


using namespace std;

class GovComp : public Company{
public:
	GovComp (string name, string department, double paperValue, int numOfPapers);
	virtual Company& operator+(const Company& other) const; //add two companies. throws InvalidOpException
	virtual void print(ostream& os) const;
};

