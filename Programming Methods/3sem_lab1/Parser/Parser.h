#pragma once

#include "Formula.h"
#include "../TableManager.h"

//TableManager = Table*
static class Parser
{
private:
	static list<Phrase> ToPostfix(list<Phrase> listPhrase);
	static bool BalanceParentheses(list<Phrase> listPhrase);
	static int PriorityOperator(string s);
	static bool IsOperator(Phrase ph);
	static string Calculate(list<Phrase> postfixPhrases, Table* manager);
	static string Int(list<Phrase> phrase, string x);
	static string Dif(list<Phrase> phrase, string x);
public:
	
	static void Parse(string str, Table* manager);
};

 


 
