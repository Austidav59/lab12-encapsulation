/***********************************************************************
* Header File:
*    ACCELERATION
* Author:
*    Jacob Isaksen, Austin Davis
* Summary:
*    Everything we need to know about acceleration
************************************************************************/

#pragma once
#include "angle.h"

class TestAcceleration;
class TestVelocity;
class TestPosition;
class TestLander;
class Angle;

/*********************************************
* Acceleration
* Let's get moving
*********************************************/
class Acceleration
{
   friend TestPosition;
   friend TestVelocity;
   friend TestAcceleration;
   friend TestLander;

public:
   // constructors
   Acceleration() : ddx(0.0), ddy(0.0) { }
   Acceleration(double ddx, double ddy) : ddx(ddx), ddy(ddy) { }
   Acceleration(Angle a, double magnitude) { set(a, magnitude); }

   // getters
   double getDDX() const { return ddx; }
   double getDDY() const { return ddy; }

   // setters
   void setDDX(double ddx) { this->ddx = ddx; }
   void setDDY(double ddy) { this->ddy = ddy; }
   void set(const Angle& a, double magnitude);

   // new methods
   void addDDX(double ddx) { this->ddx += ddx; }
   void addDDY(double ddy) { this->ddy += ddy; }
   void add(const Acceleration& rhs);

   Acceleration operator + (const Acceleration& rhs) const
   {
	   Acceleration aReturn(*this);
	   aReturn.add(rhs);
	   return aReturn;
   }

private:
   double ddx;     // horizontal acceleration
   double ddy;     // vertical acceleration
};
