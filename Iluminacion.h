#pragma once
#include <GL/freeglut.h>
#include "Lector de Objetos.h"

namespace std
{
	//Iluminacion
	Vertex luzPosition;
	Vertex luzDir;
	Vertex vLuz;
	float ambient = 0.25f;

	void foco(Vertex luzDir)
	{
		glColor3f(1.0, 0.9, 0.0);

		glPointSize(10);
		glBegin(GL_POINTS);
			glVertex3f(luzDir.getX(), luzDir.getY(), luzDir.getZ());
		glEnd();
	}
	//Vector Normal
	Vertex normalCara(vector<Vertex> vCalc) //Método para obtener la normal de la cara
	{
		float a1, a2, a3; float b1, b2, b3; float c1, c2, c3; //Variables para obtener los vectores

		a1 = vCalc[0].getX(); a2 = vCalc[0].getY(); a3 = vCalc[0].getZ(); // A : (x,y,z) 
		//cout << "A ( " << a1 << ", " << a2 << ", " << a3 << ")\n";
		b1 = vCalc[1].getX(); b2 = vCalc[1].getY(); b3 = vCalc[1].getZ(); // B : (x,y,z)
		//cout << "B ( " << b1 << ", " << b2 << ", " << b3 << ")\n";
		c1 = vCalc[2].getX(); c2 = vCalc[2].getY(); c3 = vCalc[2].getZ(); // C : (x,y,z)
		//cout << "C ( " << c1 << ", " << c2 << ", " << c3 << ")\n";

		Vertex Va;
		Va.setX(b1 - a1); Va.setY(b2 - a2); Va.setZ(b3 - a3); //Obtencion de Va
		//cout << "Va ( " << Va.getX() << ", " << Va.getY() << ", " << Va.getZ() << ")\n";

		Vertex Vb;
		Vb.setX(c1 - b1); Vb.setY(c2 - b2); Vb.setZ(c3 - b3); //Obtencion de Vb
		//cout << "Vb ( " << Vb.getX() << ", " << Vb.getY() << ", " << Vb.getZ() << ")\n";

		float Vax = Va.getX(); float Vay = Va.getY(); float Vaz = Va.getZ(); //Variables de los puntos de Va
		float Vbx = Vb.getX(); float Vby = Vb.getY(); float Vbz = Vb.getZ(); //Variables de los puntos de Vb

		//Calculo de Normales para x y z
		float Nx = (Vay * Vbz) - (Vaz * Vby);
		float Ny = (Vaz * Vbx) - (Vax * Vbz);
		float Nz = (Vax * Vby) - (Vay * Vbx);

		//Magnitud
		double magnitud = sqrt((Nx * Nx) + (Ny * Ny) + (Nz * Nz));

		//Normal 
		Vertex N;
		N.setX(Nx / magnitud); N.setY(Ny / magnitud); N.setZ(Nz / magnitud);
		//cout << "Normal (" << N.getX() << ", " << N.getY() << ", " << N.getZ() << ")\n";

		//Al obtener la normal vaciar los vertices
		vCalc.clear();

		return N;
	}

	void normalLuz(Vertex luzDir, Vertex luzPosition) 
	{
		vLuz.setX(luzDir.getX() - luzPosition.getX());
		vLuz.setY(luzDir.getY() - luzPosition.getY());
		vLuz.setZ(luzDir.getZ() - luzPosition.getZ());

		//Magnitud
		double magnitud = sqrt((vLuz.getX() * vLuz.getX()) + (vLuz.getY() * vLuz.getY()) + (vLuz.getZ() * vLuz.getZ()));

		if (magnitud == 0) 
		{
			vLuz.setX(0);
			vLuz.setY(0);
			vLuz.setZ(0);
		}
		else 
		{
			vLuz.setX(vLuz.getX() / magnitud);
			vLuz.setY(vLuz.getY() / magnitud);
			vLuz.setZ(vLuz.getZ() / magnitud);
		}
	}

	//Recibe como parametro el color del objeto 
	void luzAmbiental(float R, float G, float B)
	{
		float luz = 1;
		float fuerza = 0.25;
		float ambient = fuerza * luz;
		R = R * ambient; G = G * ambient; B = B * ambient;

		glColor3f(R, G, B); //Se dibuja el color con luz ambiental 
	}
	//Difusa 
	float clamp(float x, float min, float max) 
	{
		if (x < min) x = min;
		else if (x > max) x = max;
		return x;
	}
	float dot(Vertex n,Vertex l) 
	{
		float cosTheta;
		//Realizar el producto punto de la normal con la direccion dela luz para obtener cosTheta
		cosTheta = (n.getX() * l.getX()) + (n.getY() * l.getY()) + (n.getZ() * l.getZ());

		return cosTheta;
	}
}