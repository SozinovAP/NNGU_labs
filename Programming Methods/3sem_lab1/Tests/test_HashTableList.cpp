#pragma once
#include "gtest/gtest.h"
#include "../Tables/HashTableList.h"

TEST(HashTableList, can_default_constructor)
{
	ASSERT_NO_THROW(HashTableList arT);
}
TEST(HashTableList, can_set_start_size)
{
	ASSERT_NO_THROW(HashTableList arT(5));
}

TEST(HashTableList, can_insert)
{
	HashTableList arT;
	Polynomial poly;

	ASSERT_NO_THROW(arT.Insert("rdd", poly));
}
TEST(HashTableList, cant_insert_with_exist_name)
{
	HashTableList arT;
	Polynomial poly, poly2;

	arT.Insert("rdd", poly);
	
	ASSERT_ANY_THROW(arT.Insert("rdd", poly2));
}


TEST(HashTableList, can_remove_on_name)
{
	HashTableList arT;
	Polynomial poly;


	arT.Insert("rdd", poly);
	
	ASSERT_NO_THROW(arT.Remove("rdd"));
}
TEST(HashTableList, cant_remove_if_name_not_exist)
{
	HashTableList arT;
	Polynomial poly;

	ASSERT_ANY_THROW(arT.Remove("rdd"));
	
	arT.Insert("rdd", poly);
	
	ASSERT_ANY_THROW(arT.Remove("b"));
}
TEST(HashTableList, can_remove_for_any_pos)
{
	HashTableList arT;
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

TEST(HashTableList, can_find_exist_value)
{
	HashTableList arT;
	std::string str = "3xyz";
	Monomial m(str);
	Polynomial poly;
	poly += m;

	arT.Insert("rdd", poly);

	ASSERT_NE(arT.Find("rdd"), nullptr);
	string nn = arT.Find("rdd")->ToStr();
	ASSERT_EQ(nn, poly.ToStr());
}
TEST(HashTableList, cant_find_not_exist_value)
{
	HashTableList arT;
	Polynomial poly;

	ASSERT_EQ(arT.Find("rdd"), nullptr);
	
	arT.Insert("rdd", poly);
	
	ASSERT_EQ(arT.Find("b"), nullptr);
}

TEST(HashTableList, can_replace)
{
	HashTableList arT;
	
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

TEST(HashTableList, get_count)
{
	HashTableList arT;
	Polynomial poly;

	ASSERT_EQ(arT.GetCount(), 0);
	arT.Insert("rdd", poly);
	ASSERT_EQ(arT.GetCount(), 1);
	arT.Insert("edb", poly);
	arT.Insert("crf", poly);
	arT.Remove("rdd");
	ASSERT_EQ(arT.GetCount(), 2);
}
TEST(HashTableList, check_Empty)
{
	HashTableList arT;
	Polynomial poly;

	ASSERT_TRUE(arT.IsEmpty());
	arT.Insert("rdd", poly);
	ASSERT_FALSE(arT.IsEmpty());
	arT.Remove("rdd");
	ASSERT_TRUE(arT.IsEmpty());
}
