#include <iostream>
#include "Set.h"
using namespace std;

Set::Set() {
    // Create an empty set
    m_size = 0;
    head = nullptr;
    tail = nullptr;
}

Set::~Set() {
    // Deletes all dynamically allocated memory
    Node* p = head;
    while (head != nullptr) {
        p = head;
        head = head->next;
        delete p;
    }
}

Set::Set(const Set& other) {
    
    // Set sizes equal to each other
    m_size = other.m_size;
    
    // If the other set is empty, create a new empty set
    if (other.m_size == 0) {
        head = nullptr;
        tail = nullptr;
    }
    // If the other set is not empty, create a new set
    else {
        head = new Node;
        head->prev = nullptr;
        Node* p = head;
        
        // Copy every node except for the last node
        for (Node* n = other.head; n->next != nullptr; n = n->next) {
            Node* addNode = new Node;
            p->data = n->data;
            p->next = addNode;
            addNode->prev = p;
            p = addNode;
        }
        
        // Copy the tail node
        p->data = other.tail->data;
        p->next = nullptr;
        tail = p;
    }
    
}

Set& Set::operator=(const Set &s) {
    
    // Check if the lists are the same
    if (this != &s) {
        Set temp(s); // Copy the right hand side into a temporary Set
        swap(temp); // Swap left hand side with the temporary Set
    }
    return *this;
}

bool Set::insert(const ItemType &value) {
    // Check if the value is already in the list
    if (contains(value)) return false;
    
    // Create a new node to be inserted and set its value
    Node* n = new Node;
    n->data = value;
    
    // Case 1: List is empty
    if (head == nullptr) {
        // Connect the first node
        head = n;
        tail = n;
        n->prev = nullptr;
        n->next = nullptr;
    }
    // Case 2: List is not empty
    else {
        // Connect the new node to the end of the list
        tail->next = n;
        n->prev = tail;
        tail = n;
        n->next = nullptr;
    }
    // Increment size
    m_size++;
    return true;
}

int Set::size() const {
    // Return the size of the list
    return m_size;
}

bool Set::empty() const {
    // Return whether the list is empty or not
    return m_size == 0;
}

bool Set::erase(const ItemType &value) {
    // Check if the value is in the list
    if (!contains(value)) return false;
    
    // Find the node in the list to be deleted
    Node* p = head;
    while (p->data != value) {
        p = p->next;
    }
    
    // If the node to be delete isn't the head node, connect the previous node to the node's next node
    if (p->prev != nullptr) p->prev->next = p->next;
    
    // If the node to be deleted is the head node, connect head node to next entry
    else head = p->next;
    
    // If the node to be deleted isn't the tail node, connect the next node to the node's previous node
    if (p->next != nullptr) p->next->prev = p->prev;
    
    // If the node to be deleted is the tail node, connect tail node to previous entry
    else tail = p->prev;
    
    // Decrease size of list
    m_size--;
    
    // Delete the node we removed
    delete p;
    
    return true;
}

bool Set::contains(const ItemType &value) const {
    // Check if the list is empty
    if (head == nullptr) return false;
    
    // Loop through each node in the list
    for (Node* p = head; p != nullptr; p = p->next) {
        // Return true if value is found
        if (p->data == value) return true;
    }

    return false;
}

bool Set::get(int i, ItemType &value) const {
    // Check if the index is valid
    if (i < 0 || i >= size()) return false;
    
    // Create a temporary copy of our Set so we can delete nodes from it
    Set temp(*this);
    
    // Delete the maximum value i number of times
    for (int j = 0; j < i; j++) {
        
        // Loop through the set and find the maximum value
        ItemType max = temp.head->data;
        for (Node* p = temp.head; p != nullptr; p = p->next) {
            if (p->data > max) max = p->data;
        }
        // Delete the maximum value
        temp.erase(max);
    }
    
    // Find the new maximum value
    ItemType max = temp.head->data;
    for (Node* p = temp.head; p != nullptr; p = p->next) {
        if (p->data > max) max = p->data;
    }
    
    // Set value equal to the new maximum
    value = max;
    
    return true;
}

void Set::swap(Set &other) {
    
    // Swap the sizes
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
    
    // Swap the head nodes
    Node* tempHead = head;
    head = other.head;
    other.head = tempHead;
    
    // Swap the tail nodes
    Node* tempTail = tail;
    tail = other.tail;
    other.tail = tempTail;
}


void Set::dump() const {
    // Print out the value of each entry
    for (Node* p = head; p != nullptr; p = p->next) {
        cerr << p->data << " ";
    }
}

void unite(const Set& s1, const Set& s2, Set& result) {
    
    // Copy s1 into result
    result = s1;
    
    // Loop through the entries in s2
    for (int i = 0; i < s2.size(); i++) {
        // Get the item to insert
        ItemType temp;
        s2.get(i, temp);
        // Insert item into result -> Insert function only inserts if item is not a duplicate
        result.insert(temp);
    }
    
}

void difference(const Set& s1, const Set& s2, Set& result) {
    
    // Copy s1 into result
    result = s1;
    
    // Loop through entries in s2
    for (int i = 0; i < s2.size(); i++) {
        // Get the item to erase
        ItemType temp;
        s2.get(i, temp);
        // If result contains an item in s2, erase that item
        if (result.contains(temp)) result.erase(temp);
        
        // If result doesn't contain an item in s2, insert that item
        else result.insert(temp);
    }
    
}
