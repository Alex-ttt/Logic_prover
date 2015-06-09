#include "Stores.h"

void RulesStore::createRule(TNodes &args){
	switch(args.back()->getConclusionType()){
	case S_RULE:
		{
			auto S = new S_Rule(args);
			rules.push_back(S);
			break;
		}

	case G_RULE:
		rules.push_back(new G_Rule(args));
		break;

	case REWRITE:
		rules.push_back(new Rewrite(args));
		break;

	default:
		throw BAN_Exception("Rule Construction exceprion");
	}
}

void RulesStore::copyVector(TNodes &src, TNodes &dst, int from, int to){
	dst.reserve(to - from + 1);
	for(int i = from; i < to + 1; i++){
		dst.push_back(src[i]);
	}
}

void RulesStore::orderRules(){								// Sort all rules in order S -> G -> R
	int s = 0, r = 0, length = rules.size();
	for(int i = 0; i < length; i++){
		switch(rules[i]->getRuleType()){
		case S_RULE:
			if(s != i)
				swap(rules[i], rules[s]);
			s++;
			break;

		case REWRITE:
			if(i < length - r - 1)
				swap(rules[i], rules[length - r - 1]);
			r++;
			break;
		}
	}

	s_size = s; r_size = r; g_size = length - s - r;
}

int RulesStore::getS_Size() const {
	return s_size;
}

int RulesStore::getG_Size() const {
	return g_size;
}

int RulesStore::getR_Size() const {
	return r_size;
}

RulesStore::RulesStore(Parser &parser){
	if(!parser.ParsingComplete())
		parser.Parse();

	auto rulesStatements = parser.getRulesStatements();
	int lastRuleStart = 0;
	for(int i = 0; i < rulesStatements.size(); i++){
		if(rulesStatements[i]->isConclusion()){
			TNodes args;
			copyVector(rulesStatements, args, lastRuleStart, i);
			createRule(args);
			lastRuleStart = i + 1;
		}
	}
	orderRules();
}

void RulesStore::print() const {
	for(auto rule : rules){
		rule->print();
		cout << endl;
	}
}

StatementsStore::StatementsStore(TNodes &s){
	statements = s;
}

RulesApplicator::RulesApplicator(Parser &parser) : 
	ruleStore(RulesStore(parser)), statementStore(parser.getInitStatements()) {}

Node* RulesApplicator::ApplyRule(Rule *rule, const TNodes &formulas){
	//if(rule->argsCount() != formulas.size())
	//	return 0;
	//TNodes &rules = rule->getStatements();
	//for(int i = 0; i < formulas.size(); i++){
	//	if(*rules[i] != formulas[i]){
	//		rule->clearLinks();
	//		return 0;
	//	}
	//}

	//auto vars = rule->getRelatedNodes();
	//Node *new_formula = rule->getConclusion()->Clone();

	//// Not complete!!!
	return 0;
}