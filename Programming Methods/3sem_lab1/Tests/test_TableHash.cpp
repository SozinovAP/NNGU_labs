#pragma once
#include "gtest/gtest.h"
#include "../Tables/TableHash.h"

using namespace std;

TEST(TableHash, th_default_constructor)
{
    ASSERT_NO_THROW(TableHash th);
}
TEST(TableHash, th_startLength_constructor)
{
	ASSERT_NO_THROW(TableHash th(5));
}

TEST(TableHash, th_insert)
{
	TableHash th;
	Polynomial p;

	ASSERT_NO_THROW(th.Insert("a", p));
}
TEST(TableHash, th_cant_insert_same_name)
{
	TableHash th;
	Polynomial p, p2;

	th.Insert("a", p);
	ASSERT_ANY_THROW(th.Insert("a", p2));
}


TEST(TableHash, th_canRemove_exist_value)
{
	TableHash th;
	Polynomial p;

	
	th.Insert("a", p);
	ASSERT_NO_THROW(th.Remove("a"));
}

TEST(TableHash, th_cantRemove_not_exist_value)
{
	TableHash th;
	Polynomial p;

	ASSERT_ANY_THROW(th.Remove("a"));
	th.Insert("a", p);
	ASSERT_ANY_THROW(th.Remove("b"));
}
TEST(TableHash, th_canRemove_not_first_value)
{
	TableHash th;
	Polynomial p;


	th.Insert("a", p);
	th.Insert("b", p);
	th.Insert("c", p);
	th.Insert("d", p);
	th.Insert("e", p);
	ASSERT_NO_THROW(th.Remove("b"));
	ASSERT_NO_THROW(th.Remove("d"));
	ASSERT_NO_THROW(th.Remove("e"));
}

TEST(TableHash, th_can_find_exist_value)
{
	TableHash th;
	std::string str = "xyz^2";
	Monomial m(str);
	Polynomial p;
	p += m;

	th.Insert("a", p);

	ASSERT_NE(th.Find("a"), nullptr);

	std::ostringstream stream;
	stream << *th.Find("a");

	ASSERT_EQ(str, stream.str());
}
TEST(TableHash, th_cant_find_not_exist_value)
{
	TableHash th;
	Polynomial p;

	ASSERT_EQ(th.Find("a"), nullptr);
	th.Insert("a", p);
	ASSERT_EQ(th.Find("b"), nullptr);
}

TEST(TableHash, th_replace_works_fine)
{
	TableHash th;
	std::string str = "xyz^2";
	std::string str2 = "xz^5";
	Monomial m(str);
	Monomial m2(str2);
	Polynomial p,p2;
	p += m;
	p2 += m2;

	th.Insert("a", p);

	ASSERT_NO_THROW(th.Replace("a", p2));

	std::ostringstream stream;
	stream << *th.Find("a");

	ASSERT_EQ(str2, stream.str());
}

TEST(TableHash, th_getCount_works_fine)
{
	TableHash th;
	Polynomial p;

	ASSERT_EQ(th.GetCount(), 0);
	th.Insert("a", p);
	ASSERT_EQ(th.GetCount(), 1);
	th.Insert("b", p);
	th.Insert("c", p);
	th.Remove("a");
	ASSERT_EQ(th.GetCount(), 2);
}
TEST(TableHash, th_isEmpty_works_fine)
{
	TableHash th;
	Polynomial p;

	ASSERT_TRUE(th.IsEmpty());
	th.Insert("a", p);
	ASSERT_FALSE(th.IsEmpty());
	th.Remove("a");
	ASSERT_TRUE(th.IsEmpty());
}

TEST(TableHash, th_clear_works_fine)
{
	TableHash th;
	Polynomial p;
	th.Insert("a", p);


	ASSERT_NO_THROW(th.Clear());
	ASSERT_TRUE(th.IsEmpty());
	ASSERT_ANY_THROW(th.Remove("a"));
}

TEST(TableHash, th_iterator_begin_and_iterator_end_equal)
{
	TableHash th;

	ASSERT_NO_THROW(th.begin());
	ASSERT_NO_THROW(th.end());

	ASSERT_TRUE(th.begin() == th.end());
}

TEST(TableHash, th_iterators_begin_and_end_works_fine)
{
	TableHash th;
	Polynomial p;
	string name = "a";
	th.Insert(name, p);
	ASSERT_NO_THROW(th.begin());
	ASSERT_NO_THROW(th.end());
	ASSERT_FALSE(th.begin() == th.end());
	ASSERT_EQ((*th.begin()).GetName(), name);
}

TEST(TableHash, th_iterator_begin_works_fine)
{
	TableHash th;
	Polynomial p;
	th.Insert("a", p);
	th.Insert("b", p);
	th.Insert("c", p);
	th.Insert("d", p);
	ASSERT_TRUE((*th.begin()).GetName() == "b");
}

TEST(TableHash, th_iterators_operator_increment_works_fine_one_time)
{
	TableHash th;
	Polynomial p;
	string name = "a";
	th.Insert(name, p);
	ASSERT_TRUE(++th.begin() == th.end());
}

TEST(TableHash, th_iterator_works_fine_with_severals_numbers)
{
	Polynomial p;
	TableHash th;

	const int count = 10;
	int b[count]{ 1,2,3,6,4,5,7,0,8,9 };
	for (int i = 0; i < count; i++)
	{
		th.Insert(to_string(b[i]), p);
	}
	string a[count];
	int x = 0;
	for (Table::iterator it = th.begin(); it != th.end(); it++)
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
