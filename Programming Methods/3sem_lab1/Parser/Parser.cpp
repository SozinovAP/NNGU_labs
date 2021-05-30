#include "Parser.h"
#include <stack>

list<Phrase> Parser::ToPostfix(list<Phrase> listPhrase)
{
	stack<Phrase> stackPhrase;
	list<Phrase> postfix;

	if (!BalanceParentheses(listPhrase))
		throw "bracket unpaired";
	bool F = true;
	for (auto it = listPhrase.begin(); it != listPhrase.end(); ++it)
	{
		//cout << (*it).str << endl;
		/*if (it->str == "integral")
		{
			postfix.emplace_back(*it);
		}
		else */if ((IsOperator(*it)) || (it->str == "("))
		{
			if(F)
			{
				F = false;
			}
			if((stackPhrase.empty()) || (it->str == "("))
			{
				stackPhrase.push(*it);
			}
			else
			{
				if (Parser::PriorityOperator(it->str) > Parser::PriorityOperator(stackPhrase.top().str))
				{
					stackPhrase.push(*it);
				}
				else
				{
					while ((!stackPhrase.empty()) && (Parser::PriorityOperator(stackPhrase.top().str)) >= Parser::PriorityOperator(it->str))
					{
						postfix.emplace_back(stackPhrase.top());
						stackPhrase.pop();
					}
					stackPhrase.push(*it);
				}
			}
		}
		else if (it->str == ")")
		{
			if (F)
			{
				F = false;
			}
			while (stackPhrase.top().str != "(")
			{
				postfix.emplace_back(stackPhrase.top());
				stackPhrase.pop();
			}
			stackPhrase.pop();
		}
		else
		{
			postfix.emplace_back(*it);
			F = true;
		}
	}

	while (!stackPhrase.empty())
	{
		postfix.emplace_back(stackPhrase.top());
		stackPhrase.pop();
	}
	return postfix;
}

bool Parser::BalanceParentheses(list<Phrase> listPhrase)
{
	if (listPhrase.empty())
		throw "phrase is empty";
	stack<char> check;
	auto it = listPhrase.begin();
	//поиск 1-ой скобки, если она закрывающаяся, то расстановка не корректна
	while((it != listPhrase.end()) && (check.empty()))
	{
		if ((*it).str == "(")
		{
			check.push('(');
		}
		else if ((*it).str == ")")
		{
			return false;
		}
		++it;
	}
	//добавление всех скобок в стек
	while((it != listPhrase.end()))
	{
		if ((*it).str == "(")
		{
			check.push('(');
		}
		else if ((*it).str == ")")
		{
			check.push(')');
		}
		++it;
	}

	//если верхняя скобка открывающаяся, то расстановка некорректна
	if ((!check.empty()) && (check.top() == '('))
		return false;
	int count = 0;
	//проверка баланса скобок
	while (!check.empty())
	{
		char c = check.top();
		if (c == ')')
		{
			count--;
		}
		else
		{
			count++;
		}
		check.pop();
	}
	return (count == 0) ? true : false;
}

void Parser::Parse(string str, Table* manager)
{
	Formula formula(str);
	string res;//строка с результатом
	list<Phrase> listPhrases = formula.Parse();
	//проверка на существование знака '=', интеграла или дифференциала
	auto it = listPhrases.begin();
	bool Flag = true;
	int countSigh = 0;
	while ((it != listPhrases.end()) && (Flag))
	{
		if (it->str == "=")	//если находим =, смотрим, были ли операторы слева
		{
			Flag = false;
			if (countSigh > 0)
				throw "no operand must be before =";
			list<Phrase> tmp;
			string name = "";
			//элементы до итератора - имя
			for (auto iter = listPhrases.begin(); iter != it; ++iter)
			{
				name += iter->str;
			}
			//элементы после итератора - полином ли выражение, которое нужно вычислить
			for(auto iter = ++it; iter != listPhrases.end(); ++iter)
			{
				tmp.emplace_back(*iter);
			}
			
			tmp = ToPostfix(tmp);
			res = Calculate(tmp, manager);
			Polynomial pol(res);
			if (manager->Find(name) == nullptr)
			{
				manager->Insert(name, pol);
			}
			else
			{
				manager->Replace(name, pol);
			}
		}
		else if (IsOperator(*it))
		{
			countSigh++;
		}
		/*else if (it->str == "integral") //если находим интеграл, копируем элементы до него 
		{
			Flag = false;
			list<Phrase> tmp;
			//эдементы до интеграла - выражение, символ после - переменная, по которой берется интеграл
			for (auto iter = listPhrases.begin(); iter != it; ++it)
			{
				tmp.emplace_back(*iter);
			}
			tmp = ToPostfix(tmp);
			res = Int(tmp, listPhrases.back().str);
		}
		else if (it->str == "derivative") //если находим производную, копируем элементы до нее
		{
			Flag = false;
			list<Phrase> tmp;
			//эдементы до проиводной - выражение, символ после - переменная, по которой берется производная
			for (auto iter = listPhrases.begin(); iter != it; ++it)
			{
				tmp.emplace_back(*iter);
			}
			tmp = ToPostfix(tmp);
			res = Dif(tmp, listPhrases.back().str);
		}*/
		++it;
	}

	if (Flag)	//если не нашли =, интеграла и производной, просто вычисляем
	{
		list<Phrase> postfixPhrase = ToPostfix(listPhrases);
		res = Calculate(postfixPhrase, manager);
	}
}

int Parser::PriorityOperator(string s)
{
	if (s == "(")
	{
		return 0;
	}
	else if (s == ")")
	{
		return 1;
	}
	else if ((s == "+") || (s == "-"))
	{
		return 2;
	}
	else if ((s == "/") || (s == "*"))
	{
		return 3;
	}
	else if ((s == "integral") || (s == "'"))
	{
		return 4;
	}
	else
		throw "uncorrect symbol";
}

bool Parser::IsOperator(Phrase ph)
{
	//string oper = "+-*/";

	if (ph.phraseType == PhraseType::sign)
	{
		if (ph.str == ")" || ph.str == "(")
		{
			return false;
		}
		return true;
	}
	else
	{
		return false;
	}

	//return (oper.find(s) == -1) ? false : true;
}

string Parser::Calculate(list<Phrase> postfixPhrases, Table* manager)
{
	string str = "";
	bool F = true;
	stack<Polynomial> tmpOperand;
	Polynomial tmp;
	auto it = postfixPhrases.begin();
	while ((it) != postfixPhrases.end())
	{
		if (IsOperator(*it))
		{
			bool Oper1find = false;
			bool Oper2find = false;
			Polynomial Oper1, Oper2;
			if (!tmpOperand.empty())
			{
				Oper2 = tmpOperand.top();//*manager->Find(tmpOperand.top().ToStr());;
				tmpOperand.pop();
				Oper2find = true;
			}
			if (!tmpOperand.empty())
			{
				Oper1 = tmpOperand.top();//*manager->Find(tmpOperand.top().ToStr());;
				tmpOperand.pop();
				Oper1find = true;
			}
			if (!(Oper1find && Oper2find))
				throw "False";
			if(it->str == "+")
			{
				tmp = Oper1 + Oper2;
			}
			else if(it->str == "-")
			{
				tmp = Oper1 - Oper2;
			}
			else if (it->str == "*")
			{
				tmp = Oper1 * Oper2;
			}
			else if (it->str == "'")
			{
				tmp = Oper1.Dif(Oper2.ToStr()[0]);
			}
			else if (it->str == "integral")
			{
				tmp = Oper1.Integr(Oper2.ToStr()[0]);
			}
			tmpOperand.push(tmp);
		}
		else
		{
			try
			{
				Polynomial pol2(it->str);
				tmpOperand.push(pol2);
			}
			catch (...)
			{
				Polynomial* pol = manager->Find(it->str);
				if (pol == nullptr)
				{
					throw "cannot be converted to polynomial and no entry in the table";
				}
				tmpOperand.push(*pol);
			}
		}
		it++;
	}
	/*Polynomial* pol = manager->Find(it->str);
	if (pol == nullptr)
	{
		if (IsOperator(it->str))
		{
			postfixPhrases.emplace_back(*it);
		}
		else
		{
			try
			{
				Polynomial pol2(it->str);
			}
			catch (...)
			{
				throw "cannot be converted to polynomial and no entry in the table";
			}
		}
	}*/
	if (tmpOperand.size() != 1)
	{
		throw "too much operands";
	}

	return tmpOperand.top().ToStr();
}

/*string Parser::Dif(list<Phrase> phrase, string x)
{
	string res = "";
	phrase = ToPostfix(phrase);
	//!!!
	return res;
}

string Parser::Int(list<Phrase> phrase, string x)
{
	string res = "";
	phrase = ToPostfix(phrase);
	//!!!
	return res;
}*/