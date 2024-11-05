#include "Map.h"

Map::Map() {
	head = nullptr; // init head to null
}
bool Map::empty() const {
	if (head == nullptr) { // return true if head is null
		return true;
	}
	return false; // else return false
}
int Map::size() const {
	return m_size; // return size
}
bool Map::insert(const KeyType& key, const ValueType& value) {
	if (contains(key)) { // call contains function to check if key is in map, if so return false
		return false;
	}
	Pair* p = new Pair; // create a new pair to insert
	p->key = key; // set key and value in the new pair to the given key/value
	p->value = value; 
	p->m_prev = nullptr; // set previous to null
	p->m_next = head; // set next to current head
	if (head != nullptr) { // if head is not null, set head's previous to p
		head->m_prev = p;
	}
	head = p; // change the current head to p
	m_size++; // increment size
	return true;
}
bool Map::update(const KeyType& key, const ValueType& value) {
	Pair* p = head; // create pointer and set to head
	if (p == nullptr) { // if p is null, there are no keys, therefore, can return false
		return false;
	}
	if (!contains(key)) { // if the map does not contain the key, return false
		return false;
	}
	while (p->key != key) { // keep moving to next pair until you reach the pair with a key equal to given key
		p = p->m_next; 
	}
	p->value = value; // set the value to the new value
	return true;
}
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
	if (!update(key, value)) { // call update function
		insert(key, value);  // if update function fails, call insert function
	}
	return true;
}
bool Map::erase(const KeyType& key) {
	if (!contains(key)) { // if key doesn't exist, nothing to erase, can return false
		return false;
	}
	Pair* p = head; // init pointer to head
	while (p->key != key) { // loop through the pairs until you find the correct key
		p = p->m_next;
	}
	if (p->m_prev != nullptr) { // if p is not the first node
		Pair* temp1 = p->m_prev; // create temporary pointer to m_prev of p
		temp1->m_next = p->m_next; // set temp1's m_next to p's m_next
	}
	else {
		head = p->m_next; // if p is the first node, set head to the next node
	}
	if (p->m_next != nullptr) { // if p is not the last node
		Pair* temp2 = p->m_next; // set a temporary pointer to the next node
		temp2->m_prev = p->m_prev; // set this tenp2's m_prev to the node (or null) before p
	}
	delete p; // delete the node
	m_size--; // decrease size
	return true;
}
bool Map::contains(const KeyType& key) const {
	Pair* p = head; // set pointer to head
	while (p != nullptr && p->key != key) { // loop through pairs until you reach the end or you get the correct key
		p = p->m_next;
	}
	return (p != nullptr); // if key is not found, p will be null and return false, if key is found, p is not null and will not return false
}
bool Map::get(const KeyType& key, ValueType& value) const {
	Pair* p = head; // set pointer to head
	if (!contains(key)) { // if key is not in map, return false
		return false;
	}
	while (p->key != key) { // loop through pairs until you find correct key
		p = p->m_next;
	}
	value = p->value; // set value to the value of p connected to key
	return true;
}
bool Map::get(int i, KeyType& key, ValueType& value) const {
	if (0 > i || i >= size()) { // if i is out of bounds, return false
		return false;
	}
	Pair* p = head; // set pointer to head

	while (p!= nullptr) { // loop through the pairs
		if (isGreaterThanX(p->key) == i) { // call isGreaterThanX function, if p->key is greater than exactly i pairs
			key = p->key; // set key and value appropriately
			value = p->value;
			break; // break out of the while loop
		}
		p = p->m_next;
	}
	return true;
}
void Map::swap(Map& other) {
	Pair* temp = head; // create temporary pointer to head
	head = other.head; // set head to other head
	other.head = temp; // set other head to temp
	int temp2 = m_size; // create temporary integer equalling m_size
	m_size = other.m_size; // set m_size to the other size
	other.m_size = temp2;  // set the other size to temporary variable
}
Map::Map(const Map& m) {
	Pair* p = nullptr; // initialize several pointers to be used later
	Pair* next = nullptr;
	Pair* prev = nullptr;
	if (m.head == nullptr) { // if the head of m is null, it is just an empty map
		head = nullptr; // set head to null in this case
	}
	else { // otherwise
		head = new Pair; // set head to a new Pair
		head->key = m.head->key; // assign the key and value appropriately
		head->value = m.head->value;
		head->m_prev = nullptr; // this is the head so m_prev should be null
		p = head; // set p to head
		next = m.head->m_next; // set next to the m_next of the head in m
		prev = p; // set prev to p
	}
	while (next != nullptr) { // loop through next which now points to m
		p->m_next = new Pair; // create a new Pair as the next node of p
		p = p->m_next;  // set p to that new Pair
		p->key = next->key;  // set the key and value appropriately
		p->value = next->value; 
		p->m_prev = prev; // set previous of this p to the stored prev 
		prev = p; // change prev to p
		next = next->m_next; // set next to next node
	}
	if (p != nullptr) { // if p is not null, then p is now the last node in the list
		p->m_next = nullptr; // the next pointer in p is now null
	}
	m_size = m.m_size;
}
Map::~Map() {
	eraseAll(); // just call eraseAll private function
}
int Map::isGreaterThanX(const KeyType& key) const {
	int result = 0; // initialize a count variable to 0
	Pair* p = head; // set pointer to head
	while (p != nullptr) { // loop through the nodes
		if (key > p->key) { // if key is greater than p's key, increment result
			result++;
		}
		p = p->m_next;
	}
	return result;
}
Map& Map::operator= (const Map& m) {
	if (this == &m) { // if current map already equals m
		return *this; // return current map
	}
	eraseAll(); // erase everything in this map
	Map temp(m); // make temporary copy of m
	swap(temp); // swap this map with temp
	return *this; // return this map
}
void Map::eraseAll() {
	Pair* temp = head; // set pointer to head
	while (temp != nullptr) { // loop through the nodes
		Pair* temp2 = temp->m_next; // create temp pointer to point to the next node
		delete temp; // delete current node
		temp = temp2; // set temp to next node saved in temp2
	}
}
bool merge(const Map& m1, const Map& m2, Map& result) {
	KeyType key;
	ValueType value, value2;
	Map temp(m1); // call copy constructor
	bool returnvalue = true; // returnvalue starts as true, will be changed as needed later
	for (int i = 0; i < m2.size(); i++) { // loop from 0 to size of m2
		m2.get(i, key, value); // get the keys in order from least to greatest
		if (!temp.contains(key)) { // if key not already in temp, insert it
			temp.insert(key, value);
		}
		else {
			temp.get(key, value2); // get the value of key in temp
			if (value != value2) {
				temp.erase(key); // erase the key if the values don't match and set returnvalue to false
				returnvalue = false;
			}
		}
	}
	result.swap(temp); // swap result with temp
	return returnvalue;
}
void reassign(const Map& m, Map& result) { 
	Map temp(m); // call copy constructor
	KeyType key, key2;
	ValueType value, value2;
	for (int i = 0; i < m.size()-1; i++) { // loop from 0 to one less than the size of m
		temp.get(i, key, value); // get key greater than i other keys
		temp.get(i + 1, key2, value2); // get key greater than i+1 other 
		temp.update(key, value2); // update value of key greater than i other keys to the value of key greater than i+1 keys
	}
	temp.get(0, key, value); // finally get the value from the first node
	temp.update(key2, value); // update the last key to have that value
	result.swap(temp); // swap temporary map with result
}