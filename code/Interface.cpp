#pragma once
#include "Interface.h"
#include <iostream>
#include "ValuePaper.h"
#include "AllCompanies.h"
#include "AllValuePapers.h"
#include "PrivateCompany.h"
#include "GovOrganization.h"
#include "GovComp.h"
#include "Stock.h"
#include "ValuePaper.h"
#include "GovStock.h"
#include "Company.h"
#include "DebtPaper.h"

using namespace std;

void Interface::modifyExistingCompany(const string& name){
	Company* comp_p = AllCompanies::instance().findComp(name);
	if(comp_p == NULL){
		cout << "company doesn't exist" << endl;
		
		return;
	}
	Company& comp = *comp_p;
	cout << "Choose:" << endl;
	cout << "	1.Change name" << endl;
	cout << "	2.Change paper value" << endl;
	cout << "	3.Change paper number" << endl;
	cout << "	4.Add to company" << endl;
	cout << "	5.Print" << endl;
	cout << "	6.Go back" << endl;
	
	int choice;
	cin >> choice;
	
	switch(choice){
		case 1:{
			cout << "Enter new name:" << endl;
			string name;
			cin >> name;
			//change name of value paper (if exists)
			ValuePaper* paperOfComp = AllValuePapers::instance().findPaper(comp.getName());
			if(paperOfComp){ //if paper exists
				AllValuePapers::instance().changeName(*paperOfComp, name);
			}
			AllCompanies::instance().changeName(comp, name);
			//comp.changeName(name);
	
		}break;
		case 2:{
			cout << "Enter new value:" << endl;
			double val;
			cin >> val;
			comp.changePaperValue(val);
			//if value paper of comp exists ->  also change its value
			ValuePaper* valuePaperOfComp = AllValuePapers::instance().findPaper(name);
			if(valuePaperOfComp != NULL){
				valuePaperOfComp->changeValue(val);
			}
			
		}break;
		case 3:{
			cout << "Enter new number of papers:";
			int newNum;
			cin >> newNum;
			int currentOwnedNumOfPapers = AllValuePapers::instance().getPaperOrCreate(name)->getValuePerPaper();
			if(newNum < currentOwnedNumOfPapers){
				cout << "Cannot set num of papers to less than is currently owned" << endl;
			}
			comp.changeNumOfPapers(newNum);
			//only if comp is private - need change own % for stock of this comp
			if(dynamic_cast<PrivateCommpany*>(comp_p)){
				PrivateCommpany& privateComp = dynamic_cast<PrivateCommpany&>(comp);
				Stock* stockForPrivateComp = dynamic_cast<Stock*>(AllValuePapers::instance().findPaper(comp.getName()));
				stockForPrivateComp->updateOwnPercent();
			}
		}break;
		case 4:{
			cout << "Enter name of company to add with:";
			string othername;
			cin >> othername;
			Company* otherComp = AllCompanies::instance().findComp(othername);
			if(otherComp == NULL){
				cout << "company doesn't exist" << endl; //todo: suggest user to create it
				break;
			}
			//create & store the result of the addition between two companies
			try{
				Company& result = comp + (*otherComp);
				AllCompanies::instance().addCompany(&result);
			}catch(InvalidOpException e){ //an exception will be thrown if companies are not of same type
				cout << e.what() << endl;
				return;
			}
			bool comp1HasPaper = (AllValuePapers::instance().findPaper(comp.getName()) != NULL);
			bool comp2HasPaper = (AllValuePapers::instance().findPaper(otherComp->getName()) != NULL);
			//add value papers of comps only if both currently have a value paper
			if(comp1HasPaper && comp2HasPaper){
				//create new value paper for new company
				//get reference to value papers of two added companies
				ValuePaper& comp1VP = *(AllValuePapers::instance().getPaperOrCreate(comp.getName()));
				ValuePaper& comp2VP = *(AllValuePapers::instance().getPaperOrCreate(otherComp->getName()));
		
				//create new value paper
				ValuePaper& newStock = comp1VP.operator +(comp2VP);
				//add new paper to container
				AllValuePapers::instance().add(newStock);
			}
			//remove two operands companies
			AllCompanies::instance().removeCompany(comp.getName());
			AllCompanies::instance().removeCompany(otherComp->getName());
			//remove papers of two operands companies
			AllValuePapers::instance().remove(comp.getName());
			AllValuePapers::instance().remove(otherComp->getName());
		}break;
		case 5:{
			cout << comp << endl;
		}break;
		default:
			return;
			break;
	}
}

void Interface::addCompany(string dname = "DEFAULT"){
	int compType;
	string name, department;
	double paperValue;
	int numOfPapers;
	bool validDetails = true;
	do{
		try{
			validDetails = true;
			cout << "Enter company type:" << endl;
			cout << "	1: Private" << endl;
			cout << "	2: Government" << endl;
			cout << "	3: Govermemt Company" << endl;
			cin >> compType;
			if(dname == "DEFAULT"){
				cout << "Enter company name: ";
				cin >> name;
				cout << endl;
			}else{
				name = dname;
			}
			
			cout << "Enter company department: ";
			cin >> department;
			cout << endl;
			cout << "Enter paper value: ";
			cin >> paperValue;
			cout << endl;
			cout << "Enter number of papers: ";
			cin >> numOfPapers;
			cout << endl;
			//craete new comp and add to container

			if(compType == 1){
				AllCompanies::instance().addCompany(new PrivateCommpany(name, department, paperValue, numOfPapers));
				
			}
			else if(compType == 2){
				AllCompanies::instance().addCompany(new GovOrganization(name, department, paperValue, numOfPapers));
				
			}
			else if(compType == 3){
				AllCompanies::instance().addCompany(new GovComp(name, department, paperValue, numOfPapers));
				
			}
		}catch(InvalidOpException& e){
			cout << e.what() << endl;
			validDetails = false;
			cout << "Please Re-Enter company details" << endl;
		}
	}while(!validDetails);
}

void Interface::modifyCompanies(){
	bool run = true;
	while(run){
		cout << "Companies Menu:" << endl;
		cout << "	1.Create new company" << endl;
		cout << "	2.Delete existing company" << endl;
		cout << "	3.Print specific company" << endl;
		cout << "	4.Print all companies" << endl;
		cout << "	5.Modify existing company" << endl;
		cout << "	6.Go back" << endl;
		int choice;
		cin >> choice;
		switch(choice){
			case 1:{
				addCompany();
				
			}break;
			case 2:{
				cout << "Enter company name: ";
				string name;
				cin >> name;
				cout << endl;
				try{
					//remove paper of company if exists
					ValuePaper* paperForComp = AllValuePapers::instance().findPaper(name);
					if(paperForComp){ //if exists
						AllValuePapers::instance().remove(name);
					}
					//remove company
					AllCompanies::instance().removeCompany(name);
				
				}catch(InvalidOpException& e){
					cout << e.what() << endl;
				}
			}break;
			case 3:{
				cout << "Enter company name: ";
				string name;
				cin >> name;
				cout << endl;
				try{
					AllCompanies::instance().print(name);
				}catch(InvalidOpException& e){
					cout << e.what() << endl;
				}
			}break;
			case 4:{
				AllCompanies::instance().printAll();
			}break;
			case 5:{
				cout << "Enter company name: ";
				string name;
				cin >> name;
				cout << endl;
				modifyExistingCompany(name); //todo: impl.
			}break;
			case 6:{
				run = false;
			} break;
			
		}
	}
}

void Interface::modifySpecificPaper(){
	cout << "Enter name of company: ";
	string name;
	cin >> name;
	cout << endl;
	if(AllCompanies::instance().findComp(name) == NULL){
		//cout << "Company does not exist" << endl; //todo: suggest to create comp
		cout << "Dear Mr.wong - the company doesn't exit. Would you like to create it? [Y\\N]" << endl;
		char choice;
		cin >> choice;
		if(choice != 'Y')
			return;
		
		addCompany(name);
		cout << "Company added" << endl;
		
	}
	ValuePaper* paper_p = AllValuePapers::instance().getPaperOrCreate(name); //get if exists, delte if doesn't exist
	ValuePaper& paper = *paper_p; //get if exists, delte if doesn't exist
	//paper.setCompanies(&companies); //set reference to companies
	bool isDeptPaper = dynamic_cast<DeptPaper*>(paper_p);
	bool isGovStock = dynamic_cast<GovStock*>(paper_p);
	
	cout << "Choose:" << endl;
	cout << "	1.Buy" << endl;
	cout << "	2.Sell" << endl;
	if(isDeptPaper){// if paper is debt paper
		cout << "	3.add to return date" << endl;
		cout << "	4.change interest rate" << endl;
	}
	if(isGovStock){
		cout << "	5.Change can be traded" << endl;
	}
	cout << "	6.Go back" << endl;
	
	int choice;
	cin >> choice;
	
	switch(choice){
		case 1:{
			cout << "Enter amount to buy: ";
			int amount;
			cin >> amount;
			cout << endl;
			int totalPapersOfCompany = AllCompanies::instance().findComp(name)->getNumOfPapers();

			if(amount + paper.getNumOfPapers() > totalPapersOfCompany){
				cout << "Cannot buy more papers than the company has" << endl;
				return;
			}
			paper.buy(amount);
			//if is stock - update own %
			if(dynamic_cast<Stock*>(paper_p)){
				Stock& stock = dynamic_cast<Stock&>(paper);
				stock.updateOwnPercent();
			}
		}break;
		case 2:{
			cout << "Enter amount to sell: ";
			int amount;
			cin >> amount;
			cout << endl;
			try{
				paper.sell(amount);
			}catch(InvalidOpException e){
				cout << e.what() << endl;
				return;
			}
			//if sold all papers of company - remove stock from container
			if(paper.getNumOfPapers() == 0){ 
				AllValuePapers::instance().remove(paper.getCompName());
			}
		}break;
		case 3:{
			if(!isDeptPaper){
				cout << "Invalid Choice!" << endl;
				break;
			}
			int year, month, day;
			cout << "Enter time to add:" << endl;
			cout << "Years: ";
			cin >> year;
			cout << endl;
			cout << "Months: ";
			cin >> month;
			cout << endl;
			cout << "Days: ";
			cin >> day;
			cout << endl;
			DeptPaper& dp = dynamic_cast<DeptPaper&>(paper);
			try{
				dp.addToReturnDate(year, month, day);
			}catch(InvalidDateExcetion e){
				e.what();
				return;
			}
		}break;
		case 4:{
			if(!isDeptPaper){
				cout << "Invalid Choice" << endl;
				break;
			}
			cout << "Enter new interest rate: ";
			double newIntr;
			cin >> newIntr;
			cout << endl;
			
			DeptPaper& dp = dynamic_cast<DeptPaper&>(paper);
			try{
				dp.changeInterest(newIntr);
			}catch(InvalidOpException e){
				cout << e.what() << endl;
				return;
			}
		}break;
		case 5:{
			if(!isGovStock)
				break;
			cout << "Choose can be traded: [Y/N]" << endl;
			char canBeTraded;
			cin >> canBeTraded;
			GovStock& gs = dynamic_cast<GovStock&>(paper);
			gs.SetCanBeTraded((canBeTraded == 'Y'));
		}break;
		default:
			return;
	}
}

void Interface::modifyValuePapers(){
	bool run = true;
	while(run){
		cout << "Choose:" << endl;
		cout << "	1.Modify specific paper" << endl;
		cout << "	2.Add 1 year to all return dates of value papers" << endl;
		cout << "	3.Calculate total worth of all value papers" << endl;
		cout << "	4.Print specific value paper" << endl;
		cout << "	5.Print all value papers" << endl;
		cout << "	6.Go back" << endl;
		
		int choice;
		cin >> choice;
		
		switch(choice){
			case 1:{
				modifySpecificPaper();
			}break;
			case 2:{
				AllValuePapers::instance().addYearToAll();
			}break;
			case 3:{
				cout << "Total worth: " << AllValuePapers::instance().calcTotalValue() << endl;
			}break;
			case 4:{
				cout << "Enter paper's company name: ";
				string name;
				cin >> name;
				cout << endl;
				ValuePaper* paper = AllValuePapers::instance().findPaper(name);
				if(paper == NULL){
					cout << "Paper doesn't exist" << endl; //todo: suggest to create it
					break;
				}
				AllValuePapers::instance().print(name);
			}break;
			case 5:{
				AllValuePapers::instance().printAll();
			}break;
			case 6:{
				run = false;
			}break;
		}
	}
}

void Interface::mainUi(){
	
	bool run = true;
	while(run){
		cout << "Choose:" << endl;
		cout << "	1.Modify companies" << endl;
		cout << "	2.Modify value papers" << endl;
		cout << "	3.Exit" << endl;
		int choice;
		cin >> choice;
		switch(choice){
			case 1:
				modifyCompanies();
				break;
			case 2:
				modifyValuePapers();
				break;
			case 3:
				run = false;
				break;
			default:
				cout << "Invalid choice" << endl;
				break;
		}
	}
}
	void Interface::start(){
		mainUi();
	}
	
	Interface& Interface::instance(){
		static Interface* i = new Interface();
		return *i;
	}
	

