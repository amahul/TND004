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

	/***
	* Operator<
	* To sort the tree alphabetically
	* O(1)
	***/
	bool operator<(const Row& row) const {
		return key < row.key;
	}
	/***
	* Operator==
	* To compare the words and vectors
	* O(1)
	***/
	bool operator==(const Row& a) const {
		return key == a.key && counter == a.counter;
	}

};

/***
	* To remove any character that is not alphanumeric, ' or -.
	* O(1)
***/
bool isPunc(const char& c) {
	//std::cout << c << std::endl;

	if (c == '\'' || c == '-' || isalnum(c)) return false; //remove any character that is not alphanumeric (0123456789 or alphabet)

	else return true;

}

/***
	* Operator<<
	* To write out the vectors in order to manually check if they're correct
	* O(1)
***/
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
			// Remove special characters, O(n)
			inWord.erase(std::remove_if(inWord.begin(), inWord.end(), isPunc), inWord.end());

			// Set word to lowercase, O(n)
			std::transform(inWord.begin(), inWord.end(), inWord.begin(), std::tolower);

			// Use BST funstion to check if inWord exists in tree
			// Worst-case: O(n), Best-case: O(1) ?? Fast find är O(n)
			BinarySearchTree<Row>::Iterator findWord = Tree.find(inWord);

			// InWord already exists in tree
			if (findWord != Tree.end()) {
				// increase counter
				findWord->counter++;
			}
			else {
				// Insert word in tree if not exists
				Tree.insert(inWord);
			}

			++total_counter;

		}
		file.close();

		// Insert values from tree to vector
		std::vector<Row> V;
		//V.reserve(Tree.get_count_nodes());
		std::copy(Tree.begin(), Tree.end(), std::back_inserter(V)); // O(n)
		//std::copy(Tree.begin(), Tree.end(), push_back(V));

		// Make vector of Facit-file
		std::vector<Row> facit;
		std::string fWord;
		int fCount;

		std::ifstream in("../code/frequency_table.txt");
		//std::ifstream in("../code/frequency_table_long.txt");

		// O(n)
		while (in >> fWord >> fCount) {
			Row pFacit;
			pFacit.key = fWord;
			pFacit.counter = fCount;
			facit.push_back(pFacit);
		}

		// Print table, O(n)
		/*std::cout << "\n\n\n------ Table: ----------\n";
		std::vector<Row>::iterator r;
		for (r = V.begin(); r != V.end(); ++r) {
			std::cout << std::left << std::setw(25) << r->key << r->counter << "\n";
		}*/

		std::cout << "\n\n" << "Number of words in the file = " << total_counter << "\n";
		std::cout << "Number of unique words in the file = " << Tree.get_count_nodes() << "\n\n";;


		// Print vector to file to manually check if it's ok, O(n)
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