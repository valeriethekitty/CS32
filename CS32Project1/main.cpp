#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include "Game.h"
#include "City.h"
#include "globals.h"
#include "History.h"
#include "Player.h"
#include "Tooter.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

    // Play the game
    g.play();
}