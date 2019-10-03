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
	cout << searchWord << endl;
	// Binary search for word
	low = 0;
	high = dictionary.size() - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		cout << mid;
		// SearchResult negative value means word is to the left, positive value means
		// word is to the right, value of 0 means word was found
		searchResult = searchWord.compare(dictionary[mid]);
		cout << searchResult << endl;
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

void deBuggy(const vector <string>& dictionary, string startWord, string endWord){
	long startInd, endInd;
	cout << startWord << " " << endWord << endl;
	for (int i = 0; i < dictionary.size(); i++){
		if(dictionary[i] == startWord) startInd = i;
		if(dictionary[i] == endWord) endInd = i;
	}
	// startInd = binarySearch(startWord, dictionary);
	// endInd = binarySearch(endWord, dictionary);
	cout << startInd << " " << endInd << endl;
}


//-----------------------------------------------------------------------------------------
int main()
{
	vector< string> dictionary;    		// Vector of dictionary words read in from file
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
		cout << "Currently we have " << dictionary.size() << " words of length "
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
			break;
		case 2:
			displaySomeDictionaryWords(dictionary);
			break;
		case 3: break;
		case 4: break;
		case 5: 
			cout << startWord << " " << endWord << endl;
			deBuggy(dictionary, startWord, endWord);
			break;
		case 6: break;
		case 7: break;
		case 8: exit(0); break;
		default: exit(0); break;
		}
	} while (true);

	return 0;
}//end main()



