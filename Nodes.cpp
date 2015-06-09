#include "Nodes.h"

VarNode::VarNode(const string &str) : Node(variable), name(str), relatedNode(0) {}

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

bool VarNode::operator == (Node *c){
	relatedNode = c;
	return true;
}

bool SimpleNode::operator == (Node *c){
	SimpleNode *unaryNode = dynamic_cast<SimpleNode*>(c);
	return unaryNode && function == c->getFuncType() && *arg1 == unaryNode->getFirstArg();
}

bool DoubleNode::operator == (Node *c){
	DoubleNode *doubleNode = dynamic_cast<DoubleNode*>(c);
	return doubleNode && function == doubleNode->getFuncType() &&
		*arg1 == doubleNode->getFirstArg() && *arg2 == doubleNode->getSecondArg(); 
}

bool TripleNode::operator == (Node *c){
	TripleNode *tripleNode = dynamic_cast<TripleNode*>(c);
	return 
		tripleNode &&
		function == tripleNode->getFuncType()  &&
		*arg1 == tripleNode->getFirstArg() && 
		*arg2 == tripleNode->getSecondArg() &&
		*arg3 == tripleNode->getThirdArg();
}

void VarNode::clearLinks(){
	relatedNode = 0;
}

void SimpleNode::clearLinks(){
	arg1->clearLinks();
}

void DoubleNode::clearLinks(){
	arg1->clearLinks();
	arg2->clearLinks();
}

void TripleNode::clearLinks(){
	arg1->clearLinks();
	arg2->clearLinks();
	arg3->clearLinks();
}

void VarNode::getRelatedNodes(vector<VarNode*> &nodes){
	nodes.push_back(this);
}

void SimpleNode::getRelatedNodes(vector<VarNode*> &nodes){
	arg1->getRelatedNodes(nodes);
}

void DoubleNode::getRelatedNodes(vector<VarNode*> &nodes){
	arg1->getRelatedNodes(nodes);
	arg2->getRelatedNodes(nodes);
}

void TripleNode::getRelatedNodes(vector<VarNode*> &nodes){
	arg1->getRelatedNodes(nodes);
	arg2->getRelatedNodes(nodes);
	arg3->getRelatedNodes(nodes);
}

Node* VarNode::Clone() const {
	return new VarNode(name);
}

Node* SimpleNode::Clone() const {
	return new SimpleNode(arg1->Clone(), function);
}

Node* DoubleNode::Clone() const {
	return new DoubleNode(arg1->Clone(), arg2->Clone(), function);
}

Node* TripleNode::Clone() const {
	return new TripleNode(arg1->Clone(), arg2->Clone(), arg3->Clone(), function);
}

string VarNode::getName() const {
	return name;
}

Node* VarNode::getRelatedNode() const {
	return relatedNode;
}

void SimpleNode::replaceArgsTo(vector<VarNode*> &nodes){
	VarNode *var = dynamic_cast<VarNode*>(arg1);
	if(!var){
		arg1->replaceArgsTo(nodes);
		return;
	}
	string str = var->getName();
	for(auto node : nodes){
		if(node->getName() == str){
			arg1 = node->getRelatedNode();
			break;
		}
	}
}

void DoubleNode::replaceArgsTo(vector<VarNode*> &nodes){
	VarNode *var1 = dynamic_cast<VarNode*>(arg1);
	VarNode *var2 = dynamic_cast<VarNode*>(arg2);

	if(!var1){
		arg1->replaceArgsTo(nodes);
	} else {
		string str = var1->getName();
		for(auto node : nodes){
			if(node->getName() == str){
				arg1 = node->getRelatedNode();
				break;
			}
		}
	}

	if(!var2){
		arg2->replaceArgsTo(nodes);
	} else {
		string str = var2->getName();
		for(auto node : nodes){
			if(node->getName() == str){
				arg2 = node->getRelatedNode();
				break;
			}
		}
	}
}

void TripleNode::replaceArgsTo(vector<VarNode*> &nodes){
	VarNode *var1 = dynamic_cast<VarNode*>(arg1);
	VarNode *var2 = dynamic_cast<VarNode*>(arg2);
	VarNode *var3 = dynamic_cast<VarNode*>(arg3);

	if(!var1){
		arg1->replaceArgsTo(nodes);
	} else {
		string str = var1->getName();
		for(auto node : nodes){
			if(node->getName() == str){
				arg1 = node->getRelatedNode();
				break;
			}
		}
	}

	if(!var2){
		arg2->replaceArgsTo(nodes);
	} else {
		string str = var2->getName();
		for(auto node : nodes){
			if(node->getName() == str){
				arg2 = node->getRelatedNode();
				break;
			}
		}
	}

	if(!var3){
		arg3->replaceArgsTo(nodes);
	} else {
		string str = var3->getName();
		for(auto node : nodes){
			if(node->getName() == str){
				arg3 = node->getRelatedNode();
				break;
			}
		}
	}
}