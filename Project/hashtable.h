#include "linkedlist.h"

class Hash
{
    // Pointer to an array containing buckets
    linkedlist *table;
	unsigned int bucketSize;
public:
    Hash(const unsigned int x);
    ~Hash();
    // inserts a key into hash table
    void insertItem(string word);
    void displayMostUsed();
};
