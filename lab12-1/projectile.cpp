/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
 #include "acceleration.h"
 #include "position.h"
 #include "velocity.h"
 #include "howitzer.h"
 using namespace std;


 void Projectile::advance(double simulationTime)
 {
     if (flightPath.empty()) return;
     PositionVelocityTime pvt = flightPath.back();
     double speed = pvt.v.getSpeed();
     double altitude = pvt.pos.getMetersY();
     double density = densityFromAltitude(altitude);
     double dragCoefficient = dragFromMach(speedSoundFromAltitude(altitude));
     double windResistance = forceFromDrag(density, dragCoefficient, radius, speed);
     double gravity = gravityFromAltitude(altitude);
     double acceleration = windResistance / mass;
     Angle ang = pvt.v.getAngle();
     Acceleration acc(0.0, 0.0);
     acc.set(ang, acceleration);

     Position lastPos = flightPath.back().pos;
     Velocity lastVel = flightPath.back().v;
     double area = M_PI * radius * radius;

     // Update position based on velocity and gravity using getX() and getY()
     double newX = pvt.pos.getMetersX() + pvt.v.getDX() * simulationTime + 0.5 * acc.getDDX() * simulationTime * simulationTime;
     double newY = pvt.pos.getMetersY() + pvt.v.getDY() * simulationTime + 0.5 * (acc.getDDY() - gravity) * simulationTime * simulationTime;
     Position newPos(newX, newY);

     // Update velocity based on gravity
     double newDX = pvt.v.getDX() + acc.getDDX() * simulationTime;
     double newDY = pvt.v.getDY() + (acc.getDDY() - gravity) * simulationTime;
     Velocity newV(newDX, newDY);

     Projectile::PositionVelocityTime newPVT;
     newPVT.pos = newPos;
     newPVT.v = newV;
     newPVT.t = simulationTime;


     // Store new state in flight path
     flightPath.push_back(newPVT);
 }

 /*void Projectile::fire()
 {
     
 }*/

 