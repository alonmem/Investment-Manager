#pragma once

#include "GovOrganization.h"
#include "Company.h"
#include "InvalidOpException.h"

#include <typeinfo>

GovOrganization::GovOrganization (string name, string department, double paperValue, int numOfPapers) : Company(name, department, paperValue, numOfPapers){
	//empty
}

Company& GovOrganization::operator+(const Company& other) const{
	if(typeid(other) != typeid(GovOrganization)){
		throw InvalidOpException("Cannot add two companies of different type");
	}
	string newname = this->name + "&" + other.getName();
	string newDept = this->department + "&" + other.getDepartment();
	double newValue = (this->paperValue + other.getPaperValue()) / 2.0;
	int newNum = this->numOfPapers + other.getNumOfPapers();
	Company* newComp = new GovOrganization(newname, newDept, newValue, newNum);
	//todo: add paperValues of this companies from OUTSIDE of this method(from the func that called this method)
	return *newComp; //todo: fix this memory leak
	
}

void GovOrganization::print(ostream& os) const{
	os << "[Government Organization name:" << this->name << ",Department:" << department << ", NumOfPapers:" << numOfPapers << ", Paper value:" << paperValue << "]" << endl;
}