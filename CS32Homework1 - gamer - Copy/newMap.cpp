#include <string>
#include "newMap.h"
#include <iostream>
#include <stdlib.h>

Map::Map(int max) {
    if (max < 0) {
        std::cout << "max cannot be negative." << std::endl;
        exit(1);
    }
    numSize = 0;
    maxSize = max;
    map = new Pair[max];
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    // If key is not equal to any key currently in the map and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).
    if (contains(key) || size() >= maxSize) {
        return false;
    }
    map[size()].key = key;
    map[size()].value = value;
    numSize++;
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value that it currently maps to, but instead map to
    // the value of the second parameter; in this case, return true.
    // Otherwise, make no change to the map and return false.
    for (int i = 0; i < size(); i++) {
        if (map[i].key == key) {
            map[i].value = value;
            return true;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value that it currently maps to, but instead map to
    // the value of the second parameter; in this case, return true.
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that the key is not already in the map and the map has a fixed
    // capacity and is full).
    for (int i = 0; i < size(); i++) {
        if (map[i].key == key) {
            map[i].value = value;
            return true;
        }
    }
    if (size() >= maxSize) {
        return false;
    }
    map[size()].key = key;
    map[size()].value = value;
    numSize++;
    return true;
}

bool Map::erase(const KeyType& key) {
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.
    for (int i = 0; i < size(); i++) {
        if (map[i].key == key) {
            for (int j = i; j < size() - 1; j++) {
                map[j] = map[j + 1];
            }
            numSize--;
            return true;
        }
    }
    return false;
}

bool Map::contains(const KeyType& key) const {
    for (int i = 0; i < size(); i++) {
        if (map[i].key == key) {
            return true;
        }
    }
    return false;
    // Return true if key is equal to a key currently in the map, otherwise
// false.
}

bool Map::get(const KeyType& key, ValueType& value) {
    // If key is equal to a key currently in the map, set value to the
    // value in the map which the key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.
    for (int i = 0; i < size(); i++) {
        if (map[i].key == key) {
            value = map[i].value;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) {
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of the key/value pair in the map whose key is strictly
    // greater than exactly i keys in the map and return true.  Otherwise,
    // leave the key and value parameters unchanged and return false.
    if (i < 0 || i >= size()) {
        return false;
    }
    for (int j = 0; j < size(); j++) {
        if (greaterThanX(map[j].key) == i) {
            key = map[j].key;
            value = map[j].value;
            break;
        }
    }
    return true;
}

void Map::swap(Map& other) {
    // Exchange the contents of this map with the other one.
    Pair* temp = other.map;
    other.map = map;
    map = temp;
    int temp1 = other.numSize;
    other.numSize = numSize;
    numSize = temp1;
    temp1 = other.maxSize;
    other.maxSize = maxSize;
    maxSize = temp1;
}

Map::~Map() {
    delete[] map;
}

int Map::greaterThanX(const KeyType& key) const {
    int count = 0;
    for (int i = 0; i < size(); i++) {
        if (map[i].key > key) {
            count++;
        }
    }
    return count;
}