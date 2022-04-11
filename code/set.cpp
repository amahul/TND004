#include "set.h"
#include "node.h"

int Set::Node::count_nodes = 0;  // initialize total number of existing nodes to zero

/*****************************************************
 * Implementation of the member functions             *
 ******************************************************/

 // Used for debug purposes -- static member function
 // Return number of existing nodes
int Set::get_count_nodes() {
	return Set::Node::count_nodes;
}

// Default constructor
Set::Set() : counter{ 0 } {
	// IMPLEMENT before Lab1 HA

	head = new Node;
	tail = new Node;

	head->next = tail;
	tail->prev = head;
}

// Conversion constructor
Set::Set(int n) : Set{} {  // create an empty list
	// IMPLEMENT before Lab1 HA

	insert_node(tail, n);
}

// Constructor to create a Set from a sorted vector v
Set::Set(const std::vector<int>& v) : Set{} {  // create an empty list
	// IMPLEMENT before Lab1 HA

	// Loop through values in v
	for (size_t i = 0; i < v.size(); i++) {
		insert_node(tail, v[i]);
	}
}

// Make the set empty
void Set::make_empty() {
	// IMPLEMENT before Lab1 HA
	Node* temp = head->next;
	while (temp != tail) {
		remove_node(temp);
		temp = head->next;
	}

}

// Destructor
Set::~Set() {
	// Member function make_empty() can be used to implement the destructor
	// IMPLEMENT before Lab1 HA
	make_empty();
	remove_node(head);
	remove_node(tail);
	head = nullptr;
	tail = nullptr;
}

// Copy constructor
Set::Set(const Set& source) : Set{} {  // create an empty list
	// IMPLEMENT before Lab1 HA
	Node* copyNode = source.head->next;

	//std::cout << copyNode->value;
	while (copyNode != source.tail) {
		insert_node(tail, copyNode->value);
		copyNode = copyNode->next;
	}

}


// Copy-and-swap assignment operator
Set& Set::operator=(Set source) {
	// IMPLEMENT before Lab1 HA
	// Swap all private variables
	std::swap(counter, source.counter);

	std::swap(head, source.head);
	std::swap(tail, source.tail);

	return *this;
}

// Test set membership
bool Set::is_member(int val) const {
	// IMPLEMENT before Lab1 HA
	Node* iterator = head->next;
	while (iterator != tail) {
		// Return true if value exists
		if (iterator->value == val) return true;
		iterator = iterator->next;
	}
	return false;  // return false if val not found
}

// Test whether a set is empty
bool Set::is_empty() const {
	return (counter == 0);
}

// Return number of elements in the set
size_t Set::cardinality() const {
	return counter;
}

// Return true, if the set is a subset of b, otherwise false
// a <= b iff every member of a is a member of b
bool Set::less_than(const Set& b) const {
	// IMPLEMENT

	return false;  // remove this line
}

// Modify *this such that it becomes the union of *this with Set S
// Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S) {
	// IMPLEMENT

	return *this;
}

// Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S) {
	// IMPLEMENT

	return *this;
}

// Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S) {
	// IMPLEMENT

	return *this;
}

/* ******************************************** *
 * Private Member Functions -- Implementation   *
 * ******************************************** */

 // If you add any private member functions to class Set then write the implementation here


void Set::write_to_stream(std::ostream& os) const {
	if (is_empty()) {
		os << "Set is empty!";
	}
	else {
		Set::Node* temp{ head->next };

		os << "{ ";
		while (temp != tail) {
			os << temp->value << " ";
			temp = temp->next;
		}
		os << "}";
	}
}


// Insert a new Node storing val after the Node pointed by p
void Set::insert_node(Node* p, int val) {
	// IMPLEMENT before Lab1 HA
	// s.117-118 i kursbok, eller slide 6 föreläsning 4
	Node* newNode = new Node(val, p, p->prev); //step 1 and 2
	p->prev = p->prev->next = newNode; // step 3 and 4
	++counter;
}

// Remove the Node pointed by p
void Set::remove_node(Node* p) {
	// IMPLEMENT before Lab1 HA
	// s.118 i kursbok
	if (p->next) //if p has a next, repoint p->next->prev to the one node before p (removing from the beginning)
		p->next->prev = p->prev;

	if (p->prev) //if p has a prev, repoint p->prev->next to the one node after p (removing from the end)
		p->prev->next = p->next;

	delete p;
	counter--;
}
