#include "Map.h"
#include <iostream>
#include <cassert>

int main() {
	Map m;
	// For an empty map:
	assert(m.size() == 0);			// test size
	assert(m.empty());				// test empty
	assert(!m.erase("Ricky"));		// nothing to erase
	assert(m.insert("Ricky", 5));	// insert a node Ricky
	assert(m.erase("Ricky"));		// can now erase Ricky
	m.insert("Jennifer", 69);		// insert more nodes
	m.insert("Gertrude", 420);
	m.insert("Janice", 19);
	assert(!m.insert("Gertrude", 666)); // cannot insert with same key
	assert(!m.update("Francesca", 3.14)); // cannot update when the key is not already there
	assert(m.update("Gertrude", 101)); // update succeeds
	assert(m.insertOrUpdate("Victoria", 2.718)); // insertOrUpdate succeeds if key not there
	assert(m.insertOrUpdate("Janice", 20)); // insertOrUpdate succeeds if key exists already
	assert(m.contains("Janice")); // check if contains works
	assert(!m.contains("Judy"));  // check if contains returns false when key is not there
	KeyType key;
	ValueType value;
	assert(m.get("Janice", value) && value == 20); // check to make sure get returns correct value if key exists
	assert(!m.get("Jisoo", value)); // check to make sure get returns false if key not there
	assert(!m.get(-1, key, value)); // get should return false if i is negative
	assert(!m.get(69, key, value)); // get should return false if i >= size()
	assert(m.get(2, key, value)); // get should return the correct value	
	Map m2;			// make a second map
	m2.insert("Lucifer", 666); // add some nodes to the second map
	m2.insert("Euler", 2.718);
	m2.insert("Avogadro", 6.022); 
	m.swap(m2); // swap the two maps
	assert(m2.size() == 4); // check the size of m2
	assert(m.size() == 3); // check the size of m
	assert(m.contains("Euler")); // make sure m contains original m2 nodes
	assert(!m.contains("Janice")); // make sure m does not contain its original nodes
	assert(m2.contains("Janice")); // make sure m2 contains nodes from m
	Map result;
	assert(merge(m, m2, result)); // merge should return true because there are no identical keys with different values
	assert(result.contains("Janice")); // result should have values from m2
	assert(result.contains("Euler")); // result should have values from m
	assert(merge(m, m2, m)); // merge should still work if the passed in parameters are the same
	assert(m.contains("Janice")); // m should have values from m2
	assert(m.contains("Euler")); // m should also have values from m before
	assert(merge(m, m, m2)); // test if the two merged Maps are the same it still works
	assert(m2.contains("Euler")); // test if m2 has values from m
	m2.update("Jennifer", 777); // Jennifer won the lottery
	assert(!merge(m, m2, result)); // this should return false because m and m2 both have Jennifer but with different values 
	reassign(m, result); // reassign values of m 
	assert(result.get("Janice", value) && value != 20); // check to make sure the value is different
	reassign(m, m); // reassign when result Map is the same as the original map
	assert(m.get("Janice", value) && value != 20); // make sure it is changed 
	std::cout << "all tests passed" << std::endl;
	return 0;
} 

/* int main() {

	std::cerr << "*** Main starts" << std::endl;

	Map m2;

	std::cerr << "*** Inserting two thiings" << std::endl;
	m2.insert("Jennifer", 69);
	m2.insert("Victoria", 2.718);

	Map m;          // make a second map
	Map result;

	std::cerr << "*** Merge m m2 m" << std::endl;
	merge(m, m2, m);

	std::cerr << "*** Updating Jennifer" << std::endl;
	m2.update("Jennifer", 777);

	std::cerr << "*** Merge m m2 result" << std::endl;
	merge(m, m2, result);

	std::cout << "*** all tests passed" << std::endl;
	return 0;
} */