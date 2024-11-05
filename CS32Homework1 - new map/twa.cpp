// tester.cpp
// To test HW 1 Problem 5, uncomment the following line:
// #define TESTNEW

// #ifdef TESTNEW
#include "newMap.h"  // Make KeyType a type alias for std::string, ValueType for double
// #else */
// #include "Map.h"  // Make KeyType a type alias for std::string, ValueType for double
/*#endif*/

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <type_traits>
using namespace std;

const KeyType DUMMY = "junk";
const KeyType DEFAULT = "";
const KeyType ARRAY[6] = {
    "alfa", "baker", "charlie", "delta", "echo", "foxtrot"
};

const ValueType DUMMYV = 123;
const ValueType DEFAULTV = 0;
const ValueType ARRAYV[6] = { 10, 20, 30, 40, 50, 60 };

bool has(const Map& m, const KeyType& k, const ValueType& v)
{
    ValueType v2 = DEFAULTV;
    m.get(k, v2);
    ValueType v3 = DUMMYV;
    m.get(k, v3);
    return v2 == v && v3 == v;
}

const int SPEC_MAX = 150;

bool get2type(bool (Map::*)(const KeyType&, ValueType&) const) { return true; }
bool get2type(bool (Map::*)(const KeyType&, ValueType&)) { return false; }
bool get2type(...) { return false; }
bool get3type(bool (Map::*)(int, KeyType&, ValueType&) const) { return true; }
bool get3type(bool (Map::*)(int, KeyType&, ValueType&)) { return false; }
bool get3type(...) { return false; }

void testone(int n)
{
    if (n <= 5)
    {
        switch (n)
        {
        default: {
            cout << "Bad argument" << endl;
        } break; case  1: {
            assert((is_same<decltype(&Map::empty), bool (Map::*)() const>::value));
        } break; case  2: {
            assert((is_same<decltype(&Map::size), int (Map::*)() const>::value));
        } break; case  3: {
            assert((is_same<decltype(&Map::contains), bool (Map::*)(const KeyType&) const>::value));
        } break; case  4: {
            assert(get2type(&Map::get));
        } break; case  5: {
            assert(get3type(&Map::get));
        }
        }
        return;
    }
    Map m;
    switch (n)
    {
    default: {
        cout << "Bad argument" << endl;
    } break; case  1: {
        assert((is_same<decltype(&Map::empty), bool (Map::*)() const>::value));
    } break; case  2: {
        assert((is_same<decltype(&Map::size), int (Map::*)() const>::value));
    } break; case  3: {
        assert((is_same<decltype(&Map::contains), bool (Map::*)(const KeyType&) const>::value));
    } break; case  4: {
        assert(get2type(&Map::get));
    } break; case  5: {
        assert(get3type(&Map::get));
    } break; case  6: {
        assert(m.empty());
    } break; case  7: {
        assert(m.size() == 0);
    } break; case  8: {
        assert(!m.update(DEFAULT, DUMMYV) && m.size() == 0);
    } break; case  9: {
        assert(!m.erase(DEFAULT) && m.size() == 0);
    } break; case 10: {
        assert(!m.contains(DEFAULT));
    } break; case 11: {
        ValueType v = DUMMYV;
        assert(!m.get(DEFAULT, v) && v == DUMMYV);
    } break; case 12: {
        KeyType k = DEFAULT;
        ValueType v = DUMMYV;
        assert(!m.get(0, k, v) && k == DEFAULT && v == DUMMYV);
    } break; case 13: {
        assert(m.insert(DUMMY, DUMMYV));
    } break; case 14: {
        m.insert(DUMMY, DUMMYV);
        assert(!m.empty());
    } break; case 15: {
        m.insert(DUMMY, DUMMYV);
        assert(m.size() == 1);
    } break; case 16: {
        m.insert(DUMMY, DUMMYV);
        assert(m.contains(DUMMY));
    } break; case 17: {
        m.insert(DUMMY, DUMMYV);
        ValueType v = DEFAULTV;
        assert(m.get(DUMMY, v));
    } break; case 18: {
        m.insert(DUMMY, DUMMYV);
        ValueType v = DEFAULTV;
        m.get(DUMMY, v);
        assert(v == DUMMYV);
    } break; case 19: {
        m.insert(ARRAY[1], DUMMYV);
        ValueType v = DEFAULTV;
        assert(!m.get(ARRAY[0], v) && !m.get(ARRAY[2], v));
    } break; case 20: {
        m.insert(ARRAY[1], ARRAYV[1]);
        ValueType v = DUMMYV;
        m.get(ARRAY[0], v);
        assert(v == DUMMYV);
        m.get(ARRAY[2], v);
        assert(v == DUMMYV);
    } break; case 21: {
        m.insert(DUMMY, DUMMYV);
        KeyType k = DEFAULT;
        ValueType v = DEFAULTV;
        assert(m.get(0, k, v));
    } break; case 22: {
        m.insert(DUMMY, DUMMYV);
        KeyType k = DEFAULT;
        ValueType v = DEFAULTV;
        m.get(0, k, v);
        assert(k == DUMMY && v == DUMMYV);
    } break; case 23: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        assert(!m.empty() && m.size() == 2);
    } break; case 24: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        assert(m.contains(ARRAY[0]) && m.contains(ARRAY[1]));
    } break; case 25: {
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[0], ARRAYV[0]);
        assert(has(m, ARRAY[0], ARRAYV[0]) && has(m, ARRAY[1], ARRAYV[1]));
    } break; case 26: {
        m.insert(ARRAY[0], DUMMYV);
        m.insert(ARRAY[1], DUMMYV);
        assert(has(m, ARRAY[0], DUMMYV) && has(m, ARRAY[1], DUMMYV));
    } break; case 27: {
        assert(m.insert(ARRAY[1], ARRAYV[1]));
        assert(m.insert(ARRAY[0], ARRAYV[0]));
    } break; case 28: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[0], ARRAYV[2]);
        assert(m.size() == 2);
    } break; case 29: {
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[2]);
        assert(has(m, ARRAY[0], ARRAYV[0]) && has(m, ARRAY[1], ARRAYV[1]));
    } break; case 30: {
        assert(m.insert(ARRAY[0], ARRAYV[0]));
        assert(m.insert(ARRAY[1], ARRAYV[1]));
        assert(!m.insert(ARRAY[0], ARRAYV[2]));
    } break; case 31: {
        assert(m.insert(ARRAY[1], ARRAYV[1]));
        assert(m.insert(ARRAY[0], ARRAYV[0]));
        assert(!m.insert(ARRAY[1], ARRAYV[1]));
    } break; case 32: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        m.update(ARRAY[1], DUMMYV);
        assert(m.size() == 3 && m.contains(ARRAY[0]) &&
            m.contains(ARRAY[1]) && m.contains(ARRAY[2]));
    } break; case 33: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        m.update(ARRAY[1], DUMMYV);
        assert(has(m, ARRAY[0], ARRAYV[0]) && has(m, ARRAY[1], DUMMYV) &&
            has(m, ARRAY[2], ARRAYV[2]));
    } break; case 34: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        assert(m.update(ARRAY[1], DUMMYV));
    } break; case 35: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.update(ARRAY[2], ARRAYV[0]);
        assert(m.size() == 2 && has(m, ARRAY[0], ARRAYV[0]) &&
            has(m, ARRAY[1], ARRAYV[1]) && !m.contains(ARRAY[2]));
    } break; case 36: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        assert(!m.update(ARRAY[2], ARRAYV[2]) && !m.update(ARRAY[3], ARRAYV[0]));
    } break; case 37: {
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insertOrUpdate(ARRAY[0], ARRAYV[0]);
        assert(!m.empty() && m.size() == 2);
    } break; case 38: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insertOrUpdate(ARRAY[1], ARRAYV[1]);
        assert(has(m, ARRAY[0], ARRAYV[0]) && has(m, ARRAY[1], ARRAYV[1]));
    } break; case 39: {
        m.insert(ARRAY[0], DUMMYV);
        m.insertOrUpdate(ARRAY[1], DUMMYV);
        assert(has(m, ARRAY[0], DUMMYV) && has(m, ARRAY[1], DUMMYV));
    } break; case 40: {
        assert(m.insert(ARRAY[1], ARRAYV[1]));
        assert(m.insertOrUpdate(ARRAY[0], ARRAYV[0]));
    } break; case 41: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insertOrUpdate(ARRAY[0], ARRAYV[2]);
        assert(m.size() == 2 && has(m, ARRAY[0], ARRAYV[2]) &&
            has(m, ARRAY[1], ARRAYV[1]));
    } break; case 42: {
        assert(m.insert(ARRAY[0], ARRAYV[0]));
        assert(m.insert(ARRAY[1], ARRAYV[1]));
        assert(m.insertOrUpdate(ARRAY[0], ARRAYV[2]));
    } break; case 43: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        m.insertOrUpdate(ARRAY[1], DUMMYV);
        assert(m.size() == 3 && has(m, ARRAY[0], ARRAYV[0]) &&
            has(m, ARRAY[1], DUMMYV) && has(m, ARRAY[2], ARRAYV[2]));
    } break; case 44: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        assert(m.insertOrUpdate(ARRAY[1], DUMMYV));
    } break; case 45: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insertOrUpdate(ARRAY[2], ARRAYV[0]);
        assert(m.size() == 3 && has(m, ARRAY[0], ARRAYV[0]) &&
            has(m, ARRAY[1], ARRAYV[1]) && has(m, ARRAY[2], ARRAYV[0]));
    } break; case 46: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        assert(m.insertOrUpdate(ARRAY[2], ARRAYV[2]));
    } break; case 47: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        assert(m.erase(ARRAY[1]));
    } break; case 48: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.erase(ARRAY[1]);
        assert(!m.empty() && m.size() == 1 && has(m, ARRAY[0], ARRAYV[0]) &&
            !m.contains(ARRAY[1]));
    } break; case 49: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.erase(ARRAY[0]);
        assert(!m.empty() && m.size() == 1 && has(m, ARRAY[1], ARRAYV[1]) &&
            !m.contains(ARRAY[0]));
    } break; case 50: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.erase(ARRAY[0]);
        m.erase(ARRAY[1]);
        assert(m.size() == 0);
    } break; case 51: {
        m.insert(ARRAY[3], ARRAYV[3]);
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[4], ARRAYV[4]);
        m.erase(ARRAY[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.erase(ARRAY[4]);
        m.insert(ARRAY[5], ARRAYV[5]);
        m.erase(ARRAY[3]);
        m.insert(ARRAY[2], ARRAYV[2]);
        assert(m.size() == 3 && has(m, ARRAY[1], ARRAYV[1]) &&
            has(m, ARRAY[2], ARRAYV[2]) && has(m, ARRAY[5], ARRAYV[5]) &&
            !m.contains(ARRAY[0]) && !m.contains(ARRAY[3]) &&
            !m.contains(ARRAY[4]));
    } break; case 52: {
        m.insert(ARRAY[3], ARRAYV[3]);
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[3], ARRAYV[3]);
        m.insert(ARRAY[4], ARRAYV[4]);
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[4], ARRAYV[4]);
        m.erase(ARRAY[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.erase(ARRAY[4]);
        m.insert(ARRAY[5], ARRAYV[5]);
        m.erase(ARRAY[3]);
        m.insert(ARRAY[2], ARRAYV[2]);
        m.insert(ARRAY[1], ARRAYV[1]);
        assert(m.size() == 3 && has(m, ARRAY[1], ARRAYV[1]) &&
            has(m, ARRAY[2], ARRAYV[2]) && has(m, ARRAY[5], ARRAYV[5]) &&
            !m.contains(ARRAY[0]) && !m.contains(ARRAY[3]) &&
            !m.contains(ARRAY[4]));
    } break; case 53: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        assert(!m.erase(ARRAY[2]) && m.size() == 2);
    } break; case 54: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        KeyType k;
        ValueType v;
        assert(!m.get(-1, k, v));
    } break; case 55: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        KeyType k = DUMMY;
        ValueType v = DUMMYV;
        m.get(-1, k, v);
        assert(k == DUMMY && v == DUMMYV);
    } break; case 56: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        KeyType k;
        ValueType v;
        assert(!m.get(2, k, v));
    } break; case 57: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        KeyType k = DUMMY;
        ValueType v = DUMMYV;
        m.get(2, k, v);
        assert(k == DUMMY && v == DUMMYV);
    } break; case 58: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        KeyType k = DUMMY;
        ValueType v = DUMMYV;
        m.get(0, k, v);
        assert(k == ARRAY[0]);
    } break; case 59: {
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[0], ARRAYV[0]);
        KeyType k = DUMMY;
        ValueType v = DUMMYV;
        m.get(0, k, v);
        assert(k == ARRAY[0]);
    } break; case 60: {
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[0], ARRAYV[0]);
        KeyType k0 = DUMMY;
        ValueType v0 = DUMMYV;
        m.get(0, k0, v0);
        KeyType k1 = DUMMY;
        ValueType v1 = DUMMYV;
        m.get(1, k1, v1);
        assert(k0 == ARRAY[0] && v0 == ARRAYV[0] && k1 == ARRAY[1] && v1 == ARRAYV[1]);
    } break; case 61: {
        m.insert(ARRAY[3], ARRAYV[3]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[4], ARRAYV[4]);
        m.insert(ARRAY[2], ARRAYV[2]);
        assert(m.size() == 5);
        KeyType k;
        ValueType v;
        for (int i = 0; i < 5; i++)
        {
            m.get(i, k, v);
            assert(k == ARRAY[i]);
        }
    } break; case 62: {
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[0], ARRAYV[0]);
        assert(m.size() == 2);
        KeyType k;
        ValueType v;
        for (int i = 0; i < 2; i++)
        {
            m.get(i, k, v);
            assert(k == ARRAY[i]);
        }
    } break; case 63: {
        m.insert(DEFAULT, DUMMYV);
        assert(m.size() == 1 && has(m, DEFAULT, DUMMYV));
    } break; case 64: {
        m.update(DEFAULT, DUMMYV);
        assert(m.size() == 0 && !m.contains(DEFAULT));
    } break; case 65: {
        m.insertOrUpdate(DEFAULT, DUMMYV);
        assert(m.size() == 1 && has(m, DEFAULT, DUMMYV));
    } break; case 66: {
        m.insert(DEFAULT, DUMMYV);
        m.erase(DEFAULT);
        assert(m.size() == 0 && !m.contains(DEFAULT));
    } break; case 67: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        {
            Map m2;
            m2.insert(ARRAY[2], ARRAYV[2]);
            m2.insert(ARRAY[3], ARRAYV[3]);
            m.swap(m2);
            assert(m.size() == 2 && m2.size() == 2);
            for (int k = 0; k < 2; k++)
            {
                assert(!has(m, ARRAY[k], ARRAYV[k]));
                assert(has(m2, ARRAY[k], ARRAYV[k]));
            }
            for (int k = 2; k < 4; k++)
            {
                assert(has(m, ARRAY[k], ARRAYV[k]));
                assert(!has(m2, ARRAY[k], ARRAYV[k]));
            }
        }
    } break; case 68: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        {
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[4], ARRAYV[4]);
            m.swap(m2);
            assert(m.size() == 2 && m2.size() == 3);
        }
    } break; case 69: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        {
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[4], ARRAYV[4]);
            m.swap(m2);
            for (int k = 0; k < 3; k++)
            {
                assert(!has(m, ARRAY[k], ARRAYV[k]));
                assert(has(m2, ARRAY[k], ARRAYV[k]));
            }
            for (int k = 3; k < 5; k++)
            {
                assert(has(m, ARRAY[k], ARRAYV[k]));
                assert(!has(m2, ARRAY[k], ARRAYV[k]));
            }
        }
    } break; case 70: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        {
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[4], ARRAYV[4]);
            m2.swap(m);
            for (int k = 0; k < 3; k++)
            {
                assert(!has(m, ARRAY[k], ARRAYV[k]));
                assert(has(m2, ARRAY[k], ARRAYV[k]));
            }
            for (int k = 3; k < 5; k++)
            {
                assert(has(m, ARRAY[k], ARRAYV[k]));
                assert(!has(m2, ARRAY[k], ARRAYV[k]));
            }
        }
    } break; case 71: {
        KeyType k;
        for (int n = 0; n < SPEC_MAX; n++)
        {
            assert(m.insert(k, DUMMYV));
            k += 'x';
        }
        assert(m.size() == SPEC_MAX);
    } break; case 72: {
        KeyType k;
        for (int n = 0; n < SPEC_MAX; n++)
        {
            assert(m.insert(k, DUMMYV));
            k += 'x';
        }
        assert(!m.insert(k, DUMMYV) && m.size() == SPEC_MAX && !m.contains(k));
    } break; case 73: {
        assert(m.insert(DUMMY, DUMMYV));
        for (int n = 0; n < 10 * SPEC_MAX; n++)
            assert(m.insertOrUpdate(DUMMY, DUMMYV));
        assert(m.size() == 1);
    } break; case 74: {
        KeyType k;
        KeyType kfirst;
        for (int n = 0; n < SPEC_MAX; n++)
        {
            if (n == 0)
            {
                kfirst = k;
                assert(m.insert(kfirst, DUMMYV));
            }
            else
                assert(m.insert(k, DUMMYV));
            k += 'x';
        }
        assert(!m.insert(k, DUMMYV));
        m.erase(kfirst);
        assert(m.insert(k, DUMMYV));
        k += 'x';
        assert(!m.insert(k, DUMMYV));
    } break; case 75: {
        const int CAPACITY = 2;
        Map m2(CAPACITY);
        KeyType k;
        for (int n = 0; n < CAPACITY; n++)
        {
            assert(m2.insert(k, DUMMYV));
            k += 'x';
        }
        assert(!m2.insert(k, DUMMYV));
    } break; case 76: {
        const int CAPACITY = SPEC_MAX * 2;
        Map m2(CAPACITY);
        KeyType k;
        for (int n = 0; n < CAPACITY; n++)
        {
            assert(m2.insert(k, DUMMYV));
            k += 'x';
        }
        assert(!m2.insert(k, DUMMYV));
    } break; case 77: {
        const int CAPACITY = SPEC_MAX * 2;
        Map m2(CAPACITY);
        KeyType keys[CAPACITY];
        KeyType k;
        for (int n = 0; n < CAPACITY; n++)
        {
            keys[n] = k;
            k += 'x';
        }
        for (int n = 0; n < CAPACITY / 2; n++)
        {
            assert(m2.insert(keys[n], DUMMYV));
            assert(m2.insert(keys[CAPACITY - 1 - n], DUMMYV));
        }
        for (int n : { CAPACITY - 1, 0, 2 * CAPACITY / 3, CAPACITY / 3 })
        {
            KeyType k;
            ValueType v;
            assert(m2.get(n, k, v) && k == keys[n]);
        }
    } break; case 78: {
        const int CAPACITY = 2;
        Map m2(CAPACITY);
        m.swap(m2);
        KeyType k;
        for (int n = 0; n < CAPACITY; n++)
        {
            assert(m.insert(k, DUMMYV));
            k += 'x';
        }
        assert(!m.insert(k, DUMMYV));
        for (int n = 0; n < SPEC_MAX; n++)
        {
            assert(m2.insert(k, DUMMYV));
            k += 'x';
        }
        assert(!m2.insert(k, DUMMYV));
    } break; case 79: {
        // This test checked that swap takes the same amount of time
        // no matter how many items are in the Maps.
    } break; case 80: {
        // This test checked that the destructor deletes the dynamic array.
    } break; case 81: {
        // This test checked that a copied map allocates a new array.
    } break; case 82: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        {
            Map m2(m);
            m2.insert(ARRAY[3], ARRAYV[3]);
            assert(m2.size() == m.size() + 1);
        }
    } break; case 83: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        {
            Map m2(m);
            m2.insert(ARRAY[3], ARRAYV[3]);
            assert(m2.size() == 4);
            for (int n = 0; n < m2.size(); n++)
            {
                KeyType k;
                ValueType v;
                m2.get(n, k, v);
                assert(k == ARRAY[n]);
            }
        }
    } break; case 84: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        m.insert(ARRAY[2], ARRAYV[2]);
        {
            Map m2(m);
            m2.insert(ARRAY[3], ARRAYV[3]);
            assert(m.size() == 3);
            for (int n = 0; n < m.size(); n++)
            {
                KeyType k;
                ValueType v;
                m.get(n, k, v);
                assert(k == ARRAY[n]);
            }
        }
    } break; case 85: {
        {
            Map m2;
            Map m3(m2);
            assert(m2.size() == 0 && m3.size() == 0);
            m2.insert(ARRAY[0], ARRAYV[0]);
            m3.insert(ARRAY[1], ARRAYV[1]);
            assert(m2.size() == 1 && m3.size() == 1);
            KeyType k;
            ValueType v;
            m2.get(0, k, v);
            assert(k == ARRAY[0]);
            m3.get(0, k, v);
            assert(k == ARRAY[1]);
        }
    } break; case 86: {
        {
            Map m2(2);
            m2.insert(ARRAY[0], ARRAYV[0]);
            m2.insert(ARRAY[1], ARRAYV[1]);
            Map m3(m2);
            assert(!m3.insert(ARRAY[2], ARRAYV[2]));
        }
    } break; case 87: {
        // This test checked that the assignment operator doesn't just
        // copy a pointer.
    } break; case 88: {
        {
            Map m2;
            Map m3;
            m3.insert(ARRAY[0], ARRAYV[0]);
            m3.insert(ARRAY[1], ARRAYV[1]);
            m3 = m2;
            m2.insert(ARRAY[2], ARRAYV[2]);
            m3.insert(ARRAY[3], ARRAYV[3]);
            assert(m2.size() == 1 && m3.size() == 1);
            KeyType k;
            ValueType v;
            m2.get(0, k, v);
            assert(k == ARRAY[2]);
            m3.get(0, k, v);
            assert(k == ARRAY[3]);
        }
    } break; case 89: {
        {
            Map m2;
            Map m3;
            m3.insert(ARRAY[0], ARRAYV[0]);
            m3.insert(ARRAY[1], ARRAYV[1]);
            assert(m3.size() == 2);
            m2 = m3;
            assert(m2.size() == 2 && m3.size() == 2);
            m2.insert(ARRAY[2], ARRAYV[2]);
            m3.insert(ARRAY[3], ARRAYV[3]);
            assert(m2.size() == 3 && m3.size() == 3);
            for (int n = 0; n < m2.size(); n++)
            {
                KeyType k;
                ValueType v;
                m2.get(n, k, v);
                assert(k == ARRAY[n]);
            }
            KeyType ka[3] = { ARRAY[0], ARRAY[1], ARRAY[3] };
            for (int n = 0; n < m3.size(); n++)
            {
                KeyType k;
                ValueType v;
                m3.get(n, k, v);
                assert(k == ka[n]);
            }
        }
    } break; case 90: {
        // This test checked that the assignment operator doesn't just
        // copy a pointer.
    } break; case 91: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        {
            Map m2;
            m2.insert(ARRAY[2], ARRAYV[2]);
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[4], ARRAYV[4]);
            m2 = m;
            m2.insert(ARRAY[5], ARRAYV[5]);
            assert(m2.size() == m.size() + 1);
        }
    } break; case 92: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        {
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[4], ARRAYV[4]);
            m2.insert(ARRAY[5], ARRAYV[5]);
            m2 = m;
            m2.insert(ARRAY[2], ARRAYV[2]);
            assert(m2.size() == 3);
            for (int n = 0; n < m2.size(); n++)
            {
                KeyType k;
                ValueType v;
                m2.get(n, k, v);
                assert(k == ARRAY[n]);
            }
        }
    } break; case 93: {
        m.insert(ARRAY[0], ARRAYV[0]);
        m.insert(ARRAY[1], ARRAYV[1]);
        {
            Map m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            m2.insert(ARRAY[4], ARRAYV[4]);
            m2.insert(ARRAY[5], ARRAYV[5]);
            m2 = m;
            m2.insert(ARRAY[2], ARRAYV[2]);
            assert(m.size() == 2);
            for (int n = 0; n < m.size(); n++)
            {
                KeyType k;
                ValueType v;
                m.get(n, k, v);
                assert(k == ARRAY[n]);
            }
        }
    } break; case 94: {
        // This test checked that self-assignment doesn't change the
        // number of items in existence.
    } break; case 95: {
        {
            Map m2;
            m2.insert(ARRAY[0], ARRAYV[0]);
            m2.insert(ARRAY[1], ARRAYV[1]);
            m2.insert(ARRAY[2], ARRAYV[2]);
            m2 = m2;
            m2.insert(ARRAY[3], ARRAYV[3]);
            assert(m2.size() == 4);
            for (int n = 0; n < m2.size(); n++)
            {
                KeyType k;
                ValueType v;
                m2.get(n, k, v);
                assert(k == ARRAY[n]);
            }
        }
    }
    }
}

int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed" << endl;
}