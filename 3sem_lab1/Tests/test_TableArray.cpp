#pragma once
#include "gtest/gtest.h"
#include "../Tables/TableArray.h"

using namespace std;

TEST(TableArray, ta_default_constructor)
{
    ASSERT_NO_THROW(TableArray ta);
}
TEST(TableArray, ta_startLength_constructor)
{
	ASSERT_NO_THROW(TableArray ta(5));
}

TEST(TableArray, ta_insert)
{
	TableArray ta;
	Polynomial p;

	ASSERT_NO_THROW(ta.Insert("a", p));
}
TEST(TableArray, ta_cant_insert_same_name)
{
	TableArray ta;
	Polynomial p, p2;

	ta.Insert("a", p);
	ASSERT_ANY_THROW(ta.Insert("a", p2));
}


TEST(TableArray, ta_canRemove_exist_value)
{
	TableArray ta;
	Polynomial p;

	
	ta.Insert("a", p);
	ASSERT_NO_THROW(ta.Remove("a"));
}
TEST(TableArray, ta_cantRemove_not_exist_value)
{
	TableArray ta;
	Polynomial p;

	ASSERT_ANY_THROW(ta.Remove("a"));
	ta.Insert("a", p);
	ASSERT_ANY_THROW(ta.Remove("b"));
}
TEST(TableArray, ta_canRemove_not_first_value)
{
	TableArray ta;
	Polynomial p;


	ta.Insert("a", p);
	ta.Insert("b", p);
	ta.Insert("c", p);
	ta.Insert("d", p);
	ta.Insert("e", p);
	ASSERT_NO_THROW(ta.Remove("b"));
	ASSERT_NO_THROW(ta.Remove("d"));
	ASSERT_NO_THROW(ta.Remove("e"));
}

TEST(TableArray, ta_can_find_exist_value)
{
	TableArray ta;
	std::string str = "xyz^2";
	Monomial m(str);
	Polynomial p;
	p += m;

	ta.Insert("a", p);

	ASSERT_NE(ta.Find("a"), nullptr);

	std::ostringstream stream;
	stream << *ta.Find("a");

	ASSERT_EQ(str, stream.str());
}
TEST(TableArray, ta_cant_find_not_exist_value)
{
	TableArray ta;
	Polynomial p;

	ASSERT_EQ(ta.Find("a"), nullptr);
	ta.Insert("a", p);
	ASSERT_EQ(ta.Find("b"), nullptr);
}

TEST(TableArray, ta_replace_works_fine)
{
	TableArray ta;
	std::string str = "xyz^2";
	std::string str2 = "xz^5";
	Monomial m(str);
	Monomial m2(str2);
	Polynomial p,p2;
	p += m;
	p2 += m2;

	ta.Insert("a", p);

	ASSERT_NO_THROW(ta.Replace("a", p2));

	std::ostringstream stream;
	stream << *ta.Find("a");

	ASSERT_EQ(str2, stream.str());
}

TEST(TableArray, ta_getCount_works_fine)
{
	TableArray ta;
	Polynomial p;

	ASSERT_EQ(ta.GetCount(), 0);
	ta.Insert("a", p);
	ASSERT_EQ(ta.GetCount(), 1);
	ta.Insert("b", p);
	ta.Insert("c", p);
	ta.Remove("a");
	ASSERT_EQ(ta.GetCount(), 2);
}
TEST(TableArray, ta_isEmpty_works_fine)
{
	TableArray ta;
	Polynomial p;

	ASSERT_TRUE(ta.IsEmpty());
	ta.Insert("a", p);
	ASSERT_FALSE(ta.IsEmpty());
	ta.Remove("a");
	ASSERT_TRUE(ta.IsEmpty());
}

TEST(TableArray, ta_clear_works_fine)
{
	TableArray ta;
	Polynomial p;
	ta.Insert("a", p);


	ASSERT_NO_THROW(ta.Clear());
	ASSERT_TRUE(ta.IsEmpty());
	ASSERT_ANY_THROW(ta.Remove("a"));
}

TEST(TableArray, ta_iterator_begin_and_iterator_end_equal)
{
	TableArray ta;

	ASSERT_NO_THROW(ta.begin());
	ASSERT_NO_THROW(ta.end());

	ASSERT_TRUE(ta.begin() == ta.end());
}

TEST(TableArray, ta_iterators_begin_and_end_works_fine)
{
	TableArray ta;
	Polynomial p;
	string name = "a";
	ta.Insert(name, p);
	ASSERT_NO_THROW(ta.begin());
	ASSERT_NO_THROW(ta.end());

	ASSERT_FALSE(ta.begin() == ta.end());
	ASSERT_TRUE(++ta.begin() == ta.end());
	ASSERT_EQ((*ta.begin()).GetName(), name);
}

TEST(TableArray, ta_iterators_operator_increment_works_fine_one_time)
{
	TableArray ta;
	Polynomial p;
	string name = "a";
	ta.Insert(name, p);
	ASSERT_TRUE(++ta.begin() == ta.end());
}

TEST(TableArray, ta_iterators_operator_increment_works_fine_several_times)
{
	TableArray ta;
	Polynomial p;
	ASSERT_TRUE(ta.begin() == ta.end());

	const int count = 10;
	int a[count]{ 1,2,3,6,4,5,7,0,8,9 };
	for (int i = 0; i < count; i++)
	{
		ta.Insert(to_string(a[i]), p);
	}

	int x = 0;
	for (Table::iterator it = ta.begin(); it != ta.end(); it++)
	{
		ASSERT_EQ((*it).GetName(), to_string(a[x]));
		x++;
	}
	ASSERT_EQ(x, count);

}