#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>  // used in node.h
#include <iterator> 
#include <vector>
#include "dsexceptions.h"

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree {
private:
	struct Node;  // nested class defined in node.h

public:
	class Iterator;  // Exercise 2: nested class to be defined in Iterator.h

	BinarySearchTree() : root{ nullptr } {
	}

	/**
	 * Copy constructor
	 * O(1)
	 */
	BinarySearchTree(const BinarySearchTree& rhs) : root{ clone(rhs.root) } {
	}

	/**
	* Constructor from vector
	*/
	explicit BinarySearchTree(const std::vector<Comparable>& V) {

		root = createBST(std::begin(V), std::end(V), nullptr);

	}

	/**
	 * Destructor for the tree
	 * O(n), goes through the entire tree and removes everything
	 */
	~BinarySearchTree() {
		makeEmpty();
	}

	/**
	 * Copy assignment: copy and swap idiom
	 * O(1)
	 */
	BinarySearchTree& operator=(BinarySearchTree _copy) {
		std::swap(root, _copy.root);
		return *this;
	}

	/**
	 * Find the smallest item in the tree.
	 * Throw UnderflowException if empty.
	 * O(1) if it's empty
	 * O(n) otherwise
	 */
	const Comparable& findMin() const {
		if (isEmpty()) {
			throw UnderflowException{};
		}

		return findMin(root)->element;
	}

	/**
	 * Find the largest item in the tree.
	 * Throw UnderflowException if empty.
	 * O(1) if it's empty
	 * O(n) otherwise
	 */
	const Comparable& findMax() const {
		if (isEmpty()) {
			throw UnderflowException{};
		}

		return findMax(root)->element;
	}

	/**
	 * Returns true if x is found in the tree.
	 * O(n)
	 */
	bool contains(const Comparable& x) const {
		return (contains(x, root) != nullptr);
	}

	/**
	 * Test if the tree is logically empty.
	 * Return true if empty, false otherwise.
	 * O(1)
	 */
	bool isEmpty() const {
		return root == nullptr;
	}

	/**
	 * Print the tree contents in sorted order.
	 * O(n)
	 */
	void printTree(std::ostream& out = std::cout) const {
		if (isEmpty()) {
			out << "Empty tree";
		}
		else {
			//inorder(root, out);
			preorder(root, out);
		}
	}

	/**
	 * Make the tree logically empty.
	 * O(n)
	 */
	void makeEmpty() {
		root = makeEmpty(root);
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 * Worst-case: O(n)
	 * Best-case: O(1)
	 */
	void insert(const Comparable& x) {
		root = insert(x, root);
	}

	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 * Worst-case: O(n)
	 * Best-case: O(1)
	 */
	void remove(const Comparable& x) {
		root = remove(x, root);
	}

	/** 
	 * Return total number of existing nodes
	 * Used for debug purposes
	 * O(1)
	 */
	static int get_count_nodes() {
		return Node::count_nodes;
	}


	/**
	* Returns the value stored in the parent of the node storing x
	* O(n)
	**/
	const Comparable get_parent(const Comparable& x) const {

		if (!root) return Comparable{};

		// Get node with value x
		Node* xNode = contains(x, root);

		// if xNode exist and it has a parent, return the parents element, otherwise return Comparable{}
		if (xNode != nullptr) {
			if (xNode->parent != nullptr) return xNode->parent->element;
			else return Comparable{};
		}
		else return Comparable{};
	}

	/**
	* Returns an iterator to the smallest value in tree
	* O(n) since findMin = O(n)
	**/
	Iterator begin() {
		if (isEmpty()) return end();

		return Iterator(this, findMin(root));
	}

	/**
	* Returns an iterator
	* O(1)
	**/
	Iterator end() {

		return Iterator(this, nullptr);
	}


	/**
	* Returns an iterator poitning to the Node storing value x
	* O(n) since contains = O(n)
	**/
	Iterator find(const Comparable& x) {
		// Check if tree contains x
		Node* res = contains(x, root);
		if (res) return Iterator(this, res); //Iteratorn m?ste veta vilket tr?d den tillh?r (this), inte nullptr
		else return end();
	}


private:
	Node* root;

	/**
	 * Private member function to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Return a pointer to the node storing x.
	 * O(n)
	 */
	Node* insert(const Comparable& x, Node* t) { //Node* parent
		if (t == nullptr) {
			t = new Node{ x, nullptr, nullptr }; //, parent
		}
		else if (x < t->element) {
			t->left = insert(x, t->left); //skippa parent nedanf?r h?r
			t->left->parent = t;    //set parent of new node to t
		}
		else if (t->element < x) {
			t->right = insert(x, t->right);
			t->right->parent = t;   //set parent of new node to t
		}
		else {
			;  // Duplicate; do nothing
		}
		return t;
	}

	/**
	 * Private member function to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Return a pointer to the new root of the subtree that had root x
	 * O(n)
	 */
	Node* remove(const Comparable& x, Node* t) {
		if (t == nullptr) {
			return t;  // Item not found
		}
		if (x < t->element) {
			t->left = remove(x, t->left);
		}
		else if (t->element < x) {
			t->right = remove(x, t->right);
		}
		else if (t->left != nullptr && t->right != nullptr) {  // Two children
			t->element = findMin(t->right)->element;
			t->right = remove(t->element, t->right);
		}
		else {
			Node* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			if (t != nullptr) t->parent = oldNode->parent; // repoint parent till grandparent
			delete oldNode;
		}
		return t;
	}

	/**
	 * Private member function to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 * O(n)
	 */
	Node* findMin(Node* t) const {
		if (t == nullptr) {
			return nullptr;
		}
		if (t->left == nullptr) {
			return t;
		}

		// Tail recursion can be easily replaced by a loop
		return findMin(t->left);  // recursive call
	}

	/**
	 * Private member function to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 * O(n)
	 */
	Node* findMax(Node* t) const {
		if (t != nullptr) {
			while (t->right != nullptr) {
				t = t->right;
			}
		}
		return t;
	}

	/**
	 * Private member function to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the subtree.
	 * Return a pointer to the node storing x, if x is found
	 * Otherwise, return nullptr
	 * O(n)
	 */
	Node* contains(const Comparable& x, Node* t) const {
		if (t == nullptr) {
			return t;
		}
		else if (x < t->element) {
			return contains(x, t->left);
		}
		else if (t->element < x) {
			return contains(x, t->right);
		}
		else {
			return t;  // Match
		}
	} // in the course book, this function returns a bool

	/****** NONRECURSIVE VERSION*************************
	Node *contains(const Comparable &x, Node *t) const {
		while (t != nullptr) {
			if (x < t->element) {
				t = t->left;
			} else if (t->element < x) {
				t = t->right;
			} else {
				return t;  // Match
			}
		}
		return t;  // No match
	}
	*****************************************************/

	/**
	 * Private member function to make subtree empty.
	 * O(n)
	 */
	Node* makeEmpty(Node* t) {
		if (t != nullptr) {
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		return nullptr;
	}

	/**
	 * Private member function to print a subtree rooted at t in sorted order.
	 * In-order traversal is used
	 * O(n)
	 */
	void inorder(Node* t, std::ostream& out) const {
		if (t != nullptr) {
			inorder(t->left, out);
			out << t->element << '\n';
			inorder(t->right, out);
		}
	}

	/**
   * Private member function to print a subtree rooted at t in sorted order.
   * Pre-order traversal is used
   * O(n)
   */
	void preorder(Node* t, std::ostream& out, int indent = 2) const {
		if (t != nullptr) {
			out << std::setw(indent) << t->element << '\n';
			preorder(t->left, out, indent + 2);
			preorder(t->right, out, indent + 2);
		}
	}

	/**
	 * Private member function to clone subtree.
	 * O(n)
	 */
	Node* clone(Node* t, Node* pt = nullptr) const {
		if (t == nullptr) {
			return nullptr;
		}
		else {

			// Create new node with value of t
			Node* temp = new Node{ t->element };

			// Recursive call for "children", temp is parent
			temp->left = clone(t->left, temp);
			temp->right = clone(t->right, temp);

			// Set parent
			temp->parent = pt;

			return temp;

			//return new Node{t->element, clone(t->left), clone(t->right)};
		}
	}

	/**
	* Private member function to create a BST from a sorted vector
	* O(n)
	*/
	Node* createBST(typename std::vector<Comparable>::const_iterator first, typename std::vector<Comparable>::const_iterator last, Node* parent) {

		int n = std::distance(first, last);

		if (n == 0) return nullptr;

		typename std::vector<Comparable>::const_iterator mid = std::next(first, n / 2);
		Node* midNode = new Node{ *mid, nullptr, nullptr, parent };

		//if(root) std::cout << "root = " << root->element << '\n';

		midNode->left = createBST(first, mid, midNode);
		midNode->right = createBST(std::next(mid), last, midNode);

		return midNode;
	}


	/**
	* Private member function to find successor of element stored in node t
	* example: seq: {1, 2, 3, 4, 5},  successor to 3 = 4
	*/
	Node* find_successor(Node* t) const {

		// empty tree
		if (t == nullptr) return nullptr;

		// If t has a node to the right, then that value is bigger than t, find the smallest value in the right branch to get the successor.
		if (t->right != nullptr) return findMin(t->right);

		// If we don't have a node to the right, then climb back up until the node has a node to the left.

		Node* child = t;
		Node* parent = child->parent;

		while (parent != nullptr && child == parent->right) {
			child = parent;
			parent = child->parent;
		}

		// Returns pointer to the node storing the successor of the value given in node t, 
		return parent;
	}

	/**
	* Private member function to find predecessor of element stored in node t
	* example: seq: {1, 2, 3, 4, 5},  predecessor to 3 = 2
	*/
	Node* find_predecessor(Node* t) const {

		// empty tree
		if (t == nullptr) return nullptr;

		// If t has a node to the left, then that value is smaller than t, find the largest value in the left branch to get the predecessor.
		if (t->left != nullptr) return findMax(t->left);

		// If we don't have a node to the left, then climb back up until the node has a node to the right.
		/*while (t->parent != nullptr && t != t->parent->right) {
			t = t->parent;
		}*/

		Node* child = t;
		Node* parent = child->parent;

		while (parent != nullptr && child == parent->left) {
			child = parent;
			parent = child->parent;
		}

		// Returns pointer to the node storing the successor of the value given in node t, 
		return parent;
	}

};

// Include definitions of the nested classes
#include "node.h"
#include "iterator.h"