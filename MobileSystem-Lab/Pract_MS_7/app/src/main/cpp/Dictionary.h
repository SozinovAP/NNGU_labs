//
// Created by alexs on 01.05.2021.
//

#ifndef PRACT_MS_7_DICTIONARY_H
#define PRACT_MS_7_DICTIONARY_H

#include <cstdint>
#include "jni.h"
#include <vector>
#include <string>

class Dictionary
{
private:
    std::vector<std::string> dictionary;
public:
    Dictionary();
    Dictionary(std::vector<std::string>& _dictionary);

    void Add(std::string& word);
    void Add(int index, std::string& word);
    void Remove();
    void Remove(int index);
    std::string GetByIndex(int index);
    std::string GetDictionary();
};


#endif //PRACT_MS_7_DICTIONARY_H
