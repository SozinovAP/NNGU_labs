#include "Monomial.h"

Monomial::Monomial(int coef, int powers)
{
	this->coef = coef;
	this->powers = powers;
}

Monomial::Monomial(const Monomial& monom)
{
	coef = monom.coef;
	powers = monom.powers;
}

Monomial::Monomial(const std::string &str)
{
	int i = 0;

	coef = 1;

	if (str[i] == '+')
	{
		i++;
	}
	if (str[i] == '-')
	{
		coef = -1;
		i++;
	}

	int tmp = 0;
	if (std::isdigit(str[i]))
	{
		while (std::isdigit(str[i]))
		{
			tmp = tmp * 10 + (str[i] - '0');
			i++;
		}
		coef *= tmp;
	}

	powers = 0;
	for (; i < str.length(); i++)
	{
		int st = 0;
		char c = str[i];

		if (str.length() > i + 1 && str[i + 1] == '^')
		{
			if (str.length() < i + 2 || !isdigit(str[i + 2]))
				throw input_exc::wrong_pow;
			while (std::isdigit(str[i + 2]))
			{
				st = st * 10 + (str[i + 2] - '0');
				i++;
				if (st / 100)
					throw input_exc::too_large_power;
				if (st < 0)
					throw input_exc::negative_power;
			}
			i++;
		}
		else
			st = 1;

		if (c == 'x' || c == 'X')
			powers += 10000 * st;
		else if(c == 'y' || c == 'Y')
			powers += 100 * st;
		else if(c == 'z' || c == 'Z')
			powers += st;
		else
			throw input_exc::wrong_var;

	}

}

void Monomial::SetCoef(int coef)
{
	this->coef = coef;
}

int Monomial::GetCoef(void) const
{
	return coef;
}

void Monomial::SetPowers(int powers)
{
	this->powers = powers;
}

int Monomial::GetPowers(void) const
{
	return powers;
}

Monomial& Monomial::operator=(const Monomial &monom)
{
	coef = monom.coef;
	powers = monom.powers;
	return *this;
}

bool Monomial::operator==(const Monomial &monom)
{
	return (powers == monom.powers && coef == monom.coef);
}

bool Monomial::operator!=(const Monomial &monom)
{
	return (powers != monom.powers || coef != monom.coef);
}

bool Monomial::operator<(const Monomial &monom)
{
	return (powers < monom.powers);
}

std::ostream & operator<<(std::ostream & stream, const Monomial & m)
{
	if (m.coef == 0) return stream;

	if (m.coef != 1)
	{
		if (m.coef == -1)
			stream << "-";
		else
			stream << m.coef;
	}
	if (m.coef == 1 && m.powers == 0)
	{
		stream << "1";
	}
	if (m.powers / 10000)
	{
		stream << "x";
		if (m.powers / 10000 != 1)
			stream << "^" << m.powers / 10000;
	}
	if (m.powers / 100 % 100)
	{
		stream << "y";
		if (m.powers / 100 % 100 != 1)
			stream << "^" << m.powers / 100 % 100;
	}
	if (m.powers % 10)
	{
		stream << "z";
		if (m.powers % 100 != 1)
			stream << "^" << m.powers % 100;
	}

	return stream;
}

std::string Monomial::toStr()
{
	std::string s;
	if (coef == 0) 
		return s;

	if (coef != 1)
	{
		if (coef == -1 && powers>0)
			s += "-";
		else
			s += std::to_string(coef);
	}
	if (coef == 1 && powers == 0)
	{
		s += "1";
	}
	if (powers / 10000)
	{
		s += "x";
		if (powers / 10000 != 1)
		{
			s += "^";
			s += std::to_string(powers / 10000);
		}
	}
	if (powers / 100 % 100)
	{
		s += "y";
		if (powers / 100 % 100 != 1)
		{
			s += "^";
			s += std::to_string(powers / 100 % 100);
		}
	}
	if (powers % 10)
	{
		s += "z";
		if (powers % 100 != 1)
		{
			s += "^";
			s += std::to_string(powers % 100);
		}
	}

	return s;
}