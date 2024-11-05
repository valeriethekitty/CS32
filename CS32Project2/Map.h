#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
public:
    Map();
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    Map(const Map& m);
    Map& operator= (const Map& m);
    ~Map();
private:
    struct Pair {
        KeyType key;
        ValueType value;
        Pair* m_next;
        Pair* m_prev;
    };
    Pair *head = nullptr;
    int m_size = 0;
    int isGreaterThanX(const KeyType& key) const;
    void eraseAll();
};

bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

#endif
