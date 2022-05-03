#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cassert>  //assert
#include <ctype.h> //ispunct

#include "BinarySearchTree.h"

#define TEST_EXERCISE3

/* *********************************************
 * Exercise 3: frequency table
 ********************************************* */

#ifdef TEST_EXERCISE3

struct Row {
	// ADD CODE: exercise 3

	std::string key;
	int counter = 0;

	// default constructor
	Row() : counter{ 0 } {};

	// constructor
	Row(std::string word) : key{ word }, counter{ 1 }{};
	
	// default destructor
	~Row() = default;

	// Operator<, sort alphabetically
	bool operator<(const Row& row) const {
		return key < row.key;
	}

	// Operator ==, check if both vectors are equal
	bool operator==(const Row& a) const {
		return key == a.key && counter == a.counter;
	}	

};

// Add other stuff, if needed

bool isPunc(const char& c) {
	//std::cout << c << std::endl;
	if (c == '\'' || isalnum(c) ) return false;
	//if (ispunct(c) || c == 'Æ') return true; //remove any character that is not alphanumeric
	else return true;

}

// To control vector
//std::ostream& operator<<(std::ostream& os, const Row& r) {
//	return os << std::left << std::setw(25) << r.key << r.counter << "\n";
//}

#endif


void exercise3() {
#ifdef TEST_EXERCISE3
	{
		std::ifstream file("../code/text.txt");  // contains 56 unique words
		//std::ifstream file("../code/text_long.txt"); // contains 497 unique words

		if (!file) {
			//std::cout << "Couldn't open file text.txt\n";
			 std::cout << "Couldn't open file text_long.txt\n";
			return;
		}

		int total_counter = 0;

		std::string inWord;
		BinarySearchTree<Row> Tree;
		Row new_row;

		// While we find a new word in in_File
		while (file >> inWord)
		{
			// Remove special characters
			inWord.erase(std::remove_if(inWord.begin(), inWord.end(), isPunc), inWord.end());

			// Set word to lowercase
			std::transform(inWord.begin(), inWord.end(), inWord.begin(), std::tolower);

			BinarySearchTree<Row>::Iterator findWord = Tree.find(inWord);

			if (findWord != Tree.end()) {
				findWord->counter++;
			} 
			else {
				Tree.insert(inWord);
				findWord = Tree.begin();
			}

			++total_counter;

		}
		file.close();

		// Insert to vector
		std::vector<Row> V;
		std::copy(Tree.begin(), Tree.end(), std::back_inserter(V));

		// Make vector of Facit-file
		std::vector<Row> facit;
		std::string fWord;
		int fCount;

		std::ifstream in("../code/frequency_table.txt");
		//std::ifstream in("../code/frequency_table_long.txt");

		while (in >> fWord >> fCount) {
			Row pFacit;
			pFacit.key = fWord;
			pFacit.counter = fCount;
			facit.push_back(pFacit);
		}

		// Print table
		/*std::cout << "\n\n\n------ Table: ----------\n";
		std::vector<Row>::iterator r;
		for (r = V.begin(); r != V.end(); ++r) {
			std::cout << std::left << std::setw(25) << r->key << r->counter << "\n";
		}*/

		std::cout << "\n\n" << "Number of words in the file = " << total_counter << "\n";
		std::cout << "Number of unique words in the file = " << Tree.get_count_nodes() << "\n\n";;


		// Print vector to file to check if it's ok
		/*std::ofstream testA("../code/AAA.txt");
		std::ofstream testB("../code/BBB.txt");
		if (testA.is_open() && testB.is_open())
		{
			for (int i = 0; i < facit.size(); i++) {
				testA << facit[i];
				testB << V[i];
			}
		}
		else std::cout << "Unable to open file";*/

		// Compare facit-vector and our vector
		std::cout << "Check with facit if our vector is correct. " << "\n\n\n";;
		assert(V == facit);
	} 

	//assert(BinarySearchTree<Row>::get_count_nodes() == 0);
	
	std::cout << "Success!!\n";
#endif
}