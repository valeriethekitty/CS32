#ifndef GEODATABASE_INCLUDED
#define GEODATABASE_INCLUDED

#include "base_classes.h"
#include "HashMap.h"
#include <vector>

class GeoDatabase : public GeoDatabaseBase
{
public:
	GeoDatabase();
	virtual ~GeoDatabase();
	virtual bool load(const std::string& map_data_file);
	virtual bool get_poi_location(const std::string& poi, GeoPoint& point) const;
	virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
	virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
	//std::string parseNumber(const std::string& s, int& start, char separator);
	void connectedPoints(const GeoPoint& pt1, const GeoPoint& pt2);
	HashMap<GeoPoint> m_pois;
	HashMap<std::vector<GeoPoint>> m_connectedPoints;
	HashMap<std::string> m_streetNames;
};

#endif // GEODATABASE_INCLUDED
