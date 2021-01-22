#pragma once
#include <GL/freeglut.h>
#include "Vista.h"

namespace std
{
	//Variables para el Look At
	float eye_x = 1.0;
	float eye_y = 1.0;
	float eye_z = 5.0;
	Vec3 eye = Vec3(eye_x, eye_y, eye_z); //eye

	float camera_x = 0.0;
	float camera_y = 0.0;
	float camera_z = 0.0;
	Vec3 camera = Vec3(camera_x, camera_y, camera_z); //target

	float up_x = 0.0;
	float up_y = 1.0;
	float up_z = 0.0;
	Vec3 up = Vec3(up_x, up_y, up_z); //up

	////////// C á m a r a  /////////////
	void camara(float x, float y, float z)
	{
		eye_x += x;
		eye_y += y;
		eye_z += z;

		eye = Vec3(eye_x, eye_y, eye_z);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//gluLookAt(eye_x, eye_y, eye_z, 0.0, 0.0, 0.0, up_x, up_y, up_z);
		LookAt(eye, camera, up);
	}

	////////// T e c l a d o  /////////////
	void teclado(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 'd':
			camara(0.1f, 0.0f, 0.0f);// Derecha
			break;
		case 'a':
			camara(-0.1f, 0.0f, 0.0f);// Izquierda
			break;
		case'w':
			camara(0.0f, 0.1f, 0.0f);// Arriba
			break;
		case 's':
			camara(0.0f, -0.1f, 0.0f);// Abajo
			break;

		case 27: //esc
			eye_x = 4;
			eye_y = 4;
			eye_z = 4;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			//gluLookAt(eye_x, eye_y, eye_z, 0.0, 0.0, 0.0, up_x, up_y, up_z);
			LookAt(eye, camera, up);
			break;
		}
		glutPostRedisplay();
	}
}