// Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "hashtable.h"
#include <fstream>
#include <sstream>
#include <chrono> // to measure the elapsed time

int main()
{

	auto start = std::chrono::high_resolution_clock::now();

	string stopWords[] = { "a","able","about","above","abroad","according","accordingly","across","actually","adj","after","afterwards","again","against","ago","ahead","ain't","all","allow","allows","almost","alone","along","alongside","already","also","although","always","am","amid","amidst","among","amongst","an","and","another","any","anybody","anyhow","anyone","anything","anyway","anyways","anywhere","apart","appear","appreciate","appropriate","are","aren't","around","as","a's","aside","ask","asking","associated","at","available","away","awfully","b", "back", "backward", "backwards", "be", "became", "because", "become", "becomes", "becoming", "been", "before", "beforehand", "begin", "behind", "being", "believe", "below", "beside", "besides", "best", "better", "between", "beyond", "both", "brief", "but", "by", "c", "came", "can", "cannot", "cant", "can't", "caption", "cause", "causes", "certain", "certainly", "changes", "clearly", "c'mon", "co", "co.", "com", "come", "comes", "concerning", "consequently", "consider", "considering", "contain", "containing", "contains", "corresponding", "could", "couldn't", "course", "c's", "currently", "d", "dare", "daren't", "definitely", "described", "despite", "did", "didn't", "different", "directly", "do", "does", "doesn't", "doing", "done", "don't", "down", "downwards", "during", "e", "each", "edu", "eg", "eight", "eighty", "either", "else", "elsewhere", "end", "ending", "enough", "entirely", "especially", "et", "etc", "even", "ever", "evermore", "every", "everybody", "everyone", "everything", "everywhere", "ex", "exactly", "example", "except", "f", "fairly", "far", "farther", "few", "fewer", "fifth", "first", "five", "followed", "following", "follows", "for", "forever", "former", "formerly", "forth", "forward", "found", "four", "from", "further", "furthermore", "g", "get", "gets", "getting", "given", "gives", "go", "goes", "going", "gone", "got", "gotten", "greetings", "h", "had", "hadn't", "half", "happens", "hardly", "has", "hasn't", "have", "haven't", "having", "he", "he'd", "he'll", "hello", "help", "hence", "her", "here", "hereafter", "hereby", "herein", "here's", "hereupon", "hers", "herself", "he's", "hi", "him", "himself", "his", "hither", "hopefully", "how", "howbeit", "however", "hundred", "i", "i'd", "ie", "if", "ignored", "i'll", "i'm", "immediate", "in", "inasmuch", "inc", "inc.", "indeed", "indicate", "indicated", "indicates", "inner", "inside", "insofar", "instead", "into", "inward", "is", "isn't", "it", "it'd", "it'll", "its", "it's", "itself", "i've", "j", "just", "k", "keep", "keeps", "kept", "know", "known", "knows", "l", "last", "lately", "later", "latter", "latterly", "least", "less", "lest", "let", "let's", "like", "liked", "likely", "likewise", "little", "look", "looking", "looks", "low", "lower", "ltd", "m", "made", "mainly", "make", "makes", "many", "may", "maybe", "mayn't", "me", "mean", "meantime", "meanwhile", "merely", "might", "mightn't", "mine", "minus", "miss", "more", "moreover", "most", "mostly", "mr", "mrs", "much", "must", "mustn't", "my", "myself", "n", "name", "namely", "nd", "near", "nearly", "necessary", "need", "needn't", "needs", "neither", "never", "neverf", "neverless", "nevertheless", "new", "next", "nine", "ninety", "no", "nobody", "non", "none", "nonetheless", "noone", "no-one", "nor", "normally", "not", "nothing", "notwithstanding", "novel", "now", "nowhere", "o", "obviously", "of", "off", "often", "oh", "ok", "okay", "old", "on", "once", "one", "ones", "one's", "only", "onto", "opposite", "or", "other", "others", "otherwise", "ought", "oughtn't", "our", "ours", "ourselves", "out", "outside", "over", "overall", "own", "p", "particular", "particularly", "past", "per", "perhaps", "placed", "please", "plus", "possible", "presumably", "probably", "provided", "provides", "q", "que", "quite", "qv", "r", "rather", "rd", "re", "really", "reasonably", "recent", "recently", "regarding", "regardless", "regards", "relatively", "respectively", "right", "round", "s", "said", "same", "saw", "say", "saying", "says", "second", "secondly", "see", "seeing", "seem", "seemed", "seeming", "seems", "seen", "self", "selves", "sensible", "sent", "serious", "seriously", "seven", "several", "shall", "shan't", "she", "she'd", "she'll", "she's", "should", "shouldn't", "since", "six", "so", "some", "somebody", "someday", "somehow", "someone", "something", "sometime", "sometimes", "somewhat", "somewhere", "soon", "sorry", "specified", "specify", "specifying", "still", "sub", "such", "sup", "sure", "t", "take", "taken", "taking", "tell", "tends", "th", "than", "thank", "thanks", "thanx", "that", "that'll", "thats", "that's", "that've", "the", "their", "theirs", "them", "themselves", "then", "thence", "there", "thereafter", "thereby", "there'd", "therefore", "therein", "there'll", "there're", "theres", "there's", "thereupon", "there've", "these", "they", "they'd", "they'll", "they're", "they've", "thing", "things", "think", "third", "thirty", "this", "thorough", "thoroughly", "those", "though", "three", "through", "throughout", "thru", "thus", "till", "to", "together", "too", "took", "toward", "towards", "tried", "tries", "truly", "try", "trying", "t's", "twice", "two", "u", "un", "under", "underneath", "undoing", "unfortunately", "unless", "unlike", "unlikely", "until", "unto", "up", "upon", "upwards", "us", "use", "used", "useful", "uses", "using", "usually", "v", "value", "various", "versus", "very", "via", "viz", "vs", "w", "want", "wants", "was", "wasn't", "way", "we", "we'd", "welcome", "well", "we'll", "went", "were", "we're", "weren't", "we've", "what", "whatever", "what'll", "what's", "what've", "when", "whence", "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "where's", "whereupon", "wherever", "whether", "which", "whichever", "while", "whilst", "whither", "who", "who'd", "whoever", "whole", "who'll", "whom", "whomever", "who's", "whose", "why", "will", "willing", "wish", "with", "within", "without", "wonder", "won't", "would", "wouldn't", "x", "y", "yes", "yet", "you", "you'd", "you'll", "your", "you're", "yours", "yourself", "yourselves", "you've", "z", "zero" };
	int firstLetterLocation[27];
	firstLetterLocation[0] = 0; // start of the letter a
	firstLetterLocation[26] = sizeof(stopWords) / sizeof(stopWords[0]); // start of the letter a

	//index with the first letters of every stop word. For easy searching
	for (int i = 0; i < sizeof(stopWords) / sizeof(stopWords[0]); i++) {
		switch (stopWords[i][0])
		{
		case 97: // b at the end of a
			firstLetterLocation[1] = i + 1;
			break;
		case 98: // c at the end of b
			firstLetterLocation[2] = i + 1;
			break;
		case 99: // d
			firstLetterLocation[3] = i + 1;
			break;
		case 100: // e
			firstLetterLocation[4] = i + 1;
			break;
		case 101: // f
			firstLetterLocation[5] = i + 1;
			break;
		case 102: // g
			firstLetterLocation[6] = i + 1;
			break;
		case 103: // h
			firstLetterLocation[7] = i + 1;
			break;
		case 104: // i
			firstLetterLocation[8] = i + 1;
			break;
		case 105: // j
			firstLetterLocation[9] = i + 1;
			break;
		case 106: // k
			firstLetterLocation[10] = i + 1;
			break;
		case 107: // l
			firstLetterLocation[11] = i + 1;
			break;
		case 108: // m
			firstLetterLocation[12] = i + 1;
			break;
		case 109: // n
			firstLetterLocation[13] = i + 1;
			break;
		case 110: // o
			firstLetterLocation[14] = i + 1;
			break;
		case 111: // p
			firstLetterLocation[15] = i + 1;
			break;
		case 112: // q
			firstLetterLocation[16] = i + 1;
			break;
		case 113: // r
			firstLetterLocation[17] = i + 1;
			break;
		case 114: // s
			firstLetterLocation[18] = i + 1;
			break;
		case 115: // t
			firstLetterLocation[19] = i + 1;
			break;
		case 116: // u
			firstLetterLocation[20] = i + 1;
			break;
		case 117: // v
			firstLetterLocation[21] = i + 1;
			break;
		case 118: // w
			firstLetterLocation[22] = i + 1;
			break;
		case 119: // x
			firstLetterLocation[23] = i + 1;
			break;
		case 120: // y
			firstLetterLocation[24] = i + 1;
			break;
		case 121: // z at the end of y    (121 is y)
			firstLetterLocation[25] = i + 1;
			break;
		default:
			break;
		}
	}



	Hash hashTable(900003); // create a hash table with a size of 900003

	//Download link of the .csv dataset is available in the "Project Instructions.pdf"
	//It was too big to push to GitHub
	ifstream dataset("test.csv"); // to read from the file              
	string line, word;
	bool stopWordFlag = false; //If the word is one of the stopWords

	if (!dataset.good())
		cout << "Unable to read open file!\n";
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
				for (unsigned int i = 0; i < word.length(); i++) { // make every letter of the word lowercase

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

	auto finish = std::chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = finish - start;

	cout << "Elapsed time: " << elapsed.count() << " s\n";

	//while(true){}

	return 0;
}
