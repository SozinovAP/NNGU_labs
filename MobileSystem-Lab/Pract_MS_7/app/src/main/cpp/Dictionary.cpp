//
// Created by alexs on 01.05.2021.
//

#include "Dictionary.h"
#include "Tools.h"

Dictionary::Dictionary()
{
    dictionary = std::vector<std::string>();
}

Dictionary::Dictionary(std::vector<std::string>& _dictionary)
{
    dictionary = _dictionary;
}

void Dictionary::Add(std::string& word)
{
    if (word.empty())
        return;
    dictionary.push_back(word);
}

void Dictionary::Add(int index, std::string& word)
{
    if (word.empty())
        return;
    if (index < 0 || index >= dictionary.size())
        return;

    dictionary.insert(dictionary.begin() + index, word);
}

void Dictionary::Remove()
{
    if (dictionary.empty())
        return;
    dictionary.pop_back();
}

void Dictionary::Remove(int index)
{
    if (index < 0 || index >= dictionary.size())
        return;

    dictionary.erase(dictionary.begin() + index);
}

std::string Dictionary::GetByIndex(int index)
{
    if (index < 0 || index >= dictionary.size())
        return std::string();

    return dictionary[index];
}

std::string Dictionary::GetDictionary()
{
    if (dictionary.empty())
        return std::string();

    std::string str;
    for (int ind = 0; ind < dictionary.size() - 1; ++ind)
    {
        str += dictionary[ind] + ", ";
    }
    str += dictionary[dictionary.size() - 1];

    str[0] = std::toupper(str[0]);
    return str;
}

static Dictionary *dictionaryObj = nullptr;

extern "C"
{
    JNIEXPORT void JNICALL
    Java_com_example_pract_1ms_17_DictionaryActivity_Dictionary__(JNIEnv *env, jobject thiz) {
        dictionaryObj = new Dictionary();
    }

    JNIEXPORT void JNICALL
    Java_com_example_pract_1ms_17_DictionaryActivity_Dictionary__Ljava_util_ArrayList_2(JNIEnv *env,
            jobject thiz,
            jobject _dictionary) {
        std::vector<std::string> res = Tools::ArrayListToStdVector(env, _dictionary);
        dictionaryObj = new Dictionary(res);
    }

    JNIEXPORT void JNICALL
    Java_com_example_pract_1ms_17_DictionaryActivity_Add__ILjava_lang_String_2(JNIEnv *env,
            jobject thiz, jint index,
            jstring word) {
        std::string stdWord = Tools::JstringToString(env, word);
        dictionaryObj->Add((int)index, stdWord);
    }

    JNIEXPORT void JNICALL
    Java_com_example_pract_1ms_17_DictionaryActivity_Add__Ljava_lang_String_2(JNIEnv *env, jobject thiz,
            jstring word) {
        std::string stdWord = Tools::JstringToString(env, word);
        dictionaryObj->Add(stdWord);
    }

    JNIEXPORT void JNICALL
    Java_com_example_pract_1ms_17_DictionaryActivity_Remove__(JNIEnv *env, jobject thiz) {
        dictionaryObj->Remove();
    }

    JNIEXPORT void JNICALL
    Java_com_example_pract_1ms_17_DictionaryActivity_Remove__I(JNIEnv *env, jobject thiz, jint index) {
        dictionaryObj->Remove((int)index);
    }

    JNIEXPORT jbyteArray  JNICALL
    Java_com_example_pract_1ms_17_DictionaryActivity_GetByIndex(JNIEnv *env, jobject thiz, jint index) {
        std::string word = dictionaryObj->GetByIndex((int)index);
        return Tools::StringToJByteArray(env, word);
    }

    JNIEXPORT jbyteArray  JNICALL
    Java_com_example_pract_1ms_17_DictionaryActivity_GetDictionary(JNIEnv *env, jobject thiz) {
        std::string word = dictionaryObj->GetDictionary();
        return Tools::StringToJByteArray(env, word);
    }
}


