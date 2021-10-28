#include "AccountSet.h"
#include <iostream>
using namespace std;

AccountSet::AccountSet() : m_accountSet()
{
}

bool AccountSet::add(unsigned long acctNum) {
    if (m_accountSet.contains(acctNum)) return false;
    m_accountSet.insert(acctNum);
    return true;
}

int AccountSet::size() const {
    return m_accountSet.size();
}

void AccountSet::print() const {
    ItemType x;
    for (int i = m_accountSet.size() - 1; i >= 0; i--) {
        m_accountSet.get(i, x);
        cout << x << endl;
    }
}
