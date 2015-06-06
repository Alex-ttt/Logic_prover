#include "Parser.h"
#include <fstream>
#include <string>

using std::ifstream;

bool Parser::isLetter(char ch) const {
	return ch >= 'A' && ch <= 'Z' ||
			ch >= 'a' && ch <= 'z' ||
			ch == '_';
}

void Parser::removeSpace(string &str){
	for(int i = 0; i < str.length(); i++){
		if(str[i] == ' '){
			str.erase(str.begin() + i);
		}
	}
}

string& Parser::getCurrentLine(){
	return	inputStream[line];
}

void Parser::checkClosedParenthesis(){
	if(getCurrentLine()[pos_in_line] != ')')
		throw BAN_Exception("Closed parethesis expected in line " + to_string(line));
	else
		pos_in_line++;
}

void Parser::checkComma(){
	if(getCurrentLine()[pos_in_line++] != ',')
		throw BAN_Exception("Comma expected in line " + to_string(line));
}

int Parser::getArgsCount(func f) const {
	switch (f)
	{
	case variable:
		return 0;

	case fresh:
		return 1;

	case shared_key:
	case secret:
	case encrypt:
		return 3;

	default:
		return 2;
	}
}

Parser::Parser(const string &rulesFile, const string &initialFile) 
	:	line(0), pos_in_line(0), rules_count(0), currentRulesType(S_RULE),
		initialStatesComplete(false), rulesComplete(false) {

	funcs["believes"] = believes;
	funcs["received"] = received;
	funcs["said"] = said;
	funcs["controls"] = controls;
	funcs["fresh"] = fresh;
	funcs["shared_key"] = shared_key;
	funcs["public_key"] = public_key;
	funcs["secret"] = secret;
	funcs["encrypt"] = encrypt;
	funcs["combine"] = combine;
	funcs["comma"] = comma;
	funcs["inv"] = inv;
	funcs["distinct"] = distinct;

	ifstream f1(rulesFile), f2(initialFile);
	string str;
	while(!f1.eof()){
		getline(f1, str);
		removeSpace(str);
		inputStream.push_back(str);
		rules_count++;
	}
	while(!f2.eof()){
		getline(f2, str);
		removeSpace(str);
		inputStream.push_back(str);
	}

	f1.close();
	f2.close();
}

Parser::~Parser(){
	inputStream.clear();
}


bool Parser::isStatement(const string &str){
	if(str.empty()){
		currentRulesType = S_RULE;
		return false;
	} else if(str == "S:"){
		currentRulesType = S_RULE;
		return false;
	} else if(str == "G:"){
		currentRulesType = G_RULE;
		return false;
	} else if(str == "R:"){
		currentRulesType = REWRITE;
		return false;
	}

	return true;
}

Node* Parser::ParseStatement(){
	string formula = getCurrentLine();
	if(!isStatement(formula))
		return 0;

	int start = pos_in_line;
	while(isLetter(formula[pos_in_line])){
		pos_in_line++;
	}
	string sub_statement = formula.substr(start, pos_in_line - start);
	func current_function = funcs[sub_statement];
	int size = getArgsCount(current_function);
	
	if(size == 0)
		return new VarNode(sub_statement);
	

	if(formula[pos_in_line] == '(')
			pos_in_line++;
		else
			throw BAN_Exception("Opened parethesis expected in line " + to_string(line));

	switch(size)
	{
	case 1:
		{
			Node *arg = ParseStatement();
			checkClosedParenthesis();

			return new SimpleNode(arg, current_function);
		}

	case 2:
		{
			Node *arg1 = ParseStatement(), *arg2;
			checkComma();
			arg2 = ParseStatement();
			checkClosedParenthesis();

			return new DoubleNode(arg1, arg2, current_function);
		}

	case 3:
		{
			Node *arg1 = ParseStatement(), *arg2, *arg3;
			checkComma();
			arg2 = ParseStatement();
			checkComma();
			arg3 = ParseStatement();
			checkClosedParenthesis();

			return new TripleNode(arg1, arg2, arg3, current_function);
		}

	default:
		throw BAN_Exception("Parser error " + to_string(line));
	}
	
}

TNodes Parser::getInitStatements() const {
	return statements;
}

TNodes Parser::getRulesStatements() const {
	return rules;
}

void Parser::print() const {
	for(auto formula : statements){
		formula->print();
		cout << endl;
	}
}

void Parser::printRules() const {
	for(auto formula : rules){
		if(formula->isConclusion())
			cout << "Conclusion:" << endl;
		
		formula->print();
		cout << endl;
	}
}

void Parser::ParseRules(){
	for(int i = 0; i < rules_count; i++){
		Node *rule = ParseStatement();
		if(rule){
			rules.push_back(rule);
		} else {
			if(!rules.empty()){
				rules.back()->setConclusion(true);
				rules.back()->setConlusionType(currentRulesType);
			}
		}
		pos_in_line = 0;
		line++;
	}

	if(!rules.empty()){
		rules.back()->setConclusion(true);
		rules.back()->setConlusionType(currentRulesType);
	}
	rulesComplete = true;
}

void Parser::ParseInitialState(){
	for(int i = rules_count; i < inputStream.size(); i++){
		if(Node *stmnt = ParseStatement())
			statements.push_back(stmnt);
		pos_in_line = 0;
		line++;
	}
	initialStatesComplete = true;
}

void Parser::Parse(){
	if(!rulesComplete)
		ParseRules();
	if(!initialStatesComplete)
		ParseInitialState();
	inputStream.clear();
}

bool Parser::ParsingComplete() const {
	return rulesComplete && initialStatesComplete;
}
