void removeOdd(vector<int>& v)
{
	vector<int>::iterator p = v.begin(); 
	while (p != v.end()) {
		if (*p % 2 != 0) {
			p = v.erase(p);
		}
		else {
			p++;
		}
	}
}