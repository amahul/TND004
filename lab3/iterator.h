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

    Comparable* operator*() {
        return current->element;
    }

    Comparable& operator->() {
        &current->element;
    }

    bool operator==(const Iterator& it) {
        return (current == it.current);
    }

    bool operator!=(const Iterator& it) {
        return !(current == it.current);
    }

    Iterator& operator++() {
        current = bts->find_successor(current);
        return *this;
    }

    Iterator operator++(int) {
        Iterator result = *this;
        this->operator++();
        return result;
    }

    Iterator& operator--() {
        current = bts->find_predecessor(current);
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
    BinarySearchTree* bts = nullptr;

    Iterator(BinarySearchTree* p1, Node* p2) : bts{ p1 }, current{ p2 }{
    };


    // template <typename Comparable> // varför igen, krashar annars?
};
