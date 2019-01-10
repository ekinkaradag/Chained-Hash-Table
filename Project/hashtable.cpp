#include "hashtable.h"

Hash::Hash(const unsigned int x) {
	bucketSize = x;
	table = new linkedlist[bucketSize];
}


Hash::~Hash() {
	delete[] table;
}


void Hash::insertItem(string word) {
	unsigned int loc = 6151; //prime number
	
	const unsigned int x = 769; //prime number

	for (unsigned int i = 0; i < word.length(); i++) {
		loc = x * loc + (word[i]);
	}
	loc = loc % bucketSize;
	
	if (!table[loc].search(word)) { // If found, the word's count will increase
		table[loc].insertNew(word);
	}
	
}


void Hash::displayMostUsed() {
	unsigned long topCounts[10] = { 0,0,0,0,0,0,0,0,0,0 };
	unsigned long tempTopCount = 0;
	string topWords[10];
	string tempTopWord;
	for (unsigned int i = 0; i < bucketSize; i++) {


		if (table[i].length() > 0) { // If we ever inserted any word to the currently reading linkedList
			table[i].mostUsedInList(&tempTopCount, &tempTopWord);

			//For top 10 insertion
			if (tempTopCount > topCounts[0]) {
				for (int j = 9; j > 0; j--) {
					topCounts[j] = topCounts[j - 1];
					topWords[j] = topWords[j - 1];
				}
				topCounts[0] = tempTopCount;
				topWords[0] = tempTopWord;
			}
			else if (tempTopCount > topCounts[1]) {
				for (int j = 9; j > 1; j--) {
					topCounts[j] = topCounts[j - 1];
					topWords[j] = topWords[j - 1];
				}
				topCounts[1] = tempTopCount;
				topWords[1] = tempTopWord;
			}
			else if (tempTopCount > topCounts[2]) {
				for (int j = 9; j > 2; j--) {
					topCounts[j] = topCounts[j - 1];
					topWords[j] = topWords[j - 1];
				}
				topCounts[2] = tempTopCount;
				topWords[2] = tempTopWord;
			}
			else if (tempTopCount > topCounts[3]) {
				for (int j = 9; j > 3; j--) {
					topCounts[j] = topCounts[j - 1];
					topWords[j] = topWords[j - 1];
				}
				topCounts[3] = tempTopCount;
				topWords[3] = tempTopWord;
			}
			else if (tempTopCount > topCounts[4]) {
				for (int j = 9; j > 4; j--) {
					topCounts[j] = topCounts[j - 1];
					topWords[j] = topWords[j - 1];
				}
				topCounts[4] = tempTopCount;
				topWords[4] = tempTopWord;
			}
			else if (tempTopCount > topCounts[5]) {
				for (int j = 9; j > 5; j--) {
					topCounts[j] = topCounts[j - 1];
					topWords[j] = topWords[j - 1];
				}
				topCounts[5] = tempTopCount;
				topWords[5] = tempTopWord;
			}
			else if (tempTopCount > topCounts[6]) {
				for (int j = 9; j > 6; j--) {
					topCounts[j] = topCounts[j - 1];
					topWords[j] = topWords[j - 1];
				}
				topCounts[6] = tempTopCount;
				topWords[6] = tempTopWord;
			}
			else if (tempTopCount > topCounts[7]) {
				for (int j = 9; j > 7; j--) {
					topCounts[j] = topCounts[j - 1];
					topWords[j] = topWords[j - 1];
				}
				topCounts[7] = tempTopCount;
				topWords[7] = tempTopWord;
			}
			else if (tempTopCount > topCounts[8]) {
				topCounts[9] = topCounts[8];
				topWords[9] = topWords[8];

				topCounts[8] = tempTopCount;
				topWords[8] = tempTopWord;
			}
		}

	}
	if (topCounts[9] != 0) {
		for (int i = 0; i < 10; i++)
			cout << topWords[i] << "\t\t" << topCounts[i] << "\n";
	}
}