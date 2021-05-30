#pragma once

#include <string>
#include <iostream>
#include <cctype>

class Monomial
{
private:
	int coef;
	int powers;

public:
	Monomial(int coef = 0, int powers = 0);
	Monomial(const Monomial& monom);
	Monomial(const std::string &str);

	void SetCoef(int coef);
	int GetCoef(void) const;
	void SetPowers(int powers);
	int GetPowers(void) const;
	Monomial& operator=(const Monomial &monom);
	bool operator==(const Monomial &monom);
	bool operator!=(const Monomial &monom);
	bool operator<(const Monomial &monom);

	friend std::ostream& operator<<(std::ostream &stream, const Monomial &m);
	std::string toStr();
	
};

enum class input_exc
{
	wrong_var, wrong_pow, too_large_power, negative_power
};