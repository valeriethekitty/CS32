#include "router.h"
#include <vector>
#include <string>
#include "HashMap.h"
#include "base_classes.h"
#include "geotools.h"
#include <algorithm>

Router::Router(const GeoDatabaseBase& geo_db) : m_geodbb(geo_db) {
}

Router::~Router() {}

void print(std::vector<GeoPoint> r)
{
	if (r.size() == 0) {
		std::cerr << "no" << std::endl;
		return;
	}
	double total = 0;
	GeoPoint previous = r[0];
	for (auto p : r) {
		double d = distance_earth_miles(previous, p);
		//std::cerr << p.to_string() << "... " << d << std::endl;
		total += d;
		previous = p;
	}
	std::cerr << "DEBUG total: " << total << std::endl;
}

double getScore(const HashMap<double>& h, const GeoPoint& g) {
	if (h.find(g.to_string()) != nullptr) {
		return *h.find(g.to_string());
	}
	else {
		return 1000000000;
	}
}

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const {
	std::vector<GeoPoint> r;
	std::vector<GeoPoint> openSet; 
	HashMap<bool> visited;
	openSet.push_back(pt1);
	HashMap<GeoPoint> cameFrom;
	std::string goal = pt2.to_string();
	HashMap<double> cheapestPath;
	HashMap<double> estimatePath; // idk how to implement this
	cheapestPath.insert(pt1.to_string(), 0);
	estimatePath.insert(pt1.to_string(), distance_earth_miles(pt1, pt2));
	while (!openSet.empty()) {
		double cheap = 100000000;
		int mini = 0;
		for (int i = 0; i < openSet.size(); i++) {
			double s = getScore(estimatePath, openSet[i]);
			if (s < cheap) {
				cheap = s;
				mini = i;
			}
		}
		GeoPoint curr = openSet[mini];
		openSet.erase(openSet.begin() + mini);
		bool* v = visited.find(curr.to_string());
		if (v != nullptr && *v == true) {
			continue;
		}
		visited.insert(curr.to_string(), true);
		if (curr.to_string() == goal) {
			return reconstructPath(cameFrom, curr, pt1);
		}
		std::vector<GeoPoint> neighbors = m_geodbb.get_connected_points(curr);
		for (int i = 0; i < neighbors.size(); i++) {
			if (visited.find(neighbors[i].to_string()) == nullptr) {
				double temp = getScore(cheapestPath, curr) + distance_earth_miles(curr, neighbors[i]);
				if (temp < getScore(cheapestPath, neighbors[i])) {
					/*if (!hasPoint(neighbors[i], openSet)) {
						openSet.push_back(neighbors[i]);
					}*/
					openSet.push_back(neighbors[i]);
					cheapestPath.insert(neighbors[i].to_string(), temp);
					estimatePath.insert(neighbors[i].to_string(), temp + distance_earth_miles(neighbors[i], pt2));
					cameFrom[neighbors[i].to_string()] = curr;
				}
			}
		}
	}
	return r;
}

bool Router::hasPoint(GeoPoint point, std::vector<GeoPoint> v) const {
	std::string pt = point.to_string();
	for (int i = 0; i < v.size(); i++) {
		if (v[i].to_string() == pt) {
			return true;
		}
	}
	return false;
}

std::vector<GeoPoint> Router::reconstructPath(HashMap<GeoPoint>& cameFrom, GeoPoint current, GeoPoint original) const {
	std::vector<GeoPoint> total_path;
	std::string curr = current.to_string();
	if (curr == original.to_string()) {
		total_path.push_back(original);
		return total_path;
	}
	/*while (cameFrom.find(curr) != nullptr && cameFrom.find(curr)->to_string() != original.to_string()) {
		std::cerr << curr << " bruhh" << std::endl;
		total_path.push_back(cameFrom[curr]);
		curr = cameFrom[curr].to_string();
	}
	if (cameFrom.find(curr) != nullptr && cameFrom.find(curr)->to_string() == original.to_string()) {
		total_path.push_back(original);
	}*/
	total_path.push_back(current);
	while (cameFrom.find(curr) != nullptr) {
		GeoPoint temp = cameFrom[curr];
		curr = temp.to_string();
		total_path.push_back(temp);
	}
	/*if (cameFrom.find(curr) != nullptr && cameFrom.find(curr)->to_string() == original.to_string()) {
		total_path.push_back(original);
	}*/
	std::reverse(total_path.begin(), total_path.end());
	//print(total_path);
	return total_path;
}
