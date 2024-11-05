void removeOdd(list<int>& li)
{
	list<int>::iterator p = li.begin();
	while (p != li.end()) {
		if (*p % 2 != 0) {
			list<int>::iterator q = li.erase(p);
			p = q;
		}
		else {
			p++;
		}
	}
}