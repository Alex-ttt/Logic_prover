#include "Rules.h"


S_Rule::S_Rule(TNodes &rules) : Rule(rules) {}

G_Rule::G_Rule(TNodes &rules) : Rule(rules, G_RULE) {}

Rewrite::Rewrite(TNodes &rules) : Rule(rules, REWRITE) {}

Node* Rule::getConclusion(){
	return args.empty() ? 0 : args.back();
}

TNodes Rule::getStatements(){
	return args;
}

int Rule::size() const {
	return args.size();
}

int Rule::argsCount() const {
	return args.size() - 1;
}

RuleType Rule::getRuleType() const {
	return type;
}

vector<VarNode*> Rule::getRelatedNodes(){
	vector<VarNode*> ret;
	for(int i = 0; i < args.size() - 1; i++){
		args[i]->getRelatedNodes(ret);
	}

	return ret;
}

void Rule::clearLinks(){
	for(int i = 0; i < args.size() - 1; i++){
		args[i]->clearLinks();
	}
}

void Rule::print() const {
	for(auto a : args){
		if(a->isConclusion())
			cout << "Conclusion:" << endl;
		a->print();
	}
}
