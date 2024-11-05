#ifndef HASHMAP_INCLUDED
#define HASHMAP_INCLUDED

#include <string>
#include <iostream> 
#include <vector>

template <typename T>
class HashMap {
public:
	HashMap(double max_load = 0.75); // constructor
	~HashMap(); // destructor; deletes all of the items in the hashmap
	inline int size() const { // return the number of associations in the hashmap
		return m_numAssociations;
	}
	// The insert method associates one item (key) with another (value).
	// If no association currently exists with that key, this method inserts
	// a new association into the hashmap with that key/value pair. If there is
	// already an association with that key in the hashmap, then the item
	// associated with that key is replaced by the second parameter (value).
	// Thus, the hashmap must contain no duplicate keys.
	void insert(const std::string& key, const T& value);
	// If no association exists with the given key, return nullptr; otherwise,
	// return a pointer to the value associated with that key. This pointer can be
	// used to examine that value or modify it directly within the map.
	const T* find(const std::string& key) const;
	// Defines the bracket operator for HashMap, so you can use your map like this:
	// your_map["david"] = 2.99;
	// If the key does not exist in the hashmap, this will create a new entry in
	// the hashmap and map it to the default value of type T. Then it will return a
	// reference to the newly created value in the map.
	T& operator[](const std::string& key);
	T* find(const std::string& key) {
		const auto& hm = *this;
		return const_cast<T*>(hm.find(key));
	}
	HashMap(const HashMap&) = delete;
	HashMap& operator=(const HashMap&) = delete;
private:
	double m_maxLoadFactor;
	int m_numBuckets = 10;
	int m_numAssociations = 0;
	std::vector<std::vector<std::pair<std::string, T>>> m_hashmap;
};

template <typename T>
HashMap<T>::HashMap(double max_load) {
	if (max_load < 0) { m_maxLoadFactor = 0.75; }
	else { m_maxLoadFactor = max_load; }
	m_hashmap = std::vector<std::vector<std::pair<std::string, T>>>(m_numBuckets);
}

template <typename T>
HashMap<T>::~HashMap() {}

template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value) {
	T* t = find(key);
	if (t != nullptr) {
		*t = value;
	}
	else {
		if ((1.0 * m_numAssociations + 1) / m_numBuckets > m_maxLoadFactor) {
			std::vector<std::vector<std::pair<std::string, T>>> temp = m_hashmap;
			m_hashmap.erase(m_hashmap.begin(), m_hashmap.end());
			m_numAssociations = 0;
			m_numBuckets *= 2;
			m_hashmap.resize(m_numBuckets);
			for (int j = 0; j < temp.size(); j++) {
				for (int k = 0; k < temp[j].size(); k++) {
					insert(temp[j][k].first, temp[j][k].second);
				}
			}
		}
		size_t i = std::hash<std::string>()(key) % m_numBuckets;
		std::pair<std::string, T> p;
		p.first = key;
		p.second = value;
		m_hashmap[i].push_back(p); // how to check if there is already a key there
		m_numAssociations++; // only if key not there
	}
}

template <typename T>
const T* HashMap<T>::find(const std::string& key) const {
	size_t i = std::hash<std::string>()(key) % m_numBuckets;
	for (int j = 0; j < m_hashmap[i].size(); j++) {
		if (m_hashmap[i][j].first == key) {
			return &m_hashmap[i][j].second;
		}
	}
	return nullptr;
}

template <typename T>
T& HashMap<T>::operator[](const std::string& key) {
	T* t = find(key);
	if (t != nullptr) {
		return *t;
	}
	insert(key, T());
	return *find(key);
}

#endif // HASHMAP_INCLUDED