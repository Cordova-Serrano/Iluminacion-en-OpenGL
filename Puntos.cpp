#include "Puntos.h"

namespace std
{
	Puntos::Puntos(void)
	{
	}
	// S e t t e r s
	void Puntos::setX(float X)
	{
		x = X;
	}
	void Puntos::setY(float Y)
	{
		y = Y;
	}
	void Puntos::setZ(float Z)
	{
		z = Z;
	}
	// G e t t e r s
	float Puntos::getX(void)
	{
		return x;
	}

	float Puntos::getY(void)
	{
		return y;
	}

	float Puntos::getZ(void)
	{
		return z;
	}
}
