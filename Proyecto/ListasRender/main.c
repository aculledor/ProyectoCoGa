/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: acull
 *
 * Created on 14 de mayo de 2020, 20:40
 */

#include <stdio.h>
#include <stdlib.h>

void crearParedes() {
    int X = 20, Z = 40, c = 1, cc = 1;
    float y, x, z, intX = 0.5, intZ = 0.5, intY = 0.3, Y = 0.9;

    FILE *datos = fopen("datosPared.txt", "w");

    for (y = 0; y < Y; y += intY) {
        for (x = -intX; x < X + intX; x += intX) {
            //Pared forntal, frente
            fprintf(datos, "//Pared frente Poligono %d\n", c);
            fprintf(datos, "glNormal3f(0.0f, 0.0f, 1.0f);\n"); //1
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 0.0f);\n\n", x + intX, y + intY);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, 1.0f);\n"); //2
            fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 0.0f);\n\n", x, y + intY);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, 1.0f);\n"); //3
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 0.0f);\n\n", x, y);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, 1.0f);\n"); //4
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 0.0f);\n\n", x, y);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, 1.0f);\n"); //5
            fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 0.0f);\n\n", x + intX, y);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, 1.0f);\n"); //6
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 0.0f);\n\n", x + intX, y + intY);
            
            //Pared forntal parte de atras
            fprintf(datos, "//Pared trasera Poligono %d\n", c);
            fprintf(datos, "glNormal3f(0.0f, 0.0f, -1.0f);\n"); //6
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, -0.5f);\n\n", x + intX, y + intY);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, -1.0f);\n"); //5
            fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, -0.5f);\n\n", x + intX, y);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, -1.0f);\n"); //4
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, -0.5f);\n\n", x, y);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, -1.0f);\n"); //3
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, -0.5f);\n\n", x, y);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, -1.0f);\n"); //2
            fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, -0.5f);\n\n", x, y + intY);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, -1.0f);\n"); //1
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, -0.5f);\n\n", x + intX, y + intY);

            //Pared Trasera parte de delante
            fprintf(datos, "//Pared trasera Poligono %d\n", c);
            fprintf(datos, "glNormal3f(0.0f, 0.0f, -1.0f);\n"); //6
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 40.0f);\n\n", x + intX, y + intY);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, -1.0f);\n"); //5
            fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 40.0f);\n\n", x + intX, y);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, -1.0f);\n"); //4
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 40.0f);\n\n", x, y);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, -1.0f);\n"); //3
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 40.0f);\n\n", x, y);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, -1.0f);\n"); //2
            fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 40.0f);\n\n", x, y + intY);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, -1.0f);\n"); //1
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 40.0f);\n\n", x + intX, y + intY);
            
            //Pared trasera parte de atras
            fprintf(datos, "//Pared frente Poligono %d\n", c);
            fprintf(datos, "glNormal3f(0.0f, 0.0f, 1.0f);\n"); //1
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 40.5f);\n\n", x + intX, y + intY);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, 1.0f);\n"); //2
            fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 40.5f);\n\n", x, y + intY);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, 1.0f);\n"); //3
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 40.5f);\n\n", x, y);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, 1.0f);\n"); //4
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 40.5f);\n\n", x, y);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, 1.0f);\n"); //5
            fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 40.5f);\n\n", x + intX, y);

            fprintf(datos, "glNormal3f(0.0f, 0.0f, 1.0f);\n"); //6
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, %.2ff, 40.5f);\n\n", x + intX, y + intY);


            c++;
        }
        for (z = -intZ; z < Z + intZ; z += intZ) {
            //Pared derecha parte delantera
            fprintf(datos, "//Pared derecha Poligono %d\n", cc);
            fprintf(datos, "glNormal3f(-1.0f, 0.0f, 0.0f);\n"); //1
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(20.0f, %.2ff, %.2ff);\n\n", y + intY, z + intZ);

            fprintf(datos, "glNormal3f(-1.0f, 0.0f, 0.0f);\n"); //2
            fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(20.0f, %.2ff, %.2ff);\n\n", y + intY, z);

            fprintf(datos, "glNormal3f(-1.0f, 0.0f, 0.0f);\n"); //3
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(20.0f, %.2ff, %.2ff);\n\n", y, z);

            fprintf(datos, "glNormal3f(-1.0f, 0.0f, 0.0f);\n"); //4
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(20.0f, %.2ff, %.2ff);\n\n", y, z);

            fprintf(datos, "glNormal3f(-1.0f, 0.0f, 0.0f);\n"); //5
            fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(20.0f, %.2ff, %.2ff);\n\n", y, z + intZ);

            fprintf(datos, "glNormal3f(-1.0f, 0.0f, 0.0f);\n"); //6
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(20.0f, %.2ff, %.2ff);\n\n", y + intY, z + intZ);
            
            //Pared derecha parte trasera
            fprintf(datos, "//Pared iquierda Poligono %d\n", cc);
            fprintf(datos, "glNormal3f(1.0f, 0.0f, 0.0f);\n"); //6
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(20.5f, %.2ff, %.2ff);\n\n", y + intY, z + intZ);

            fprintf(datos, "glNormal3f(1.0f, 0.0f, 0.0f);\n"); //5
            fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(20.5f, %.2ff, %.2ff);\n\n", y, z + intZ);

            fprintf(datos, "glNormal3f(1.0f, 0.0f, 0.0f);\n"); //4
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(20.5f, %.2ff, %.2ff);\n\n", y, z);

            fprintf(datos, "glNormal3f(1.0f, 0.0f, 0.0f);\n"); //3
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(20.5f, %.2ff, %.2ff);\n\n", y, z);

            fprintf(datos, "glNormal3f(1.0f, 0.0f, 0.0f);\n"); //2
            fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(20.5f, %.2ff, %.2ff);\n\n", y + intY, z);

            fprintf(datos, "glNormal3f(1.0f, 0.0f, 0.0f);\n"); //1
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(20.5f, %.2ff, %.2ff);\n\n", y + intY, z + intZ);

            //Pared izquierda parte delantera
            fprintf(datos, "//Pared iquierda Poligono %d\n", cc);
            fprintf(datos, "glNormal3f(1.0f, 0.0f, 0.0f);\n"); //6
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(0.0f, %.2ff, %.2ff);\n\n", y + intY, z + intZ);

            fprintf(datos, "glNormal3f(1.0f, 0.0f, 0.0f);\n"); //5
            fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(0.0f, %.2ff, %.2ff);\n\n", y, z + intZ);

            fprintf(datos, "glNormal3f(1.0f, 0.0f, 0.0f);\n"); //4
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(0.0f, %.2ff, %.2ff);\n\n", y, z);

            fprintf(datos, "glNormal3f(1.0f, 0.0f, 0.0f);\n"); //3
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(0.0f, %.2ff, %.2ff);\n\n", y, z);

            fprintf(datos, "glNormal3f(1.0f, 0.0f, 0.0f);\n"); //2
            fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(0.0f, %.2ff, %.2ff);\n\n", y + intY, z);

            fprintf(datos, "glNormal3f(1.0f, 0.0f, 0.0f);\n"); //1
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(0.0f, %.2ff, %.2ff);\n\n", y + intY, z + intZ);
            
            //Pared izquierda parte trasera
            fprintf(datos, "//Pared derecha Poligono %d\n", cc);
            fprintf(datos, "glNormal3f(-1.0f, 0.0f, 0.0f);\n"); //1
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(-0.5f, %.2ff, %.2ff);\n\n", y + intY, z + intZ);

            fprintf(datos, "glNormal3f(-1.0f, 0.0f, 0.0f);\n"); //2
            fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(-0.5f, %.2ff, %.2ff);\n\n", y + intY, z);

            fprintf(datos, "glNormal3f(-1.0f, 0.0f, 0.0f);\n"); //3
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(-0.5f, %.2ff, %.2ff);\n\n", y, z);

            fprintf(datos, "glNormal3f(-1.0f, 0.0f, 0.0f);\n"); //4
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(-0.5f, %.2ff, %.2ff);\n\n", y, z);

            fprintf(datos, "glNormal3f(-1.0f, 0.0f, 0.0f);\n"); //5
            fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(-0.5f, %.2ff, %.2ff);\n\n", y, z + intZ);

            fprintf(datos, "glNormal3f(-1.0f, 0.0f, 0.0f);\n"); //6
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(-0.5f, %.2ff, %.2ff);\n\n", y + intY, z + intZ);

            cc++;
        }
    }

    c = 0;

    for (x = -intX; x < X + intX; x += intX) {
        fprintf(datos, "//Borde delante Poligono #%d\n", c);
        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //1
        fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
        fprintf(datos, "glVertex3f(%.2ff, 0.9f, 0.0f);\n\n", x);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //2
        fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
        fprintf(datos, "glVertex3f(%.2ff, 0.9f, -0.5f);\n\n", x + intX);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //3
        fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
        fprintf(datos, "glVertex3f(%.2ff, 0.9f, -0.5f);\n\n", x);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //4
        fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
        fprintf(datos, "glVertex3f(%.2ff, 0.9f, 0.0f);\n\n", x);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //5
        fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
        fprintf(datos, "glVertex3f(%.2ff, 0.9f, 0.0f);\n\n", x + intX);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //6
        fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
        fprintf(datos, "glVertex3f(%.2ff, 0.9f, -0.5f);\n\n", x + intX);

        fprintf(datos, "//Borde detras Poligono #%d\n", c);
        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //1
        fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
        fprintf(datos, "glVertex3f(%.2ff, 0.9f, 40.5f);\n\n", x);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //2
        fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
        fprintf(datos, "glVertex3f(%.2ff, 0.9f, 40.0f);\n\n", x + intX);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //3
        fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
        fprintf(datos, "glVertex3f(%.2ff, 0.9f, 40.0f);\n\n", x);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //4
        fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
        fprintf(datos, "glVertex3f(%.2ff, 0.9f, 40.5f);\n\n", x);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //5
        fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
        fprintf(datos, "glVertex3f(%.2ff, 0.9f, 40.5f);\n\n", x + intX);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //6
        fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
        fprintf(datos, "glVertex3f(%.2ff, 0.9f, 40.0f);\n\n", x + intX);

        c++;
    }

    c = 0;

    for (z = -intZ; z < Z + intZ; z += intZ) {
        fprintf(datos, "//Borde pared izquierda Poligono #%d\n", c);
        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //1
        fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
        fprintf(datos, "glVertex3f(-0.5f, 0.9f, %.2ff);\n\n", z + intZ);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //2
        fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
        fprintf(datos, "glVertex3f(0.0f, 0.9f, %.2ff);\n\n", z);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //3
        fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
        fprintf(datos, "glVertex3f(-0.5f, 0.9f, %.2ff);\n\n", z);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //4
        fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
        fprintf(datos, "glVertex3f(-0.5f, 0.9f, %.2ff);\n\n", z + intZ);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //5
        fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
        fprintf(datos, "glVertex3f(0.0f, 0.9f, %.2ff);\n\n", z + intZ);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //6
        fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
        fprintf(datos, "glVertex3f(0.0f, 0.9f, %.2ff);\n\n", z);


        fprintf(datos, "//Borde pared derecha Poligono #%d\n", c);
        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //1
        fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
        fprintf(datos, "glVertex3f(20.0f, 0.9f, %.2ff);\n\n", z + intZ);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //2
        fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
        fprintf(datos, "glVertex3f(20.5f, 0.9f, %.2ff);\n\n", z);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //3
        fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
        fprintf(datos, "glVertex3f(20.0f, 0.9f, %.2ff);\n\n", z);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //4
        fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
        fprintf(datos, "glVertex3f(20.0f, 0.9f, %.2ff);\n\n", z + intZ);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //5
        fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
        fprintf(datos, "glVertex3f(20.5f, 0.9f, %.2ff);\n\n", z + intZ);

        fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //6
        fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
        fprintf(datos, "glVertex3f(20.5f, 0.9f, %.2ff);\n\n", z);


        c++;
    }
}

void crearSuelo() {
    int X = 100, Z = 100, c = 1;
    float x, z, intX = 1, intZ = 1;

    FILE *datos = fopen("datosChan.txt", "w");

    for (z = 0; z < Z; z += intZ) {
        for (x = 0; x < X; x += intX) {
            fprintf(datos, "//Poligono #%d\n", c);
            fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //1
            fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, 0.0f, %.2ff);\n\n", x, z + intZ);

            fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //2
            fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, 0.0f, %.2ff);\n\n", x + intX, z);

            fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //3
            fprintf(datos, "glTexCoord2f(0.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, 0.0f, %.2ff);\n\n", x, z);

            fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //4
            fprintf(datos, "glTexCoord2f(0.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, 0.0f, %.2ff);\n\n", x, z + intZ);

            fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //5
            fprintf(datos, "glTexCoord2f(1.0f, 1.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, 0.0f, %.2ff);\n\n", x + intX, z + intZ);

            fprintf(datos, "glNormal3f(0.0f, 1.0f, 0.0f);\n"); //6
            fprintf(datos, "glTexCoord2f(1.0f, 0.0f);\n");
            fprintf(datos, "glVertex3f(%.2ff, 0.0f, %.2ff);\n\n", x + intX, z);

            c++;
        }
    }
}

int main(int argc, char** argv) {

    crearParedes();

    //crearSuelo();

    return (EXIT_SUCCESS);
}