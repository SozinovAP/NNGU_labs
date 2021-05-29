#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	const int size = 5;
	TMatrix<int> m(size);
	TMatrix<int> mCopy(m);

	EXPECT_EQ(m, mCopy);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	const int size = 5;
	TMatrix<int> m(size);
	TMatrix<int> mCopy(m);

	EXPECT_NE(&m[0], &mCopy[0]);
}

TEST(TMatrix, can_get_size)
{
	const int size = 5;
	TMatrix<int> m(size);

	EXPECT_EQ(size, m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	const int size = 5;
	TMatrix<int> m(size);

	ASSERT_NO_THROW(m[0][0] = -2);

	m[1][1] = 4;

	EXPECT_EQ(4, m[1][1]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	const int size = 5;
	TMatrix<int> m(size);

	ASSERT_ANY_THROW(m[-1][-1] = -2);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	const int size = 5;
	TMatrix<int> m(size);

	ASSERT_ANY_THROW(m[3][6] = -2);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	const int size = 2;
	TMatrix<int> m(size);

	m[0][0] = 2;
	m[0][1] = 5;
	m[1][1] = -5;

	ASSERT_NO_THROW(m = m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	const int size = 2;
	TMatrix<int> m(size);
	TMatrix<int> mCopy(size);

	m[0][0] = -2;
	m[0][1] = 4;
	m[1][1] = -5;

	ASSERT_NO_THROW(mCopy = m);


	EXPECT_EQ(m[0][0], mCopy[0][0]);
	EXPECT_EQ(m[0][1], mCopy[0][1]);
	EXPECT_EQ(m[1][1], mCopy[1][1]);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	const int size1 = 2, size2 = 3;
	TMatrix<int> m(size1);
	TMatrix<int> mCopy(size2);

	m[0][0] = -2;
	m[0][1] = 6;
	m[1][1] = -3;
	mCopy = m;

	EXPECT_EQ(size1, mCopy.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	const int size1 = 2, size2 = 3;
	TMatrix<int> m(size1);
	TMatrix<int> mCopy(size2);

	m[0][0] = 3;
	m[0][1] = -4;
	m[1][1] = 3;
	mCopy = m;

	EXPECT_EQ(m, mCopy);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	const int size = 2;
	TMatrix<int> m(size);
	TMatrix<int> mCompare(size);

	m[0][0] = -2;
	m[0][1] = 6;
	m[1][1] = 4;
	mCompare = m;

	EXPECT_TRUE(mCompare == m);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	const int size = 2;
	TMatrix<int> m(size);

	m[0][0] = -2;
	m[0][1] = 6;
	m[1][1] = 4;

	EXPECT_TRUE(m == m);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	const int size1 = 5, size2 = 3;
	TMatrix<int> m(size1);
	TMatrix<int> mCompare(size2);

	EXPECT_FALSE(m == mCompare);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	const int size = 2;
	TMatrix<int> m(size);
	TMatrix<int> mAdd(size);

	m[0][0] = -2;
	m[0][1] = 6;
	m[1][1] = 3;

	mAdd[0][0] = -1;
	mAdd[0][1] = -4;
	mAdd[1][1] = 2;

	EXPECT_NO_THROW(m + mAdd);

	TMatrix<int> mSum(size);

	mSum = m + mAdd;

	EXPECT_EQ(-3, mSum[0][0]);
	EXPECT_EQ(2, mSum[0][1]);
	EXPECT_EQ(5, mSum[1][1]);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	const int size1 = 3, size2 = 2;
	TMatrix<int> m(size1), m2(size2);

	ASSERT_ANY_THROW(m + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	const int size = 2;
	TMatrix<int> m(size);
	TMatrix<int> m2(size);

	m[0][0] = -2;
	m[0][1] = 6;
	m[1][1] = 3;

	m2[0][0] = -1;
	m2[0][1] = -4;
	m2[1][1] = 2;

	EXPECT_NO_THROW(m - m2);

	TMatrix<int> mSub(size);

	mSub = m - m2;

	EXPECT_EQ(-1, mSub[0][0]);
	EXPECT_EQ(10, mSub[0][1]);
	EXPECT_EQ(1, mSub[1][1]);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	const int size1 = 3, size2 = 2;
	TMatrix<int> m(size1), m2(size2);

	ASSERT_ANY_THROW(m - m2);
}

