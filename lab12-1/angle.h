/***********************************************************************
* Header File:
*    ANGLE
* Author:
*    Jacob Isaksen, Austin Davis
* Summary:
*    Everything we need to know about a direction
************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

class TestAngle;
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestHowitzer;
class TestProjectile;

class Angle
{
public:
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestHowitzer;
   friend TestProjectile;

   Angle() : radians(0.0) {}
   Angle(const Angle& rhs) : radians(rhs.radians) {}
   Angle(double degrees) : radians(normalize(degrees* M_PI / 180.0)) {}

   double getDegrees() const { return radians * 180.0 / M_PI; }
   double getRadians() const { return radians; }

   double getDx() const { return cos(radians); }
   double getDy() const { return sin(radians); }

   bool isRight() const { return radians > -M_PI_2 && radians <= M_PI_2; }
   bool isLeft() const { return !isRight(); }

   void setDegrees(double degrees);
   void setRadians(double radians);

   void setUp() { radians = 0.0; }
   void setDown() { radians = M_PI; }
   void setRight() { radians = M_PI_2; }
   void setLeft() { radians = M_PI + M_PI_2; }


   void reverse() { radians = normalize(radians + M_PI); }

   Angle& add(double delta);

   void setDxDy(double dx, double dy);

   Angle& operator+(double degrees);

private:
   double normalize(double radians) const;

   double radians; // Internal representation in radians
};

inline std::ostream& operator<<(std::ostream& out, const Angle& rhs)
{
   out << rhs.getDegrees() << " degrees";
   return out;
}
