#include "GamerMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    GamerMap m;
    assert(m.numGamers() == 0);
    m.addGamer("asda");
    assert(m.numGamers() == 1);
    m.addGamer("xdfs");
    assert(m.numGamers() == 2);
    m.print();
    assert(m.hoursSpent("asda") == 0);
    m.play("xdfs", 1.5);
    m.play("xdfs", 0.5);
    m.play("asda", 0.12);
    m.print();
    assert(m.hoursSpent("xdfs") == 2);
    assert(!m.play("idk", 0.5));
    assert(m.hoursSpent("idk") == -1);
    assert(!m.addGamer("asda"));
    assert(!m.play("asda", -1));
    cout << "Passed all tests" << endl;
}