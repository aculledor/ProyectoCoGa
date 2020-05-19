#pragma once
 
/*Tamañonho de ventana
 */
#define W_WIDTH 1000
#define W_HEIGHT 1000

/*Variables globales
*/
#define INCREMENTO .01
#define PI 3.1416
#define GradosToRadianes 0.017453f

/*Variables de la camara
*/
#define FOV 45.0f

/*Variables de las luces
*/
#define ANGFOCO 45.0f

/*Pared
*/
#define ALTOPARED .9f
#define LARGOPARED 40.0f

/*Cielo
*/
#define TAMCIELO 50.0f

/*Suelo
*/
#define ANCHOSUELO 20.0f
#define LARGOSUELO 40.0f

/*Focos
*/
#define XZFOCOS .5f
#define YFOCOS 5.0f

#define XCABFOCOS 1.5f
#define YCABFOCOS 1.0f
#define ZCABFOCOS .1f

/*Tamanho estructura cubo
*/
#define TAMCUBO 0.6f

/*Porteria
*/
#define XZPALO 0.25f
#define YPALO 2.5f

#define YZLARGUERO 0.25f
#define XLARGUERO 5.6f

/*Pelota
*/
#define TAMPELOTA 0.25f
#define ROCERAP 0.00005f
#define ROCELEN 0.000025f

//Puntos
typedef struct {
	float x;
	float y;
	float z;
} punto;

//Pelota movil
typedef struct {
	float tam;
	float velocidad;
	float angulo;
	punto posicion;
	punto rotacionEjes;
	punto color;
	int listarender;
	unsigned int textura;
} esfera;

//Cubos
typedef struct {
	punto posicion;
	punto tamanho;
	float vel_giro;
	float aceleracion;
	float angulo_giro;
	float velocidad;
	punto color;
	int listarender;
	unsigned int textura;
} cubo;

//Cubo estatico
typedef struct {
	punto posicion;
	float rotY;
	punto tam;
	punto color;
	int listarender;
	unsigned int textura;
} elemEstatico;

//Obstaculo
typedef struct {
	punto posicion;
	punto limNeg;	//Limite hacia el positivo de los ejes
	punto limPos;	//Limite hacia el positivo de los ejes
	float rotY;
	punto tam;
	punto color;
	int listarender;
	unsigned int textura;
} obstaculo;

//Luces
typedef struct {
	GLfloat posicion[4];
	GLfloat direccion[4];
	GLfloat ambiente[4];
	GLfloat lambert[4];
	GLfloat phong[4];
	float	apertura;
} luz;


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
} strutSuelo;

/*-----------------------------------------------------------------------------------
	Funciones implementadas en Source.cpp
*/
int myEsfera();
int myCubos();
int mySuelo();
int myParedes();
int mySueloMC();