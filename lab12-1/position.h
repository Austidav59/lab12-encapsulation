/***********************************************************************
* Header File:
*    POSITION
* Author:
*    Jacob Isaksen, Austin Davis
* Summary:
*    Everything we need to know about a location on the screen.
************************************************************************/


#pragma once

#include <iostream>
#include <cmath>

class TestPosition;
class Acceleration;
class Velocity;
class TestGround;
class TestHowitzer;
class TestProjectile;

class Position
{
public:
   friend ::TestPosition;
   friend ::TestGround;
   friend ::TestHowitzer;
   friend ::TestProjectile;

   // constructors
   Position() : x(0.0), y(0.0) {}
   Position(double x, double y);
   Position(const Position& pt) : x(pt.x), y(pt.y) {}
   Position& operator = (const Position& pt);

   // getters
   double getMetersX() const { return x; }
   double getMetersY() const { return y; }
   double getPixelsX() const;
   double getPixelsY() const;

   // setters
   static void setZoom(double z);
   static double getZoom();
   void setMeters(double xMeters, double yMeters) { x = xMeters; y = yMeters; }
   void setMetersX(double xMeters) { x = xMeters; }
   void setMetersY(double yMeters) { y = yMeters; }
   void setPixelsX(double xPixels);
   void setPixelsY(double yPixels);
   double addMetersX(double dx) { x += dx; return x; }
   double addMetersY(double dy) { y += dy; return y; }
   double addPixelsX(double dx);
   double addPixelsY(double dy);
   void add(const Acceleration& a, const Velocity& v, double t);
   void reverse() { x = -x; y = -y; }

private:
   double x;                 // horizontal position
   double y;                 // vertical position
   static double metersFromPixels; // Declare the static member variable
};

// stream I/O useful for debugging
std::ostream& operator << (std::ostream& out, const Position& pt);
std::istream& operator >> (std::istream& in, Position& pt);

struct PT
{
   double x;
   double y;
};
