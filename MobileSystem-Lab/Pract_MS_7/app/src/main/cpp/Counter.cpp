//
// Created by alexs on 30.04.2021.
//

#include "Counter.h"

Counter::Counter()
{
	count = 0;
}

Counter::Counter(int _count)
{
	count = _count;
}

int Counter::Increment()
{
	return ++count;
}

int Counter::Decrement()
{
	return --count;
}

int Counter::Reset()
{
	count = 0;
	return count;
}

int Counter::GetCount() const
{
	return count;
}

void Counter::SetCount(int newCount)
{
	count = newCount;
}

static Counter *counterObj = NULL;

extern "C"
{
    JNIEXPORT void JNICALL
    Java_com_example_pract_1ms_17_CounterActivity_Counter__(JNIEnv *env, jobject thiz) {
        counterObj = new Counter();
    }

    JNIEXPORT void JNICALL
    Java_com_example_pract_1ms_17_CounterActivity_Counter__I(JNIEnv *env, jobject thiz, jint count) {
        counterObj = new Counter((int) count);
    }

    JNIEXPORT jint JNICALL
    Java_com_example_pract_1ms_17_CounterActivity_Increment(JNIEnv *env, jobject thiz) {
        return jint(counterObj->Increment());
    }

    JNIEXPORT jint JNICALL
    Java_com_example_pract_1ms_17_CounterActivity_Decrement(JNIEnv *env, jobject thiz) {
        return jint(counterObj->Decrement());
    }

    JNIEXPORT jint JNICALL
    Java_com_example_pract_1ms_17_CounterActivity_Reset(JNIEnv *env, jobject thiz) {
        return jint(counterObj->Reset());
    }

    JNIEXPORT jint JNICALL
    Java_com_example_pract_1ms_17_CounterActivity_GetCount(JNIEnv *env, jobject thiz) {
        return jint(counterObj->GetCount());
    }

    JNIEXPORT void JNICALL
    Java_com_example_pract_1ms_17_CounterActivity_SetCount(JNIEnv *env, jobject thiz, jint new_count) {
        counterObj->SetCount((int) new_count);
    }
}
