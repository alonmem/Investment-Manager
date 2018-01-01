#pragma once
#include "ValuePaper.h"

#include "Date.h"
	

using namespace std;

//todo: rename class to DebtPaper
class DeptPaper : public virtual ValuePaper{
protected:
	double interest;
	Date toReturn;
public:
	DeptPaper(string compName, int numOfPapers, double valuePerPaper,  Date toReturn, double interest); //c'tor
	virtual void buy(int num);
	virtual bool sell(int num);
	virtual void print(ostream& os) const;
	virtual ValuePaper& operator+(const ValuePaper& other) const; //add two DebtPapers
	void addToReturnDate(int years, int months, int days); //adds toAdd to returnData of this DebtPapaer. throws InvalidDateException
	void changeInterest(double newInterest); //changes the interest of this DebtPaper. throws InvalidOpException.
	
	DeptPaper& SetInterest(double interest) {this->interest = interest; return *this;}
	DeptPaper& SetToReturn(const Date& toReturn) {this->toReturn = toReturn; return *this;}
	double GetInterest() const {return interest;}
	const Date& GetToReturn() const {return toReturn;}

};
