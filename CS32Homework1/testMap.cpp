#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

/*    int main()
    {
        Map m;  // maps strings to doubles
        assert(m.empty());
        ValueType v = -1234.5;
        assert(!m.get("abc", v) && v == -1234.5); // v unchanged by get failure
        m.insert("xyz", 9876.5);
        assert(m.size() == 1);
        KeyType k = "hello";
        assert(m.get(0, k, v) && k == "xyz" && v == 9876.5);
        assert(!m.get(2, k, v) && k == "xyz" && v == 9876.5);
        Map p;
        p.insert("x", 33);
        assert(!p.insert("x", 33));
        p.insert("idk", 2);
        assert(p.size() == 2);
        p.swap(m);
        assert(p.contains("xyz"));
        assert(!p.contains("idk"));
        assert(p.size() == 1);
        assert(m.size() == 2);
        cout << "Passed all tests" << endl;
    } */