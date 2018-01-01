#pragma once
#include "AllValuePapers.h"
#include "AllCompanies.h"
#include "PrivateCompany.h"
#include "GovOrganization.h"
#include "GovComp.h"
#include "GovStock.h"
#include "Stock.h"
#include "DebtPaper.h"
#include "ValuePaper.h"
#include <utility>
#include <functional>

using namespace std;
void AllValuePapers:: deleteAll(){
	
	map<string, ValuePaper*>::const_iterator itr;
	for(itr = valuePapers.begin(); itr != valuePapers.end(); ++itr){
		valuePapers.erase(itr->first);
		delete itr->second;
	}
	
}

AllValuePapers& AllValuePapers::instance(){
	static AllValuePapers* i = new AllValuePapers(); //will only be executed once
	return *i; //return referce to instance
}

ValuePaper* AllValuePapers::findPaper(const string& name) const{
	map<string, ValuePaper*>::const_iterator paperItr = valuePapers.find(name);
	if(paperItr == valuePapers.end())
		return NULL;
		
	return paperItr->second;
	
}

void AllValuePapers::buy(string compName, int amount){
	//check if company exsits
	Company* compToBuyFrom = AllCompanies::instance().findComp(compName);
	if(compToBuyFrom == NULL)
		throw InvalidOpException("Company doesn't exist");
	
	bool valuePaperExists = (findPaper(compName) != NULL);
	ValuePaper* valuePaperToBuy = this->getPaperOrCreate(compName);
	
	int totalCompanyPapers = compToBuyFrom->getNumOfPapers();
	//if tries to buy invalid amount of papers
	if(amount <= 0 || valuePaperToBuy->getNumOfPapers() + amount > totalCompanyPapers){
		//remove paper that was just created (if it didn't exist before this operatrion)
		if(!valuePaperExists){
			this->remove(compName);
		}
		throw InvalidOpException("Invalid amount of papers to buy");
	}
	valuePaperToBuy->buy(amount);
}

void AllValuePapers::sell(string compName, int amount){
	//check if company exsits
	Company* compToSellFrom = AllCompanies::instance().findComp(compName);
	if(compToSellFrom == NULL)
		throw InvalidOpException("Company doesn't exist");
	
	ValuePaper* valuePaperToSell = this->getPaperOrCreate(compName);
	
	//if tries to buy invalid amount of papers
	if(amount <= 0 || valuePaperToSell->getNumOfPapers() < amount){
		throw InvalidOpException("Invalid amount of papers to buy");
	}
	
	valuePaperToSell->sell(amount);
}

ValuePaper* AllValuePapers::getPaperOrCreate(string compName){
	//get refernece to current paper if already exists
	ValuePaper* paperForComp = (findPaper(compName));
	//get refernece to company of paper
	Company* compOfPaper = AllCompanies::instance().findComp(compName);
	if(paperForComp == NULL){ //if stock for this company does not currently exist - create it & add to container
		//create new value paper according to companie's type
		
		bool goodDetails = true;
		//if company is private comp
		if(dynamic_cast<PrivateCommpany*>(compOfPaper)){
			do{
				try{
					goodDetails = true;
					
					paperForComp = new Stock(compName, 0, compOfPaper->getPaperValue(), 0.0);
				}catch(exception& e){
					cout << e.what() << endl;
					goodDetails = false;
				}
			}while(!goodDetails);
			
		}else{
		cout << "Enter details for Value Paper of " << compName << endl;
		//if company is gov org
		if(dynamic_cast<GovOrganization*>(compOfPaper)){
			do{
				try{
					goodDetails = true;
					cout << "Enter date: [year,month,day]" << endl;
					int year, month, day;
					cin >> year >> month >> day;
					cout << "Enter interest rate:" << endl;
					double ir;
					cin >> ir;
					paperForComp = new DeptPaper(compName, 0, compOfPaper->getPaperValue(), Date(year, month, day), ir);
				}catch(exception& e){
					cout << e.what() << endl;
					goodDetails = false;
				}
				
			}while(!goodDetails);
			
		}
		
	
		
		if(dynamic_cast<GovComp*>(compOfPaper)){
				do{
				try{
					goodDetails = true;
					
					cout << "Enter date: [year,month,day]" << endl;
					int year, month, day;
					cin >> year >> month >> day;
					cout << "Enter interest rate:" << endl;
					double ir;
					cin >> ir;
					paperForComp = new GovStock(compName, 0, compOfPaper->getPaperValue(), 0.0, Date(year, month, day), ir, true);
				}catch(exception& e){
					cout << e.what() << endl;
					goodDetails = false;
				}
				
			}while(!goodDetails);
		}
		}	
		//add new craeted value paper to container
		valuePapers.insert(make_pair(paperForComp->getCompName(), paperForComp));
		//valuePapers.push_back(paperForComp);
	}
	return paperForComp;
}

//adds year to al return dates of debptPapers
void AllValuePapers::addYearToAll(){
	//loop through all value papers
	map<string, ValuePaper*>::iterator itr;
	for(itr = valuePapers.begin(); itr != valuePapers.end(); ++itr){
		ValuePaper* current = itr->second;
		//check if current value paper is not a stock
		if(!dynamic_cast<Stock*>(current)){
			//add 1 year to return date
			DeptPaper* dp = dynamic_cast<DeptPaper*>(current);
			cout << "adding to return date of:" << dp->getCompName() << endl;
			try{
				dp->addToReturnDate(1,0,0);
			}catch(InvalidDateExcetion e){
				//do nothing - don't add to return date
			}
		}
	}
		
}

//returns sum of all papers values
double AllValuePapers::calcTotalValue() const {
	double sum = 0;
	map<string, ValuePaper*>::const_iterator itr;
	for(itr = valuePapers.begin(); itr != valuePapers.end(); ++itr){
		ValuePaper* current = itr->second;
		sum += current->calcValue();
	}
	return sum;
}


void AllValuePapers::print(const string& name) const{
	ValuePaper& toPrint = *(this->findPaper(name));
	cout << toPrint << endl;
}

void AllValuePapers::printAll() const{
	map<string, ValuePaper*>::const_iterator itr;
	for(itr = valuePapers.begin(); itr != valuePapers.end(); ++itr){
		ValuePaper* current = itr->second;
		cout << (*current) << endl;
	}
}

void AllValuePapers::add(const ValuePaper& paper){
	//check if already exists with same company name
	if(findPaper(paper.getCompName()) != NULL)
		throw InvalidOpException("Value paper for same company already exists");
	
	
	valuePapers.insert(make_pair(paper.getCompName(),const_cast<ValuePaper*>( &paper)));
}

void AllValuePapers::remove(const string& compName){
	valuePapers.erase(compName);
	
}

void AllValuePapers::changeName(ValuePaper& paper, string& newName){
	//name: name of paper is its key - need to remove from set and re-add to set with new name
	//remove from set
	this->remove(paper.getCompName());
	
	paper.setCompName(newName);
	
	//re add to set
	this->add(paper);
}