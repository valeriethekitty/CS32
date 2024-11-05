#ifndef NEWMAP_INCLUDED
#define NEWMAP_INCLUDED

#include <string>

using KeyType = std::string;
using ValueType = double;

const int DEFAULT_MAX_ITEMS = 150;

class Map
{
public:
    Map(int max = DEFAULT_MAX_ITEMS);
    inline bool empty() const {
        // Return true if the map is empty, otherwise false.
        return numSize == 0;
    }
    inline int size() const {
        return numSize; // Return the number of key/value pairs in the map.
    }
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    ~Map();

private:
    struct Pair {
        KeyType key;
        ValueType value;
    };
    Pair* map;
    int maxSize = DEFAULT_MAX_ITEMS;
    int numSize = 0;
    int greaterThanX(const KeyType& key) const;
};

#endif