#pragma once
#include "Monomial.h"
#include "list.h"

class Polynomial
{
private:
	TList<Monomial> monomials;

public:
	Polynomial();
	Polynomial(const TList<Monomial> &mon);
	Polynomial(const Polynomial& p);
	Polynomial(std::string s);

	Polynomial& operator-(const Polynomial& p) const;
	Polynomial& operator+(const Polynomial& p) const;
	Polynomial& operator*(const Polynomial& p) const;
	Polynomial& operator*(const Monomial& m) const;
	Polynomial& operator+=(const Monomial &m);
	Polynomial& operator=(const Polynomial & p);
	bool operator==(const Polynomial & p)const;
	bool operator!=(const Polynomial & p)const;

	friend std::ostream & operator<<(std::ostream & stream, const Polynomial &p);
	friend std::istream & operator>>(std::istream & stream, Polynomial & p);

	std::string ToStr() const;
	bool HasX();
	bool HasY();
	bool HasZ();
	bool IsEmpty();
	void Sort();
	int Det(int x, int y, int z);
	Polynomial Dif(char v);
	Polynomial Integr(char v);
	int GetMonomialsCount();
};