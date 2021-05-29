#pragma once
#include "gtest/gtest.h"
#include "../Tables/ArraySortTable.h"

using namespace std;

TEST(ArraySortTable, can_default_constructor)
{
	ASSERT_NO_THROW(ArraySortTable arT);
}
TEST(ArraySortTable, can_set_start_size)
{
	ASSERT_NO_THROW(ArraySortTable arT(5));
}

TEST(ArraySortTable, can_insert)
{
	ArraySortTable arT;
	Polynomial poly;

	ASSERT_NO_THROW(arT.Insert("rdd", poly));
}
TEST(ArraySortTable, cant_insert_with_exist_name)
{
	ArraySortTable arT;
	Polynomial poly, poly2;

	arT.Insert("rdd", poly);
	
	ASSERT_ANY_THROW(arT.Insert("rdd", poly2));
}


TEST(ArraySortTable, can_remove_on_name)
{
	ArraySortTable arT;
	Polynomial poly;

	arT.Insert("rdd", poly);
	ASSERT_NO_THROW(arT.Remove("rdd"));
}
TEST(ArraySortTable, cant_remove_if_name_not_exist)
{
	ArraySortTable arT;
	Polynomial poly;

	ASSERT_ANY_THROW(arT.Remove("rdd"));
	
	arT.Insert("rdd", poly);
	
	ASSERT_ANY_THROW(arT.Remove("bcd"));
}
TEST(ArraySortTable, can_remove_for_any_pos)
{
	ArraySortTable arT;
	Polynomial poly;

	arT.Insert("rdd", poly);
	arT.Insert("bdd", poly);
	arT.Insert("edc", poly);
	arT.Insert("dgt", poly);
	arT.Insert("efr", poly);
	
	ASSERT_NO_THROW(arT.Remove("bdd"));
	ASSERT_NO_THROW(arT.Remove("dgt"));
	ASSERT_NO_THROW(arT.Remove("rdd"));
}

TEST(ArraySortTable, can_find_exist_value)
{
	ArraySortTable arT;
	std::string str = "3xyz";
	Monomial m(str);
	Polynomial poly;
	poly += m;

	arT.Insert("rdd", poly);

	ASSERT_NE(arT.Find("rdd"), nullptr);
	string nn = arT.Find("rdd")->ToStr();
	ASSERT_EQ(nn, poly.ToStr());
}
TEST(ArraySortTable, cant_find_not_exist_value)
{
	ArraySortTable arT;
	Polynomial poly;

	ASSERT_EQ(arT.Find("rdd"), nullptr);
	
	arT.Insert("rdd", poly);
	
	ASSERT_EQ(arT.Find("b"), nullptr);
}

TEST(ArraySortTable, can_replace)
{
	ArraySortTable arT;
	
	std::string str = "4xyz";
	std::string str2 = "xz^3";
	Monomial mon(str);
	Monomial mon2(str2);
	Polynomial poly, poly2;
	poly += mon;
	poly2 += mon2;

	arT.Insert("rdd", poly);

	ASSERT_NO_THROW(arT.Replace("rdd", poly2));

	string nn = arT.Find("rdd")->ToStr();
	ASSERT_EQ(nn, poly2.ToStr());
}

TEST(ArraySortTable, get_count)
{
	ArraySortTable arT;
	Polynomial poly;

	ASSERT_EQ(arT.GetCount(), 0);
	arT.Insert("rdd", poly);
	ASSERT_EQ(arT.GetCount(), 1);
	arT.Insert("edb", poly);
	arT.Insert("crf", poly);
	arT.Remove("rdd");
	ASSERT_EQ(arT.GetCount(), 2);
}
TEST(ArraySortTable, check_Empty)
{
	ArraySortTable arT;
	Polynomial poly;

	ASSERT_TRUE(arT.IsEmpty());
	
	arT.Insert("rdd", poly);
	
	ASSERT_FALSE(arT.IsEmpty());
	
	arT.Remove("rdd");
	
	ASSERT_TRUE(arT.IsEmpty());
}

TEST(ArraySortTable, insert_on_sort)
{
	ArraySortTable arT;
	Polynomial poly;

	arT.Insert("ac", poly);
	arT.Insert("bb", poly);
	arT.Insert("bc", poly);
	arT.Insert("dd", poly);
	arT.Insert("aa", poly);

	ASSERT_EQ(arT.GetName(0), "aa");
	ASSERT_EQ(arT.GetName(1), "ac");
	ASSERT_EQ(arT.GetName(2), "bb");
	ASSERT_EQ(arT.GetName(3), "bc");
	ASSERT_EQ(arT.GetName(4), "dd");

}

TEST(ArraySortTable, throw_if_uncorrect_position)
{
	ArraySortTable arT;
	Polynomial poly;

	arT.Insert("ac", poly);
	arT.Insert("bb", poly);
	arT.Insert("bc", poly);
	arT.Insert("dd", poly);
	arT.Insert("aa", poly);

	ASSERT_ANY_THROW(arT.GetName(-1));
	ASSERT_ANY_THROW(arT.GetName(arT.GetCount() + 1));

}