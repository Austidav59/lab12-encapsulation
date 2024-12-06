/***********************************************************************
 * Header File:
 *    PHYSICS
 * Author:
 *    Austin Davis, Jacob Isaksen
 * Summary:
 *    Laws of motion, effects of gravity, wind resistance, etc.
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>
#include <stdexcept>
using namespace std;

/*******************************************************
 * AREA FROM RADIUS
 * Compute the area of a circle from the radius
 *    area = pi * radius ^ 2
 ********************************************************/
inline double areaFromRadius(double radius)
{
    return M_PI * (radius * radius);
}

/**********************************************************
 * FORCE FROM DRAG
 * Determine the drag on a shell based on several factors:
 *    density  : The density of the air (kg/m^3)
 *    drag     : The drag coefficient of the shell (no units)
 *    radius   : The radius of the shell (m)
 *    velocity : The velocity of the shell (m/s)
 * The force is determined by:
 *    force = 1/2 * density * drag * area * velocity^2
 ************************************************************/
inline double forceFromDrag(double density, double drag,
                            double radius, double velocity)
{
    return 0.5 * density * drag * areaFromRadius(radius) * (velocity * velocity);
}

/**********************************************************
 * ACCELERATION FROM FORCE
 * Calculate acceleration from a given force and mass.
 *    force        : N
 *    mass         : kg
 *    acceleration : m/s^2
 * Equation: f = m * a
 ************************************************************/
inline double accelerationFromForce(double force, double mass)
{
    return force / mass;
}

/***********************************************************
 * VELOCITY FROM ACCELERATION
 * Determine how much velocity will be imparted in a given time
 * from a given acceleration.
 *    acceleration : m/s^2
 *    time         : s
 * Equation: v = a * t
 ************************************************************/
inline double velocityFromAcceleration(double acceleration, double time)
{
    return acceleration * time;
}

/*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linearly interpolate.
 * Equation:
 *   (r - r0) / (d - d0) = (r1 - r0) / (d1 - d0)
 * Thus:
 *   r = r0 + (r1 - r0) * (d - d0) / (d1 - d0)
 **********************************************************/
inline double linearInterpolation(double d0, double r0,
                                  double d1, double r1,
                                  double d)
{
    if (d1 == d0) {
        throw std::invalid_argument("d0 and d1 must be different values.");
    }
    return r0 + (r1 - r0) * (d - d0) / (d1 - d0);
}

/*********************************************************
 * MAPPING
 * A simple structure to represent the domain and the range.
 * Used for linear interpolation
 *********************************************************/
struct Mapping
{
   double domain;
   double range;
};

/*********************************************************
 * LINEAR INTERPOLATION FROM MAPPING ARRAY
 * Linearly interpolate from a list of domains and ranges.
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain);

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on altitude
 *********************************************************/
double gravityFromAltitude(double altitude);

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on altitude
 *********************************************************/
double densityFromAltitude(double altitude);

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * Calculate the speed of sound at a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude);

/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient based on Mach number.
 *********************************************************/
double dragFromMach(double speedMach);
