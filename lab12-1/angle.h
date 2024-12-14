/***********************************************************************
* Header File:
*    ANGLE
* Author:
*    Jacob Isaksen, Austin Davis
* Summary:
*    Everything we need to know about a direction
************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

class TestAngle;
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestHowitzer;
class TestProjectile;

class Angle
{
public:
	friend TestAcceleration;
	friend TestVelocity;
	friend TestAngle;
	friend TestHowitzer;
	friend TestProjectile;

	Angle() : radians(0.0) {}
	Angle(const Angle& rhs) : radians(rhs.radians) {}
	Angle(double degrees) : radians(0.0) { setDegrees(degrees); }

	double getDegrees() const { return radians * 180.0 / M_PI; }
	double getRadians() const { return radians; }

	double getDx() const { return sin(radians); }
	double getDy() const { return cos(radians); }

	bool isRight() const { return radians < M_PI; }
	bool isLeft() const { return radians > M_PI; }

	void setDegrees(double degrees) { radians = normalize(convertToRadians(degrees)); }
	void setRadians(double radians) { this->radians = normalize(radians); }
	void setNaturalRadians(double radians);  // Set without normalization (for howitzer elevation change)

	void setUp() { radians = 0.0; }
	void setDown() { radians = M_PI; }
	void setRight() { radians = M_PI * 0.5; }
	void setLeft() { radians = M_PI * 1.5; }


	void reverse() { radians = normalize(radians + M_PI); }

	Angle operator-() const
	{
		Angle aReturn(*this);
		aReturn.reverse();
		return aReturn;
	}

	Angle& add(double delta)
	{
		radians = normalize(radians + delta);
		return *this;
	}

	void setDxDy(double dx, double dy)
	{
		radians = normalize(atan2(dx, dy));

	}

	Angle& operator+(double degrees)
	{
		return Angle(getDegrees() + degrees);
	}

private:
	double normalize(double radians) const;

	double convertToRadians(double degrees) const
	{
		return degrees / 360.0 * (M_PI * 2.0);
	}

	double convertToDegrees(double radians) const
	{
		return radians / (M_PI * 2.0) * 360.0;
	}


	double radians; // Internal representation in radians
};

inline std::ostream& operator<<(std::ostream& out, const Angle& rhs)
{
	out << rhs.getDegrees() << " degrees";
	return out;
}