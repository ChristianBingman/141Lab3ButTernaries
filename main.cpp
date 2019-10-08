/* ------------------------------------------------
 * sample.cpp
 *
 * Class: Program #3 for CS 141, Fall 2019
 * System: Windows/Arch x64
 * Author: Anastasiia Evdokimova && Christian Bingman
 *
*/
#include <iostream>
#include <string>
#include <fstream>      // For file input
#include <vector>		// For dictionary vector
#include <iomanip>		// For setw()
#include <cctype>       // For tolower()
using namespace std;


//---------------------------------------------------------------
// Display ID info
//
void displayIdInfo()
{
	cout << " \n"
		<< "Program #3: Work Play  \n"
		<< "Author: Anastasiia Evdokimova && Christian Bingman     \n"
		<< "Program: 3          \n"
		<< "System:  Windows/Arch x64         \n"
		<< " \n";
}//end displayIDInfo()


//-----------------------------------------------------------------------------------------
//  You should use parameters for the dictionary, the word lengths array, 
//  the length of words to use, and the total number of words.
void readInWordsFromFile(string fileName, vector <string>& dictionary, int currentWordLength, int newDictionarySize)
{
	ifstream inputFileStream;
	string inputWord;				    // stores each word as it is read
	int currentWordNum = 0;							// current index of dictionary

	// Set new size to the dictionary based on how many words of chosen length are in the dictionary
	dictionary.resize(newDictionarySize);
	// Open input file
	inputFileStream.open(fileName.c_str());

	// Verify that the open worked
	if (!inputFileStream.is_open()) {
		cout << "Could not find input file " << fileName << "  Exiting..." << endl;
		exit(-1);
	}

	// Read all the words from the file and store those of current lenght into dictionary
	while (inputFileStream >> inputWord) {
		if (inputWord.length() == currentWordLength) {
			if (isupper(inputWord[0])) {
				for (int i = 0; i < inputWord.length(); i++) {
					inputWord[i] = tolower(inputWord[i]);
				}
			}
			dictionary.at(currentWordNum) = inputWord;
			currentWordNum++;
		}
	}
	inputFileStream.close();    // Close the input file.
}


//--------------------------------------------------------------------------------------
// Use binary search to look up the search word in the dictionary vector, returning
// the word's index if found, -1 otherwise.
//
long binarySearch(
	string searchWord,            // word to be looked up
	const vector< string>& dictionary)   // the dictionary of words
{
	long low, mid, high;     // array indices for binary search
	long searchResult = -1;  // Stores index of word if search succeeded, else -1

	// Binary search for word
	low = 0;
	high = dictionary.size() - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		// SearchResult negative value means word is to the left, positive value means
		// word is to the right, value of 0 means word was found
		searchResult = searchWord.compare(dictionary[mid]);
		if (searchResult == 0) {
			// Word IS in dictionary, so return the index where the word was found
			return mid;
		}
		else if (searchResult < 0) {
			high = mid - 1; // word should be located before the mid location
		}
		else {
			low = mid + 1; // word should be located after the mid location
		}
	}
	// Word was not found
	return -1;
}//end binarySearch()

long regularSearch(string searchWord, const vector< string>& dictionary) {
	for (int i = 0; i < dictionary.size(); i++) {
		if (dictionary.at(i) == searchWord)
			return i;
	}
	return -1;
}

void dictionaryScan(string fileName, vector<int>& wordsNumByLength, int& totalWordsCount) {
	ifstream inputFileStream; // Declare the input file stream
	string line; //variable for reading lines
	// Open input file and verify that file was found
	inputFileStream.open(fileName.c_str());
	if (!inputFileStream.is_open()) {
		cout << "Could not find input file " << fileName << "  Exiting..." << endl;
		exit(-1);
	}
	//count total number of words and number of words by their length
	while (getline(inputFileStream, line)) {
		if (line.length() > wordsNumByLength.size()) {  // if the lenght hasn't been represented already
			wordsNumByLength.resize(line.length(), 0);  // give additional memory to the vector for new data (second parameter sets default value to 0)
		}
		wordsNumByLength.at(line.length() - 1)++;
		totalWordsCount++;
	}
}

void printMainMenu() {
	cout << "Choose from the following options:  \n"
		<< "   1. Change the word length        \n"
		<< "   2. Display some dictionary words \n"
		<< "   3. Get start and end words       \n"
		<< "   4. Play the word change game     \n"
		<< "   5. Find the end word with debug  \n"
		<< "   6. Find the end word             \n"
		<< "   7. Display an answer sequence    \n"
		<< "   8. Exit the program              \n"
		<< "Your choice -> ";
}

void displayTotWordCount(int totalWordsNumber, const vector<int>& wordsNumByLength) {
	cout << "Total number of words in dictionary file : " << totalWordsNumber << endl << endl;
	cout << "Word lengths where there are more than 1400 words: " << endl;
	cout << "Length  How Many" << endl << "------  --------" << endl;
	for (int i = 0; i < wordsNumByLength.size(); i++) {
		if (wordsNumByLength.at(i) > 1400) {
			cout << setw(6) << i + 1 << setw(8) << wordsNumByLength.at(i) << endl;
		}
	}
	cout << endl;
}

bool verifyWord(string word, const vector <string>& dictionary) {
	long wordSearchIndex = binarySearch(word, dictionary);
	// Check for the word length and presence in the dictionary
	if ((word.length() != dictionary.at(0).length())) {
		cout << "   *** '" << word << "' is not of length " << dictionary.at(0).length() << ". Please retry." << endl;
		return false;
	}
	else
		if (wordSearchIndex == -1) {
			cout << "   *** '" << word << "' is not in the dictionary. Please retry." << endl;
			return false;
		}
		else {
			return true;
		}
}

bool findSimilarWords(const vector <string>& dictionary, string word, string endWord, vector <string>& currentWordCollection, bool hideOutput) {
	int letterDifference;
	for (int i = 0; i < dictionary.size(); i++) {
		letterDifference = 0;
		for (int j = 0; j < word.length(); j++) {
			if (word[j] != dictionary.at(i)[j]) {
				letterDifference++;
			}
			if (letterDifference > 1) {
				break;
			}
		}
		if ((letterDifference == 1) && (regularSearch(dictionary.at(i), currentWordCollection) == -1)) {
			currentWordCollection.push_back(dictionary.at(i));
			if (!hideOutput) {
				cout << currentWordCollection.size() - 1 << ":" << dictionary.at(i) << " ";
			}
			if (dictionary.at(i) == endWord) {
				cout << endl << endl;
				return true;
			}
		}
	}
	return false;
}

void createWordChain(const vector <string>& dictionary, string startWord, string endWord, vector <string>& wordChain, bool hideOutput = true, bool displayReverseSequence = false) {
	int currentWordInd = 0;
	string currentSearchWord;
	bool endWordFound = false;
	vector <int> searchedWordsIndexes;
	wordChain.resize(0);
	wordChain.push_back(startWord);
	searchedWordsIndexes.push_back(0);
	do {
		currentSearchWord = wordChain.at(currentWordInd);
		if (!hideOutput) {
			cout << endl << currentWordInd << ". " << currentSearchWord << ":   ";
		}
		int previousWordChainSize = wordChain.size();
		endWordFound = findSimilarWords(dictionary, currentSearchWord, endWord, wordChain, hideOutput);
		if (!endWordFound) {
			currentWordInd++;
			if (wordChain.size() > previousWordChainSize) {
				searchedWordsIndexes.push_back(previousWordChainSize + 1);
			}
			else {
				searchedWordsIndexes.push_back(-1);
			}
		}
	} while ((!endWordFound) && (wordChain.size() > currentWordInd));
	if (endWordFound) {
		cout << "Winning sequence was found!" << endl;
		/*if (displayReverseSequence) {
			int currentParentIndex
			while (wordChain.size() )
		}*/
	}
	else
	{
		cout << "Winning sequence was not found!" << endl;
	}
}

void getStartEndWords(const vector <string>& dictionary, string& startWord, string& endWord) {
	cout << endl;
	bool isWordVerifyed = false;
	// User input is requested again if it doesn't pass the criteria
	do {
		cout << "Enter starting word, or 'r' for a random word: ";
		cin >> startWord;
		if (startWord == "r") {
			startWord = dictionary[rand() % dictionary.size()]; // Picking a random line from the dictionary
			break;
		}
		// If user wishes to exit the program
		if (endWord == "exit") {
			exit(0);
		}
		// Check for the word length and presence in the dictionary
		isWordVerifyed = verifyWord(startWord, dictionary);
		if (!isWordVerifyed) {
			startWord = "";
		}
	} while (!isWordVerifyed);
	// Similar to the input of the startWord
	do {
		cout << "Enter ending word, or 'r' for a random word: ";
		cin >> endWord;
		if (endWord == "r") {
			endWord = dictionary[rand() % dictionary.size()];
			break;
		}
		if (endWord == "exit") {
			exit(0);
		}
		isWordVerifyed = verifyWord(endWord, dictionary);
		if (!isWordVerifyed) {
			endWord = "";
		}
	} while (!isWordVerifyed);
}

void playWordChangingGame(string startWord, string endWord, const vector <string>& dictionary) {
	string currentWord, userInputWord; // Separate the user input since it has to pass all the checks first
	int turnsCounter = 1, differentLettersAmount;
	// Check whether start and end words are set
	if ((startWord == "") || (endWord == "")) {
		cout << "   *** You must first set start and end words.  Please retry.";
		return;
	}
	currentWord = startWord;
	do {
		cout << turnsCounter << "Previous word is '" << currentWord << "'. Next word: ";
		cin >> userInputWord;
		if (userInputWord == "exit") {
			return;
		}
		if (verifyWord(userInputWord, dictionary)) { //Check that the inputted word is in the dictionary
			differentLettersAmount = 0;
			for (int i = 0; i < userInputWord.length(); i++) {
				if (userInputWord.at(i) != currentWord.at(i)) {
					differentLettersAmount++;
				}
			}
			if (differentLettersAmount == 1) {
				currentWord = userInputWord;
				turnsCounter++;
			}
			else
			{
				cout << "   *** '" << userInputWord << "' must be exactly 1 character different.  Please retry.";
				exit(0);
			}
		}
	} while (currentWord != endWord); // When user enters endWord and it passes all the checks, loop will end
	cout << "Congratulations, you did it!" << endl;
}

void displaySomeDictionaryWords(const vector <string>& dictionary) {
	int startIndex, lastIndex;			// User-inputted indexes for displaying words
	//Input indexes for displayed words
	do {
		cout << "Enter the start and end index values of words to display: ";
		cin >> startIndex >> lastIndex;
	} while ((startIndex < 0) || (lastIndex > dictionary.size() - 1) || (startIndex > lastIndex)); //check that indexes are not out of bound

	//Display words from startIndex to lastIndex
	for (int i = startIndex; i <= lastIndex; i++) {
		cout << i << " " << dictionary.at(i) << endl;
	}
}

//-----------------------------------------------------------------------------------------
int main()
{
	vector< string> dictionary, wordChain;    		// Vector of dictionary words read in from file
	vector <int> wordsNumByLength;		// Vector of the amount of words where number of words is stored under the index of their lenght-1
	int lengthOfWordsToUse = 3;         // Default length of word to use in word transformation
	string startWord = "dog";           // The start word for transformation
	string endWord = "cat";             // The end word for transformation
	int menuOption = -1;                // User menu option selection
	string fileName = "dictionary.txt";	// Using this in case file name will change
	int totalWordsNumber = 0;			// Used to store total number of words
	// Display ID info
	displayIdInfo();
	// Seed the random number generator
	srand(1);  // Change 1 to time(0) for non-predictable results, but leave as 1 for testing
	//Check the amount of words in dictionary
	dictionaryScan(fileName, wordsNumByLength, totalWordsNumber);
	//resizing dictionary according to the amount of words starting with the letter
	readInWordsFromFile(fileName, dictionary, lengthOfWordsToUse, wordsNumByLength.at(lengthOfWordsToUse - 1));
	displayTotWordCount(totalWordsNumber, wordsNumByLength);
	// Menu display and handling infinite loop
	do {
		cout << endl << "Currently we have " << dictionary.size() << " words of length "
			<< lengthOfWordsToUse << " in the dictionary.  \n"
			<< "Changing from '" << startWord << "' to '" << endWord << "'" << endl
			<< endl;
		printMainMenu();
		cin >> menuOption;

		// Menu option handling should go here
		switch (menuOption) {
		case 1:
			cout << "What length words do you want to use? ";
			cin >> lengthOfWordsToUse;
			startWord = "";
			endWord = "";
			readInWordsFromFile(fileName, dictionary, lengthOfWordsToUse, wordsNumByLength.at(lengthOfWordsToUse - 1));
			break;
		case 2:
			displaySomeDictionaryWords(dictionary);
			break;
		case 3:
			getStartEndWords(dictionary, startWord, endWord);
			break;
		case 4:
			playWordChangingGame(startWord, endWord, dictionary);
			break;
		case 5:
			createWordChain(dictionary, startWord, endWord, wordChain, false);
			break;
		case 6:
			createWordChain(dictionary, startWord, endWord, wordChain);
			break;
		case 7: break;
		case 8: exit(0); break;
		default: exit(0); break;
		}
	} while (true);
	return 0;
}//end main()



