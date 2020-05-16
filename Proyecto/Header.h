#pragma once

#define W_WIDTH 1000
#define W_HEIGHT 1000
#define TAMCUBO 0.6f
#define INCREMENTO .01
#define DISTANCIA 10
#define PI 3.1416
#define FOV 45.0f
#define GradosToRadianes 0.017453f
#define ANGFOCO 30
#define FRAMESUELO 15
#define TAMCHARCO 1.5f
#define ANCHOSUELO 20.0f
#define LARGOSUELO 40.0f
#define ALTOPARED .9f
#define LARGOPARED 40.0f
#define TAMPELOTA 0.5f
#define TAMCIELO 50.0f

//Puntos
typedef struct {
	float x;
	float y;
	float z;
} punto;

//Vectores
typedef struct {
	float x;
	float y;
	float z;
} vector;

//Objetos esfericos
typedef struct {
	float X;
	float Z;
	float translate;
	float tamanho;
	float vel_giro;
	punto color;
	int listarender;
	unsigned int textura;
} esfera;

//Cubos
typedef struct {
	float X;
	float Z;
	float tamanho;
	float vel_giro;
	float aceleracion;
	float angulo_giro;
	float velocidad;
	punto color;
	int listarender;
	unsigned int textura;
} cubo;

//Palo
typedef struct {
	float ancho;
	float alto;
	float rotacion;
	punto color;
	int listarender;
	unsigned int texture;
} staff;

//Suelo
typedef struct {
	float X_neg;
	float X_pos;
	float Z_neg;
	float Z_pos;
	float intervalo;
	punto color;
	int listarender;
	unsigned int textura;
	unsigned int imagenes[15];
} strutSuelo;

void myCamara();

void myTeclado(unsigned char trans, int x, int y);
void myTeclasespeciales(int cursor, int x, int y);
void myEjes();

int myEsfera();
int myCubos();
int mySuelo();
int myCharco();
int myParedes();
int mySueloMC();