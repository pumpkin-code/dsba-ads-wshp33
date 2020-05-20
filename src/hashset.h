// template hash set class

#ifndef  _HASHSET_H_ 
#define  _HASHSET_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

//using namespace std;

template<class TKey, class THashFunc, class TKeyEqual>
class HashSet {
public:
    // hashtable entries
    class Entry {
        public:
        TKey key;
        bool used;
        // TODO: consider to add "removed" field

        Entry() : used(false) {}
    };

protected:
    int _entries;               ///< number of entries
    int _prime;                 ///< index to size table

    std::vector<Entry>* _ht;    ///< Stores a hashtable.
    THashFunc _hf;              ///< hash function on TKey
    TKeyEqual _eq;              ///< equality predicate on TKey

    int getTableSize()  const { return prime_list[_prime]; }
    double getLoadFactor() const { return double(size()) / getTableSize(); }


    //int resize();
    int resize()
    {
        if (_prime == num_primes - 1)
        {
            std::cerr << "maximal table size reached, aborting ...\n";
            exit(2);
        }

        int mm = prime_list[_prime];
        ++_prime;
        int m = prime_list[_prime];

        std::vector<Entry>* ptr = new std::vector<Entry>(m);

        for (int i = 0; i < mm; ++i)
        {
            if ((*_ht)[i].used) {
                TKey kk = (*_ht)[i].key;

                int p = _hf(kk) % m;

                while (p < m && (*ptr)[p].used)
                    ++p;

                if (p == m)
                    p = 0;

                while ((*ptr)[p].used)
                    ++p;

                (*ptr)[p].key = kk;
                (*ptr)[p].used = true;
            }
        }
        delete _ht;
        _ht = ptr;

        return  m;
    }

public:

    // we do not compute prime numbers but use a table instead
    static const int num_primes = 25;
    //static const unsigned long prime_list[];
    const unsigned long prime_list[num_primes] =
            {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
             196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
             50331653, 100663319, 201326611, 402653189, 805306457};

    HashSet()
        : _entries(0)
        , _prime(0)
        , _ht(new std::vector<Entry>(prime_list[0]))
    {
    }

    virtual ~HashSet()
    {
        delete _ht;
    }

    virtual int size() const { return _entries; }

    // virtual bool search(const key_type& k)
    virtual bool search(const TKey& k)
    {
        int p = _hf(k) % getTableSize();

        while ((*_ht)[p].used)
        {
            if (_eq((*_ht)[p].key, k))    // equality predicate for key_type
                return true;

            ++p;
            if (p == getTableSize())      // wrap around to beginning
                p = 0;
        }
        return false;
    }

    virtual void insert(const TKey& k)
    {
        // TODO: Implement the method
    }

    virtual void remove(const TKey& k)
    {
        // TODO: Implement the method
    }
}; // class HashSet


#endif
