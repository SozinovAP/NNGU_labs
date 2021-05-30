#pragma once
#include "gtest/gtest.h"
#include "../Tables/TableList.h"

using namespace std;

TEST(TableList, tl_default_constructor)
{
	ASSERT_NO_THROW(TableList tl);
}
TEST(TableList, tl_startLengtl_constructor)
{
	ASSERT_NO_THROW(TableList tl);
}

TEST(TableList, tl_insert)
{
	TableList tl;
	Polynomial p;

	ASSERT_NO_THROW(tl.Insert("a", p));
}

TEST(TableList, tl_cant_insert_same_name)
{
	TableList tl;
	Polynomial p, p2;

	tl.Insert("a", p);
	ASSERT_ANY_THROW(tl.Insert("a", p2));
}

TEST(TableList, tl_canRemove_exist_value)
{
	TableList tl;
	Polynomial p;


	tl.Insert("a", p);
	ASSERT_NO_THROW(tl.Remove("a"));
}

TEST(TableList, tl_cantRemove_not_exist_value)
{
	TableList tl;
	Polynomial p;

	ASSERT_ANY_THROW(tl.Remove("a"));
	tl.Insert("a", p);
	ASSERT_ANY_THROW(tl.Remove("b"));
}

TEST(TableList, tl_canRemove_not_first_value)
{
	TableList tl;
	Polynomial p;


	tl.Insert("a", p);
	tl.Insert("b", p);
	tl.Insert("c", p);
	tl.Insert("d", p);
	tl.Insert("e", p);
	ASSERT_NO_THROW(tl.Remove("b"));
	ASSERT_NO_THROW(tl.Remove("d"));
	ASSERT_NO_THROW(tl.Remove("e"));
}

TEST(TableList, tl_can_find_exist_value)
{
	TableList tl;
	std::string str = "xyz^2";
	Monomial m(str);
	Polynomial p;
	p += m;

	tl.Insert("a", p);

	ASSERT_NE(tl.Find("a"), nullptr);

	std::ostringstream stream;
	stream << *tl.Find("a");

	ASSERT_EQ(str, stream.str());
}
TEST(TableList, tl_cant_find_not_exist_value)
{
	TableList tl;
	Polynomial p;

	ASSERT_EQ(tl.Find("a"), nullptr);
	tl.Insert("a", p);
	ASSERT_EQ(tl.Find("b"), nullptr);
}

TEST(TableList, tl_replace_works_fine)
{
	TableList tl;
	std::string str = "xyz^2";
	std::string str2 = "xz^5";
	Monomial m(str);
	Monomial m2(str2);
	Polynomial p, p2;
	p += m;
	p2 += m2;

	tl.Insert("a", p);

	ASSERT_NO_THROW(tl.Replace("a", p2));

	std::ostringstream stream;
	stream << *tl.Find("a");

	ASSERT_EQ(str2, stream.str());
}

TEST(TableList, tl_getCount_works_fine)
{
	TableList tl;
	Polynomial p;

	ASSERT_EQ(tl.GetCount(), 0);
	tl.Insert("a", p);
	ASSERT_EQ(tl.GetCount(), 1);
	tl.Insert("b", p);
	tl.Insert("c", p);
	tl.Remove("a");
	ASSERT_EQ(tl.GetCount(), 2);
}
TEST(TableList, tl_isEmpty_works_fine)
{
	TableList tl;
	Polynomial p;

	ASSERT_TRUE(tl.IsEmpty());
	tl.Insert("a", p);
	ASSERT_FALSE(tl.IsEmpty());
	tl.Remove("a");
	ASSERT_TRUE(tl.IsEmpty());
}

TEST(TableList, tl_clear_works_fine)
{
	TableList tl;
	Polynomial p;
	tl.Insert("a", p);


	ASSERT_NO_THROW(tl.Clear());
	ASSERT_TRUE(tl.IsEmpty());
	ASSERT_ANY_THROW(tl.Remove("a"));
}

TEST(TableList, tl_iterator_begin_and_iterator_end_equal)
{
	TableList tl;

	ASSERT_NO_THROW(tl.begin());
	ASSERT_NO_THROW(tl.end());

	ASSERT_TRUE(tl.begin() == tl.end());
}

TEST(TableList, tl_iterators_begin_and_end_works_fine)
{
	TableList tl;
	Polynomial p;
	string name = "a";
	tl.Insert(name, p);
	ASSERT_NO_THROW(tl.begin());
	ASSERT_NO_THROW(tl.end());
	ASSERT_FALSE(tl.begin() == tl.end());
	ASSERT_EQ((*tl.begin()).GetName(), name);
}

TEST(TableList, tl_iterator_begin_works_fine)
{
	TableList tl;
	Polynomial p;
	tl.Insert("a", p);
	tl.Insert("b", p);
	tl.Insert("c", p);
	tl.Insert("d", p);
	ASSERT_TRUE((*tl.begin()).GetName() == "a");
}

TEST(TableList, tl_iterators_operator_increment_works_fine_one_time)
{
	TableList tl;
	Polynomial p;
	string name = "a";
	tl.Insert(name, p);
	ASSERT_TRUE(++tl.begin() == tl.end());
}

TEST(TableList, tl_iterator_works_fine_witl_severals_numbers)
{
	Polynomial p;
	TableList tl;

	const int count = 10;
	int b[count]{ 1,2,3,6,4,5,7,0,8,9 };
	for (int i = 0; i < count; i++)
	{
		tl.Insert(to_string(b[i]), p);
	}
	string a[count];
	int x = 0;
	for (Table::iterator it = tl.begin(); it != tl.end(); it++)
	{
		a[x] = (*it).GetName();
		x++;
	}
	ASSERT_EQ(x, count);

	sort(a, a + count);
	for (int i = 0; i < count; i++)
	{
		ASSERT_EQ(a[i], to_string(i));
	}
}
