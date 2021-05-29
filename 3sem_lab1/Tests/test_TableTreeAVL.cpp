#pragma once
#include "gtest/gtest.h"
#include "../Tables/TableTreeAVL.h"

using namespace std;

TEST(TableTreeAVL, tt_default_constructor)
{
    ASSERT_NO_THROW(TableTreeAVL tt);
}

TEST(TableTreeAVL, tt_insert)
{
	TableTreeAVL tt;
	Polynomial p;

	ASSERT_NO_THROW(tt.Insert("a", p));
}
TEST(TableTreeAVL, tt_cant_insert_same_name)
{
	TableTreeAVL tt;
	Polynomial p, p2;

	tt.Insert("a", p);
	ASSERT_ANY_THROW(tt.Insert("a", p2));
}


TEST(TableTreeAVL, tt_canRemove_exist_value)
{
	TableTreeAVL tt;
	Polynomial p;

	tt.Insert("a", p);
	ASSERT_NO_THROW(tt.Remove("a"));
}
TEST(TableTreeAVL, tt_cantRemove_not_exist_value)
{
	TableTreeAVL tt;
	Polynomial p;

	ASSERT_ANY_THROW(tt.Remove("a"));
	tt.Insert("a", p);
	ASSERT_ANY_THROW(tt.Remove("b"));
}

TEST(TableTreeAVL, tt_can_find_exist_value)
{
	TableTreeAVL tt;
	std::string str = "xyz^2";
	Monomial m(str);
	Polynomial p;
	p += m;

	tt.Insert("a", p);

	ASSERT_NE(tt.Find("a"), nullptr);

	std::ostringstream stream;
	stream << *tt.Find("a");

	ASSERT_EQ(str, stream.str());
}
TEST(TableTreeAVL, tt_cant_find_not_exist_value)
{
	TableTreeAVL tt;
	Polynomial p;

	ASSERT_EQ(tt.Find("a"), nullptr);
	tt.Insert("a", p);
	ASSERT_EQ(tt.Find("b"), nullptr);
}

TEST(TableTreeAVL, tt_replace_works_fine)
{
	TableTreeAVL tt;
	std::string str = "xyz^2";
	std::string str2 = "xz^5";
	Monomial m(str);
	Monomial m2(str2);
	Polynomial p,p2;
	p += m;
	p2 += m2;

	tt.Insert("a", p);

	ASSERT_NO_THROW(tt.Replace("a", p2));

	std::ostringstream stream;
	stream << *tt.Find("a");

	ASSERT_EQ(str2, stream.str());
}

TEST(TableTreeAVL, tt_getCount_works_fine)
{
	TableTreeAVL tt;
	Polynomial p;

	ASSERT_EQ(tt.GetCount(), 0);
	tt.Insert("a", p);
	ASSERT_EQ(tt.GetCount(), 1);
	tt.Insert("b", p);
	tt.Insert("c", p);
	ASSERT_EQ(tt.GetCount(), 3);
	tt.Remove("a");
	ASSERT_EQ(tt.GetCount(), 2);
}
TEST(TableTreeAVL, tt_isEmpty_works_fine)
{
	TableTreeAVL tt;
	Polynomial p;

	ASSERT_TRUE(tt.IsEmpty());
	tt.Insert("a", p);
	ASSERT_FALSE(tt.IsEmpty());
	tt.Remove("a");
	ASSERT_TRUE(tt.IsEmpty());
}

TEST(TableTreeAVL, tt_clear_works_fine)
{
	TableTreeAVL tt;
	Polynomial p;
	tt.Insert("a", p);


	ASSERT_NO_THROW(tt.Clear());
	ASSERT_TRUE(tt.IsEmpty());
	ASSERT_ANY_THROW(tt.Remove("a"));
}

TEST(TableTreeAVL, tt_getheight_works_fine)
{
	TableTreeAVL tt;
	Polynomial p;
	ASSERT_NO_THROW(tt.GetHeight());
	ASSERT_EQ(0, tt.GetHeight());
	tt.Insert("c", p);
	ASSERT_EQ(1, tt.GetHeight());
	tt.Insert("b", p);
	ASSERT_EQ(2, tt.GetHeight());
	tt.Insert("d", p);
	ASSERT_EQ(2, tt.GetHeight());
	tt.Insert("a", p);
	ASSERT_EQ(3, tt.GetHeight());
	tt.Remove("a");
	ASSERT_EQ(2, tt.GetHeight());
	tt.Remove("b");
	ASSERT_EQ(2, tt.GetHeight());
	tt.Remove("d");
	ASSERT_EQ(1, tt.GetHeight());
	tt.Remove("c");
	ASSERT_EQ(0, tt.GetHeight());
}

TEST(TableTreeAVL, tt_balance_on_insert_works_fine)
{
	TableTreeAVL tt;
	Polynomial p;
	tt.Insert("a", p);
	tt.Insert("b", p);
	tt.Insert("c", p);
	ASSERT_EQ(2, tt.GetHeight());
}

TEST(TableTreeAVL, tt_balance_on_remove_works_fine)
{
	TableTreeAVL tt;
	Polynomial p;
	tt.Insert("b", p);
	tt.Insert("c", p);
	tt.Insert("a", p);
	tt.Insert("d", p);
	ASSERT_EQ(3, tt.GetHeight());
	tt.Remove("a");
	ASSERT_EQ(2, tt.GetHeight());
}

TEST(TableTreeAVL, tt_bigbalance_on_insert_works_fine)
{
	TableTreeAVL tt;
	Polynomial p;
	tt.Insert("b", p);
	tt.Insert("a", p);
	tt.Insert("e", p);
	tt.Insert("d", p);
	tt.Insert("f", p);
	ASSERT_EQ(3, tt.GetHeight());
	tt.Insert("c", p);
	ASSERT_EQ(3, tt.GetHeight());
}
TEST(TableTreeAVL, tt_bigbalance_on_insert_works_fine2)
{
	TableTreeAVL tt;
	Polynomial p;
	tt.Insert("a", p);
	tt.Insert("c", p);
	ASSERT_EQ(2, tt.GetHeight());
	tt.Insert("b", p);
	ASSERT_EQ(2, tt.GetHeight());
}

TEST(TableTreeAVL, tt_bigbalance_on_remove_works_fine)
{
	TableTreeAVL tt;
	Polynomial p;
	tt.Insert("c", p);
	tt.Insert("b", p);
	tt.Insert("f", p);
	tt.Insert("a", p);
	tt.Insert("e", p);
	tt.Insert("g", p);
	tt.Insert("d", p);
	ASSERT_EQ(4, tt.GetHeight());
	tt.Remove("a");
	ASSERT_EQ(3, tt.GetHeight());
}

TEST(TableTreeAVL, tt_iterator_begin_and_iterator_end_equal)
{
	TableTreeAVL tt;

	ASSERT_NO_THROW(tt.begin());
	ASSERT_NO_THROW(tt.end());

	ASSERT_TRUE(tt.begin() == tt.end());
}

TEST(TableTreeAVL, tt_iterators_begin_and_end_works_fine)
{
	TableTreeAVL tt;
	Polynomial p;
	string name = "a";
	tt.Insert(name, p);
	ASSERT_NO_THROW(tt.begin());
	ASSERT_NO_THROW(tt.end());

	ASSERT_FALSE(tt.begin() == tt.end());
	ASSERT_TRUE(++tt.begin() == tt.end());
	ASSERT_EQ((*tt.begin()).GetName(), name);
}
	
TEST(TableTreeAVL, tt_iterators_operator_increment_works_fine_one_time)
{
	TableTreeAVL tt;
	Polynomial p;
	string name = "a";
	tt.Insert(name, p);
	ASSERT_TRUE(++tt.begin() == tt.end());
}

TEST(TableTreeAVL, tt_iterators_works_fine_several_times)
{
	TableTreeAVL tt;
	Polynomial p;
	const int count = 10;
	int a[count]{ 1,2,3,6,4,5,7,0,8,9 };
	for (int i = 0; i < count; i++)
	{
		tt.Insert(to_string(a[i]), p);
	}

	sort(a, a + count);

	int x = 0;
	for (Table::iterator it = tt.begin(); it != tt.end(); it++)
	{
		ASSERT_EQ((*it).GetName(), to_string(a[x]));
		x++;
	}
	ASSERT_EQ(x, count);

}