#include "TQueue.h"
#include <gtest.h>
#include <clocale>

//test create
TEST(TQueue, can_create_queue_with_positive_length)
{
	ASSERT_NO_THROW(TQueue<int> quI(5));
	ASSERT_NO_THROW(TQueue<double> quD(5));
	ASSERT_NO_THROW(TQueue<char> quC(5));
}

TEST(TQueue, if_size_queue_negative_size_1)
{
	TQueue<int> quI(-5);

	EXPECT_EQ(quI.GetSize(), 1);
}

TEST(TQueue, if_size_queue_zero_size_1)
{
	TQueue<int> quI(0);

	EXPECT_EQ(quI.GetSize(), 1);
}

TEST(TQueue, if_size_queue_too_large_size_MaxSize)
{
	TQueue<int> quI(MaxMemSize + 1);
	EXPECT_EQ(quI.GetSize(), MaxMemSize);
}

//test push
TEST(TQueue, can_push_to_queue)
{
	TQueue<int> qu(2);

	ASSERT_NO_THROW(qu.Push(2));
	ASSERT_NO_THROW(qu.Push(-2));
	EXPECT_EQ(-2, qu.GetTopElem());
}

TEST(TQueue, throw_when_push_to_full_queue)
{
	TQueue<int> qu(3);
	
	qu.Push(3);
	qu.Push(4);
	qu.Push(5);

	ASSERT_ANY_THROW(qu.Push(6));

}

TEST(TQueue, can_push_when_low_larger_top)
{
	TQueue<int> qu(3);
	
	qu.Push(3);
	qu.Push(4);
	qu.Push(5);
	qu.Pop();

	ASSERT_NO_THROW(qu.Push(1));
	EXPECT_EQ(1, qu.GetTopElem());
	EXPECT_EQ(4, qu.GetLowElem());
}
//test pop
TEST(TQueue, can_pop_from_queue)
{
	TQueue<int> qu(5);
	
	qu.Push(2);
	qu.Push(3);

	EXPECT_EQ(2, qu.Pop());
	EXPECT_EQ(3, qu.Pop());
}

TEST(TQueue, throw_when_pop_from_empty_queue)
{
	TQueue<int> qu(3);

	ASSERT_ANY_THROW(qu.Pop());
}

//test get
TEST(TQueue, can_get_elem_by_index)
{
	TQueue<int> qu(5);
	
	for (int i = 0; i < 5; i++)
		qu.Push(i);
	
	EXPECT_EQ(0, qu.GetElemByIndex(0));
	EXPECT_EQ(4, qu.GetElemByIndex(4));
}
TEST(TQueue, can_get_low_elem)
{
	TQueue<int> qu(4);
	
	qu.Push(6);

	EXPECT_EQ(6, qu.GetLowElem());
}

TEST(TQueue, throw_when_get_in_empty_queue)
{
	TQueue<int> qu(4);

	ASSERT_ANY_THROW(qu.GetLowElem());
}

TEST(TQueue, can_get_size)
{
	TQueue<int> qu(5);
	
	EXPECT_EQ(5, qu.GetSize());
}

TEST(TQueue, can_get_count_elem)
{
	TQueue<int> qu(5);
	
	for (int i = 0; i < 4; i++)
		qu.Push(i);
	
	EXPECT_EQ(4, qu.GetCountElem());
}

TEST(TQueue, can_get_low_and_top_index)
{
	TQueue<int> qu(5);
	
	for (int i = 0; i < 5; i++)
		qu.Push(i);

	EXPECT_EQ(0, qu.GetLowIndex());
	EXPECT_EQ(4, qu.GetTopIndex());
}

TEST(TQueue, can_get_next_and_prev_index)
{
	TQueue<int> qu(5);
	
	int i = 4;
	int j = 4;
	
	qu.GetNextIndex(&i);
	qu.GetPrevIndex(&j);
	
	EXPECT_EQ(0, i);
	EXPECT_EQ(3, j);
	
}

//test empty
TEST(TQueue, check_empty)
{
	TQueue<int> qu(4);
	
	EXPECT_EQ(true, qu.IsEmpty());
	
	qu.Push(4);
	
	EXPECT_EQ(false, qu.IsEmpty());
}

//test full
TEST(TQueue, check_full)
{
	TQueue<int> qu(2);
	
	EXPECT_EQ(false, qu.IsFull());
	
	qu.Push(4);
	qu.Push(3);
	
	EXPECT_EQ(true, qu.IsFull());
}

//test swap
TEST(TQueue, swap)
{
	TQueue<int> qu(5);
	
	for (int i = 0; i < 5; i++)
		qu.Push(i);
	
	qu.swap(0, 4);
	
	EXPECT_EQ(4, qu.GetElemByIndex(0));
	EXPECT_EQ(0, qu.GetElemByIndex(4));
}