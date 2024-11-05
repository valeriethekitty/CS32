#ifndef TOURGENERATOR_INCLUDED
#define TOURGENERATOR_INCLUDED

#include "base_classes.h"
#include <string>
#include <vector>
#include "tourcmd.h"
#include "geopoint.h"

class TourGenerator : public TourGeneratorBase
{
public:
	TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
	virtual ~TourGenerator();
	virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
private:
	bool proceed(std::vector<TourCommand>& result, std::string poi, std::string poi2) const;
	void turn(std::vector<TourCommand>& result, GeoPoint g1, GeoPoint g2, GeoPoint g3) const;
	std::string getDirection(GeoPoint g1, GeoPoint g2) const;
	const GeoDatabaseBase& m_geodbb;
	const RouterBase& m_routerbase;
};

#endif // TOURGENERATOR_INCLUDED
