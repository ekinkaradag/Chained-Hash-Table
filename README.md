
# Chained Hash Table Data Structure
This is my Data Structures and Algorithms (C++) 2018-2019 fall term project. We were expected to write a C++ console application which reads a .csv text file that consists of 1.6M tweets and then prints out the top 10 most frequent words in the tweets. We had to exclude stop words which is used very often in daily life (i.e. a, an, the, like). 30% of the project's grade was given for the execution time, so I had to implement the program with a minimal time complexity.

I used Visual Studio with C++ to compile, but any other compiler can be used to implement the source code.

<hr />

### Used Libraries

```cpp
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono> // to measure the elapsed time
```

<br />
<hr />

### Getting The Stop Words

- The program starts with reading the stopwords.txt file which consists of stop words at every line. [Stop words can be found here](https://www.link-assistant.com/seo-stop-words.html)
- Then, it indexes the starting points of word's first letters (e.g. starting point index of the stop words that start with letter a is 0, for b 61, for c 89 and so on).
- Indexing point helps the program to decrease the time to search the word in the stop words array.
- Program will only search the stop words between the starting index and until the next one (e.g. if the program wants to search the words that start with letter b it would search from stopWords[61] to stopWords[89])
- I created a virtual ending point because if z is the starting letter, it would not now when to stop.
<p align="center">
<a href="https://github.com/ekinkaradag/Chained-Hash-Table/blob/master/Report%20Images/Stop-Words-Array.png">
<img src="https://github.com/ekinkaradag/Chained-Hash-Table/blob/master/Report%20Images/Stop-Words-Array.png" width="500">
</a>
</p>

```cpp
firsLetterLocation[0] == 0						// a
firsLetterLocation[1] == 61						// b
firsLetterLocation[2] == 89						// c
firsLetterLocation[25] == 657						// z
firsLetterLocation[26] == sizeof(stopWords) / sizeof(stopWords[0])	// 659 in this case
// All of the above will return true
```

<br />
<hr />

### Creating a Chained Hash Table

<a href="https://github.com/ekinkaradag/Chained-Hash-Table/blob/master/Report%20Images/Chained-Hash-Table.png">
<img align="right" src="https://github.com/ekinkaradag/Chained-Hash-Table/blob/master/Report%20Images/Chained-Hash-Table.png" width="320" />
</a>

- I've made a chained hash table from scratch to easily insert the words.
- The size of the hash table is defined in main(). I preferred to use the size 1000003 because it is a prime number, useful in modulus operations to differentiate the words’ locations(avoid collisions) and I found out that the total number of words to be inserted is 804718.
- Every point of the hash table consists of linked links. If there is more than one node on a specific location, I would have a collision which would slow down the searching process but I would be sure every "proper" word is counted.
- Linked lists consists of nodes which has the following elements;

```cpp
string word;
unsigned long count;
node *link;
```
<br />
<hr />

### Cleaning The Words

The program starts reading the test.csv file with ifstream

After program gets to the 6th comma separated “string” field in the current reading line from the file (tweet section from test.csv) and separates them into words, then it cleans the unnecessary characters from the words and organize them for insertion.

1. If the length of the word ever becomes or is already one character do nothing and go to the next word.
2. Erase every non-letter characters unless if it is apostrophe (' ).
3. If the apostrophe is in the beginning of the word, erase it.
4. After cleaning is done, make every letter lowercase for both searching for it in the stop words and the hash table.
5. Search the word in stop words between the indexes we created earlier.
6. If the stop word flag isn't raised, insert it(The word's count increment of already existing words will be handled in the insertNew function), otherwise skips to the next word.

<br />
<hr />

### Hash Table Function

<a href="https://github.com/ekinkaradag/Chained-Hash-Table/blob/master/Report%20Images/Chained-Hash-Table.png">
<img align="right" src="https://github.com/ekinkaradag/Chained-Hash-Table/blob/master/Report%20Images/Chained-Hash-Table.png" width="320" />
</a>

- I used the function below to insert the words into the most correct position possible with the help of prime numbers (to avoid collisions as much as possible).

```cpp
unsigned int loc = 6151; //prime number
const unsigned int x = 769; //prime number
for (unsigned int i = 0; i < word.length(); i++) {
	loc = x * loc + (word[i]);
}
loc = loc % bucketSize;
if (!table[loc].search(word)) { // If found, the word's count will increase
    table[loc].insertNew(word);
}
```

- If  the word is already in the list, search function increases the word’s count automatically. insertNew function adds the new word with count 1 to the beginning of the linked list.
- I did not use another function to get the hash key because it is unnecessary in this case and this is really easy to understand in my opinion.

<br />
<hr />

### Getting The Most Used Word From The Linked List

- Since both integer value “count” and string value “word” can’t be returned from a function, I used addressing in the function of the list.
- After getting the most used word and its count from the currently reading array, hash table’s displayMostUsed function stores them to local arrays if and only if the word’s count is greater than any other count in the local array.
- I didn’t have to sort the top 10 array in displayMostUsed function because it shifts the counts towards the end of the array, as the new values come in.

```cpp
void linkedlist::mostUsedInList(unsigned long *topCount, string *topWord) {
 unsigned long currentHigh = 0;
 node *temp = first;
 while (temp != NULL) { //search in the current list
     if (temp->wordCount > currentHigh) {
         currentHigh = temp->wordCount;
         *topWord = temp->data;
         *topCount = temp->wordCount;
     }
     temp = temp->link;
 }
 delete temp;
}
```

<br />
<hr />

### My Output

    good		89403
    day		84769
    today		64623
    love		63453
    work		62862
    time		56089
    lol		55159
    im		50156
    night		41383
    amp		40729
    
    Elapsed time: 9.73036 s

I ran the program on a laptop with a i7-7700Q CPU, DDR4 SODIMM 16GB(2x8GB) RAM and a 256GB NVMe SSD to get this running time.
