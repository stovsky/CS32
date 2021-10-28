#ifndef Set_h
#define Set_h

#include <iostream>
#include <string>

using ItemType = std::string;

class Set
{
  public:
    Set(); // Default constructor
    Set(const Set& s); // Copy constructor
    Set& operator=(const Set& s); // Assignment operator
    ~Set(); // Destructor

    bool empty() const;

    int size() const;

    bool insert(const ItemType& value);

    bool erase(const ItemType& value);
  
    bool contains(const ItemType& value) const;
  
    bool get(int i, ItemType& value) const;

    void swap(Set& other);

    void dump() const;
    
private:

    // Node declaration
    struct Node {
        ItemType data;
        Node* next;
        Node* prev;
    };
    
    Node* head;
    Node* tail;
    int m_size;
    
};

void unite(const Set& s1, const Set& s2, Set& result);
void difference(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */
