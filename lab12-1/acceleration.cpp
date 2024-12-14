/***********************************************************************
* Source File:
*    ACCELERATION
* Author:
*    Jacob Isaksen, Austin Davis
* Summary:
*    Everything we need to know about changing speed
************************************************************************/

#include "acceleration.h"
#include "angle.h"
#include <cmath>

/*********************************************
* ACCELERATION : SET
*  set from angle and direction
*********************************************/
void Acceleration::set(const Angle& a, double magnitude)
{
   ddx = magnitude * sin(a.getRadians());
   ddy = magnitude * cos(a.getRadians());
}

/*********************************************
* ACCELERATION : ADD
*  Add two acceleration objects
*********************************************/
void Acceleration::add(const Acceleration& rhs)
{
   ddx += rhs.getDDX();
   ddy += rhs.getDDY();
}

