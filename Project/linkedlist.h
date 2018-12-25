#pragma once

#include <iostream>
#include <string>
using namespace std;

struct node
{
    unsigned long wordCount;
    string data;
    node *link;
};

class linkedlist {
    node *first, *last;
    
    int count;
public:
    linkedlist();
    int length()const;
    bool isEmptyList()const;
    bool search(string) const; //if Found it also increases the word count
    void insertNew(string);
    void mostUsedInList(unsigned long *topCount, string *topWord);
    ~linkedlist();
};
