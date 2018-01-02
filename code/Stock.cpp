#pragma once
#include "Stock.h"
#include <typeinfo>
#include "AllCompanies.h"

using namespace std;

Stock::Stock(string compName, int numOfPapers, double valuePerPaper, double ownPercent) : ValuePaper(compName, numOfPapers, valuePerPaper){
	if(ownPercent < 0 || ownPercent > 100)
		throw InvalidOpException("Invalid own percent");
	this->ownPercent = ownPercent;
}

void Stock::buy(int num){
	if(num < 0)
		throw InvalidOpException("cannot buy negative amount");
	//this cae is handleded AllValuePapers
	/*if(this->numOfPapers + num > totalStocksInComp){
		throw InvalidOpException("not enough stocks in company");
	}*/
	//add stocks
	this->numOfPapers += num;
	//update own percent
	updateOwnPercent();
}

//sells stocks, returns true of user sold all of his stocks
bool Stock::sell(int num){
	if(num < 0)
		throw InvalidOpException("cannot sell negative number of stocks");
	if(this->numOfPapers < num){
		throw InvalidOpException("cannot sell more stocks than user has");
	}
	//add stocks
	this->numOfPapers -= num;
	//update own percent
	this->updateOwnPercent();
	return numOfPapers == 0;
}

void Stock::print(ostream& os) const{
	
	os << "Stock: " << endl << "name: "<< compName << endl <<"Number Of Stocks: " << numOfPapers << endl <<"Stock Value: " << valuePerPaper << endl <<"percentage: " << ownPercent << endl;
}

ValuePaper& Stock::operator+(const ValuePaper& other) const{
	//todo: also apply changes to DebtPaper's add
	if(typeid(other) != typeid(Stock)){
		throw InvalidOpException("Cannot add valuepapers of different types");
	}
	int totalStocksOfBothComps = 0; //todo: init this field, sum of total stocks of each companyS
	totalStocksOfBothComps = AllCompanies::instance().findComp(compName)->getNumOfPapers() + AllCompanies::instance().findComp(other.getCompName())->getNumOfPapers();
	//totalStocksOfBothComps = companies->find(this->compName) + companies->find(other.compName); //todo: should remove comment off this line, but im afraid!
	string newname = compName + "&" + other.getCompName();
	int newNumOfStocks = numOfPapers + other.getNumOfPapers();
	double newValue = (valuePerPaper + other.getValuePerPaper()) / 2.0;
	//cout << "new stock: num of papers owned:" << newNumOfStocks << ", total num of papers in comp:" << totalStocksOfBothComps << endl; //todo: for debug

	double newOwnPercent = ((double)newNumOfStocks / (double) totalStocksOfBothComps) * 100.0;
	Stock* newStock = new Stock(newname, newNumOfStocks, newValue, newOwnPercent); 
	return *newStock; //DAT memory leak though
}

//updates own percent of this stock
void Stock::updateOwnPercent(){
	int totalStocksInComp = AllCompanies::instance().findComp(compName)->getNumOfPapers();
	//todo: init numOfStocksInComp
	this->ownPercent = ((double)this->numOfPapers / (double)totalStocksInComp) * 100.0;

}
