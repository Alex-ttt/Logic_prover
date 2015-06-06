#pragma once

#include <map>

#include "Nodes.h"

class Parser {
private:
	map<string, func> funcs;
	vector<string> inputStream;
	TNodes rules;
	RuleType currentRulesType;
	int pos_in_line, line, rules_count;
	bool rulesComplete, initialStatesComplete;
	
	void checkClosedParenthesis();
	void checkComma();
	void removeSpace(string &str);
	bool isLetter(char ch) const;
	string& getCurrentLine();
	int getArgsCount(func f) const;
	bool isStatement(const string &str);

public:
	Parser(const string &rulesFile, const string &initialFile);
	~Parser();

	TNodes statements;
	TNodes getInitStatements() const;
	TNodes getRulesStatements() const;
	void print() const;
	void printRules() const;
	void ParseInitialState();
	void Parse();
	void ParseRules();
	Node* ParseStatement();
	bool ParsingComplete() const;
};
