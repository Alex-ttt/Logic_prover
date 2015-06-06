#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "BAN_Exception.h"

using namespace std;

class Node;

typedef vector<Node*> TNodes;

enum RuleType {
	S_RULE,
	G_RULE,
	REWRITE
};

enum func {
	variable,		// X, A, Key etc.
	believes,		// P believes X
	received,		// P received X
	said,			// P said X
	controls,		// P controls X
	fresh,			// fresh(X)
	public_key,		// (Key, P)
	shared_key,		// (Key, P, Q)
	secret,			// (Y, P, Q) - P and Q have secret Y
	encrypt,		// (X, K, P) - X encrypted with K by P
	combine,		// Maybe unnecessary
	comma,			// (X, Y)
	inv,			// (K1, K2) - K1 and K2 are a public/private pair
	distinct		// (P, Q) - this is principals
};
