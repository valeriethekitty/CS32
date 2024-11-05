#ifndef ROUTER_INCLUDED
#define ROUTER_INCLUDED

#include "base_classes.h"
#include <string>
#include <vector>
#include "geopoint.h"
#include "HashMap.h"

class Router : public RouterBase
{
public:
	Router(const GeoDatabaseBase& geo_db);
	virtual ~Router();
	virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
	std::vector<GeoPoint> reconstructPath(HashMap<GeoPoint>& cameFrom, GeoPoint current, GeoPoint original) const;
	bool hasPoint(GeoPoint point, std::vector<GeoPoint> v) const;
	const GeoDatabaseBase& m_geodbb;
};

#endif // ROUTER_INCLUDED

