#include "tour_generator.h"
#include "tourcmd.h"
#include "base_classes.h"
#include "geopoint.h"
#include "geotools.h"
#include <string>
#include <vector>

TourGenerator::TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router) : m_geodbb(geodb), m_routerbase(router) {

}

TourGenerator::~TourGenerator() {

}
//std::vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const {
//	std::vector<TourCommand> result;
//
//	for (int i = 0; i < stops.size(); i++) {
//		TourCommand t;
//		std::string poi;
//		std::string talking_points;
//		stops.get_poi_data(i, poi, talking_points);
//		GeoPoint g;
//		if (!m_geodbb.get_poi_location(poi, g)) {
//			return std::vector<TourCommand>(0);
//		}
//		t.init_commentary(poi, talking_points);
//		result.push_back(t);
//		if (i < stops.size() - 1) {
//			std::string poi2;
//			stops.get_poi_data(i+1, poi2, talking_points);
//			if (!proceed(result, poi, poi2)) {
//				return std::vector<TourCommand>(0);
//			}
//		}
//	}
//	return result;
//}
//
//bool TourGenerator::proceed(std::vector<TourCommand>& result, std::string poi, std::string poi2) const {
//	GeoPoint g1;
//	GeoPoint g2;
//	if (!m_geodbb.get_poi_location(poi, g1) || !m_geodbb.get_poi_location(poi2, g2)) {
//		return false;
//	}
//	std::vector<GeoPoint> g = m_routerbase.route(g1, g2);
//	if (g.size() == 0) {
//		return false;
//	}
//	for (int i = 0; i < g.size() - 1; i++) {
//		TourCommand t;
//		std::string dir = getDirection(g[i], g[i + 1]);
//		std::string streetName = m_geodbb.get_street_name(g[i], g[i + 1]);
//		double distance = distance_earth_miles(g[i], g[i + 1]);
//		t.init_proceed(dir, streetName, distance, g[i], g[i + 1]);
//		result.push_back(t);
//		std::cerr << distance << std::endl;
//		if (i < g.size() - 2) {
//			if (m_geodbb.get_street_name(g[i], g[i + 1]) != m_geodbb.get_street_name(g[i + 1], g[i + 2]) && angle_of_turn(g[i], g[i+1], g[i+2]) != 0) {
//				turn(result, g[i], g[i + 1], g[i + 2]);
//			}
//		}
//	}
//	return true;
//}
//
//std::string TourGenerator::getDirection(GeoPoint g1, GeoPoint g2) const {
//	double angle = angle_of_line(g1, g2);
//	if ((angle >= 0 && angle < 22.5) || angle >= 337.5) {
//		return "east";
//	}
//	if (angle >= 22.5 && angle < 67.5) {
//		return "northeast";
//	}
//	if (angle >= 67.5 && angle < 112.5) {
//		return "north";
//	}
//	if (angle >= 112.5 && angle < 157.5) {
//		return "northwest";
//	}
//	if (angle >= 157.5 && angle < 202.5) {
//		return "west";
//	}
//	if (angle >= 202.5 && angle < 247.5) {
//		return "southwest";
//	}
//	if (angle >= 247.5 && angle < 292.5) {
//		return "south";
//	}
//	if (angle >= 292.5 && angle < 337.5) {
//		return "southeast";
//	}
//	return "";
//}
//
//void TourGenerator::turn(std::vector<TourCommand>& result, GeoPoint g1, GeoPoint g2, GeoPoint g3) const {
//	double angle = angle_of_turn(g1, g2, g3);
//
//	if (angle < 1 || angle > 359 /*|| m_geodbb.get_street_name(g1, g2) == m_geodbb.get_street_name(g2, g3)*/) {
//		return;
//	}
//	TourCommand t;
//	if (angle >=1 && angle < 180) { // between 0 and 1, 359 and 360 ??????????
//		t.init_turn("left", m_geodbb.get_street_name(g2, g3));
//		result.push_back(t); 
//		return;
//	}
//	if (angle >= 180 && angle <= 359) {
//		t.init_turn("right", m_geodbb.get_street_name(g2, g3));
//		result.push_back(t);
//	}
//	return;
//}

std::vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const {
    std::vector<TourCommand> tourCommands;
    for (int i = 0; i < stops.size(); i++) {
        std::string poi, talking_points;
        stops.get_poi_data(i, poi, talking_points);
        TourCommand commentaryCommand;
        TourCommand proceedCommand;
        TourCommand turnCommand;
        commentaryCommand.init_commentary(poi, talking_points);
        tourCommands.push_back(commentaryCommand);
        if (i + 1 < stops.size()) {
            GeoPoint currentGeoPoint;
            if (!m_geodbb.get_poi_location(poi, currentGeoPoint)) {
                continue;
            }

            std::string nextPoi, nextTalkingPoints;
            stops.get_poi_data(i + 1, nextPoi, nextTalkingPoints);
            GeoPoint nextGeoPoint;
            if (!m_geodbb.get_poi_location(nextPoi, nextGeoPoint)) {
                continue;
            }
            std::vector<GeoPoint> route = m_routerbase.route(currentGeoPoint, nextGeoPoint);
            // Generate tour commands based on the route
            for (size_t j = 0; j < route.size() - 1; j++) {
                GeoPoint p1 = route[j];
                GeoPoint p2 = route[j + 1];

                // Calculate angle between p1 and p2
                double angle = angle_of_line(p1, p2);
                // Determine direction based on angle
                std::string direction;
                if (0 <= angle && angle < 22.5) direction = "east";
                else if (22.5 <= angle && angle < 67.5) direction = "northeast";
                else if (67.5 <= angle && angle < 112.5) direction = "north";
                else if (112.5 <= angle && angle < 157.5) direction = "northwest";
                else if (157.5 <= angle && angle < 202.5) direction = "west";
                else if (202.5 <= angle && angle < 247.5) direction = "southwest";
                else if (292.5 <= angle && angle < 337.5) direction = "south";
                else if (angle >= 337.5) direction = "southeast";
                std::string streetName = m_geodbb.get_street_name(p1, p2);
                TourCommand proceedCommand;
                proceedCommand.init_proceed(direction, streetName, distance_earth_miles(currentGeoPoint, nextGeoPoint), currentGeoPoint, nextGeoPoint);
                tourCommands.push_back(proceedCommand);

                if (j + 2 < route.size()) {
                    GeoPoint p3 = route[j + 2];
                    std::string streetName1 = m_geodbb.get_street_name(p1, p2);
                    std::string streetName2 = m_geodbb.get_street_name(p2, p3);
                    double angleBetweenSegments = angle_of_turn(p1, p2, p3);

                    if (streetName1 != streetName2 && angleBetweenSegments != 0.0) {
                        std::string turnDirection = (angleBetweenSegments < 180.0) ? "left" : "right";
                        TourCommand turnCommand;
                        turnCommand.init_proceed(direction, streetName, distance_earth_km(currentGeoPoint, nextGeoPoint), currentGeoPoint, nextGeoPoint);
                        tourCommands.push_back(turnCommand);
                    }
                }
            }
        }
    }
    return tourCommands;
}