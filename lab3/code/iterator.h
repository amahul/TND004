#pragma once

/* **********************************************************
 * Class to represent a bi-directional iterator for BSTs     *
 * Bi-directional iterators can be moved in both directions, *
 * increasing and decreasing order of items keys             *
 * ***********************************************************/

template <typename Comparable>
class BinarySearchTree<Comparable>::Iterator {
public:
	// Some properties for Iterator  -- so that Iterator can be used with STL-algorithms
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = Comparable;
	using pointer = Comparable*;  // or also value_type*
	using reference = Comparable&;  // or also value_type&

	/* ****************************************************************** */

	// Exercise 2: ADD CODE   

	Iterator() {
		current = nullptr;
	}

	/**
	* Returns the value of node
	* O(1)
	*/
	Comparable& operator*() {
		return current->element;
	}

	/**
	* Returns a pointer to current node
	* O(1)
	*/
	Comparable* operator->() {
		return &current->element;
	}

	/** (equal to)
	* Returns a boolean: current node == it or not
	*/
	bool operator==(const Iterator& it) {
		return (current == it.current);
	}

	/** (not equal to)
	* Returns a boolean: current node != it or not
	*/
	bool operator!=(const Iterator& it) {
		return !(current == it.current);
	}

	/**
	* Returns the node with closest larger value
	* Pre-increment ++a
	* find_successor O(n)
	*/
	Iterator& operator++() {
		current = bst->find_successor(current);
		return *this;
	}

	// Pos-increment a++, sparar det vi har innan, går vidare, returnar det vi hade innan
	Iterator operator++(int) {
		Iterator result = *this;
		this->operator++();
		return result;
	}

	/**
	* Returns the node with closest smaller value
	* Pre-decrement
	* find_predecessor O(n)
	*/
	Iterator& operator--() {
		current = bst->find_predecessor(current);
		return *this;
	}
	//Pos-decrement
	Iterator operator--(int) {
		Iterator result = *this;
		this->operator--();
		return result;
	}

	friend class BinarySearchTree;

private:
	Node* current;
	BinarySearchTree* bst = nullptr;

	Iterator(BinarySearchTree* p1, Node* p2) : bst{ p1 }, current{ p2 }{
	};

};
