//
// Created by alexs on 30.04.2021.
//

#ifndef PRACT_MS_7_COUNTER_H
#define PRACT_MS_7_COUNTER_H


#include <cstdint>
#include "jni.h"

class Counter
{
private:
	int count;
public:
	Counter();
	Counter(int count);
	int Increment();
	int Decrement();
	int Reset();
	int GetCount() const;
	void SetCount(int newCount);
};



#endif //PRACT_MS_7_COUNTER_H
