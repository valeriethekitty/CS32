#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <string>

using KeyType = std::string;
using ValueType = double;

const int DEFAULT_MAX_ITEMS = 150;

class Map
{
public:
    inline Map() {
        numSize = 0; // Create an empty map (i.e., one whose size() is 0).
    }
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

private:
    struct Pair {
        KeyType key;
        ValueType value;
    };
    
    Pair map[DEFAULT_MAX_ITEMS];
    int numSize;
    int greaterThanX(const KeyType& key) const;
};

#endif // !MAP_INCLUDED

