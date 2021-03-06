
// 1602428 Ekin Karadağ

#include "hashtable.h"
#include <fstream>
#include <sstream>
#include <chrono> // to measure the elapsed time

int main()
{

	auto start = chrono::high_resolution_clock::now();

	string stopWords[659];

	ifstream stopwordsFile("stopwords.txt"); // to read the stopwords
	if (!stopwordsFile.good())
		cout << "Unable to read the stopwords file! The file name has to be \"stopwords.txt\" (without quatition marks)\n";
	for (unsigned int i = 0; stopwordsFile.good(); i++) 
		getline(stopwordsFile, stopWords[i]);
	stopwordsFile.close();



	int firstLetterLocation[27];
	firstLetterLocation[0] = 0; // start of the letter a
	firstLetterLocation[26] = sizeof(stopWords) / sizeof(stopWords[0]); // top represent the end of the stop words

	//index with the first letters of every stop word. For easy searching
	for (int i = 0; i < sizeof(stopWords) / sizeof(stopWords[0]); i++) {
		if (stopWords[i] == "b")
			firstLetterLocation[1] = i;
		else if (stopWords[i] == "c")
			firstLetterLocation[2] = i;
		else if (stopWords[i] == "d")
			firstLetterLocation[3] = i;
		else if (stopWords[i] == "e")
			firstLetterLocation[4] = i;
		else if (stopWords[i] == "f")
			firstLetterLocation[5] = i;
		else if (stopWords[i] == "g")
			firstLetterLocation[6] = i;
		else if (stopWords[i] == "h")
			firstLetterLocation[7] = i;
		else if (stopWords[i] == "i")
			firstLetterLocation[8] = i;
		else if (stopWords[i] == "j")
			firstLetterLocation[9] = i;
		else if (stopWords[i] == "k")
			firstLetterLocation[10] = i;
		else if (stopWords[i] == "l")
			firstLetterLocation[11] = i;
		else if (stopWords[i] == "m")
			firstLetterLocation[12] = i;
		else if (stopWords[i] == "n")
			firstLetterLocation[13] = i;
		else if (stopWords[i] == "o")
			firstLetterLocation[14] = i;
		else if (stopWords[i] == "p")
			firstLetterLocation[15] = i;
		else if (stopWords[i] == "q")
			firstLetterLocation[16] = i;
		else if (stopWords[i] == "r")
			firstLetterLocation[17] = i;
		else if (stopWords[i] == "s")
			firstLetterLocation[18] = i;
		else if (stopWords[i] == "t")
			firstLetterLocation[19] = i;
		else if (stopWords[i] == "u")
			firstLetterLocation[20] = i;
		else if (stopWords[i] == "v")
			firstLetterLocation[21] = i;
		else if (stopWords[i] == "w")
			firstLetterLocation[22] = i;
		else if (stopWords[i] == "x")
			firstLetterLocation[23] = i;
		else if (stopWords[i] == "y")
			firstLetterLocation[24] = i;
		else if (stopWords[i] == "z")
			firstLetterLocation[25] = i;
	}

	Hash hashTable(1000003); // create a hash table with a size of 1000003	
	ifstream dataset("training.1600000.processed.noemoticon.csv"); // to read from the file
	string line, word;
	bool stopWordFlag = false; //If the word is one of the stopWords

	if (!dataset.good())
		cout << "Unable to read the file! The file name has to be \"training.1600000.processed.noemoticon.csv\" (without quatition marks)\n";
	while (dataset.good()) {
		getline(dataset, line, ',');
		getline(dataset, line, ',');
		getline(dataset, line, ',');
		getline(dataset, line, ',');
		getline(dataset, line, ',');
		getline(dataset, line, '\n'); //get to the 6th column on CVS file which is the tweet that has been posted

		stringstream iss(line);
		while (iss >> word) { // Split the whole tweet to words

			for (unsigned int i = 0; i < word.size() && word.size() > 1; i++) { // To adjust the word to fit the rules of insertion

				if (word[i] != 39) { //that character -> '
					if ((word[i] > 122) || (word[i] < 65)) {
						word.erase(i--, 1);
					}
					else if ((word[i] > 90) && (word[i] < 97)) {
						word.erase(i--, 1);
					}
				}
				else { //FAILSAFE (If the starting chracter is '
					if(i==0)
						word.erase(i--, 1);
				}

			}


			if (word.size() > 1) {
				for (unsigned int i = 0; i < word.length() && word.size() > 1; i++) { // make every letter of the word lowercase

					if (word[i] >= 65 && word[i] <= 90)
						word[i] += 32;
				}

				// Search the stop words according to indexes
				for (int i = firstLetterLocation[word[0] - 97]; i < firstLetterLocation[word[0] - 96]; i++) {
					if (word == stopWords[i]) {
						stopWordFlag = true;
						break;
					}

				}
			}
			if (!stopWordFlag && word.size() > 1) {
				hashTable.insertItem(word);
			}
			stopWordFlag = false;
		}
	}
	hashTable.displayMostUsed();

	auto finish = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = finish - start;

	cout << "\nElapsed time: " << elapsed.count() << " s\n\n";

	cout << "Press Enter to finish the program";
	cin.get();

	return 0;
}
