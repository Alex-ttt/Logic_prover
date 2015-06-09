#pragma once

#include "Common.h"

class Node {
protected:
	func function;
	bool conclusion;
	RuleType conclType;

public:
	Node(func f = variable) : function(f), conclusion(false), conclType(S_RULE){}
	virtual Node* Clone() const { return 0; };
	virtual int argsCount() const {	return 0; };
	virtual void print(int deep = 0) const {}
	void setConclusion(bool b) { conclusion = b; }
	bool isConclusion() const { return conclusion; }
	func getFuncType() const { return function; }
	void setConlusionType(RuleType type) { conclType = type; }
	RuleType getConclusionType() const { return conclType; }
	virtual bool operator == (Node *c){ return true; }
	bool operator != (Node *c){ return !(*this == c); }
	virtual void clearLinks() {}
	virtual void getRelatedNodes(vector<VarNode*> &nodes) {};
	virtual void replaceArgsTo(vector<VarNode*> &nodes) {};
};

class VarNode : public Node {
private:
	const string name;
	Node *relatedNode;

public:
	VarNode(const string &str);
	string getName() const;
	Node* Clone() const;
	void getRelatedNodes(vector<VarNode*> &nodes);
	Node* getRelatedNode() const;
	void clearLinks();
	bool operator == (Node *c);
	void print(int deep = 0) const;
};

class SimpleNode : public Node {
private:
	Node *arg1;

public:
	SimpleNode(Node *arg, func f = fresh);
	Node* Clone() const;
	void getRelatedNodes(vector<VarNode*> &nodes);
	Node* getFirstArg() const;
	int argsCount() const;
	bool operator == (Node *c);
	void clearLinks();
	void replaceArgsTo(vector<VarNode*> &nodes);
	void print(int deep = 0) const;
};

class DoubleNode : public Node {
private:
	Node *arg1;
	Node *arg2;

public:
	DoubleNode(Node *a1, Node *a2, func f = variable);
	Node* Clone() const;
	void getRelatedNodes(vector<VarNode*> &nodes);
	Node* getFirstArg() const;
	Node* getSecondArg() const;
	int argsCount() const;
	void print(int deep = 0) const;
	void clearLinks();
	bool operator == (Node *c);
	void replaceArgsTo(vector<VarNode*> &nodes);
};

class TripleNode : public Node{
private:
	Node *arg1;
	Node *arg2;
	Node *arg3;

public:
	TripleNode(Node *a1, Node *a2, Node *a3, func f = variable);
	Node* Clone() const;
	void getRelatedNodes(vector<VarNode*> &nodes);
	int argsCount() const;
	Node* getFirstArg() const;
	Node* getSecondArg() const;
	Node* getThirdArg() const;
	bool operator == (Node *c);
	void clearLinks();
	void replaceArgsTo(vector<VarNode*> &nodes);
	void print(int deep = 0) const;
};