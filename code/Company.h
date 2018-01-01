#pragma once
#include <iostream>
#include <string.h>

using namespace std;

class Company{
protected:
	string name;
	string department;
	double paperValue;
	int numOfPapers;
public:
	Company (string name, string department, double paperValue, int numOfPapers);
	void changeName(string newName); //changes name of comp
	void changePaperValue(double newValue); //change papyer value. throws InvalidOpException
	void changeNumOfPapers(int newNum); //changes num of papaers of this comp. throws InvalidOpException
	virtual Company& operator+(const Company& other) const = 0; //add two companies. throws InvalidOpException
	virtual void print(ostream& os) const = 0; //prints company to ostream
	bool isNameEqualTo(const string& name) const;
	const string& getName() const;
	int getNumOfPapers() const {return numOfPapers;}
	void setDepartment(const string& department) {this->department = department;}
	void setName(const string& name) {this->name = name;}
	void setNumOfPapers(int numOfPapers) {this->numOfPapers = numOfPapers;}
	void setPaperValue(double paperValue) {this->paperValue = paperValue;}
	const string& getDepartment() const {return department;}
	double getPaperValue() const {return paperValue;}
	
};

ostream& operator<< (ostream& os, const Company& comp);