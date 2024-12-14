/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"    // everything should have a point
#include "angle.h"       // angle of the lander
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "howitzer.h"
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
using namespace std;


/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
    // set up the simulator
    Simulator(const Position& posUpperRight) : ground(posUpperRight), a(0.0), time(0.001) {}

    // display stuff on the screen
    void display(Position posUpperRight);

    Position posUpperRight = posUpperRight;
    Angle a;
    Ground ground;
    Howitzer h;
    Projectile p;
    double time;
};
