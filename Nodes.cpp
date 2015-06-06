#include "Nodes.h"

VarNode::VarNode(const string &str) : Node(variable), name(str) {}

SimpleNode::SimpleNode(Node *arg, func f) : Node(f), arg1(arg) {}

DoubleNode::DoubleNode(Node *a1, Node *a2, func f) : Node(f), arg1(a1), arg2(a2) {}

TripleNode::TripleNode(Node *a1, Node *a2, Node *a3, func f) : Node(f), arg1(a1), arg2(a2), arg3(a3) {}

static string getStrByFunc(func function){
	static string ret_arr[] = {
		"variable", "believes", "received", "said", "controls", "fresh", "public_key",
		"shared_key", "secret", "encrypt", "combine", "comma", "inv", "distinct"
	};

	return ret_arr[function];
}

void VarNode::print(int deep) const {
	cout << string(2 * deep, ' ') << name << endl;
}

void SimpleNode::print(int deep) const {
	string tab(2 * deep, ' ');
	cout << tab << getStrByFunc(function) << ' ' << '(' << endl;
	arg1->print(deep + 1);
	cout << tab << ')' << endl;
}

void DoubleNode::print(int deep) const {
	string tab(2 * deep, ' ');
	cout << tab << getStrByFunc(function) << ' ' << '(' << endl;
	cout << tab << "ARG1:" << endl;
	arg1->print(deep + 1);
	cout << tab << "ARG2:" << endl;
	arg2->print(deep + 1);
	cout << tab << ')' << endl;
}

void TripleNode::print(int deep) const {
	string tab(2 * deep, ' ');
	cout << tab << getStrByFunc(function) << ' ' << '(' << endl;
	cout << tab << "ARG1:" << endl;
	arg1->print(deep + 1);
	cout << tab << "ARG2:" << endl;
	arg2->print(deep + 1);
	cout << tab << "ARG3:" << endl;
	arg3->print(deep + 1);
	cout << tab << ')' << endl;
}

int SimpleNode::argsCount() const {
	return 1;
}

int DoubleNode::argsCount() const {
	return 2;
}

int TripleNode::argsCount() const {
	return 3;
}

Node* SimpleNode::getFirstArg() const {
	return arg1;
}

Node* DoubleNode::getFirstArg() const {
	return arg1;
}

Node* TripleNode::getFirstArg() const {
	return arg1;
}

Node* DoubleNode::getSecondArg() const {
	return arg2;
}

Node* TripleNode::getSecondArg() const {
	return arg2;
}

Node* TripleNode::getThirdArg() const {
	return arg3;
}

bool SimpleNode::operator == (Node *c) const {
	SimpleNode *unaryNode = dynamic_cast<SimpleNode*>(c);
	return unaryNode && function == c->getFuncType() && *arg1 == unaryNode->getFirstArg();
}

bool DoubleNode::operator == (Node *c) const {
	DoubleNode *doubleNode = dynamic_cast<DoubleNode*>(c);
	return doubleNode && function == doubleNode->getFuncType() &&
		*arg1 == doubleNode->getFirstArg() && *arg2 == doubleNode->getSecondArg(); 
}

bool TripleNode::operator == (Node *c) const {
	TripleNode *tripleNode = dynamic_cast<TripleNode*>(c);
	return 
		tripleNode &&
		function == tripleNode->getFuncType()  &&
		*arg1 == tripleNode->getFirstArg() && 
		*arg2 == tripleNode->getSecondArg() &&
		*arg3 == tripleNode->getThirdArg();
}