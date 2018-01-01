#pragma once
#include <iostream>
#include <map>
#include <algorithm>

#include "Company.h"

using namespace std;

//implements singleton pattern
class AllCompanies{
private:
	map<string, Company*> companies;
	AllCompanies(){};
public:
	void deleteAll();
	static AllCompanies& instance(); //get the single istance of this class
	Company* findComp(const string& name) const; //return campny by name
	void addCompany(Company* c); //adds new company. throws InvalidOpException if company with same name already exists
	void removeCompany(const string& name); //remove a company.
	void print(const string& name) const;
	void printAll() const;
	void changeName(Company& comp, string& newName);
	//void setMAllValuePapers(const AllValuePapers& mAllValuePapers) {this->mAllValuePapers = &mAllValuePapers;} //sets reference to allValuePapers
};
