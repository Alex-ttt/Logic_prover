#pragma once

#include "Rules.h"

class RulesStore {
private:
	int s_size, g_size, r_size;
	vector<Rule*> rules;
	void createRule(TNodes &args);
	void copyVector(TNodes &src, TNodes &dest, int from, int to);
	void orderRules();

public:
	RulesStore(Parser &parser);
	int getS_Size() const;
	int getG_Size() const;
	int getR_Size() const;
	void print() const;

};

class StatementsStore {
private:
	TNodes statements;

public:
	StatementsStore(TNodes &s);
};

class RulesApplicator {
private:
	RulesStore ruleStore;
	StatementsStore statementStore;
	Node* ApplyRule(Rule *rule, const TNodes &formulas);

public:
	RulesApplicator(Parser &parser);
};