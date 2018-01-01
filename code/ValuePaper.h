
#pragma once
#include <string.h>
#include <iostream>
#include "InvalidOpException.h"

#include "AllCompanies.h"
using namespace std;

class ValuePaper{
	
protected:
	string compName;
	int numOfPapers;
	double valuePerPaper;
	
public:
	ValuePaper(string compName, int numOfPapers, double valuePerPaper); //c'tor
	virtual void buy(int num) = 0; //buy more papers. throws InvalidOpException
	virtual bool sell(int num) = 0; //sell papers. returns true if sold all current stocks. throws InvalidOpException
	void changeValue(double change); //changes value of this paper. throws InvalidOpException
	double calcValue() const; //returns the total value of this paper.
	virtual void print(ostream& os) const = 0; //print this paper's info to ostream.
	virtual ValuePaper& operator+(const ValuePaper& other) const = 0; //add two papers
	
	//getters & setters
	const string& getCompName() const;
	
	void setCompName(const string& compName) {this->compName = compName;}
	void setNumOfPapers(int numOfPapers) {this->numOfPapers = numOfPapers;}
	void setValuePerPaper(double valuePerPaper) {this->valuePerPaper = valuePerPaper;}
	//AllCompanies* getCompanies() {return companies;}
	int getNumOfPapers() const {return numOfPapers;}
	double getValuePerPaper() const {return valuePerPaper;}
};

ostream& operator<< (ostream& os, const ValuePaper& vp);