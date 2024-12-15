/***********************************************************************
* Header File:
*    VELOCITY
* Author:
*    Jacob Isaksen, Austin Davis
* Summary:
*    Everything we need to know about speed
************************************************************************/

#pragma once

class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestProjectile;
class Acceleration;
class Angle;

class Velocity
{
   friend TestPosition;
   friend TestVelocity;
   friend TestProjectile;

public:
   // constructors
   Velocity() : dx(0.0), dy(0.0) { }
   Velocity(double dx, double dy) : dx(dx), dy(dy) { }

   // getters
   double getDX() const { return dx; }
   double getDY() const { return dy; }
   double getSpeed() const;
   Angle getAngle() const;

   // setters
   void set(const Angle& angle, double magnitude);
   void setDX(double dx) { this->dx = dx; }
   void setDY(double dy) { this->dy = dy; }
   void addDX(double dx) { setDX(getDX() + dx); }
   void addDY(double dy) { setDY(getDY() + dy); }
   void add(const Acceleration& acceleration, double time);
   void add(const Velocity& rhs) { dx += rhs.getDX(); dy += rhs.getDY(); }
   void reverse();

private:
   double dx;           // horizontal velocity
   double dy;           // vertical velocity
};
