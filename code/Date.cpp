#pragma once
#include "Date.h"
#include <iostream>
#include "InvalidDateException.h"
using namespace std;
//todo: check if c'tor can throw an exception
Date::Date(int year, int month, int day){
	//check if date is invalid
	if(year < 2016 || year > 2050 || month < 0 || month > 12 || day < 0 || day > 31){
		this->year = 2016;
		this->month = 1;
		this->day = 0;
		throw InvalidDateExcetion("Invalid date");
	}
	this->year = year;
	this->month = month;
	this->day = day;	
}

bool Date::isAfter(const Date& other) const{
	if(year != other.year)
		return year > other.year;
	if(month != other.month)
		return month > other.month;
	if(day != other.day)
		return day > other.day;
		
	return false; //if same date
}

void Date::print(ostream& out) const{
	out << '[' << day << '/' << month << '/' << year << ']' << endl;
}


ostream& operator<< (ostream& out, const Date& date){
	date.print(out);
	return out;
}