#include <GL/freeglut.h>
#include <Math.h>
#include "Lector de Objetos.h"
#include "Puntos.h"
#include "Camara.h"
#include "Matrices.h"
#include "Iluminacion.h"

using namespace std;

//Resolucion de la ventana
int w = 1280, h = 720;

//Objetos
Obj Tanque("tanque.obj");
float escalaTanque = 0.25;
Obj Bala("cubo.obj");
float escalaBala = 0.05;

////////// C A R A S ///////////
void CarasTanque(Obj obj)
{
	int f, v;
	vector<Vertex> vCalc; //Vector que almacena vectores para el cálculo de la normal 
	Vertex vertices; //variable que almacena float x y z 
	float color = 1;
	float difuse;

	//C A R A S 
	for (f = 0; f < obj.faces.size(); f++)
	{
		int i = 0;

		if (obj.faces[f].refs.size() == 4)
		{
			glBegin(GL_POLYGON);
		}
		else
		{
			glBegin(GL_TRIANGLES);
		}

		for (v = 0; v < obj.faces[f].refs.size(); v++)
		{
			float x = obj.vertices[obj.faces[f].refs[v]].getX();
			float y = 1.5 + obj.vertices[obj.faces[f].refs[v]].getY();
			float z = obj.vertices[obj.faces[f].refs[v]].getZ();

			Escalacion(&x, &y, &z, escalaTanque);

			glColor3f(color * 1.0, color * 0.0, color * 0.0); //Color del vertice
			glVertex3f(x, y, z);

			if (i < 3)
			{
				//Creando vector
				vertices.setX(x);
				vertices.setY(y);
				vertices.setZ(z);
				
				vCalc.push_back(vertices);//Se agrega el vector a nuestra lista / vector
				i++;
			}
		}
		Vertex N = normalCara(vCalc);

		vCalc.clear();

		difuse = clamp(dot(N, vLuz), 0, 1);

		color = ambient + difuse;	

		glEnd();
	}
}

void CarasBala(Obj obj)
{
	int f, v;
	vector<Vertex> vCalc; //Vector que almacena vectores para el cálculo de la normal 
	Vertex vertices; //variable que almacena float x y z 
	float color = 1;
	float difuse;

	//C A R A S 
	for (f = 0; f < obj.faces.size(); f++)
	{
		int i = 0;

		if (obj.faces[f].refs.size() == 4)
		{
			glBegin(GL_POLYGON);
		}
		else
		{
			glBegin(GL_TRIANGLES);
		}

		for (v = 0; v < obj.faces[f].refs.size(); v++)
		{
			float x = obj.vertices[obj.faces[f].refs[v]].getX();
			float y = obj.vertices[obj.faces[f].refs[v]].getY();
			float z = obj.vertices[obj.faces[f].refs[v]].getZ();

			Escalacion(&x, &y, &z, escalaBala);

			glColor3f(color * 1.0, color * 0.0, color * 0.0); //Color del vertice

			Movimiento(x, y, z);

			glVertex3f(traslation.getX(), traslation.getY(), traslation.getZ());

			if (i < 3)
			{
				//Creando vector
				vertices.setX(traslation.getX());
				vertices.setY(traslation.getY());
				vertices.setZ(traslation.getZ());
				
				vCalc.push_back(vertices);//Se agrega el vector a nuestra lista / vector
				i++;
			}
			//Rotacion
			if (g >= 360) 
			{
				g = 0;
			}
			g += 0.001;
		}
		Vertex N = normalCara(vCalc);

		vCalc.clear();

		difuse = clamp(dot(N, vLuz), 0, 1);
		color = ambient + difuse;

		glEnd();
	}
}
////////// V E R T I C E S ///////////
void VerticesTanque(Obj obj)
{
	glColor3f(0.0, 0.0, 0.0);//Color de las lineas : negro

	int f, v, cont;

	for (f = 0; f < obj.faces.size(); f++)
	{
		glBegin(GL_LINE_STRIP);//Se dibujarán Líneas
		glLineWidth(2);

		for (v = 0; v < obj.faces[f].refs.size(); v++)
		{
			float x = obj.vertices[obj.faces[f].refs[v]].getX();
			float y = 1.5 + obj.vertices[obj.faces[f].refs[v]].getY();
			float z = obj.vertices[obj.faces[f].refs[v]].getZ();

			Escalacion(&x, &y, &z, escalaTanque);
			
			glVertex3f(x, y, z); //Dibujado del vertice
		}
		glEnd();
	}
}

void VerticesBala(Obj obj)
{
	glColor3f(0.0, 0.0, 0.0);

	int f, v;

	for (f = 0; f < obj.faces.size(); f++)
	{

		glBegin(GL_LINE_STRIP);
		for (v = 0; v < obj.faces[f].refs.size(); v++)
		{
			float x = obj.vertices[obj.faces[f].refs[v]].getX();
			float y = obj.vertices[obj.faces[f].refs[v]].getY();
			float z = obj.vertices[obj.faces[f].refs[v]].getZ();
			//Escalacion
			Escalacion(&x, &y, &z, escalaBala);
			//Agregamos los puntos hacia la matriz de movimiento / traslacion 
			Movimiento(x, y, z);

			glVertex3f(traslation.getX(), traslation.getY(), traslation.getZ());
		}
		glEnd();
	}
}

////////// A X E S /////////////////
void axes()
{
	glBegin(GL_LINES);//Definimos lineas para dibujar
	glLineWidth(2); //Grosor de las lineas
	glColor3f(1, 0, 0);	glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);//Eje X
	glColor3f(0, 1, 0);	glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);//Eje Y
	glColor3f(0, 0, 1);	glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);//Eje Z
	glEnd();//Dibujo finalizado
}
////////// G R I D /////////////////
void grid()
{
	GLfloat lineTam = 3.5;

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glLineWidth(2); //Grosor de las lineas
	for (GLfloat i = -lineTam; i <= lineTam; i += 0.25)
	{
		glVertex3f(i, 0, lineTam); glVertex3f(i, 0, -lineTam);
		glVertex3f(lineTam, 0, i); glVertex3f(-lineTam, 0, i);
	}
	glEnd();
}

////////// T a n q u e  /////////////
void tanque()
{
	//C A R A S 
	CarasTanque(Tanque);

	//V E R T I C E S
	VerticesTanque(Tanque);
}

////////// M a t r i c e s /////////////
void Matrices()
{
	Bezier();
	matrizBezier();
	Rotacion();
	Transformacion();
}

////////// D i s p l a y  /////////////
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	LookAt(eye, camera, up);
	//gluLookAt(eye_x, eye_y, eye_z, camera_x, camera_y, camera_z, up_x, up_y, up_z);

	//Mapa
	grid();
	axes();

	//Proyectil
	VerticesBala(Bala);
	CarasBala(Bala);

	//Tanque
	tanque();

	foco(luzPosition);

	//Matrices : Bezier, Rotacion, Transformacion 
	Matrices();

	glFlush();

	glutSwapBuffers();
}

////////// R e s h a p e  /////////////
void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Perspective(-80, w / h, 0.1f, 40);
}

int main(int argc, char** argv)
{

	//Instancias de Objetos
	Tanque.read();
	Bala.read();

	luzDir.setX(0); luzDir.setY(0); luzDir.setZ(0);//Direccion de la luz
	luzPosition.setX(3); luzPosition.setY(3); luzPosition.setZ(3);//Posicion de la Luz

	normalLuz(luzDir, luzPosition);

	//Programa
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h);

	glutCreateWindow("Avance 3 - Iluminacion");
	glDepthFunc(GL_LESS);

	glutReshapeFunc(reshape);

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutKeyboardFunc(teclado);

	glutMainLoop();
	return 0;
}
