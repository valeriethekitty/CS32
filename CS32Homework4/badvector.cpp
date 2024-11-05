void removeBad(vector<Movie*>& v)
{
	vector<Movie*>::iterator p = v.begin();
	while (p != v.end()) {
		if (*p != nullptr) {
			if ((*p)->rating() < 50) {
				delete* p;
				p = v.erase(p);
				continue;
			}
		}
		p++;
	}
}