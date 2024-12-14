/***********************************************************************
* Source File:
*    POSITION
* Author:
*    Jacob Isaksen, Austin Davis
* Summary:
*    Everything we need to know about a location on the screen.
************************************************************************/

#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include <cassert>

// Define the static member variable
//double Position::metersFromPixels = 1.0;

Position::Position(double x, double y) : x(0.0), y(0.0)
{
    setMetersX(x);
	setMetersY(y);
}

Position& Position::operator = (const Position& pt)
{
	x = pt.x;
	y = pt.y;
	return *this;
}

void Position::add(const Acceleration& a, const Velocity& v, double t)
{
   x += v.getDX() * t + 0.5 * a.getDDX() * t * t;
   y += v.getDY() * t + 0.5 * a.getDDY() * t * t;
}

std::ostream& operator << (std::ostream& out, const Position& pt)
{
   out << "(" << pt.getMetersX() << "m , " << pt.getMetersY() << "m)";
   return out;
}

std::istream& operator >> (std::istream& in, Position& pt)
{
   double x;
   double y;
   in >> x >> y;

   pt.setMetersX(x);
   pt.setMetersY(y);

   return in;
}
