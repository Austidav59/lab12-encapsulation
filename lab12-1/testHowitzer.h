/***********************************************************************
 * Header File:
 *    TEST HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Howitzer
 ************************************************************************/
#pragma once
#include "howitzer.h"
#include "unitTest.h"

 /*******************************
  * TEST HOWITZER
  * A friend class for Howitzer which contains the Howitzer unit tests
  ********************************/
class TestHowitzer : public UnitTest
{
public:
    void run()
    {
        // Ticket 1: Getters
        defaultConstructor();
        getPosition_zero();
        getPosition_middle();
        getMuzzleVelocity_slow();
        getMuzzleVelocity_standard();
        getElevation_up();
        getElevation_right();
        getElevation_left();

        // Ticket 2: Setters
        generatePosition_small();
        generatePosition_large();
        raise_rightDown();
        raise_rightUp();
        raise_leftDown();
        raise_leftUp();
        rotate_clock();
        rotate_counterClock();
        rotate_wrapClock();
        rotate_wrapCounterClock();

        report("Howitzer");
    }

private:
    double metersFromPixels = -1.0;

    /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    DEFAULT CONSTRUCTOR
     * input:   nothing
     * output:  zeros (except angle is at 45 degrees,
     *                 and the muzzle velocity is correct)
     *********************************************/
    void defaultConstructor()
    {
        setupStandardFixture();

        Howitzer h;
        assertUnit(h.position.x == 0.0);
        assertUnit(h.position.y == 0.0);
        assertUnit(fabs(h.getElevation() - M_PI / 4.0) < 0.001);
        assertUnit(h.muzzleVelocity, 827);

        teardownStandardFixture();
    }

    /*****************************************************************
    *****************************************************************
    * GETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GET POSITION ZERO
     * input:   h.pos=(0,0)
     * output:  pos=(0,0)
     *********************************************/
    void getPosition_zero()
    {
        Howitzer h;
        h.position.x = 0.0;
        h.position.y = 0.0;
        Position pos;
        pos.x = 99.99;
        pos.y = 88.88;

        pos = h.getPosition();

        assertUnit(pos.x == 0.0 && pos.y == 0.0);
    }

    /*********************************************
     * name:    GET POSITION MIDDLE
     * input:   h.pos=(123.4, 567.8)
     * output:  pos=(123.4, 567.8)
     *********************************************/
    void getPosition_middle()
    {
        Howitzer h;
        h.setPosition(123.4, 567.8);
        Position pos = h.position;
        assertUnit(fabs(pos.x - 123.4) < 0.001 && fabs(pos.y - 567.8) < 0.001);
    }

    /*********************************************
     * name:    GET MUZZLE VELOCITY - SLOW SPEED
     * input:   h.muzzleVelocity=(24.68)
     * output:  m=24.68
     *********************************************/
    void getMuzzleVelocity_slow()
    {
        Howitzer h;
        h.setMuzzleVelocity(24.68);
        assertUnit(fabs(h.muzzleVelocity - 24.68) < 0.001);
    }

    /*********************************************
     * name:    GET MUZZLE VELOCITY - STANDARD SPEED
     * input:   h.muzzleVelocity=(827.00)
     * output:  m=827
     *********************************************/
    void getMuzzleVelocity_standard()
    {
        Howitzer h;
        h.setMuzzleVelocity(827.00);
        assertUnit(fabs(h.muzzleVelocity - 827.00) < 0.001);
    }

    /*********************************************
     * name:    GET ELEVATION - up
     * input:   h.elevation=0
     * output:  e=0
     *********************************************/
    void getElevation_up()
    {
        Howitzer h;
        h.setElevation(0.0);
        assertUnit(fabs(h.getElevation() - 0.0) < 0.001);
    }

    /*********************************************
     * name:    GET ELEVATION - right
     * input:   h.elevation=0.4
     * output:  e=0.4
     *********************************************/
    void getElevation_right()
    {
        Howitzer h;
        h.setElevation(0.4);
        assertUnit(fabs(h.getElevation() - 0.4) < 0.001);
    }

    /*********************************************
     * name:    GET ELEVATION - left
     * input:   h.elevation=5.8
     * output:  e=5.8
     *********************************************/
    void getElevation_left()
    {
        Howitzer h;
        h.setElevation(5.8);
        assertUnit(fabs(h.getElevation() - 5.8) < 0.001);
    }

    /*****************************************************************
    *****************************************************************
    * SETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GENERATE POSITION small board
     * input:   (10px, 10px)
     * output:  1px <= x <= 9px
     *********************************************/
    void generatePosition_small()
    {
        Howitzer h;
        Position posUpperRight;
        posUpperRight.setPixelsX(10);
        posUpperRight.setPixelsY(10);

        h.generatePosition(posUpperRight);

        Position pos = h.position;

        assertUnit(pos.getPixelsX() >= 1 && pos.getPixelsX() <= 9);
        assertUnit(pos.getPixelsY() == 0); // Ensure y is always zero
    }

    /*********************************************
     * name:    GENERATE POSITION large board
     * input:   (1000px, 1000px)
     * output:  100px <= x <= 900px
     *********************************************/
    void generatePosition_large()
    {
        Howitzer h;
        Position posUpperRight;
        posUpperRight.setPixelsX(1000);
        posUpperRight.setPixelsY(1000);

        h.generatePosition(posUpperRight);

        Position pos = h.getPosition();

        assertUnit(pos.getPixelsX() >= 100 && pos.getPixelsX() <= 900);
        assertUnit(pos.getPixelsY() == 0); // Ensure y is always zero
    }

    /*********************************************
     * name:    RAISE to the right/down
     * input:   h.elevation=0.5radians  raise(-0.1)
     * output:  h.elevation=0.6radians
     *********************************************/
    void raise_rightDown()
    {
        Howitzer h;
        h.setElevation(0.5);
        h.raise(-0.1);
        assertUnit(fabs(h.getElevation() - 0.6) < 0.001);
    }

    /*********************************************
     * name:    RAISE to the right/up
     * input:   h.elevation=0.5radians  raise(0.1)
     * output:  h.elevation=0.4radians
     *********************************************/
    void raise_rightUp()
    {
        Howitzer h;
        h.setElevation(0.5);
        h.raise(0.1);
        assertUnit(fabs(h.getElevation() - 0.4) < 0.001);
    }

    /*********************************************
     * name:    RAISE to the left down
     * input:   h.elevation=-0.5radians  raise(-0.1)
     * output:  h.elevation=-0.6radians
     *********************************************/
    void raise_leftDown()
    {
        Howitzer h;
        h.setElevation(-0.5);
        h.raise(-0.1);
        assertUnit(fabs(h.getElevation() - (-0.6)) < 0.001);
    }

    /*********************************************
     * name:    RAISE to the left up
     * input:   h.elevation=-0.5radians  raise(0.1)
     * output:  h.elevation=0.4radians
     *********************************************/
    void raise_leftUp()
    {
        Howitzer h;
        h.setElevation(-0.5);
        h.raise(0.1);
        assertUnit(fabs(h.getElevation() - (-0.4)) < 0.001);
    }

    /*********************************************
     * name:    ROTATE CLOCKWISE no wrapping
     * input:   h.elevation=1.23 rotate=.3
     * output:  h.elevation=1.53
     *********************************************/
    void rotate_clock()
    {
        Howitzer h;
        h.setElevation(1.23);
        h.rotate(0.3);
        assertUnit(fabs(h.getElevation() - 1.53) < 0.001);
    }

    /*********************************************
     * name:    ROTATE COUNTER CLOCKWISE no wrapping
     * input:   h.elevation=1.23 rotate=-.3
     * output:  h.elevation=0.93
     *********************************************/
    void rotate_counterClock()
    {
        Howitzer h;
        h.setElevation(1.23);
        h.rotate(-0.3);
        assertUnit(fabs(h.getElevation() - 0.93) < 0.001);
    }

    /*********************************************
     * name:    ROTATE CLOCKWISE CLOCKWISE WRAP BY 2PI
     * input:   h.elevation=6.1 (2pi + -0.1) rotate=.2
     * output:  h.elevation=.1
     *********************************************/
    void rotate_wrapClock()
    {
        setupStandardFixture();
        Howitzer h;
        h.elevation.radians = 6.1;
        h.rotate(0.2 - (4.0 * M_PI));

        assertUnit(h.elevation.radians, 0.1);

        teardownStandardFixture();
    }

    /*********************************************
     * name:    ROTATE COUNTER CLOCKWISE WRAP BY 4PI
     * input:   h.elevation=0.1 rotate=-.2 - 4PI
     * output:  h.elevation=6.1 (2pi + -0.1)
     *********************************************/
    void rotate_wrapCounterClock()
    {
        setupStandardFixture();
        Howitzer h;
        h.elevation.radians = 0.1;
        h.rotate(-0.2 - (4.0 * M_PI));

        assertUnit(h.elevation.radians, M_PI * 2.0 - 0.1);

        teardownStandardFixture();
    }

    /*****************************************************************
    *****************************************************************
    * STANDARD FIXTURE
    *****************************************************************
    *****************************************************************/

    // setup standard fixture - set the zoom to 1100m per pixel
    void setupStandardFixture()
    {
        Position p;
        metersFromPixels = p.metersFromPixels;
        p.metersFromPixels = 1100.0;
    }

    // teardown the standard fixture - reset the zoom to what it was previously
    void teardownStandardFixture()
    {
        assert(metersFromPixels != -1.0);
        Position p;
        p.metersFromPixels = metersFromPixels;
    }
};