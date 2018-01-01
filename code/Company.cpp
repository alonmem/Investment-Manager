#pragma once
#include "Company.h"

Company::Company (string name, string department, double paperValue, int numOfPapers){
	this->name = name;
	this->department = department;
	this->paperValue = paperValue;
	this->numOfPapers = numOfPapers;
}

void Company::changeName(string newName){
	this->name = newName;
}

void Company::changePaperValue(double newValue){
	this->paperValue = newValue;
}

void Company::changeNumOfPapers(int newNum){
	this->numOfPapers = newNum;
}

const string& Company::getName() const{
	return this->name;
}

bool Company::isNameEqualTo(const string& name) const{
	return this->name == name;
}


ostream& operator<< (ostream& os, const Company& comp){
	comp.print(os);
	return os;
}