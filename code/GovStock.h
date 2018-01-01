#pragma once

#include <iostream>
#include "ValuePaper.h"
#include "Stock.h"
#include "DebtPaper.h"


class GovStock: public Stock, public DeptPaper{
private:
	bool canBeTraded;
public:
	GovStock(string compName, int numOfPapers, double valuePerPaper,  double ownPercent, Date toReturn, double interest, bool canBeTraded);
	virtual void buy(int num);
	virtual bool sell(int num);
	virtual void print(ostream& os) const;
	virtual ValuePaper& operator+(const ValuePaper& other) const;
	
	void SetCanBeTraded(bool canBeTraded) {this->canBeTraded = canBeTraded;}
	bool getCanBeTraded() const {return canBeTraded;}
};