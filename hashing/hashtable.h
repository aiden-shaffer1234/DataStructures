#ifndef HASH_TBL
#define HASH_TBL

#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>


// used when improper size is given (for example
// size is 0 or negatiave)

namespace cop4530 {

static const unsigned int default_capacity = 11;
static const unsigned int max_prime = 1301081;

template <typename T>
class HashTable {


    public:
        HashTable(size_t size = 101);
        ~HashTable();
        bool contains(const T &x);
        bool insert(const T & x);
        bool insert (T &&x);
        bool remove(const T &x);
        void clear();
        bool load(const char *filename);
        void dump();
        bool write_to_file(const char *filename);
	size_t size();
    private:

        unsigned long prime_below(long);
        void setPrimes(std::vector<long> &);
        void makeEmpty();
        void rehash();
        size_t myhash(const T &x);

        std::vector<std::list<T>> theLists; 
        size_t currentSize;
};

#include "hashtable.hpp"
}
#endif
