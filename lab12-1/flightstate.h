//
//  flightstate.h
//  lab12
//
//  Created by Austin Davis on 12/6/24.
//
// flightstate.h
#pragma once
#include "position.h"
#include "velocity.h"

struct FlightState {
    Position pos;
    Velocity vel;

    FlightState(const Position& p, const Velocity& v) : pos(p), vel(v) {}
};
