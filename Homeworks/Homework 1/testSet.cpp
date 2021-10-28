#include <iostream>
#include <cassert>
#include "Set.h"
using namespace std;

int main() {
    
    Set a;
    Set b;
    
    ItemType arr[6] = {"Tyler", "Matt", "Jill", "Lexi", "Mike", "Bailey"};
    for (int i = 0; i < 4; i++) {
        assert(a.insert(arr[i]));
    }
    for (int i = 3; i < 6; i++) {
        assert(b.insert(arr[i]));
    }
    
    assert(a.contains("Tyler") && a.contains("Matt") && a.contains("Jill") && a.contains("Lexi"));
    assert(b.contains("Lexi") && b.contains("Mike") && b.contains("Bailey"));
    
    assert(!a.insert("Tyler"));
    assert(!b.insert("Bailey"));
    
    ItemType x;
    assert(a.get(0, x) && x == "Tyler");
    assert(b.get(0, x) && x == "Mike");
    
    assert(!a.get(99, x) && x == "Mike");

    a.swap(b);
    assert(a.size() == 3);
    assert(b.size() == 4);

    
}

