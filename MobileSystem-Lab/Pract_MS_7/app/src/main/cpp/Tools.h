//
// Created by alexs on 01.05.2021.
//

#ifndef PRACT_MS_7_TOOLS_H
#define PRACT_MS_7_TOOLS_H

#include <cstdint>
#include "jni.h"
#include <vector>
#include <string>

class Tools {

public:
    static std::string JstringToString(JNIEnv *env, jstring jStr);

    static std::vector<std::string> ArrayListToStdVector(JNIEnv *env, jobject arrayList);

    static jobject StdVectorToArrayList(JNIEnv *env, std::vector<std::string>);

    static jbyteArray StringToJByteArray(JNIEnv * env, const std::string &nativeString);
};


#endif //PRACT_MS_7_TOOLS_H
