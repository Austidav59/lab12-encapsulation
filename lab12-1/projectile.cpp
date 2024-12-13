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
     double interval = simulationTime - currentTime();
     assert(interval > 0.0);


     double density = densityFromAltitude(altitude);
     double speedSound = speedSoundFromAltitude(altitude);
     double mach = speed / speedSound;
     double dragCoefficient = dragFromMach(mach);
     double windResistance = forceFromDrag(density, dragCoefficient, radius, speed);
     double magnitudeWind = -(windResistance / mass); //negative because it is causing decceleration
     Angle ang = pvt.v.getAngle();
     Acceleration aWind(0.0, 0.0);
     ang.setRadians(-ang.getRadians());
     aWind.set(ang, magnitudeWind);

     double magnitudeGravity = gravityFromAltitude(altitude);
     Angle angleGravity;
     angleGravity.setDown();
     Acceleration aGravity(0.0, 0.0);
     aGravity.set(angleGravity, magnitudeGravity);

     Acceleration aTotal(0.0, 0.0);
     double x = aGravity.getDDX() + aWind.getDDX();
     double y = aGravity.getDDY() + aWind.getDDY();
     aTotal.set(x,y);

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

 