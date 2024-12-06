//
//  positionvelocitytime.h
//  lab12
//
//  Created by Austin Davis on 12/6/24.
//
// positionvelocitytime.h
#pragma once
#include "position.h"
#include "velocity.h"

struct PositionVelocityTime {
    Position pos;     // Current position of the projectile
    Velocity v;      // Current velocity of the projectile
    double t;        // Time at this state

    PositionVelocityTime(const Position& p, const Velocity& vel, double time) : pos(p), v(vel), t(time) {}
};
