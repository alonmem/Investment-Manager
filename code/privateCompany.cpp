#pragma once
#include "PrivateCompany.h"
#include <typeinfo>
#include "InvalidOpException.h"
using namespace std;
PrivateCommpany::PrivateCommpany (string name, string department, double paperValue, int numOfPapers) : Company(name, department, paperValue, numOfPapers){
	//empty
}

Company& PrivateCommpany::operator+(const Company& other) const{
	if(typeid(other) != typeid(PrivateCommpany)){
		throw InvalidOpException("Cannot add two companies of different type");
	}
	string newname = this->name + "&" + other.getName();
	string newDept = this->department + "&" + other.getDepartment();
	double newValue = (this->paperValue + other.getPaperValue()) / 2.0;
	int newNum = this->numOfPapers + other.getNumOfPapers();
	
	Company* newComp = new PrivateCommpany(newname, newDept, newValue, newNum);
	
	//todo: add paperValues of this companies from OUTSIDE of this method(from the func that called this method)
	return *newComp; //todo: fix this memory leak
}

void PrivateCommpany::print(ostream& os) const{
	os << "[Private Company. name:" << this->name << ",Department:" << department << ", NumOfPapers:" << numOfPapers << ", Paper value:" << paperValue << "]" << endl;
}
/*
ostream& operator<< (ostream& os, const PrivateCommpany& comp){
	comp.print(os);
	return os;
}*/