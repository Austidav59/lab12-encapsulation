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
     if (!flying()) return;

     PositionVelocityTime pvt = flightPath.back();
     double speed = pvt.v.getSpeed();
     double altitude = pvt.pos.getMetersY();
     double interval = simulationTime; //- currentTime();
     assert(interval > -0.0001);


     double density = densityFromAltitude(altitude);
     double speedSound = speedSoundFromAltitude(altitude);
     double mach = speed / speedSound;
     double dragCoefficient = dragFromMach(mach);
     double windResistance = forceFromDrag(density, dragCoefficient, radius, speed);
     double magnitudeWind = -(windResistance / mass); //negative because it is causing decceleration
     Acceleration aWind(-pvt.v.getAngle(), magnitudeWind);

     double magnitudeGravity = gravityFromAltitude(altitude);
     Angle angleGravity;
     angleGravity.setDown();
     Acceleration aGravity(angleGravity, magnitudeGravity);

	 Acceleration aTotal = aGravity + aWind;

	 
     pvt.pos.add(aTotal, pvt.v, interval);
     pvt.v.add(aTotal, interval);
     pvt.t = simulationTime;


     // Store new state in flight path
     flightPath.push_back(pvt);
 }

 void Projectile::fire(const Position &posHowitzer,
     double simulationTime,
     const Angle &elevation,
     double muzzleVelocity)
 {
     reset();

     PositionVelocityTime pvt;
     pvt.pos = posHowitzer;
     pvt.t = simulationTime;
     pvt.v.set(elevation, muzzleVelocity);
     flightPath.push_back(pvt);
 }

 