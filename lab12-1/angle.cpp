/***********************************************************************
* Source File:
*    ANGLE
* Author:
*    Jacob Isaksen, Austin Davis
* Summary:
*    Everything we need to know about a direction
************************************************************************/

#include "angle.h"
#include <cmath>
#include <cassert>

void Angle::setDegrees(double degrees)
{
   radians = normalize(degrees * M_PI / 180.0);
}

void Angle::setRadians(double radians)
{
   this->radians = normalize(radians);
}

Angle &Angle::add(double delta)
{
   radians = normalize(radians + delta);
   return *this;
}

void Angle::setDxDy(double dx, double dy)
{
   if (dx == 0.0 && dy == 0.0)
   {
      radians = 0.0; // Default case: no movement
   }
   else if (dx == 0.0)
   {
      radians = (dy > 0) ? M_PI_2 : -M_PI_2; // Straight up or straight down
   }
   else if (dy == 0.0)
   {
      // Handle small negative dx values more accurately
      if (dx > 0)
      {
         radians = M_PI_2; // Right
      }
      else
      {
         radians = M_PI; // Left
      }
   }
   else
   {
      radians = normalize(atan2(dy, dx)); // General case for other directions
   }
}


Angle &Angle::operator+(double degrees) 
{
    double deltaInRadians = normalize(degrees * M_PI / 180.0);
    this->add(deltaInRadians);
    return *this;
}

double Angle::normalize(double radians) const
{
   if (radians >= (M_PI * 2.0)) {
      double multiples = floor(radians / (M_PI * 2.0));
      assert(radians - (M_PI * 2.0) * multiples >= 0.0);
      assert(radians - (M_PI * 2.0) * multiples <= (M_PI * 2.0));
      return radians - ((M_PI * 2.0) * multiples);
   }
   else if (radians < 0.0) {
      double multiples = ceil(-radians / (M_PI * 2.0));
      assert((M_PI * 2.0) * multiples + radians >= 0.0);
      assert((M_PI * 2.0) * multiples + radians <= (M_PI * 2.0));
      return (M_PI * 2.0) * multiples + radians;
   }
   assert(0.0 <= radians && radians <= (M_PI * 2.0));
   return radians;
}
