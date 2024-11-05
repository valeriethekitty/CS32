#include <iostream>
#include <fstream>
#include "geodb.h"
#include "geotools.h"

GeoDatabase::GeoDatabase() {}

GeoDatabase::~GeoDatabase() {}

std::string parseNumber(const std::string& s, int& start, char separator) {
	char temp[100];
	int i = 0;
	while (s[start] != separator) {
		temp[i++] = s[start++];
	}
	start++;
	temp[i] = '\0';

	return temp;
}

bool GeoDatabase::load(const std::string& map_data_file) { 
	std::ifstream infile(map_data_file); 
	if (!infile)		        // Did opening the file fail?
	{
		std::cerr << "Error: Cannot open!" << std::endl; // idk
		return false;
	}
	std::string streetName;
	while (getline(infile, streetName)) {
		std::string geoPoints;
		getline(infile, geoPoints);
		int j = 0;
		std::string lat1(parseNumber(geoPoints, j, ' '));
		std::string long1(parseNumber(geoPoints, j, ' '));
		std::string lat2(parseNumber(geoPoints, j, ' '));
		std::string long2(parseNumber(geoPoints, j, '\0'));
		
		GeoPoint pt1(lat1, long1);
		GeoPoint pt2(lat2, long2);

		std::string point1 = pt1.to_string();
		std::string point2 = pt2.to_string();
		m_streetNames.insert(point1 + point2, streetName);
		m_streetNames.insert(point2 + point1, streetName);
		connectedPoints(pt1, pt2);
		connectedPoints(pt2, pt1);
		std::string numPOI;
		getline(infile, numPOI);
		int i = std::stoi(numPOI);
		if (i > 0) {
			GeoPoint mp = midpoint(pt1, pt2);
			connectedPoints(pt1, mp);
			connectedPoints(pt2, mp);
			connectedPoints(mp, pt1);
			connectedPoints(mp, pt2);
			std::string m = mp.to_string();
			m_streetNames.insert(m + point1, streetName);
			m_streetNames.insert(point1 + m, streetName);
			m_streetNames.insert(m + point2, streetName);
			m_streetNames.insert(point2 + m, streetName);
			for (int k = 0; k < i; k++) {
				std::string poi;
				getline(infile, poi);
				int l = 0;
				std::string name = parseNumber(poi, l, '|');
				std::string latitude = parseNumber(poi, l, ' ');
				std::string longitude = parseNumber(poi, l, '\0');
				GeoPoint pt3(latitude, longitude);
				m_pois.insert(name, pt3);
				std::string point3 = pt3.to_string();
				m_streetNames.insert(m + point3, "a path");
				m_streetNames.insert(point3 + m, "a path");
				connectedPoints(mp, pt3);
				connectedPoints(pt3, mp);
			}
		}
	}
	infile.close();
	return true; 
}

void GeoDatabase::connectedPoints(const GeoPoint& pt1, const GeoPoint& pt2) {
	std::vector<GeoPoint>* g = m_connectedPoints.find(pt1.to_string());
	if (g != nullptr) {
		bool needs = true;
		for (int i = 0; i < g->size(); i++) {
			if (pt2.to_string() == (*g)[i].to_string()) {
				needs = false;
				break;
			}
		}
		if (needs) {
			g->push_back(pt2);
		}
	}
	else {
		std::vector<GeoPoint> g2;
		g2.push_back(pt2);
		m_connectedPoints.insert(pt1.to_string(), g2);
	}
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const {
	const GeoPoint* pt = m_pois.find(poi);
	if (pt == nullptr) {
		return false;
	}
	point = *pt;
	return true;
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const {
	const std::vector<GeoPoint> *g = m_connectedPoints.find(pt.to_string());
	if (g == nullptr) {
		std::vector<GeoPoint> g2(0);
		return g2;
	}
	return *g;
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const {
	const std::string *s = m_streetNames.find(pt1.to_string()+pt2.to_string());
	//const std::string* s2 = m_streetNames.find(pt2.to_string());
	if (s == nullptr) {
		return "";
	}
	return *s;
}