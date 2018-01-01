#pragma once

#include "GovStock.h"
#include "ValuePaper.h"
#include "Stock.h"
#include "DebtPaper.h"
#include <typeinfo>
#include "AllCompanies.h"
//c'tor
GovStock::GovStock(string compName, int numOfPapers, double valuePerPaper,  double ownPecrent, Date toReturn, double interest, bool canBeTraded) : 
ValuePaper(compName,numOfPapers, valuePerPaper), Stock(compName,numOfPapers, valuePerPaper, ownPecrent), DeptPaper(compName, numOfPapers, valuePerPaper, toReturn, interest){
		this->canBeTraded = canBeTraded;
}

ValuePaper& GovStock::operator+(const ValuePaper& other) const{
	if(typeid(other) != typeid(GovStock)){
		throw InvalidOpException("Cannot add valuepapers of different types");
	}
	//cast other to DeptPaper, todo: add typeid & throw an exception
	GovStock& otherGovStock = dynamic_cast<GovStock&>(const_cast<ValuePaper&>(other));
	int totalStocksOfBothComps = 0;
	totalStocksOfBothComps = AllCompanies::instance().findComp(compName)->getNumOfPapers() + AllCompanies::instance().findComp(other.getCompName())->getNumOfPapers();

	string newname = compName + "&" + otherGovStock.getCompName();
	int newNumOfStocks = numOfPapers + otherGovStock.getNumOfPapers();
	double newValue = (valuePerPaper + otherGovStock.getValuePerPaper()) / 2.0;
	double newInterest = (interest + otherGovStock.interest);
	double newOwnPercent = ((double)newNumOfStocks / (double) totalStocksOfBothComps) * 100.0;
	bool newCanBeTraded = (canBeTraded & otherGovStock.canBeTraded);
	bool isDateAfter = toReturn.isAfter(otherGovStock.toReturn);
	Date newToReturn =  isDateAfter ? otherGovStock.toReturn : toReturn; //set new date to earlier date between two operands
	DeptPaper* newGovStock = new GovStock(newname, newNumOfStocks, newValue,newOwnPercent, newToReturn, newInterest, newCanBeTraded); 
	return *newGovStock; 
}

void GovStock::print(ostream& os) const{
	os << "[Govenment Stock: " << endl;
	os << "name: "<<compName << endl;
	os << "Number Of Stocks: ";
	os << numOfPapers << endl;
	os << "Stock Value: ";
	os << valuePerPaper << endl;
	os << "interest: ";
	os << interest << endl;
	os << "experation date: ";
	toReturn.print(os);
	os << endl;
	os << "Can Be Traded: " << (canBeTraded ? "Yes" : "No");
	os << endl;
}

void GovStock::buy(int num){
	DeptPaper::buy(num);
}
bool GovStock::sell(int num){
	return DeptPaper::sell(num);
}