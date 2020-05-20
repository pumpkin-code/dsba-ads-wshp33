#ifndef  _DICTIONARY_H_ 
#define  _DICTIONARY_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>
#include  <stdlib.h>

#include  "hashset.h"


class HashFunction {
public:
    unsigned int operator()(const std::string& s)  const
    {
        
        // Complete definition
        
    }
};

class Equality {
public:
    //Equality() {}
    bool operator()(const std::string& a, const std::string& b)  const
    {
        return  (a == b);
    }
};

class Dictionary:
        public HashSet<std::string, HashFunction, Equality>
{
    // Complete definition
public:
    Dictionary(const std::string& filename);

};

#endif // _DICTIONARY_H_
