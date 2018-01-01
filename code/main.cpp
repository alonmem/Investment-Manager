#include "Interface.h"
#include <iostream>
using namespace std;
int main(){
	cout << "Welcome, Enum Wong." << endl << endl;
	Interface::instance().start();
	AllCompanies::instance().deleteAll();
	AllValuePapers::instance().deleteAll();
	return 0;
}