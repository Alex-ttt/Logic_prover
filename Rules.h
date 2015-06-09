#pragma once
#include "Parser.h"

class Rule {
	TNodes args;
	RuleType type;

public:
	Rule(TNodes &rules, RuleType _type = S_RULE) : args(rules), type(_type) {}
	Node* getConclusion();
	TNodes getStatements();
	int size() const;
	int argsCount() const;
	RuleType getRuleType() const;
	vector<VarNode*> getRelatedNodes();
	void clearLinks();
	void print() const;
};

class S_Rule : public Rule {
public:
	S_Rule(TNodes &rules);
};

class G_Rule : public Rule {
public:
	G_Rule(TNodes &rules);

};

class Rewrite : public Rule {
public:
	Rewrite(TNodes &rules);
};

