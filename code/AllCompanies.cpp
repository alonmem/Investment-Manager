#pragma once
#include "AllCompanies.h"
#include "InvalidOpException.h"
#include "PrivateCompany.h"
#include "GovOrganization.h"


using namespace std;

void AllCompanies:: deleteAll(){
	
	map<string, Company*>::const_iterator itr;
	for(itr = companies.begin(); itr != companies.end(); ++itr){
		companies.erase(itr->first);
		delete itr->second;
	}
	
}

AllCompanies& AllCompanies::instance(){
	static AllCompanies* i = new AllCompanies(); //will only be executed once
	return *i; //return referce to instance
}


Company* AllCompanies::findComp(const string& name) const{
	//Company* val = companies.find(name)->second;
	//return val;
	map<string, Company*>::const_iterator paperItr = companies.find(name);
	if(paperItr == companies.end())
		return NULL;
		
	return paperItr->second;
}

void AllCompanies::addCompany(Company* c){

	//check if company with same name already exists
	Company* toAdd = this->findComp(c->getName());
	if(toAdd != NULL){
		throw InvalidOpException("Company with same name already exists");
	}
	else{
	//	this->companies.push_back(const_cast<Company*>(c));
	this->companies.insert(make_pair(c->getName(), c));
	}
}

void AllCompanies::removeCompany(const string& name){
	companies.erase(name);

}


void AllCompanies::print(const string& name) const{
	Company* toPrint = this->findComp(name);
	if(toPrint == NULL)
		throw InvalidOpException("Company doesn't exist");
	else{
		toPrint->print(cout);
	}
}

void AllCompanies::printAll() const{
	//loop through all companies and print them all
	map<string, Company*>::const_iterator itr;
	
		
	for(itr = companies.begin(); itr != companies.end(); ++itr){
		Company* current = itr->second;
		current->print(cout);
	}
}

void AllCompanies::changeName(Company& comp, string& newName){
	//note: company name is set's key
	//remove given company from set
	this->removeCompany(comp.getName());
	comp.setName(newName);
	//re-add to set
	this->addCompany(const_cast<Company*>(&comp));
	
}
