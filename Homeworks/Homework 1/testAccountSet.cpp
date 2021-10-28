#include "AccountSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    AccountSet as;
    assert(as.size() == 0);
    assert(as.add(444));
    assert(!as.add(444));
    assert(as.size() == 1);
    assert(as.add(123));
    assert(as.add(456));
    assert(as.size() == 3);
    assert(!as.add(123));
    assert(as.size() == 3);
    as.print();
}
