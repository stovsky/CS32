#include <iostream>
#include <cassert>
#include "newSet.h"
using namespace std;

int main() {
    
    Set a(4);
    Set b(62);
    
    ItemType arr[6] = {"Tyler", "Matt", "Jill", "Lexi", "Mike", "Bailey"};
    for (int i = 0; i < 4; i++) {
        assert(a.insert(arr[i]));
    }
    for (int i = 3; i < 6; i++) {
        assert(b.insert(arr[i]));
    }
    
    assert(a.contains("Tyler") && a.contains("Matt") && a.contains("Jill") && a.contains("Lexi"));
    assert(b.contains("Lexi") && b.contains("Mike") && b.contains("Bailey"));
    
    assert(!a.insert("Tiger"));
    
    ItemType x;
    assert(a.get(0, x) && x == "Tyler");
    assert(b.get(0, x) && x == "Mike");
    
    assert(!a.get(99, x) && x == "Mike");
    
    Set c = a;
    assert(c.size() == 4);
    assert(c.contains("Tyler") && c.contains("Matt") && c.contains("Jill") && c.contains("Lexi"));
    assert(!c.contains("Mike"));
    
    c = b;
    assert(c.size() == 3);
    assert(c.contains("Lexi") && c.contains("Mike") && c.contains("Bailey"));
    assert(!c.contains("Matt"));
    
    a.swap(b);
    assert(a.size() == 3);
    assert(b.size() == 4);
    assert(!b.insert("Tiger"));
    
}
