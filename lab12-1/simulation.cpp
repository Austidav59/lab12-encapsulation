/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

 #include "simulation.h"  // for SIMULATION
 #include "uiDraw.h"      // for RANDOM and DRAW*
 #include <ctime>  	// for the time function
using namespace std;


 /**********************************************************
  * DISPLAY
  * Draw on the screen
  **********************************************************/
void Simulator::display(Position posUpperRight)
{
	double elevation = ground.getElevationMeters(posUpperRight);
	ogstream gout;
	Position pos(elevation,0.0);
	gout = pos;
	gout << "Helow World\n";

    /*draw the ground*/
	ground.draw(gout);
	gout.drawTarget(ground.getTarget());

    /*draw the Howitzer*/
    gout.drawHowitzer(h.getPosition(), a.getRadians(), 0.0);

	/*draw the projectile*/
	gout.drawProjectile(p.getPosition(), p.getFlightTime());

}
