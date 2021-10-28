#include "Set.h"
#include <iostream>
using namespace std;

Set::Set() {
    m_size = 0;
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
     
    if (m_size >= DEFAULT_MAX_ITEMS || contains(value)) return false;

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
                m_set[j] = m_set[j+1];
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
    
    ItemType temp;
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
        temp = other.m_set[i];
        other.m_set[i] = this->m_set[i];
        this->m_set[i] = temp;
    }
    
}
