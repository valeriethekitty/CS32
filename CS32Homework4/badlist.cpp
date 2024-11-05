void removeBad(list<Movie*>& li)
{
	list<Movie*>::iterator p = li.begin();
	while (p != li.end()) {
		if (*p != nullptr) {
			if ((*p)->rating() < 50) {
				delete *p;
				p = li.erase(p);
				continue;
			}
		}
		p++;
	}
}