#pragma once

#include "Common.h"

class Node {
protected:
	func function;
	bool conclusion;
	RuleType conclType;

public:
	Node(func f = variable) : function(f), conclusion(false), conclType(S_RULE){}
	virtual int argsCount() const {	return 0; };
	virtual void print(int deep = 0) const {}
	void setConclusion(bool b) { conclusion = b; }
	bool isConclusion() const { return conclusion; }
	func getFuncType() const { return function; }
	void setConlusionType(RuleType type) { conclType = type; }
	RuleType getConclusionType() const { return conclType; }
	virtual bool operator == (Node *c) const { return true; }
	bool operator != (Node *c) const { return !(*this == c); }
};

class VarNode : public Node {
public:
	VarNode(const string &str);
	const string name;
	void print(int deep = 0) const;
};

class SimpleNode : public Node {
private:
	Node *arg1;

public:
	SimpleNode(Node *arg, func f = fresh);
	Node* getFirstArg() const;
	int argsCount() const;
	bool operator == (Node *c) const;
	void print(int deep = 0) const;
};

class DoubleNode : public Node {
private:
	Node *arg1;
	Node *arg2;

public:
	DoubleNode(Node *a1, Node *a2, func f = variable);
	Node* getFirstArg() const;
	Node* getSecondArg() const;
	int argsCount() const;
	void print(int deep = 0) const;
	bool operator == (Node *c) const;
};

class TripleNode : public Node{
private:
	Node *arg1;
	Node *arg2;
	Node *arg3;

public:
	TripleNode(Node *a1, Node *a2, Node *a3, func f = variable);
	int argsCount() const;
	Node* getFirstArg() const;
	Node* getSecondArg() const;
	Node* getThirdArg() const;
	bool operator == (Node *c) const;
	void print(int deep = 0) const;
};