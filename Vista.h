#pragma once
#include <GL/freeglut.h>
#include <Math.h>

namespace std
{
    struct Vec3
    {
        float values[3];

        Vec3()
        {
            values[0] = values[1] = values[2] = 0;
        }

        Vec3(float x, float y, float z)
        {
            values[0] = x;
            values[1] = y;
            values[2] = z;
        }

        // Provide array-like index operators for the components of the vector.
        const float& operator[] (int index) const
        {
            return values[index];
        }
        float& operator[] (int index)
        {
            return values[index];
        }
    };

    struct Vec4
    {
        float values[4];

        Vec4()
        {
            values[0] = values[1] = values[2] = values[3] = 0;
        }

        Vec4(float x, float y, float z, float w)
        {
            values[0] = x;
            values[1] = y;
            values[2] = z;
            values[3] = w;
        }

        // Provide array-like index operators for the components of the vector.
        const float& operator[] (int index) const
        {
            return values[index];
        }
        float& operator[] (int index)
        {
            return values[index];
        }
    };

    struct Mat4
    {
        Vec4 columns[4];

        Mat4()
        {
            columns[0] = Vec4(1, 0, 0, 0);
            columns[1] = Vec4(0, 1, 0, 0);
            columns[2] = Vec4(0, 0, 1, 0);
            columns[3] = Vec4(0, 0, 0, 1);
        }

        Mat4(Vec4 x, Vec4 y, Vec4 z, Vec4 w)
        {
            columns[0] = x;
            columns[1] = y;
            columns[2] = z;
            columns[3] = w;
        }

        // Provide array-like index operators for the columns of the matrix.
        const Vec4& operator[](int index) const
        {
            return columns[index];
        }
        Vec4& operator[](int index)
        {
            return columns[index];
        }
    };

    Vec3 restaVectores(Vec3 vectorA, Vec3 vectorB)
    {
        Vec3 vector;

        vector.values[0] = vectorA.values[0] - vectorB.values[0];
        vector.values[1] = vectorA.values[1] - vectorB.values[1];
        vector.values[2] = vectorA.values[2] - vectorB.values[2];

        return vector;
    }

    Mat4 mulMat(Mat4 matA, Mat4 matB)
    {
        Mat4 mult = {
            Vec4((matA.columns[0].values[0] * matB.columns[0].values[0]) +
                 (matA.columns[0].values[1] * matB.columns[1].values[0]) +
                 (matA.columns[0].values[2] * matB.columns[2].values[0]) +
                 (matA.columns[0].values[3] * matB.columns[3].values[0]) ,

                 (matA.columns[0].values[0] * matB.columns[0].values[1]) +
                 (matA.columns[0].values[1] * matB.columns[1].values[1]) +
                 (matA.columns[0].values[2] * matB.columns[2].values[1]) +
                 (matA.columns[0].values[3] * matB.columns[3].values[1]) ,

                 (matA.columns[0].values[0] * matB.columns[0].values[2]) +
                 (matA.columns[0].values[1] * matB.columns[1].values[2]) +
                 (matA.columns[0].values[2] * matB.columns[2].values[2]) +
                 (matA.columns[0].values[3] * matB.columns[3].values[2]) ,

                 (matA.columns[0].values[0] * matB.columns[0].values[3]) +
                 (matA.columns[0].values[1] * matB.columns[1].values[3]) +
                 (matA.columns[0].values[2] * matB.columns[2].values[3]) +
                 (matA.columns[0].values[3] * matB.columns[3].values[3])
                 ),

            Vec4((matA.columns[1].values[0] * matB.columns[0].values[0]) +
                 (matA.columns[1].values[1] * matB.columns[1].values[0]) +
                 (matA.columns[1].values[2] * matB.columns[2].values[0]) +
                 (matA.columns[1].values[3] * matB.columns[3].values[0]) ,

                 (matA.columns[1].values[0] * matB.columns[0].values[1]) +
                 (matA.columns[1].values[1] * matB.columns[1].values[1]) +
                 (matA.columns[1].values[2] * matB.columns[2].values[1]) +
                 (matA.columns[1].values[3] * matB.columns[3].values[1]) ,

                 (matA.columns[1].values[0] * matB.columns[0].values[2]) +
                 (matA.columns[1].values[1] * matB.columns[1].values[2]) +
                 (matA.columns[1].values[2] * matB.columns[2].values[2]) +
                 (matA.columns[1].values[3] * matB.columns[3].values[2]) ,

                 (matA.columns[1].values[0] * matB.columns[0].values[3]) +
                 (matA.columns[1].values[1] * matB.columns[1].values[3]) +
                 (matA.columns[1].values[2] * matB.columns[2].values[3]) +
                 (matA.columns[1].values[3] * matB.columns[3].values[3])
                 ),

            Vec4((matA.columns[2].values[0] * matB.columns[0].values[0]) +
                 (matA.columns[2].values[1] * matB.columns[1].values[0]) +
                 (matA.columns[2].values[2] * matB.columns[2].values[0]) +
                 (matA.columns[2].values[3] * matB.columns[3].values[0]) ,

                 (matA.columns[2].values[0] * matB.columns[0].values[1]) +
                 (matA.columns[2].values[1] * matB.columns[1].values[1]) +
                 (matA.columns[2].values[2] * matB.columns[2].values[1]) +
                 (matA.columns[2].values[3] * matB.columns[3].values[1]) ,

                 (matA.columns[2].values[0] * matB.columns[0].values[2]) +
                 (matA.columns[2].values[1] * matB.columns[1].values[2]) +
                 (matA.columns[2].values[2] * matB.columns[2].values[2]) +
                 (matA.columns[2].values[3] * matB.columns[3].values[2]) ,

                 (matA.columns[2].values[0] * matB.columns[0].values[3]) +
                 (matA.columns[2].values[1] * matB.columns[1].values[3]) +
                 (matA.columns[2].values[2] * matB.columns[2].values[3]) +
                 (matA.columns[2].values[3] * matB.columns[3].values[3])
                 ),

             Vec4((matA.columns[3].values[0] * matB.columns[0].values[0]) +
                 (matA.columns[3].values[1] * matB.columns[1].values[0]) +
                 (matA.columns[3].values[2] * matB.columns[2].values[0]) +
                 (matA.columns[3].values[3] * matB.columns[3].values[0]) ,

                 (matA.columns[3].values[0] * matB.columns[0].values[1]) +
                 (matA.columns[3].values[1] * matB.columns[1].values[1]) +
                 (matA.columns[3].values[2] * matB.columns[2].values[1]) +
                 (matA.columns[3].values[3] * matB.columns[3].values[1]) ,

                 (matA.columns[3].values[0] * matB.columns[0].values[2]) +
                 (matA.columns[3].values[1] * matB.columns[1].values[2]) +
                 (matA.columns[3].values[2] * matB.columns[2].values[2]) +
                 (matA.columns[3].values[3] * matB.columns[3].values[2]) ,

                 (matA.columns[3].values[0] * matB.columns[0].values[3]) +
                 (matA.columns[3].values[1] * matB.columns[1].values[3]) +
                 (matA.columns[3].values[2] * matB.columns[2].values[3]) +
                 (matA.columns[3].values[3] * matB.columns[3].values[3])
                 )
        };

        return mult;
    }

    Vec3 rotacion(Vec3 vector, float angulo)
    {
        Mat4 matrizRotada;
        Vec3 vectorRotado;

        Mat4 matrizRotacion = {
              Vec4(cos(angulo),      -sin(angulo),      0,   0),
              Vec4(sin(angulo),      cos(angulo),       0,   0),
              Vec4(0,                0,                 1,   0),
              Vec4(0,                0,                 0,   1)
        };

        Mat4 matrizVertice = {
              Vec4(0,      0,      0,   vector.values[0]),
              Vec4(0,      0,      0,   vector.values[1]),
              Vec4(0,      0,      0,   vector.values[2]),
              Vec4(0,      0,      0,                  1)
        };

        matrizRotada = mulMat(matrizRotacion, matrizVertice);

        vectorRotado.values[0] = matrizRotada.columns[0].values[3];
        vectorRotado.values[1] = matrizRotada.columns[1].values[3];
        vectorRotado.values[2] = matrizRotada.columns[2].values[3];

        return vectorRotado;
    }

    Vec3 normal(Vec3 vector)
    {
        Vec3 N; //Vector Normal 

        //Calculo de Normales para x y z
        float Nx = vector.values[0];
        float Ny = vector.values[1];
        float Nz = vector.values[2];

        //Magnitud
        double magnitud = sqrt(pow(Nx, 2) + pow(Ny, 2) + pow(Nz, 2));

        N.values[0] = Nx / magnitud;
        N.values[1] = Ny / magnitud;
        N.values[2] = Nz / magnitud;

        return N;
    }

    Vec3 cross(Vec3 vA, Vec3 vB)
    {
        Vec3 puntoCruz;

        float Vax = vA.values[0]; float Vay = vA.values[1]; float Vaz = vA.values[2];
        float Vbx = vB.values[0]; float Vby = vB.values[1]; float Vbz = vB.values[2];

        puntoCruz.values[0] = (Vay * Vbz) - (Vaz * Vby);
        puntoCruz.values[1] = (Vaz * Vbx) - (Vax * Vbz);
        puntoCruz.values[2] = (Vax * Vby) - (Vay * Vbx);

        return puntoCruz;
    }

    void LookAt(Vec3 eye, Vec3 target, Vec3 up)
    {
        Mat4 matrizLookAt;

        Vec3 eye_target = restaVectores(eye, target);

        Vec3 zaxis = normal(eye_target);    // The "forward" vector.
        Vec3 xaxis = normal(cross(up, zaxis));// The "right" vector.
        Vec3 yaxis = cross(zaxis, xaxis);     // The "up" vector.

        Mat4 orientation = {
           Vec4(xaxis.values[0], yaxis.values[0], zaxis.values[0], 0),
           Vec4(xaxis.values[1], yaxis.values[1], zaxis.values[1], 0),
           Vec4(xaxis.values[2], yaxis.values[2], zaxis.values[2], 0),
           Vec4(0,       0,       0,     1)
        };

        Mat4 translation = {
            Vec4(1,      0,      0,   0),
            Vec4(0,      1,      0,   0),
            Vec4(0,      0,      1,   0),
            Vec4(-eye.values[0], -eye.values[1], -eye.values[2], 1)
        };

        matrizLookAt = mulMat(orientation, translation);

        GLfloat lookAt[16];
        int k = 0;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                lookAt[k] = matrizLookAt.columns[i].values[j];
                k++;
            }
        }
        glMultMatrixf(lookAt);
    }

    void Perspective(float angleOfView, float aspecto, float cerca, float lejos)
    {
        Mat4 matrizPerspectiva;

        float f = 1 / tan(angleOfView / 2);

        matrizPerspectiva.columns[0].values[0] = f / aspecto;
        matrizPerspectiva.columns[1].values[1] = f;
        matrizPerspectiva.columns[2].values[2] = (lejos + cerca) / (cerca - lejos);
        matrizPerspectiva.columns[2].values[3] = -1;
        matrizPerspectiva.columns[3].values[2] = (2 * lejos * cerca) / (cerca - lejos);
        matrizPerspectiva.columns[3].values[3] = 0;

        GLfloat perspectiva[16];
        int k = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                perspectiva[k] = matrizPerspectiva.columns[i].values[j];
                k++;
            }
        }
        glMultMatrixf(perspectiva);
    }
}

