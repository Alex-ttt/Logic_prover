#include <iostream>
#include <string>
#include <fstream>
#include "Stores.h"

using namespace std;

int main(){
	Parser p("Basic_BAN_rules.txt", "input.txt");
	//RulesStore store(p);
	p.Parse();
	auto Nodes = p.getInitStatements();
	try{
		cout << (*Nodes[0] == Nodes[1]) << endl;
	} catch(BAN_Exception &exc){
		cout << exc.getMessage() << endl;
	}

	cin.get();
	return 0;
}