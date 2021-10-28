#include "newSet.h"
#include <iostream>
using namespace std;

Set::Set() {
    m_size = 0;
    m_max = DEFAULT_MAX_ITEMS;
    m_set = new ItemType[m_max];
}

Set::Set(int size) {
    if (size < 0) size = DEFAULT_MAX_ITEMS;
    m_size = 0;
    m_max = size;
    m_set = new ItemType[m_max];
}

Set::Set(const Set& s) {
    m_size = s.m_size;
    m_max = s.m_max;
    m_set = new ItemType[s.m_max];
    for (int i = 0; i < m_size; i++) {
        m_set[i] = s.m_set[i];
    }
}

Set& Set::operator=(const Set &s) {
    if (this != &s) {
        m_size = s.m_size;
        m_max = s.m_max;
        delete [] m_set;
        m_set = new ItemType[s.m_max];
        for (int i = 0; i < m_size; i++) {
            m_set[i] = s.m_set[i];
        }
    }
    return *this;
}

Set::~Set() {
    delete [] m_set;
}

bool Set::empty() const {
    return m_size == 0;
}

int Set::size() const {
    return m_size;
}

void Set::dump() const {
    for (int i = 0; i < m_size; i++) {
        cerr << m_set[i] << " " << endl;
    }
}

bool Set::insert(const ItemType &value) {
     
    if (m_size >= DEFAULT_MAX_ITEMS || contains(value) || m_size + 1 > m_max) return false;

    int pos = m_size;
    for (int i = 0; i < m_size; i++) {
        if (value < m_set[i]) {pos = i; break;}
    }
    
    m_size++;
    for (int i = m_size - 1; i > pos; i--) {
        m_set[i] = m_set[i - 1];
    }
    m_set[pos] = value;
    return true;
}

bool Set::erase(const ItemType &value) {
    
    if (!contains(value)) return false;
    
    for (int i = 0; i < m_size; i++) {
        if (m_set[i] == value) {
            m_size--;
            for (int j = i; j < m_size; j++) {
                m_set[j] = m_set[j + 1];
            }
        }
    }
    return true;
}

bool Set::contains(const ItemType &value) const {
    
    for (int i = 0; i < m_size; i++) {
        if (m_set[i] == value) return true;
    }
    return false;
}

bool Set::get(int i, ItemType &value) const {
    
    if (i < 0 || i >= size()) return false;
    
    value = m_set[m_size - 1 - i];
    return true;
}

void Set::swap(Set &other) {
    
    int temp_size = other.m_size;
    other.m_size = this->m_size;
    this->m_size = temp_size;
    
    int temp_max = other.m_max;
    other.m_max = this->m_max;
    this->m_max = temp_max;
    
    ItemType* temp_set = other.m_set;
    other.m_set = this->m_set;
    this->m_set = temp_set;
    
}

