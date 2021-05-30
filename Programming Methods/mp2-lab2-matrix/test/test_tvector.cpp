#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> v(5);
	v[0] = 1;
	v[1] = -5;
	v[2] = 6;
	v[3] = 2;
	v[4] = -1;

	TVector<int> vCopy(v);
	
	EXPECT_EQ(1, vCopy[0]);
	EXPECT_EQ(-5, vCopy[1]);
	EXPECT_EQ(6, vCopy[2]);
	EXPECT_EQ(2, vCopy[3]);
	EXPECT_EQ(-1, vCopy[4]);

}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> v(5);
	v[0] = 5;
	v[1] = -3;
	v[2] = -4;
	v[3] = 1;
	v[4] = 4;
	
	TVector<int> vCopy(v);
	
	EXPECT_NE(&v[0], &vCopy[0]);
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(4);

	EXPECT_ANY_THROW(v[-2]);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(4);

	EXPECT_ANY_THROW(v[5]);
}

TEST(TVector, can_assign_vector_to_itself)
{
	const int size = 5;
	TVector<int> v(size);

	v[0] = -1;
	v[1] = 3;
	v[2] = -4;
	v[3] = 7;

	ASSERT_NO_THROW(v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	const int size = 4;
	TVector<int> v(size);
	TVector<int> vCopy(size);
	v[0] = -1;
	v[1] = -3;
	v[2] = 3;
	v[3] = 9;

	EXPECT_NO_THROW(vCopy = v);
	
	EXPECT_EQ(v[0], vCopy[0]);
	EXPECT_EQ(v[1], vCopy[1]);
	EXPECT_EQ(v[2], vCopy[2]);
	EXPECT_EQ(v[3], vCopy[3]);
}

TEST(TVector, assign_operator_change_vector_size)
{
	const int size1 = 4, size2 = 8;
	TVector<int> v(size1);
	TVector<int> vCopy(size2);

	v[0] = 3;
	v[1] = -4;
	v[2] = 6;
	v[3] = -11;
	vCopy = v;
	
	EXPECT_EQ(size1, v.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	const int size1 = 4, size2 = 8;
	TVector<int> v(size1);
	TVector<int> vCopy(size2);
	
	v[0] = 3;
	v[1] = -4;
	v[2] = 6;
	v[3] = -11;
	vCopy = v;

	EXPECT_EQ(v, vCopy);

}

TEST(TVector, compare_equal_vectors_return_true)
{
	const int size = 5;
	TVector<int> v(size);
	TVector<int> vCompare(size);
	
	v[0] = 1;
	v[1] = -3;
	v[2] = 5;
	v[3] = 9;
	v[4] = -1;
	vCompare = v;

	EXPECT_TRUE(vCompare == v);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	const int size = 5;
	TVector<int> v(5);
	
	v[0] = 1;
	v[1] = -3;
	v[2] = 5;
	v[3] = 9;
	v[4] = -1;

	EXPECT_TRUE(v == v);
	}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	const int size1 = 5, size2 = 3;
	TVector<int> v(size1);
	TVector<int> vCompare(size2);
	
	EXPECT_FALSE(v == vCompare);
}

TEST(TVector, can_add_scalar_to_vector)
{
	const int size = 4;
	TVector<int> v(size);
	
	v[0] = 2;
	v[1] = -1;
	v[2] = 4;
	v[3] = -5;
	
	EXPECT_NO_THROW(v + 3);

	v = v + 3;

	EXPECT_EQ(5, v[0]);
	EXPECT_EQ(2, v[1]);
	EXPECT_EQ(7, v[2]);
	EXPECT_EQ(-2, v[3]);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	const int size = 4;
	TVector<int> v(size);
	
	v[0] = 2;
	v[1] = -1;
	v[2] = 4;
	v[3] = -5;
	
	EXPECT_NO_THROW(v - 3);

	v = v - 3; 

	EXPECT_EQ(-1, v[0]);
	EXPECT_EQ(-4, v[1]);
	EXPECT_EQ(1, v[2]);
	EXPECT_EQ(-8, v[3]);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	const int size = 4;
	TVector<int> v(size);
	
	v[0] = 2;
	v[1] = -1;
	v[2] = 4;
	v[3] = 3;

	EXPECT_NO_THROW(v * 3);

	v = v * 3;

	EXPECT_EQ(6, v[0]);
	EXPECT_EQ(-3, v[1]);
	EXPECT_EQ(12, v[2]);
	EXPECT_EQ(9, v[3]);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	const int size = 4;
	TVector<int> v(size);
	TVector<int> v2(size);
	
	v[0] = 2;
	v[1] = 3;
	v[2] = -5;
	v[3] = 1;

	v2[0] = -3;
	v2[1] = 5;
	v2[2] = -1;
	v2[3] = 2;

	EXPECT_NO_THROW(v + v2);

	TVector<int> vSum(size);
	vSum = v + v2;

	EXPECT_EQ(-1, vSum[0]);
	EXPECT_EQ(8, vSum[1]);
	EXPECT_EQ(-6, vSum[2]);
	EXPECT_EQ(3, vSum[3]);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	const int size1 = 3, size2 = 2;
	TVector<int> v(size1), v2(size2);

	ASSERT_ANY_THROW(v + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	const int size1 = 4;
	TVector<int> v(size1);
	TVector<int> v2(size1);
	
	v[0] = 2;
	v[1] = 3;
	v[2] = -5;
	v[3] = 1;

	v2[0] = -3;
	v2[1] = 5;
	v2[2] = -1;
	v2[3] = 2;
	
	EXPECT_NO_THROW(v - v2);

	TVector<int> vSub(size1);
	vSub = v - v2;

	EXPECT_EQ(5, vSub[0]);
	EXPECT_EQ(-2, vSub[1]);
	EXPECT_EQ(-4, vSub[2]);
	EXPECT_EQ(-1, vSub[3]);
}
TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	const int size1 = 3, size2 = 2;
	TVector<int> v(size1), v2(size2);

	ASSERT_ANY_THROW(v - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	const int size1 = 4;
	TVector<int> v(size1);
	TVector<int> v2(size1);
	
	v[0] = 2;
	v[1] = 1;
	v[2] = -4;
	v[3] = -1;

	v2[0] = -1;
	v2[1] = 5;
	v2[2] = 2;
	v2[3] = -2;

	EXPECT_NO_THROW(v * v2);

	TVector<int> vMul(size1);
	int c = v * v2;

	EXPECT_EQ(-3, c);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	const int size1 = 3, size2 = 2;
	TVector<int> v(size1), v2(size2);

	ASSERT_ANY_THROW(v * v2);
}

