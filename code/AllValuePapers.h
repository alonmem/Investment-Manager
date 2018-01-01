#pragma once
#include <iostream>
#include <map>
#include <string>
#include "ValuePaper.h"
	
#include "AllCompanies.h"
	

using namespace std;


//implements singleton pattern
class AllValuePapers{
private:
	map<string, ValuePaper*> valuePapers; //key: name of company of paper. value : pointer to paper. todo: re-insert after changing name
	AllValuePapers(){};
public:
	void deleteAll();
	static AllValuePapers& instance(); //get the single istance of this class
	ValuePaper* findPaper(const string& name) const; // find valePaper by compName
	void add(const ValuePaper& paper); //add new value paper to container. throws InvalidOpExcetion if valuepaper with same company name already exists.
	void remove(const string& compName); //remove existing value paper to container/
	void buy(string compName, int amount); //buy value papers. throws InvalidOpException if triws to buy invalid amount of papers
	void sell(string compName, int amount); //sell value papers. throws InvalidOpException if triws to sell invalid amount of papers
	void addYearToAll(); //adds a year to return date of all DebtPapers
	double calcTotalValue() const; //return total of all value papers 
	void print(const string& name) const; //print paper value with given compName
	void printAll() const; //prints all value papers
//	void setMAllCompanies(AllCompanies* mAllCompanies) {this->mAllCompanies = mAllCompanies;} //sets refence to AllCompanies
	ValuePaper* getPaperOrCreate(string compName); //returns reference to value paper of given company if already exists, or creates new value paper if doesn't exist
	void changeName(ValuePaper& paper, string& newName); //chamges name of given value paper

};
