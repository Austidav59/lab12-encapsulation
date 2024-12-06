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

    void defaultConstructor()
    {
        Howitzer h;
        assertUnit(h.getPosition().getMetersX() == 0.0);
        assertUnit(h.getPosition().getMetersY() == 0.0);
        assertUnit(fabs(h.getElevation() - M_PI/4.0) < 0.001);
        assertUnit(fabs(h.getMuzzleVelocity() - 827.00) < 0.001);
    }

    void getPosition_zero()
    {
        Howitzer h;
        h.setPosition(0.0, 0.0);
        Position pos = h.getPosition();
        assertUnit(pos.getMetersX() == 0.0 && pos.getMetersY() == 0.0);
    }

    void getPosition_middle()
    {
        Howitzer h;
        h.setPosition(123.4, 567.8);
        Position pos = h.getPosition();
        assertUnit(fabs(pos.getMetersX() - 123.4) < 0.001 && fabs(pos.getMetersY() - 567.8) < 0.001);
    }

    void getMuzzleVelocity_slow()
    {
        Howitzer h;
        h.setMuzzleVelocity(24.68);
        assertUnit(fabs(h.getMuzzleVelocity() - 24.68) < 0.001);
    }

    void getMuzzleVelocity_standard()
    {
        Howitzer h;
        h.setMuzzleVelocity(827.00);
        assertUnit(fabs(h.getMuzzleVelocity() - 827.00) < 0.001);
    }

    void getElevation_up()
    {
        Howitzer h;
        h.setElevation(0.0);
        assertUnit(fabs(h.getElevation() - 0.0) < 0.001);
    }

    void getElevation_right()
    {
        Howitzer h;
        h.setElevation(0.4);
        assertUnit(fabs(h.getElevation() - 0.4) < 0.001);
    }

    void getElevation_left()
    {
        Howitzer h;
        h.setElevation(5.8);
        assertUnit(fabs(h.getElevation() - 5.8) < 0.001);
    }

    void generatePosition_small()
    {
        Howitzer h;
        Position posUpperRight;
        posUpperRight.setPixelsX(10);
        posUpperRight.setPixelsY(10);
        
        h.generatePosition(posUpperRight);
        
        Position pos = h.getPosition();
        
        assertUnit(pos.getPixelsX() >= 1 && pos.getPixelsX() <= 9);
        assertUnit(pos.getPixelsY() == 0); // Ensure y is always zero
    }

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

    void raise_rightDown()
    {
        Howitzer h;
        h.setElevation(0.5);
        h.raise(-0.1);
        assertUnit(fabs(h.getElevation() - 0.6) < 0.001);
    }

    void raise_rightUp()
    {
        Howitzer h;
        h.setElevation(0.5);
        h.raise(0.1);
        assertUnit(fabs(h.getElevation() - 0.4) < 0.001);
    }

    void raise_leftDown()
    {
        Howitzer h;
        h.setElevation(-0.5);
        h.raise(-0.1);
        assertUnit(fabs(h.getElevation() - (-0.6)) < 0.001);
    }

    void raise_leftUp()
    {
        Howitzer h;
        h.setElevation(-0.5);
        h.raise(0.1);
        assertUnit(fabs(h.getElevation() - (-0.4)) < 0.001);
    }

    void rotate_clock()
    {
        Howitzer h;
        h.setElevation(1.23);
        h.rotate(0.3);
        assertUnit(fabs(h.getElevation() - 1.53) < 0.001);
    }

    void rotate_counterClock()
    {
        Howitzer h;
        h.setElevation(1.23);
        h.rotate(-0.3);
        assertUnit(fabs(h.getElevation() - 0.93) < 0.001);
    }

    void rotate_wrapClock()
    {
        Howitzer h;
        h.setElevation(6.1);
        h.rotate(0.2);
        assertUnit(fabs(h.getElevation() - 0.1) < 0.001);
    }

    void rotate_wrapCounterClock()
    {
        Howitzer h;
        h.setElevation(0.1);
        h.rotate(-0.2 - 4 * M_PI);
        assertUnit(fabs(h.getElevation() - 6.1) < 0.001);
    }

    void setupStandardFixture()
    {
        Position p;
        metersFromPixels = p.metersFromPixels;
        p.metersFromPixels = 1100.0;
    }

    void teardownStandardFixture()
    {
        assert(metersFromPixels != -1.0);
        Position p;
        p.metersFromPixels = metersFromPixels;
    }
};
