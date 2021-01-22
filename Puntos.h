#pragma once

namespace std
{

	class Puntos
	{
	public:


		Puntos(void);

		float getX(void);
		float getY(void);
		float getZ(void);

		void setX(float X);
		void setY(float Y);
		void setZ(float Z);

	private:

		float x, y, z;
	};
}
