#pragma once
#include "ValuePaper.h"


ValuePaper::ValuePaper(string compName, int numOfPapers, double valuePerPaper){
	this->compName = compName;
	
	if(numOfPapers < 0 || valuePerPaper < 0)
		throw InvalidOpException("Illigle negtive value");
		
	this->numOfPapers = numOfPapers;
	this->valuePerPaper = valuePerPaper;
}

void ValuePaper::changeValue(double change){
	//throw exception if tries to change value to negative
	if(change < 0)
		throw InvalidOpException("cannot change paper value to negative");
	
	this->valuePerPaper = change;
}

const string& ValuePaper::getCompName() const{
	return this->compName;
}

double ValuePaper::calcValue() const{
	return this->valuePerPaper * this->numOfPapers;
}

/*
ostream& operator<< (ostream& os, const ValuePaper& vp){
	vp.print(os);
	return os;
}*/

ostream& operator<< (ostream& os, const ValuePaper& vp){
	vp.print(os);
	return os;
}