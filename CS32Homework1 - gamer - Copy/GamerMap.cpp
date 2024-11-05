#include "GamerMap.h"
#include <iostream>

bool GamerMap::addGamer(std::string name) {
    // If a person with the specified name is not currently in the map, 
    // and there is room in the map, add an entry for that person
    // recording that they have spent 0 hours gaming, and return true.
    // Otherwise, make no change to the map and return false.
    return (gamerMap.insert(name, 0));
}

double GamerMap::hoursSpent(std::string name) const {
    // If a person with the specified name is in the map, return how
    // many hours they have spent gaming; otherwise, return -1.
    double hour = -1;
    Map gamer = gamerMap; // why
    gamer.get(name, hour);
    return hour;
}

bool GamerMap::play(std::string name, double hours) {
    // If no person with the specified name is in the map or if hours
    // is negative, make no change to the map and return false.
    // Otherwise, increase by the hours parameter the number of hours
    // the indicated person has spent gaming and return true.
    if (hours < 0) {
        return false;
    }
    double newHours;
    Map gamer = gamerMap;
    gamer.get(name, newHours);
    newHours += hours;
    return (gamerMap.update(name, newHours));
}

void GamerMap::print() const {
    // Write to cout one line for every person in the map.  Each line
    // consists of the person's name, followed by one space, followed by
    // the number of hours that person has spent gaming.  Write no other
    // text.  The lines need not be in any particular order.
    Map gamer = gamerMap;
    for (int i = 0; i < gamerMap.size(); i++) {
        std::string name;
        double hours;
        gamer.get(i, name, hours);
        std::cout << name << " " << hours << std::endl;
    }
}