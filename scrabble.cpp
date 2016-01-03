/**
 * File: scrabble.cpp
 * ------------------
 * Created by Jerry on 4/10/10.
 */

#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "map.h"
#include "lexicon.h"

static const int kMinWordLength = 3;

/**
 * Returns a histogram of letters to frequency counts.  Since
 * the keys must be strings, they are one-letter strings in this
 * case (letters.substring(i, 1) is good for taking substrings of
 * length one).
 *
 * @param string letters the list of letters on your Scrabble rack.
 * @return Map<int> the histogram of all the letters in your rack, mapping
 *         to the number you have of each.
 */

Map<int> BuildLetterHistogram(string letters) {
	// replace the following line with your own implementation
	return Map<int>();
}

/**
 * Returns true if and only if the provided word can be formed
 * from the collection of letters represented by masterHistogram.
 *
 * @param string word the word of interest.
 * @param Map<int> the histogram of all the letters in your rack, mapping
 *        to the number you have of each.
 * @return bool true if and only if the provided word can be formed the the
 *         rack of letters provided in histogram form.
 */

bool CanFormWord(string word, Map<int>& masterHistogram) {
	// replace the following line with your own implementation.
	// you'll probably want to implement BuildLetterHistogram first
	return false;
}

/**
 * Given the specified rack of letters (duplicates allowed) and
 * the provided English lexicon, alphebatically list all words
 * that can be formed using some or all of the letters.  The algorithm
 * is intended to be brute force and the simply count letters in any
 * given word, and if we have them in our letter rack, to print it out.
 *
 * @param string letters the list of letters on your Scrabble rack.
 * @param Lexicon& english a reference to a Lexicon, already populated with
 *        the words of the English language.
 * @return void
 */

void ListAllWords(string letters, Lexicon& english) {
	Map<int> histogram = BuildLetterHistogram(letters);
	int numFound = 0;
	foreach (string word in english) {
		if (word.size() >= kMinWordLength && CanFormWord(word, histogram)) {
			if (numFound == 0) {
				cout << "You can form these words: " << endl;
			}
			numFound++;
			cout << "  " << numFound << ".) " << word << endl;
		}
	}

	if (numFound == 0) {
		cout << "Sorry, but we can't make any words out of those letters." << endl; 
	}
	
	cout << endl;
}

/**
 * Simple program that helps the user decide what his or her options
 * are in a game of Scrabble.  For the most part, self-explanatory.
 *
 * @return int 0, when the user enters a blank line.
 */

int main() {
	cout << "We're playing Scrabble, and we need some good words." << endl;
	Lexicon english("lexicon.dat");
	while (true) {
		cout << "Letters? [hit enter to quit]: ";
		string letters = GetLine();
		if (letters.empty()) break;
		if (letters.size() < kMinWordLength) {
			cout << "We need at least " << kMinWordLength << " letters.  Please try again" << endl;
		} else {
			ListAllWords(letters, english);
		}
	}
	
	return 0;
}

