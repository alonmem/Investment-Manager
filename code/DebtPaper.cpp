#pragma once
#include "DebtPaper.h"
#include "Date.h"
#include "Stock.h"
#include <typeinfo>
#include "AllCompanies.h"


using namespace std;
DeptPaper::DeptPaper(string compName, int numOfPapers, double valuePerPaper, Date d, double interest) : ValuePaper(compName, numOfPapers, valuePerPaper), toReturn(d.getYear(), d.getMonth(), d.getDay()){
	//this->toReturn = Date(d.getYear(), d.getMonth(), d.getDay());//will throw invalidDateException if date is not valid
	if(interest < 0)
		throw InvalidOpException("Cannot have negative interest rate");
	this->interest = interest;
}


void DeptPaper::buy(int num){
	//int totalStocksInComp;
	if(num < 0)
		throw InvalidOpException("cannot buy negative amount");
	//this case is handled in AllValuePapers
	//if(this->numOfPapers + num > totalStocksInComp){
	//	throw InvalidOpException("not enough stocks in company");
//	}
	//add stocks
	this->numOfPapers += num;
}

//sells stocks, returns true of user sold all of his stocks
bool DeptPaper::sell(int num){
	//int totalStocksInComp;
	//todo: init numOfStocksInComp
	if(num < 0)
		throw InvalidOpException("cannot sell negative amount");
	if(this->numOfPapers < num){
		throw InvalidOpException("cannot sell more stocks than user has");
	}
	//add stocks
	this->numOfPapers -= num;
	
	return numOfPapers == 0;
}

/*
//todo: check why this doesn't work when it's in Date.cpp (currently it's commented out)
ostream& operator<< (ostream& out, const Date& date){
	date.print(out);
	return out;
}
 * */

void DeptPaper::print(ostream& os) const{
	os << "Debt Paper" << endl;
	os << "name: " << compName << endl;
	os << "Number Of Stocks: ";
	os << numOfPapers << endl;
	os << "Stock Value: ";
	os << valuePerPaper << endl ;
	os << "interest: ";
	os << interest << endl;
	os << "experation date: ";
	os << toReturn << endl;
}

ostream& operator<<(ostream& os, const DeptPaper& dp){
	dp.print(os);
	return os;
}

ValuePaper& DeptPaper::operator+(const ValuePaper& other) const{
	if(typeid(other) != typeid(DeptPaper)){
		throw InvalidOpException("Cannot add valuepapers of different types");
	}
	//cast other to DeptPaper, todo: add typeid & throw an exception
	DeptPaper& otherDeptPaper = dynamic_cast<DeptPaper&>(const_cast<ValuePaper&>(other));
	int totalStocksOfBothComps = 0; //todo: init this field, sum of total stocks of each company
	totalStocksOfBothComps = AllCompanies::instance().findComp(compName)->getNumOfPapers() + AllCompanies::instance().findComp(other.getCompName())->getNumOfPapers();
	//todo: fix thix memory leak. should return by value but can't return ValuePaper cuz its abstract
	string newname = compName + "&" + otherDeptPaper.getCompName();
	int newNumOfStocks = numOfPapers + otherDeptPaper.getNumOfPapers();
	double newValue = (valuePerPaper + otherDeptPaper.getValuePerPaper()) / 2.0;
	double newInterest = (interest + otherDeptPaper.interest);

	bool isDateAfter = toReturn.isAfter(otherDeptPaper.toReturn);
	Date newToReturn =  isDateAfter ? otherDeptPaper.toReturn : toReturn; //set new date to earlier date between two operands
	DeptPaper* newDeptPaper = new DeptPaper(newname, newNumOfStocks, newValue, newToReturn, newInterest); 
	return *newDeptPaper; //DAT memory leak though
}

//adds to return date, throws InvalidDateExcetion
void DeptPaper::addToReturnDate(int years, int months, int days){
	//create new date
	//this will throw 'InvalidDateExcetion("Invalid date")' if new date is invalid
	Date newDate(toReturn.getYear() + years, toReturn.getMonth() + months, toReturn.getDay() + days);
	//cout << "New return date year:" << newDate.getYear() << endl;
	//set current return date to new return date
	toReturn = newDate;
}

void DeptPaper::changeInterest(double newInterest){
	if(newInterest < 0.0){
		throw InvalidOpException("Interest rate cannot be negative");
	}
	this->interest = newInterest;
}