#pragma once
#include "Lector de Objetos.h"

namespace std
{
	// B e z i e r 

	float mBezier[4][4];

	float t;

	float a = 2.0; //Altura de la curva
	float d = 0.5; //Distancia en X

	float p1x = 1.5, p1y = 1.0, p1z = 0.0; //Punto 1 = Punto Inicial

	float p2x = p1x + d, p2y = p1y + a, p2z = 0.0; //Punto 2 = Altura
	float p3x = p2x + d, p3y = p2y, p3z = 0.0; //Punto 3 = Altura 

	float p4x = p3x + d, p4y = p1y, p4z = 0.0; //Punto 4 = Punto Final

	class controlPoints {
	public:
		float x, y, z;
	};

	controlPoints points[] = { {p1x, p1y, p1z},
							  {p2x, p2y, p2z},
							  {p3x, p3y, p3z},
							  {p4x, p4y, p4z} };



	Puntos position; //Puntos
	Puntos traslation; //Puntos

	float g = 0;

	// M a t r i c e s
	float mRotation[4][4]; //Matriz de Rotacion
	float mTransform[4][4]; //Matriz de Transformacion
	float mMov[4]; //Matriz de movimiento de vertices

	////////// B E Z I E R ///////////
	void Bezier()
	{
		GLfloat a, b, c, d;

		if (t < 1)
		{
			//Variables para formula
			//Fórmula : B(t) = (1-t)^3 * (P0) + 3(1-t)^2 t(P1) + 3(1-t)t^2(P2) + t^3(P3);
			a = pow((1 - t), 3);
			b = 3 * t * pow((1 - t), 2);
			c = 3 * pow(t, 2) * (1 - t);
			d = pow(t, 3);

			position.setX(a * points[0].x + b * points[1].x + c * points[2].x + d * points[3].x);
			position.setY(a * points[0].y + b * points[1].y + c * points[2].y + d * points[3].y);
			position.setZ(a * points[0].z + b * points[1].z + c * points[2].z + d * points[3].z);

			t += 0.001;
			if (t >= 1)
			{
				t = 0; //Regresa a 0 
			}
		}
	}

	void matrizBezier()
	{
		float x, y, z;

		x = position.getX();
		y = position.getY();
		z = position.getZ();

		//Matriz auxiliar para guardar las posiciones que iran a la matriz de bezier
		float aux[4][4]{{1, 0, 0, x},
						{0, 1, 0, y},
						{0, 0, 1, z},
						{0, 0, 0, 1}};

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mBezier[i][j] = aux[i][j]; //Añadiendo los valores a la matriz de Bezier
			}
		}
	}

	////////// E S C A L A C I O N ///////////
	void Escalacion(float* x, float* y, float* z,float escala)
	{
		*x *= escala;
		*y *= escala;
		*z *= escala;
	}

	///////// R o t a c i o n  ///////////
	void Rotacion()
	{
		float coseno = (float)cos(g);
		float seno = (float)sin(g);

		float mRotX[4][4]{ {1,   0   ,	 0   ,  0},
						   {0, coseno, -seno ,  0},
						   {0,  seno , coseno, 0},
						   {0,   0   ,   0   ,  1} };

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mRotation[i][j] = mRotX[i][j];
			}
		}
	}

	///////// T r a n s f o r m a c i o n  ///////////
	void Transformacion()
	{
		//Matriz auxiliar para guardar las posiciones
		float aux[4][4]{ {0, 0, 0, 0},
						  {0, 0, 0, 0},
						  {0, 0, 0, 0},
						  {0, 0, 0, 0} };
		//Mult Mat 
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				for (int k = 0; k < 4; k++)
				{
					aux[i][j] += mBezier[i][k] * mRotation[k][j];
				}
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				mTransform[i][j] = aux[i][j];
			}
		}
	}

	///////// M o v i m i e n t o  ///////////
	void Movimiento(float x, float y, float z)
	{
		//Añadimos los valores a mover
		mMov[0] = x;
		mMov[1] = y;
		mMov[2] = z;
		mMov[3] = 1;
		//Matriz auxiliar
		float aux[4] = { 0, //x
						 0, //y
						 0, //z
						 0 };

		//Multiplicacion de matriz transformacion por vertice
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				aux[i] += mTransform[i][j] * mMov[j];
			}
		}

		traslation.setX(aux[0]);
		traslation.setY(aux[1]);
		traslation.setZ(aux[2]);
	}
}