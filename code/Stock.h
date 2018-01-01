#pragma once
#include "ValuePaper.h"
	
	
using namespace std;

class Stock : public virtual ValuePaper{
protected:
	double ownPercent;
public:
	Stock(string compName, int numOfPapers, double valuePerPaper, double ownPercent); //c'tor
	virtual void buy(int num);
	virtual bool sell(int num);
	virtual void print(ostream& os) const;
	void updateOwnPercent(); //updates ownPercent of this stock
	virtual ValuePaper& operator+(const ValuePaper& other) const; //add two papers
};

