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

	/*// default constructor
	Row() : counter{ 1 } {};
	// constructor
	Row(std::string word) : key{ word }, counter{ 1 }{};
	*/

	// Operator<, sort alphabetically
	bool operator<(const Row& row) const {
		return key < row.key;
	}

	// Operator ==, check if both vectors are equal
	bool operator==(const Row& a) {
		return key == a.key;
	}

	/*void increase_counter() {
		counter++;
	}*/

	/*void print() const {
		std::cout << std::left << std::setw(25) << key << counter << std::endl;
	}*/

	/*std::string get_key() {
		return key;
	}*/

//:private
	std::string key = "";
	int counter = 1;

};


// Add other stuff, if needed

bool isPunc(const char& c) {
	//std::cout << c << std::endl;
	if (c == '\'' || isalnum(c) ) return false;
	//if (ispunct(c) || c == 'Æ') return true; //remove any character that is not alphanumeric
	else return true;

}

// Varför behöver vi denna? 
std::ostream& operator<<(std::ostream& out, const Row& r)
{
	return out << std::left << std::setw(25) << r.key << r.counter << "\n";

}

#endif



void exercise3() {
#ifdef TEST_EXERCISE3
	{
		std::ifstream file("../code/text.txt");  // contains 56 unique words
		// std::ifstream file("../code/text_long.txt"); // contains 497 unique words

		if (!file) {
			std::cout << "Couldn't open file text.txt\n";
			// std::cout << "Couldn't open file text_long.txt\n";
			return;
		}

		// Empty frequency table
		//BinarySearchTree<Row> freq_table;

		/*std::vector<std::string> V{std::istream_iterator<std::string>{file},
								   std::istream_iterator<std::string>{} };*/

		// Check that tree is empty
		//std::cout << "Is the tree empty? ";
		//assert(freq_table.get_count_nodes() == 0);
		//std::cout << "Yes!\n\n";

		//std::string inWord;
		//Row new_row;

		int total_counter = 0;

		std::string inWord;
		BinarySearchTree<Row> Tree;
		std::vector<Row> V;

		// While we find a new word in in_File
		while (file >> inWord)
		{
			//std::cout << inWord << std::endl;
			// Remove special characters
			inWord.erase(std::remove_if(inWord.begin(), inWord.end(), isPunc), inWord.end());

			// Set word to lowercase
			std::transform(inWord.begin(), inWord.end(), inWord.begin(), std::tolower);

			Row p;
			p.key = inWord;
			BinarySearchTree<Row>::Iterator findWord = Tree.find(p);

			if (findWord != Tree.end()) {
				findWord->counter++;
			} 
			else {
				Tree.insert(p);
			}

			// Copy tree into a vector V
			std::copy(Tree.begin(), Tree.end(), std::back_inserter(V));

			//Row new_row = Row(inWord);
			//if (freq_table.contains(new_row)) {
			//	//increase counter if word already exists
			//	new_row.increase_counter();
			//}
			//else {
			//	freq_table.insert(new_row);
			//}

			++total_counter;
		}
		file.close();

		std::cout << "---------Tree: -----------\n";
		Tree.printTree();

		std::cout << "\n\n\n------ Table: ----------\n";
		std::vector<Row>::iterator r;
		//for (p = V.begin(); p != V.end(); p++) {
		//	std::cout << std::left << std::setw(25) << p->key << p->counter << std::endl;
		//}

		//std::vector<Row>::iterator p;
		for (r = V.begin(); r != V.end(); ++r) {
			std::cout << std::left << std::setw(25) << r->key << r->counter << "\n";
		}

		//std::cout << freq_table.get_count_nodes();
		/*std::cout << "total_counter " << total_counter << "\n";

		assert(total_counter == 69);*/
	
		std::ofstream myfile("../code/AAA.txt");
		if (myfile.is_open())
		{
			
			myfile << "V.size() " << V.size() << '\n';
			myfile << "---VECTOR---" << '\n';
			for (int i = 0; i < V.size(); i++) {
				myfile << V[i] << '\n';
			}
			myfile << "---END---" << '\n';

			myfile.close();
		}
		else std::cout << "Unable to open AAA";


		
	}

	std::cout << "Success!!\n";
#endif
}