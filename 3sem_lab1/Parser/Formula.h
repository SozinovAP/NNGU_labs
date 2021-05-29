#pragma once

#include <string>
#include "../Polynomial.h"
#include <list>
#include "Phrase.h"

using namespace std;

class Formula
{
private:

	string inputFormula;

public:

	Formula(string str)
	{
		this->inputFormula = str;
	}
	list<Phrase> Parse()
	{
		AddZero();
		list<Phrase> phrases;
		//cout << inputFormula << endl;
		string str = inputFormula;
		
		string prevPhrase;
		for (int i = 0; i < str.length(); i++)
		{
			int j;

			bool itsSign = false;
			std::string signStr;

			for (j = 0; j < static_cast<int>(SignType::signsCount); j++)
			{
				signStr = Phrase::signStrs[j];
				if (str.length()-i >= signStr.length() && str.substr(i, signStr.length()) == signStr)
				{
					itsSign = true;
					break;
				}
			}

			
			if (!itsSign && str[i] != ' ')
			{
				prevPhrase += str[i];
			}

			if (itsSign || str[i] == ' ' || i + 1 == str.length())
			{
				if (prevPhrase != "")
				{
					phrases.push_back(Phrase(PhraseType::str, prevPhrase));
					prevPhrase = "";
				}
			}

			if (itsSign)
			{
				phrases.push_back(Phrase(PhraseType::sign, signStr));
				i += signStr.length() - 1;
			}

		}
		
		
		return phrases;
	}
	void AddZero()
	{
		string tmp = "";
		int i = 0;
		if (inputFormula[i] == '-')
		{
			tmp += "0-";
			i++;
		}
		else if (inputFormula[i] == '+')
		{
			i++;
		}
		while (i < inputFormula.length())
		{
			if ((inputFormula[i] == '-') && (inputFormula[i - 1] == '('))
			{
				tmp += "0-";
				i++;
			}
			else if ((inputFormula[i] == '+') && (inputFormula[i - 1] == '('))
			{
				i++;
			}
			tmp += inputFormula[i++];
		}
		inputFormula = tmp;
	}
};
