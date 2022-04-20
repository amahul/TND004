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

// Default constructor, O(1)
Set::Set() : counter{ 0 } { 
	// IMPLEMENTED
	head = new Node;
	tail = new Node;

	head->next = tail;
	tail->prev = head;
}

// Conversion constructor, O(1)
Set::Set(int n) : Set{} {  // create an empty list
	// IMPLEMENTED

	insert_node(tail, n);
}

// Constructor to create a Set from a sorted vector v, O(n)
Set::Set(const std::vector<int>& v) : Set{} {  // create an empty list
	// IMPLEMENTED

	// Loop through values in v
	for (size_t i = 0; i < v.size(); i++) {
		insert_node(tail, v[i]);
	}
}

// Make the set empty, O(n)
void Set::make_empty() {
	// IMPLEMENTED
	Node* temp = head->next;
	while (temp != tail) {
		remove_node(temp);
		temp = head->next;
	}

}

// Destructor, O(n)
Set::~Set() {
	// Member function make_empty() can be used to implement the destructor
	// IMPLEMENTED
	make_empty(); //O(n)
	delete head;
	delete tail;
	
	head = nullptr; //O(1)
	tail = nullptr; //O(1)
}

// Copy constructor, O(n)
Set::Set(const Set& source) : Set{} {  // create an empty list
	// IMPLEMENTED
	Node* copyNode = source.head->next;

	//std::cout << copyNode->value;
	while (copyNode != source.tail) {
		insert_node(tail, copyNode->value);
		copyNode = copyNode->next;
	}
}


// Copy-and-swap assignment operator, O(n)
Set& Set::operator=(Set source) {
	// IMPLEMENTED
	// Swap all private variables
	std::swap(counter, source.counter);

	std::swap(head, source.head);
	std::swap(tail, source.tail);

	return *this;
}

// Test set membership, O(n)
bool Set::is_member(int val) const {
	// IMPLEMENTED
	Node* iterator = head->next;
	while (iterator != tail) {
		// Return true if value exists
		if (iterator->value == val) return true;
		iterator = iterator->next;
	}
	return false;  // return false if val not found
}

// Test whether a set is empty, O(1)
bool Set::is_empty() const {
	return (counter == 0);
}

// Return number of elements in the set, O(1)
size_t Set::cardinality() const {
	return counter;
}

// Return true, if the set is a subset of b, otherwise false
// a <= b iff every member of a is a member of b
bool Set::less_than(const Set& b) const {
	// IMPLEMENTED

	// Create nodes to keep track of position
	Node* p1 = head->next;
	Node* p2 = b.head->next;

	// While node in head and S still has a value
	while (p1 != tail && p2 != b.tail) {

		// Return false if p1 (this) is smaller than p2
		if (p1->value < p2->value) return false;

		// Equal: Move in both (values already exists in p1)
		else if (p1->value == p2->value) {
			p1 = p1->next;
			p2 = p2->next;
		}

		// p2 (b) is smaller than p1
		else {
			p2 = p2->next;
		}

	}

	// larger values in p1 than in p2
	if(p1 != tail) {
		return false;
	}

	return true;
}

// Modify *this such that it becomes the union of *this with Set S
// Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S) {
	// IMPLEMENTED

	// Create nodes to keep track of position
	Node* p1 = head->next;
	Node* p2 = S.head->next;

	// While node in head and S still has a value
	while(p1 != tail && p2 != S.tail){
		
		// Move in p1 if p1 is smaller than p2
		if(p1->value < p2->value) p1 = p1->next;
		// Insert p2->value before p1 is p2->value is smaller and move in p2
		else if(p1->value > p2->value) {
			insert_node(p1, p2->value);
			p2 = p2->next;
		}
		// Equal: Move in both (values already exists in p1)
		else {
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	// Insert all remaining values from p2 in p1
	while(p2 != S.tail){
		insert_node(tail, p2->value);
		p2 = p2->next;
	}

	return *this;
}

// Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S) {
	// IMPLEMENTED

	// Create nodes to keep track of position
	Node* p1 = head->next;
	Node* p2 = S.head->next;

	// While node in head and S still has a value
	while (p1 != tail && p2 != S.tail) {
		
		// Move in p1 if value is smaller than p2, remove and move p1
		if (p1->value < p2->value) {
			p1 = p1->next;
			remove_node(p1->prev);
		}
		// Move in p2 if value is smaller than p1
		else if (p2->value < p1->value) p2 = p2->next;
		// Equal: Move in both (values already exists in p1)
		else {
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	// remove remaining values in p1
	while (p1 != tail) {
		p1 = p1->next;
		remove_node(p1->prev);
	}

	return *this;
}

// Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S) {
	// IMPLEMENTED

	// Create nodes to keep track of position
	Node* p1 = head->next;
	Node* p2 = S.head->next;

	// While node in head and S still has a value
	while (p1 != tail && p2 != S.tail) {

		// Move in p1 if p1 is equal to p2
		if (p1->value > p2->value) {
			p2 = p2->next;
		}
		// Move in p1 if value is smaller than p2
		else if (p1->value < p2->value) p1 = p1->next;
		// Equal: Move in both (values already exists in p1)
		else { 
			p1 = p1->next;
			p2 = p2->next;
			remove_node(p1->prev);
		}
	}

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


// Insert a new Node storing val after the Node pointed by p, O(1)
void Set::insert_node(Node* p, int val) {
	// IMPLEMENTED
	// s.117-118 i kursbok, eller slide 6 föreläsning 4
	Node* newNode = new Node(val, p, p->prev); //step 1 and 2
	p->prev = p->prev->next = newNode; // step 3 and 4
	++counter;
}

// Remove the Node pointed by p, O(1)
void Set::remove_node(Node* p) {
	// IMPLEMENTED
	// s.118 i kursbok
	p->next->prev = p->prev;
	p->prev->next = p->next;

	delete p;
	counter--;
}
