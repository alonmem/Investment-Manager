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
//implemented using singleton pattern
class Interface{
private:
	Interface(){}
public:
	static Interface& instance();
	void modifyExistingCompany(const string& name);
	void addCompany(string dname);
	void modifyCompanies();
	void modifySpecificPaper();
	void modifyValuePapers();
	void mainUi();
	void start();
	
};