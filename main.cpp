#include <iostream>
#include <string>
#include <fstream>
#include "Stores.h"

using namespace std;

int main(){
	Parser p("rules.txt", "input.txt");
	//RulesStore store(p);
	p.Parse();
	auto Nodes = p.getInitStatements();
	try{

	} catch(BAN_Exception &exc){
		cout << exc.getMessage() << endl;
	}

	cin.get();
	return 0;
}