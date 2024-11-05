#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

/*int main() {
    Map m;  // maps strings to doubles
    assert(m.empty());
    ValueType v = -1234.5;
    assert(!m.get("abc", v) && v == -1234.5); // v unchanged by get failure
    m.insert("xyz", 9876.5);
    assert(m.size() == 1);
    KeyType ks = "hello";
    assert(m.get(0, ks, v) && ks == "xyz" && v == 9876.5);
    Map a(1000);   // a can hold at most 1000 key/value pairs
    Map b(5);      // b can hold at most 5 key/value pairs
    Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
    KeyType k[6] = { "sdnds", "dsjd", "ddsd", "sdsl", "ysds", "isds" };
    ValueType v2 = 2;

    // No failures inserting pairs with 5 distinct keys into b
    for (int n = 0; n < 5; n++)
        assert(b.insert(k[n], v));
    
    // Failure if we try to insert a pair with a sixth distinct key into b
    assert(!b.insert(k[5], v));
    // When two Maps' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(k[5], v) && b.insert(k[5], v));
    assert(a.contains("sdnds"));
    cout << "tests passed" << endl;
}*/