#include "TJobStream.h"
#include "TJobStream.cpp"
#include <gtest.h>


//test create
TEST(TJobStream, can_create_object)
{
	TClasster classt(3);
	
	ASSERT_NO_THROW(TJobStream p(0.1, classt, 6));
}

//test create job
TEST(TJobStream, can_get_new_job)
{
	TClasster classt(3);

	TJobStream p(0.1, classt, 6);
	ASSERT_NO_THROW(p.GetNewJob());
}
