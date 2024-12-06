/***********************************************************************
* Source File:
*    VELOCITY
* Author:
*    Jacob Isaksen, Austin Davis
* Summary:
*    Everything we need to know about speed
************************************************************************/

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"
#include <cmath>
#include <cassert>

void Velocity::add(const Acceleration& acceleration, double time) {
   dx += acceleration.getDDX() * time;
   dy += acceleration.getDDY() * time;
}

double Velocity::getSpeed() const {
   return std::sqrt(dx * dx + dy * dy);
}

void Velocity::set(const Angle& angle, double magnitude) {
   dx = magnitude * std::sin(angle.getRadians());
   dy = magnitude * std::cos(angle.getRadians());
}

Angle Velocity::getAngle() const {
   return Angle(std::atan2(dy, dx));
}
