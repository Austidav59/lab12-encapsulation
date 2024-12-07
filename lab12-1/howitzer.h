/**********************************************************************
 * Header File:
 *    HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a howitzer (aka the gun)
 ************************************************************************/

#pragma once

#include <list>
#include "projectile.h"
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"
#include "flightstate.h"          // Include for FlightState
#include "positionvelocitytime.h" // Include for PositionVelocityTime

#define DEFAULT_MUZZLE_VELOCITY   827.00     // m/s

class TestHowitzer;

/*********************************************
 * Howitzer
 * Everything we need to know about a howitzer (aka the gun)
 *********************************************/
class Howitzer
{
public:
   friend TestHowitzer;

   Howitzer()
       : mass(46.7), radius(0.077545), muzzleVelocity(DEFAULT_MUZZLE_VELOCITY), elevation(45), velocity(0, 0) // Initialize velocity
   {
       flightPath.clear();
   }

   void draw(ogstream& gout, double flightTime) const
   {
      gout.drawHowitzer(position, elevation.getRadians(), flightTime);
   }

   const Position& getPosition() const { return position; }
   void setPosition(double x, double y) { position.setMetersX(x); position.setMetersY(y); }

   double getMuzzleVelocity() const { return muzzleVelocity; }
   void setMuzzleVelocity(double velocity) { muzzleVelocity = velocity; }

   double getMass() const { return mass; }
   void setMass(double m) { mass = m; } // Setter for mass

   double getRadius() const { return radius; }
   void setRadius(double r) { radius = r; } // Setter for radius

   double getElevation() const { return elevation.getRadians(); } // Return elevation in radians
   void setElevation(double angle) { elevation.setRadians(angle); } // Set elevation angle in radians

   // Reset method to clear flight path and reset member variables
   void reset()
   {
       mass = 46.7;
       radius = 0.077545;
       flightPath.clear();
       position.setMetersX(0); // Reset position as well if needed
       position.setMetersY(0);
       elevation.setRadians(45.0); // Reset elevation to default
       velocity = Velocity(0, 0); // Reset velocity
   }

   void generatePosition(const Position& upperRight)
   {
       
       double x = rand() % static_cast<int>(upperRight.getMetersX());
       double y = 0;
       setPosition(x, y);
   }

   void raise(double delta)
   {
       // Adjust elevation by delta radians
       double radians = elevation.getRadians();
       double newRadians = 0.0;
       if (radians >= 0.0) 
       {
           if (delta < 0.0)
           {
               newRadians = radians + fabs(delta);
           }
           else 
           {
               newRadians = radians - delta;
           }
       }
       else
       {
           if (delta < 0.0)
           {
              newRadians = radians - delta;
           }
       }
       elevation.setRadians(newRadians);
   }

   void rotate(double deltaAngle)
   {
       // Rotate the howitzer by deltaAngle radians
       double newAngle = elevation.getRadians() + deltaAngle;
       elevation.setRadians(newAngle);
       
       // Normalize the angle if necessary (optional)
       if (newAngle > 2 * M_PI) {
           newAngle -= 2 * M_PI;
       } else if (newAngle < 0) {
           newAngle += 2 * M_PI;
       }
       
       elevation.setRadians(newAngle);
   }

   void fire()
   {
       //Position initialPos = position;
       //Velocity initialVel(cos(angle * M_PI / 180) * velocity, sin(angle * M_PI / 180) * velocity);
       //
       //// Add to flight path
       //flightPath.push_back({initialPos, initialVel, 0}); // Store position and velocity with time (initially 0)
       
       Position initialPos(position);
       double initialSpeed = muzzleVelocity;
       Velocity initialV;
       initialV.set(elevation, initialSpeed);
       /*Velocity initialVel(cos(angle * M_PI / 180) * velocity, sin(angle * M_PI / 180) * velocity);*/

       // Add to flight path
       flightPath.push_back({ initialPos, initialV, 1 }); // Store position and velocity with time (initially 0)
   }

   void advance()
   {
      if (flightPath.empty()) return;

      Position lastPos = flightPath.back().pos;
      Velocity lastVel = flightPath.back().v;

      // Update position based on velocity and gravity using getX() and getY()
      double newX = lastPos.getMetersX() + lastVel.getDX();
      double newY = lastPos.getMetersY() + lastVel.getDY() - (9.80665); // Gravity effect
      
      // Store new state in flight path
      flightPath.push_back({Position(newX, newY), lastVel, 0}); // Time is initially 0 (update as needed)
   }

    void setFlightPath(const std::list<PositionVelocityTime>& path) {
        flightPath = path;
    }

    void setFlightState(const FlightState& state) {
        position = state.pos;
        velocity = state.vel; // Assuming you have a member variable for velocity.
    }

    const std::list<PositionVelocityTime>& getFlightPath() const { return flightPath; }
   
private:
    Position position;
    Velocity velocity;                // Add this member variable for storing velocity.
    double mass;                       // Weight of the howitzer.
    double radius;                     // Radius of the howitzer.
    double muzzleVelocity;             // Muzzle velocity of the projectile.
    Angle elevation;                   // Elevation angle of the howitzer.
    std::list<PositionVelocityTime> flightPath; // Stores the trajectory of the projectile.

    struct PositionVelocityTime {
        Position pos;     // Current position of the projectile
        Velocity v;      // Current velocity of the projectile
        double t;        // Time at this state

        PositionVelocityTime(const Position& p, const Velocity& vel, double time) : pos(p), v(vel), t(time) {}
    };
};
