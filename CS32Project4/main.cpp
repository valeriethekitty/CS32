#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include <cassert>

#include "geodb.h"
#include "router.h"
#include "stops.h"
#include "tourcmd.h"
#include "tour_generator.h"
#include "geotools.h"  

using namespace std;

void print_tour(vector<TourCommand>& tcs)
{
    double total_dist = 0;
    std::string direction;
    double street_distance = 0;

    cout << "Starting tour...\n";

    for (size_t i = 0; i < tcs.size(); ++i)
    {
        if (tcs[i].get_command_type() == TourCommand::commentary)
        {
            cout << "Welcome to " << tcs[i].get_poi() << "!\n";
            cout << tcs[i].get_commentary() << "\n";
        }
        else if (tcs[i].get_command_type() == TourCommand::turn)
        {
            cout << "Take a " << tcs[i].get_direction() << " turn on " << tcs[i].get_street() << endl;
        }
        else if (tcs[i].get_command_type() == TourCommand::proceed)
        {
            total_dist += tcs[i].get_distance();
            if (direction.empty())
                direction = tcs[i].get_direction();
            street_distance += tcs[i].get_distance();
            if (i+1 < tcs.size() && tcs[i+1].get_command_type() == TourCommand::proceed 
                && tcs[i+1].get_street() == tcs[i].get_street() && tcs[i].get_street() != "a path")
            {
                continue;
            }

            cout << "Proceed " << std::fixed << std::setprecision(3) << street_distance << " miles " << direction << " on " << tcs[i].get_street() << endl;
            street_distance = 0;
            direction.clear();
        }
    }

    cout << "Your tour has finished!\n";
    cout << "Total tour distance: " << std::fixed << std::setprecision(3) << total_dist << " miles\n";
}

void debug() {
    HashMap<int> h;
    h["apple"] = 3;
    h.insert("bruh", 20);
    h.insert("bruhh", 20);
    h.insert("bruhhh", 20);
    h.insert("bruhhhh", 20);
    h.insert("bruhhhhh", 20);
    h.insert("bruhhhhhh", 20);
    h.insert("bruhh", 10);
    h.insert("bruhhhhhhh", 20);
}

bool hasPoint(GeoPoint p, vector<GeoPoint> pts) {
    for (int i = 0; i < pts.size(); i++) {
        if (pts[i].to_string() == p.to_string()) {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    debug();
    cerr << argc << " testarg" << endl;
    if (argc != 3)
    {
        cout << "usage: BruinTour mapdata.txt stops.txt\n";
    }

    GeoDatabase geodb;
    if (!geodb.load("mapdata.txt"))
    {
        cout << "Unable to load map data: " << argv[1] << endl;
        return 1;
    }

    GeoPoint p;
    if (geodb.get_poi_location("Diddy Riese", p))
        cout << "The PoI is at " << p.sLatitude << ", "
        << p.sLongitude << endl;
    else
        cout << "PoI not found!\n";

    std::vector<GeoPoint> pts = geodb.get_connected_points(GeoPoint("34.0731003", "-118.4931016"));
    if (pts.empty()) {
        cout << "There are no points connected to your specified point\n";
    }
    else {
        for (const auto p : pts) {
            cout << p.sLatitude << ", " << p.sLongitude << endl;
        }
    }
    
    std::vector<GeoPoint> pts2 = geodb.get_connected_points(GeoPoint("34.0600768", "-118.4467216")); // midpoint
    if (pts.empty()) {
        cout << "There are no points connected to your specified point\n";
    }
    else {
        for (const auto p : pts2) {
            cout << "mid " << p.sLatitude << ", " << p.sLongitude << endl;
        }
    }

    std::vector<GeoPoint> pts3 = geodb.get_connected_points(GeoPoint("34.0736122", "-118.4927669")); // midpoint of teakwood and glenmere
    if (pts.empty()) {
        cout << "There are no points connected to your specified point\n";
    }
    else {
        for (const auto p : pts3) {
            cout << "teak+glen" << p.sLatitude << ", " << p.sLongitude << endl;
        }
    }

    std::vector<GeoPoint> pts4 = geodb.get_connected_points(GeoPoint("34.0601422", "-118.4468929")); // fatburger
    if (pts.empty()) {
        cout << "There are no points connected to your specified point\n";
    }
    else {
        for (const auto p : pts4) {
            cout << "fatburg " << p.sLatitude << ", " << p.sLongitude << endl;
        }
    }

    /*GeoPoint p1("34.0602175", "-118.4464952");
    GeoPoint p2("34.0600768", "-118.4467216");*/
    GeoPoint p1("34.0632405", "-118.4470467");
    GeoPoint p2("34.0714373", "-118.4003842");
    cout << geodb.get_street_name(p1, p2); // writes "Kinross Avenue"
    cout << geodb.get_street_name(p2, p1); // writes "Kinross Avenue"
    GeoPoint p3("34.0732851", "-118.4931016");
    GeoPoint p4("34.0736122", "-118.4927669");
    cout << geodb.get_street_name(p3, p4); // writes "Glenmere Way"
    cout << geodb.get_street_name(p4, p3); // writes "Glenmere Way"
    GeoPoint p5("34.0601422", "-118.4468929"); //34.0599361 -118.4469479 34.0601422 - 118.4468929

    GeoPoint p6("34.0600768", "-118.4467216");
    cout << geodb.get_street_name(p5, p6); // writes "a path"
    cout << geodb.get_street_name(p6, p5); // writes "a path"
    GeoPoint p8("34.0630614", "-118.4468781");
    GeoPoint p9("34.0614911", "-118.4464410");
  
    cout << "\n This is where the route function commences" << endl;
    Router router(geodb);
    vector<GeoPoint> g = router.route(p8, p9);
    cout << "g" << endl;
    for (int i = 0; i < g.size(); i++) {
        cout << g[i].to_string() << endl;
    }
    GeoPoint p10("34.0632405", "-118.4470467"); // Broxton
    GeoPoint p11("34.0714373", "-118.4003842");

    GeoPoint p12("34.0625329", "-118.4470263"); 
    GeoPoint p13("34.0685657", "-118.4489289");

    GeoPoint a1("34.0625329", "-118.4470263");
    GeoPoint a2("34.0632405", "-118.4470467");
    GeoPoint a3("34.0636533", "-118.4470480");
    GeoPoint a4("34.0636457", "-118.4475203");
    GeoPoint a5("34.0636344", "-118.4482275");
    GeoPoint a6("34.0636214", "-118.4491386");
    GeoPoint a7("34.0640279", "-118.4495842");
    GeoPoint a8("34.0644757", "-118.4499587");
    GeoPoint a9("34.0661337", "-118.4484725");
    GeoPoint a10("34.0664085", "-118.4487051");
    GeoPoint a11("34.0665813", "-118.4488486");
    GeoPoint a12("34.0668106", "-118.4490930");
    GeoPoint a13("34.0670166", "-118.4493580");
    GeoPoint a14("34.0672971", "-118.4497256");
    GeoPoint a15("34.0683569", "-118.4491847");
    GeoPoint a16("34.0684706", "-118.4490809");
    GeoPoint a17("34.0685657", "-118.4489289");

    double sum = distance_earth_miles(a1, a2) + distance_earth_miles(a2, a3) + distance_earth_miles(a3, a4) + distance_earth_miles(a4, a5) + distance_earth_miles(a5, a6) + distance_earth_miles(a6, a7) + distance_earth_miles(a7, a8) + distance_earth_miles(a8, a9) + distance_earth_miles(a9, a10) + distance_earth_miles(a10, a11) + distance_earth_miles(a11, a12) + distance_earth_miles(a12, a13) + distance_earth_miles(a13, a14) + distance_earth_miles(a14, a15) + distance_earth_miles(a15, a16) + distance_earth_miles(a16, a17);

    cout << sum << " miles" << endl;

    vector<GeoPoint> g2 = router.route(a1, a17);
    cout << "g2" << endl;
    for (int j = 0; j < g2.size(); j++) {
        cout << g2[j].to_string() << endl;
    }
    cout << "g3" << endl;
    GeoPoint p7("34.0599361", "-118.4469479");
    vector<GeoPoint> g3 = router.route(p5, p7);
    for (int k = 0; k < g3.size(); k++) {
        cout << g3[k].to_string() << endl;
    }
    
    TourGenerator tg(geodb, router);

    Stops stops;
    if (!stops.load("stops.txt"))
    {
        cout << "Unable to load tour data: " << argv[2] << endl;
        return 1;
    }

    std::cout << "Routing...\n\n";

    vector<TourCommand> tcs = tg.generate_tour(stops);
    if (tcs.empty())
        cout << "Unable to generate tour!\n";
    else
        print_tour(tcs);
}