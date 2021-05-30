#pragma once
#include <string>
#include "../Monomial.h"

enum class PhraseType
{
	str,
	sign
};

enum class SignType
{
	plus,
	minus,
	equal,
	multiply,
	bracketopen,
	bracketclose,
	integral,
	derivative,
	signsCount
};

struct Phrase
{
	static const std::string signStrs[static_cast<int>(SignType::signsCount)];

	PhraseType phraseType;
	std::string str;

	Phrase(PhraseType phraseType, std::string str="")
	{
		this->phraseType = phraseType;
		this->str = str;
	}

};


