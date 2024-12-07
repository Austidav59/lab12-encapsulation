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

 /**********************************************************
  * DISPLAY
  * Draw on the screen
  **********************************************************/
void Simulator::display()
{
    ogstream gout;

    /*draw the ground*/
    ground.draw(gout);

    /*draw the lander*/
    gout.drawHowitzer(Position(200, 200), a.getRadians(), 1.0);
    gout.drawProjectile(Position(200, 200), 1.0);

}
