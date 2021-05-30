#include "TClasster.h"
#include "TClasster.cpp"
#include <gtest.h>


//test create
TEST(TClasster, can_create_object)
{
	ASSERT_NO_THROW(TClasster classt(6));
}

TEST(TClasster, if_uncorrect_countProc_set_countProc_1)
{
	TClasster classt(-6);
	
	EXPECT_EQ(1, classt.GetCountProc());
}

//test set
TEST(TClasster, can_set_priority)
{
	TClasster classt(3);

	ASSERT_NO_THROW(classt.SetPriority());
}

TEST(TClasster, can_set_lead_time)
{
	TClasster classt(3);

	ASSERT_NO_THROW(classt.SetLeadTime());
}



//test changeStatus
TEST(TClasster, can_change_status)
{
	TClasster classt(3);
	
	classt.ChangeStatusProc(0);
	classt.ChangeStatusProc(1);
	classt.ChangeStatusProc(1);

	EXPECT_EQ(false, classt.ThisProcIsFree(0));
	EXPECT_EQ(true, classt.ThisProcIsFree(1));
}

//test get

TEST(TClasster, can_check_Buzy_orFree_proc)
{
	TClasster classt(3);

	ASSERT_NO_THROW(classt.ThisProcIsFree(0));
}

TEST(TClasster, can_get_count_proc)
{
	TClasster classt(6);
	
	EXPECT_EQ(6, classt.GetCountProc());
}
TEST(TClasster, can_get_count_buzy_proc)
{
	TClasster classt(6);

	classt.ChangeStatusProc(0);
	classt.ChangeStatusProc(1);
	
	EXPECT_EQ(2, classt.GetCountBuzyProc());
}

TEST(TClasster, can_get_first_free_proc)
{
	TClasster classt(6);

	classt.ChangeStatusProc(0);
	classt.ChangeStatusProc(1);

	EXPECT_EQ(2, classt.BuzyProc());
}

TEST(TClasster, get_when_no_free_proc)
{
	TClasster classt(2);

	classt.ChangeStatusProc(0);
	classt.ChangeStatusProc(1);

	EXPECT_EQ(-1, classt.BuzyProc());
}