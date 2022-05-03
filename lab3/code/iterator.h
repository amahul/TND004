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
	*/
	Comparable& operator*() {
		return current->element;
	}

	/**
	* Returns a pointer to current node
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
	*/
	Iterator& operator++() {
		current = bst->find_successor(current);
		return *this;
	}

	Iterator operator++(int) {
		Iterator result = *this;
		this->operator++();
		return result;
	}

	/**
	* Returns the node with closest smaller value
	*/
	Iterator& operator--() {
		current = bst->find_predecessor(current);
		return *this;
	}

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
