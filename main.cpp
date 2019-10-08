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

	// Read all the words from the file and store those of currentth into dictionary
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
	// cout << searchWord << endl;
	// Binary search for word
	low = 0;
	high = dictionary.size() - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		// cout << mid;
		// SearchResult negative value means word is to the left, positive value means
		// word is to the right, value of 0 means word was found
		searchResult = searchWord.compare(dictionary[mid]);
		// cout << searchResult << endl;
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
		if (line.length() > wordsNumByLength.size()) {  // if the length hasn't been represented already
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
// The poorly implemented binary search function seems to only work correctly with the dictionary.
int linearSearch(string searchWord, const vector<string>& dictionary){
	for(int i = 0; i < dictionary.size(); i++){
		if(searchWord == dictionary[i]) {return 1;}
	}
	return -1;
}

int intSearch(int searchInt, const vector<int>& indicieVector){
	for(int i = 0; i < indicieVector.size(); i++){
		if(indicieVector[i] == searchInt){
			return i;
		}
	}
	return -1;
}

int lookForWord(const vector<string>& dictionary, string startWord, string endWord, int verbosityLevel = 0){
	if(startWord == "" || endWord == "" || dictionary.empty()){
		return -1;
	}
	// Starting Word
	string tempWord = startWord;
	// Vector to store words in
	vector<string> allWords;
	// Vector that contains the indicies of the starting words
	vector<int> wordIndicies;
	// Loop til found
	vector<int> counters = {0, 1, 0};
	bool found = false;
	while(!found){
		// Will get the next indicie to be pushed on to of allWords
		wordIndicies.push_back(allWords.size());
		// Push the tempWord value onto allWords
		allWords.push_back(tempWord);
		if(verbosityLevel == 2) cout << counters[0] << ": " << tempWord << "\t";
		
		for(int currLetter = 0; currLetter < tempWord.length(); currLetter++){
			if(tempWord[currLetter] == startWord[currLetter]){
			for(int newLetter = 97; newLetter < 123; newLetter++){
				tempWord[currLetter] = newLetter;
				// If the word is in the dictionary add it to allWords and print it
				if(binarySearch(tempWord, dictionary) != -1 && linearSearch(tempWord, allWords) == -1){
					allWords.push_back(tempWord);
					if(verbosityLevel == 2) cout << counters[1] << ":" << tempWord << " ";
					counters[1]++;
					if(tempWord == endWord) {
						
						if(verbosityLevel == 1){
							cout << counters[1]-1 << ":" << tempWord << endl;
							cout << counters[0] << ":" << allWords[wordIndicies[wordIndicies.size()-1]] << endl; 
							string wordToSearch = allWords[wordIndicies[wordIndicies.size()-1]];
							int indexCounter[] = {0,1};
							bool KOT = false;
							while(!KOT){
							for(int similarLoop = wordIndicies[indexCounter[0]]+1; similarLoop < wordIndicies[indexCounter[1]];similarLoop++){
								if(allWords[similarLoop] == wordToSearch){
									wordToSearch = allWords[wordIndicies[indexCounter[0]]];
									cout << indexCounter[0] << ": " << allWords[wordIndicies[indexCounter[0]]] << endl;
									indexCounter[0] = 0;
									indexCounter[1] = 1;
									similarLoop = 0;
									continue;
								}
								if(wordToSearch == allWords[0]){
									KOT = true;
									break;
								}
			

							}
							if(indexCounter[1] >= wordIndicies.size()) break;
							else{
								indexCounter[0]++;
								indexCounter[1]++;
							}}
							
						}

						cout << endl << "Word Sequence Found!" << endl;
						return 0;

					}
				}
			}
			tempWord = allWords[wordIndicies[wordIndicies.size()-1]];
			}
		}
		if(verbosityLevel == 2) cout << endl;
		// If the next word is a parent word than skip
		if(intSearch(counters[2]+1, wordIndicies) != -1) {
			counters[2]+=2;
			startWord = allWords[counters[2]-1];
		}
		else {counters[2]++;}
		counters[0]++;
		if(counters[2] < allWords.size()) {tempWord = allWords[counters[2]];}
		else{cout << "Conversion not possible using current dictionary!" << endl; return -1;}
		
	}


	return -1;
}



//-----------------------------------------------------------------------------------------
int main()
{
	vector< string> dictionary;    		// Vector of dictionary words read in from file
	vector <int> wordsNumByLength;		// Vector of the amount of words where number of words is stored under the index of theirth-1
	int lengthOfWordsToUse = 3;         // Default length of word to use in word transformation
	string startWord = "dog";           // The start word for transformation
	string endWord = "cat";             // The end word for transformation
	int menuOption = -1;                // User menu option selection
	string fileName = "dictionary.txt";	// Using this in case file name will change
	int totalWordsNumber = 0;			// Used to store total number of words
	vector<string> foundSimilar = {};
	
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
			lookForWord(dictionary, startWord, endWord, 2);
			break;
		case 6: 
			lookForWord(dictionary, startWord, endWord);
			break;
		case 7: 
			lookForWord(dictionary, startWord, endWord, 1);
			break;
		case 8: exit(0); break;
		default: exit(0); break;
		}
	} while (true);
	return 0;
}//end main()