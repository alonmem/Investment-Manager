#pragma once
#include "InvalidDateException.h"
#include <iostream>

using namespace std;
class Date{
private:
	int year;
	int month;
	int day;
public:
	Date(int year, int month, int day); //c'tor, throws InvalidDateException
	//Date(){cout << "DATE EMPTY CTOR CALLED" << endl;}; //should never be called, is for debug
	void setDay(int day) {this->day = day;}
	void setMonth(int month) {this->month = month;}
	void setYear(int year) {this->year = year;}
	int getDay() const {return day;}
	int getMonth() const {return month;}
	int getYear() const {return year;}
	bool isAfter(const Date& other) const; //returns true if this date is after given date
	void print(ostream& out) const;

};

ostream& operator<< (ostream& out, const Date& date);