#include <windows.h>

#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Header.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/*-----------------------------------------------------------------------------------
	Funcions para os efectos de sonido proporcionadas por:
	https://www.ambiera.com/irrklang/downloads.html
	e explicadas na paxina web:
	https://learnopengl.com/In-Practice/2D-Game/Audio
*/
#include "../sonido/irrKlang.h"
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

/*-----------------------------------------------------------------------------------
	Estrutura do avatar
*/
cubo baseAvatar = { {0.0f, TAMCUBO, 0.0f}, {0.25f, TAMCUBO, 0.25f}, 2.5f, 0.001f, 0.0f, 0.0f, {1.0f, .2f, .33f} };

/*-----------------------------------------------------------------------------------
	Estrutura da pelota
*/
esfera pelota = { TAMPELOTA, 0.0f, 0.0f, {2.0f, TAMPELOTA, -2.0f}, {0.0f,0.0f,0.0f}, {1.0f, 1.0f, 1.0f} };

/*-----------------------------------------------------------------------------------
	Estrutura da esfera celeste
*/
esfera esferaEstrellas = { TAMCIELO, 0.0f, 0.0f, {0.0f, 0.0f, 0.0f}, {0.0f, 180.0f, -90.0f},  {1.0f, 1.0f, 1.0f} };

/*-----------------------------------------------------------------------------------
	Estruturas das diferentas partes do chan
*/
strutSuelo baseCampo = { -ANCHOSUELO / 2 + baseAvatar.tamanho.x*0.6, ANCHOSUELO / 2 - baseAvatar.tamanho.x*0.6, -LARGOSUELO + 5 + baseAvatar.tamanho.z*0.6,    LARGOSUELO - 35 - baseAvatar.tamanho.z*0.6, 0.5f, {1.0f, 1.0f, 1.0f} };
strutSuelo baseSuelo = { -TAMCIELO * 1.5, TAMCIELO * 1.5, -TAMCIELO * 1.5,   TAMCIELO*1.5 / 4, 0.0f, {1.0f, 1.0f, 1.0f} };
strutSuelo basePared = { -ALTOPARED, ALTOPARED, -ANCHOSUELO, ANCHOSUELO, 0.0f, {1.0f, 1.0f, 1.0f} };

/*-----------------------------------------------------------------------------------
	Estruturas dos focos de luz
*/
elemEstatico baseFoco1 = { {-12.0f, 3.0f, -36.0f},  30.0f, {XZFOCOS, YFOCOS, XZFOCOS}, {1.0f, 1.0f, 1.0f} };
elemEstatico baseFoco2 = { { 12.0f, 3.0f, -36.0f}, -30.0f, {XZFOCOS, YFOCOS, XZFOCOS}, {1.0f, 1.0f, 1.0f} };
elemEstatico baseFoco3 = { {-12.0f, 3.0f,   6.0f}, 150.0f, {XZFOCOS, YFOCOS, XZFOCOS}, {1.0f, 1.0f, 1.0f} };
elemEstatico baseFoco4 = { { 12.0f, 3.0f,   6.0f}, 210.0f, {XZFOCOS, YFOCOS, XZFOCOS}, {1.0f, 1.0f, 1.0f} };
elemEstatico baseFocoCabeza = { { 0.0f, 3.8f, 0.0f},   30.0f, {XCABFOCOS, YCABFOCOS, ZCABFOCOS}, {1.0f, 1.0f, 1.0f} };

/*-----------------------------------------------------------------------------------
	Elementos da porteria
*/
elemEstatico paloIzquierda = { {-XLARGUERO/2, YPALO/2.2, 0.0f},  0.0f, {XZPALO, YPALO, XZPALO}, {1.0f, 1.0f, 1.0f} };
elemEstatico paloDerecha = { {XLARGUERO / 2, YPALO / 2.2, 0.0f},  0.0f, {XZPALO, YPALO, XZPALO}, {1.0f, 1.0f, 1.0f} };
elemEstatico larguero = { {0.0f, YPALO, 0.0f},  0.0f, {XLARGUERO/1.2, YZLARGUERO, YZLARGUERO}, {1.0f, 1.0f, 1.0f} };

/*-----------------------------------------------------------------------------------
	Estructuras de los obstaculos
*/
obstaculo obstaculo1 =	{ {-5.0f, TAMCUBO, -25.0f}, {-5.6f - baseAvatar.tamanho.x*TAMCUBO, 0.0f, -25.6f - baseAvatar.tamanho.z*TAMCUBO},	{-4.4f + baseAvatar.tamanho.x*TAMCUBO, 0.0f, -24.4f + baseAvatar.tamanho.z*TAMCUBO},	0.0f, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} };
obstaculo obstaculo2 =	{ { 0.0f, TAMCUBO, -30.0f},	{-0.6f - baseAvatar.tamanho.x*TAMCUBO, 0.0f, -30.6f - baseAvatar.tamanho.z*TAMCUBO},	{ 0.6f + baseAvatar.tamanho.x*TAMCUBO, 0.0f, -29.4f + baseAvatar.tamanho.z*TAMCUBO},	0.0f, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} };
obstaculo obstaculo3 =	{ { 5.0f, TAMCUBO, -25.0f},	{ 4.4f - baseAvatar.tamanho.x*TAMCUBO, 0.0f, -25.6f - baseAvatar.tamanho.z*TAMCUBO},	{ 5.6f + baseAvatar.tamanho.x*TAMCUBO, 0.0f, -24.4f + baseAvatar.tamanho.z*TAMCUBO},	0.0f, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} };
obstaculo obstaculo4 =	{ {-1.0f, TAMCUBO, -17.0f}, {-1.6f - baseAvatar.tamanho.x*TAMCUBO, 0.0f, -17.6f - baseAvatar.tamanho.z*TAMCUBO},	{-0.4f + baseAvatar.tamanho.x*TAMCUBO, 0.0f, -16.4f + baseAvatar.tamanho.z*TAMCUBO},	0.0f, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} };
obstaculo obstaculo5 =	{ { 2.0f, TAMCUBO, -16.0f},	{ 1.4f - baseAvatar.tamanho.x*TAMCUBO, 0.0f, -16.6f - baseAvatar.tamanho.z*TAMCUBO},	{ 2.6f + baseAvatar.tamanho.x*TAMCUBO, 0.0f, -15.4f + baseAvatar.tamanho.z*TAMCUBO},	0.0f, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} };
obstaculo obstaculo6 =	{ {-5.0f, TAMCUBO,  -7.0f},	{-5.6f - baseAvatar.tamanho.x*TAMCUBO, 0.0f,  -7.6f - baseAvatar.tamanho.z*TAMCUBO},	{-4.4f + baseAvatar.tamanho.x*TAMCUBO, 0.0f,  -6.4f + baseAvatar.tamanho.z*TAMCUBO},	0.0f, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} };
obstaculo obstaculo7 =	{ { 0.0f, TAMCUBO, -10.0f},	{-0.6f - baseAvatar.tamanho.x*TAMCUBO, 0.0f, -10.6f - baseAvatar.tamanho.z*TAMCUBO},	{ 0.6f + baseAvatar.tamanho.x*TAMCUBO, 0.0f,  -9.4f + baseAvatar.tamanho.z*TAMCUBO},	0.0f, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} };
obstaculo obstaculo8 =	{ { 5.0f, TAMCUBO, -12.0f},	{ 4.4f - baseAvatar.tamanho.x*TAMCUBO, 0.0f, -12.6f - baseAvatar.tamanho.z*TAMCUBO},	{ 5.6f + baseAvatar.tamanho.x*TAMCUBO, 0.0f, -11.4f + baseAvatar.tamanho.z*TAMCUBO},	0.0f, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} };
obstaculo obstaculo9 =	{ {-1.0f, TAMCUBO,  -5.0f},	{-1.6f - baseAvatar.tamanho.x*TAMCUBO, 0.0f,  -5.6f - baseAvatar.tamanho.z*TAMCUBO},	{-0.4f + baseAvatar.tamanho.x*TAMCUBO, 0.0f,  -4.4f + baseAvatar.tamanho.z*TAMCUBO},	0.0f, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} };
obstaculo obstaculo10 = { { 5.0f, TAMCUBO,  -8.0f},	{ 4.4f - baseAvatar.tamanho.x*TAMCUBO, 0.0f,  -8.6f - baseAvatar.tamanho.z*TAMCUBO},	{ 5.6f + baseAvatar.tamanho.x*TAMCUBO, 0.0f,  -7.4f + baseAvatar.tamanho.z*TAMCUBO},	0.0f, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} };
obstaculo obstaculos[10] = { obstaculo1, obstaculo2, obstaculo3, obstaculo4, obstaculo5, obstaculo6, obstaculo7, obstaculo8, obstaculo9, obstaculo10 };

/*-----------------------------------------------------------------------------------
	Structuras de las Luces
*/
luz luzCielo1 = { {0.0f, 3.0f, 70.0f, 1.0f},
				{0.0f, 25.0f, -20.0f, 1.0f},
				{0.0f, 0.0f, 0.0f, 0.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				ANGFOCO };

luz luzCielo2 = { {0.0f, 3.0f, -70.0f, 1.0f},
				{0.0f, 25.0f, 20.0f, 1.0f},
				{0.0f, 0.0f, 0.0f, 0.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				ANGFOCO };

luz luzCielo3 = { {70.0f, 3.0f, 0.0f, 1.0f},
				{-20.0f, 25.0f, 0.0f, 1.0f},
				{0.0f, 0.0f, 0.0f, 0.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				ANGFOCO };

luz luzCielo4 = { {-70.0f, 3.0f, 0.0f, 1.0f},
				{20.0f, 25.0f, 0.0f, 1.0f},
				{0.0f, 0.0f, 0.0f, 0.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				ANGFOCO };

luz luzFoco1 = { {baseFoco1.posicion.x, baseFoco1.posicion.y+baseFocoCabeza.posicion.y, baseFoco1.posicion.z, 1.0f},
				{6.0f,-3.0f, 8.0f, 1.0f},
				{0.0f, 0.0f, 0.0f, 0.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				ANGFOCO };

luz luzFoco2 = { {baseFoco2.posicion.x, baseFoco2.posicion.y + baseFocoCabeza.posicion.y, baseFoco2.posicion.z, 1.0f},
				{-6.0f, -3.0f, 8.0f, 1.0f},
				{0.0f, 0.0f, 0.0f, 0.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				ANGFOCO };

luz luzFoco3 = { {baseFoco3.posicion.x, baseFoco3.posicion.y + baseFocoCabeza.posicion.y, baseFoco3.posicion.z, 1.0f},
				{6.0f, -3.0f, -8.0f, 1.0f},
				{0.0f, 0.0f, 0.0f, 0.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				ANGFOCO };

luz luzFoco4 = { {baseFoco4.posicion.x, baseFoco4.posicion.y + baseFocoCabeza.posicion.y, baseFoco4.posicion.z, 1.0f},
				{-6.0f, -3.0f, -8.0f, 1.0f},
				{0.0f, 0.0f, 0.0f, 0.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				ANGFOCO };

/*-----------------------------------------------------------------------------------
	Funciones implementadas

void openGlInit();
void iniciarElementos(),
void inicializarImagenes();
void inicializarLuz();
void myTerceraPersona();
void myAvatar();
void myEstrellas();
void myMapa();
void myFoco(elemEstatico baseFoco, elemEstatico cabezaFoco);
void myObstaculos(obstaculo *obstaculos);
void myPorteria(elemEstatico elemento, float Z);
void myTeclado(unsigned char tras, int x, int y);
void evento(float R, float G, float B);
void funcionCubo(cubo objeto);
void funcionEsfera(esfera objeto);
unsigned int Carga_Texturas(char *nombre, boolean estrella);
int espacioProhibido(float X, float Z, boolean isPelota);
void actualizarLuz();*/

/*-----------------------------------------------------------------------------------
	Texturas usadas
*/
char estrellas[14]	= "caust/ski.jpg";
char cemento[17]	= "caust/cement.jpg";
char madera[15]		= "caust/wood.jpg";
char football[15]	= "caust/bell.jpg";
char pared[16]		= "caust/vric.jpg";
char soccer[19]		= "caust/soccerG.jpg";
char field[16]		= "caust/field.jpg";
char iron[16]		= "caust/iron.jpg";
char head[16]		= "caust/wall.jpeg";

/*-----------------------------------------------------------------------------------
* Variables globales
*/
int ancho, alto, camara = 0;
ISoundEngine *SoundEngine;

/*-----------------------------------------------------------------------------------
	Funcion que actualiza el color de las luces
*/
void actualizarLuz() 
{
	glLightfv(GL_LIGHT4, GL_DIFFUSE, luzFoco1.lambert);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, luzFoco2.lambert);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, luzFoco3.lambert);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, luzFoco4.lambert);
}

/*-----------------------------------------------------------------------------------
	Funcion que controla eventos del juego

*	Victoria = todo verde. Input {0.0f, 1.0f, 0.0f}
*	Derrota = todo rojo. Input {1.0f, 0.0f, 0.0f}
*	Reset = todo blanco. Input {1.0f, 1.0f, 1.0f}
*/
void evento(float R, float G, float B) {
	luzFoco1.lambert[0] = R; luzFoco1.lambert[1] = G; luzFoco1.lambert[2] = B;
	luzFoco2.lambert[0] = R; luzFoco2.lambert[1] = G; luzFoco2.lambert[2] = B;
	luzFoco3.lambert[0] = R; luzFoco3.lambert[1] = G; luzFoco3.lambert[2] = B;
	luzFoco4.lambert[0] = R; luzFoco4.lambert[1] = G; luzFoco4.lambert[2] = B;

	for (int i = 0; i < 10; i++) {
		obstaculos[i].color.x = R; obstaculos[i].color.y = G; obstaculos[i].color.z = B;
	}

	if (R*G*B == 1.0) {
		baseAvatar.posicion.x = 0.0f;
		baseAvatar.posicion.z = 0.0f;
		baseAvatar.velocidad = 0.0f;
		baseAvatar.angulo_giro = 0.0f;

		pelota.posicion.x = 2.0f;
		pelota.posicion.z = -2.0f;
		pelota.velocidad = 0.0f;
		pelota.angulo = 0.0f;
	}

	actualizarLuz();
}

/*-----------------------------------------------------------------------------------
	Funcion de manejo del teclado
*/
void myTeclado(unsigned char tras, int x, int y)
{
	switch (tras) {
		//PARTE DE ABAJO
	case 'w':
		baseAvatar.velocidad -= baseAvatar.aceleracion;
		break;
	case 's':
		baseAvatar.velocidad += baseAvatar.aceleracion;
		break;
	case 'a':
		baseAvatar.angulo_giro += baseAvatar.vel_giro;
		if (baseAvatar.angulo_giro > 360.0f)
			baseAvatar.angulo_giro -= 360.0f;
		break;
	case 'd':
		baseAvatar.angulo_giro -= baseAvatar.vel_giro;
		if (baseAvatar.angulo_giro < -360.0f)
			baseAvatar.angulo_giro += 360.0f;
		break;
	case 'c':
		camara++; if (camara > 1) camara -= 2;
		break;
	case 'r':
		evento(1.0f, 1.0f, 1.0f);
		break;
	case 'n':
		SoundEngine->play2D("caust/ost.mp3", true);
		break;
	case 'm':
		SoundEngine->stopAllSounds();
		break;
	case 27:
		exit(0);
	default:
		break;
	}
	// Se se modificou algo redebúxase
	glutPostRedisplay();
}

/*-----------------------------------------------------------------------------------
	Funcion de la camara
*/
void myTerceraPersona()
{

	/**/
	glMatrixMode(GL_PROJECTION);//Configuración de la matriz de proyeccion
	glLoadIdentity();


	gluPerspective(FOV, ancho / (1.2*alto), .1f, 100.0f);

	gluLookAt(baseAvatar.posicion.x + 5 * sin(baseAvatar.angulo_giro*GradosToRadianes),
		baseAvatar.tamanho.y*3,
		baseAvatar.posicion.z + 5 * cos(baseAvatar.angulo_giro*GradosToRadianes),


		baseAvatar.posicion.x - 5 * sin(baseAvatar.angulo_giro*GradosToRadianes),
		baseAvatar.tamanho.y,
		baseAvatar.posicion.z - 5 * cos(baseAvatar.angulo_giro*GradosToRadianes),

		0, 1, 0);

}

/*-----------------------------------------------------------------------------------
	Funcion de carga de texturas
*/
unsigned int Carga_Texturas(char *nombre) {
	// load and create a texture 
	// -------------------------
	unsigned int textura;
	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(nombre, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	else
	{
		//std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	return textura;

}

/*-----------------------------------------------------------------------------------
	Funciones para la creacion del mapeado
	y elementos del juego
*/
void myFoco(elemEstatico baseFoco, elemEstatico cabezaFoco) {


	glPushMatrix();

	glTranslatef(baseFoco.posicion.x, baseFoco.posicion.y, baseFoco.posicion.z);
	glRotatef(baseFoco.rotY, 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, baseFoco.textura);

	glPushMatrix();
	glScalef(baseFoco.tam.x, baseFoco.tam.y, baseFoco.tam.z);
	glCallList(baseFoco.listarender);
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, cabezaFoco.textura);
	glScalef(cabezaFoco.tam.x, cabezaFoco.tam.y, cabezaFoco.tam.z);
	glTranslatef(cabezaFoco.posicion.x, cabezaFoco.posicion.y, cabezaFoco.posicion.z);
	glRotatef(cabezaFoco.rotY, 1.0f, 0.0f, 0.0f);
	glCallList(cabezaFoco.listarender);
	glPopMatrix();

	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void funcionCubo(cubo objeto) {
	glBindTexture(GL_TEXTURE_2D, objeto.textura);
	glTranslatef(objeto.posicion.x, objeto.posicion.y, objeto.posicion.z);
	glRotatef(objeto.angulo_giro, 0.0f, 1.0f, 0.0f);
	glScalef(objeto.tamanho.x, objeto.tamanho.y * 2, objeto.tamanho.z);
	glColor3f(objeto.color.x, objeto.color.y, objeto.color.z);
	glCallList(objeto.listarender);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void funcionEsfera(esfera objeto) {
	glTranslatef(objeto.posicion.x, objeto.posicion.y, objeto.posicion.z);
	glScalef(objeto.tam, objeto.tam, objeto.tam);
	glColor3f(objeto.color.x, objeto.color.y, objeto.color.z);
	glBindTexture(GL_TEXTURE_2D, objeto.textura);
	glRotatef(objeto.rotacionEjes.x, 1.0f, 0.0f, 0.0f);
	glRotatef(objeto.rotacionEjes.y, 0.0f, 1.0f, 0.0f);
	glRotatef(objeto.rotacionEjes.z, 0.0f, 0.0f, 1.0f);
	glCallList(objeto.listarender);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void myPorteria(elemEstatico elemento, float Z) {
	glColor3f(elemento.color.x, elemento.color.y, elemento.color.z);
	glBindTexture(GL_TEXTURE_2D, elemento.textura);
	glPushMatrix();
	glTranslatef(elemento.posicion.x, elemento.posicion.y, elemento.posicion.z + Z);
	glScalef(elemento.tam.x, elemento.tam.y, elemento.tam.z);
	glCallList(elemento.listarender);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

}

void myObstaculos(obstaculo *obstaculos) {
	
	for (int i = 0; i < 10; i++)
	{
		glPushMatrix();
		glColor3f(obstaculos[i].color.x, obstaculos[i].color.y, obstaculos[i].color.z);
		glBindTexture(GL_TEXTURE_2D, obstaculos[i] .textura);
		glTranslatef(obstaculos[i].posicion.x, obstaculos[i].posicion.y, obstaculos[i].posicion.z);	//1
		glCallList(obstaculos[i].listarender);
		glPopMatrix();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void myAvatar()
{
	glPushMatrix();
	//Base
	funcionCubo(baseAvatar);
	
	glPopMatrix();
}

void myMapa()
{
	/*Campo
	*/
	glColor3f(baseCampo.color.x, baseCampo.color.y, baseCampo.color.z);
	glBindTexture(GL_TEXTURE_2D, baseCampo.textura);
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, -35.0f);
	glCallList(baseCampo.listarender);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	/*Suelo
	*/
	glColor3f(baseSuelo.color.x, baseSuelo.color.y, baseSuelo.color.z);
	glBindTexture(GL_TEXTURE_2D, baseSuelo.textura);
	glPushMatrix();
	glTranslatef(-50.0f, -.1f, -50.0f);
	glCallList(baseSuelo.listarender);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	/*Paredes
	*/
	glColor3f(basePared.color.x, basePared.color.y, basePared.color.z);
	glBindTexture(GL_TEXTURE_2D, basePared.textura);
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, -35.0f);
	glCallList(basePared.listarender);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	/*Focos
	*/
	myFoco(baseFoco1, baseFocoCabeza);
	myFoco(baseFoco2, baseFocoCabeza);
	myFoco(baseFoco3, baseFocoCabeza);
	myFoco(baseFoco4, baseFocoCabeza);

	/*Porterias
	*/
	/*Porteria frente
	*/
	myPorteria(paloIzquierda, -35.0f);
	myPorteria(paloDerecha, -35.0f);
	myPorteria(larguero, -35.0f);

	/*Porteria detras
	*/
	myPorteria(paloIzquierda, 5.0f);
	myPorteria(paloDerecha, 5.0f);
	myPorteria(larguero, 5.0f);

	/*Obstaculos
	*/
	myObstaculos(obstaculos);

}

void myEstrellas() {
	glBindTexture(GL_TEXTURE_2D, esferaEstrellas.textura);

	glPushMatrix();
	glScalef(esferaEstrellas.tam, esferaEstrellas.tam, esferaEstrellas.tam);
	glRotatef(esferaEstrellas.rotacionEjes.z, 0.0f, 0.0f, 1.0f);
	glCallList(esferaEstrellas.listarender);
	glPopMatrix();

}

/*-----------------------------------------------------------------------------------
	Funciones de calculo del movimiento
	Y de zonas de obstaculos
*/
int espacioProhibido(float X, float Z, boolean isPelota) {
	//Obstaculos
	for (int i = 0; i < 10; i++)
	{
		if ((obstaculos[i].limNeg.x < X && X < obstaculos[i].limPos.x) &&
			(obstaculos[i].limNeg.z < Z && Z < obstaculos[i].limPos.z)
			) 
		{
			obstaculos[i].color.x = rand() % 2;
			obstaculos[i].color.y = rand() % 2;
			obstaculos[i].color.z = rand() % 2;
			return 1;
		}

	}

	//Paredes
	if ((X > baseCampo.X_pos || X < baseCampo.X_neg)|| (Z > baseCampo.Z_pos || Z < baseCampo.Z_neg))
	{
		return 1;
	}

	//Pelota
	if (!isPelota && pelota.posicion.x-pelota.tam*1.5 < X && X < pelota.posicion.x + pelota.tam*1.5 && pelota.posicion.z - pelota.tam*1.5 < Z && Z < pelota.posicion.z + pelota.tam*1.5)
	{
		return 2;
	}

	//Victoria
	if (-2.8 < X && X < 2.8 && Z < -32.5)
	{
		return 3;
	}

	//Derrota
	if (-2.8 < X && X < 2.8 && Z > 2.5)
	{
		return 4;
	}

	return 0;
}

void movimiento()
{
	//Movimiento del Avatar
	switch (espacioProhibido(	baseAvatar.posicion.x + baseAvatar.velocidad*sin(baseAvatar.angulo_giro*GradosToRadianes),
								baseAvatar.posicion.z + baseAvatar.velocidad*cos(baseAvatar.angulo_giro*GradosToRadianes),
								false))
		{
		//Nada en el medio
		case 0:
		case 3:
		case 4: {
			baseAvatar.posicion.x += baseAvatar.velocidad*sin(baseAvatar.angulo_giro*GradosToRadianes);
			baseAvatar.posicion.z += baseAvatar.velocidad*cos(baseAvatar.angulo_giro*GradosToRadianes);

			if (baseAvatar.velocidad > 2.0f)
			{	
				baseAvatar.velocidad -= ROCERAP ;
			}
			else if (baseAvatar.velocidad < -2.0f)
			{
				baseAvatar.velocidad += ROCERAP;
			}
			else if (baseAvatar.velocidad > 0)
			{
				baseAvatar.velocidad -= ROCELEN;
			}
			else if (baseAvatar.velocidad < 0)
			{
				baseAvatar.velocidad += ROCELEN;
			}
			break;
		}
		//Pared u obstaculo
		case 1: {
			baseAvatar.velocidad = 0;
			break;
		}
		//Chocar pelota
		case 2: {
			pelota.angulo = baseAvatar.angulo_giro;
			pelota.velocidad += baseAvatar.velocidad;

			baseAvatar.velocidad *= 0.5f;
			break;
		}
		default:
			break;
	}

	//Movimiento de la pelota
	switch (espacioProhibido(	pelota.posicion.x + pelota.velocidad*sin(pelota.angulo*GradosToRadianes),
								pelota.posicion.z + pelota.velocidad*cos(pelota.angulo*GradosToRadianes),
								true))
	{
		//Nada en el medio
		case 0: 
		case 2:{
			pelota.posicion.x += pelota.velocidad*sin(pelota.angulo*GradosToRadianes);
			pelota.posicion.z += pelota.velocidad*cos(pelota.angulo*GradosToRadianes);

			if (pelota.velocidad > ROCELEN)
			{
				pelota.velocidad -= ROCELEN;
				pelota.rotacionEjes.x += 5 * sin(pelota.angulo*GradosToRadianes);
			}
			else if (pelota.velocidad < -ROCELEN)
			{
				pelota.velocidad += ROCELEN;
				pelota.rotacionEjes.x -= 5 * cos(pelota.angulo*GradosToRadianes);
			}
			else
			{
				pelota.velocidad = 0;
			}

			break;
		}
		//Pared u obstaculo
		case 1: {
			pelota.angulo *= -1;
			pelota.velocidad *= 0.75f;
			pelota.rotacionEjes.y = pelota.angulo;
			SoundEngine->play2D("caust/hit.mp3", false);
			break;
		}
		//Victoria 
		case 3: {
			pelota.velocidad = 0;
			evento(0.0f, 1.0f, 0.0f);
			SoundEngine->play2D("caust/win.mp3", false);
			break;
		}
		//Derrota
		case 4: {
			pelota.velocidad = 0;
			evento(1.0f, 0.0f, 0.0f);
			SoundEngine->play2D("caust/loose.mp3", false);
			break;
		}
	}

}

// Función de display
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Movimiento
	movimiento();

	//Camara
	myTerceraPersona();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//CIELO
	glFrontFace(GL_CW);
	myEstrellas();
	glFrontFace(GL_CCW);

	//Mapa
	myMapa();

	//Grua
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	myAvatar();

	//Pelota
	funcionEsfera(pelota);

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void openGlInit()
{
	glClearDepth(1.0f); //Valor z-buffer
	glEnable(GL_DEPTH_TEST); // z-buffer
	glEnable(GL_CULL_FACE); //ocultacion caras back
	glutInitDisplayMode(GLUT_DEPTH);
	glEnable(GL_NORMALIZE);

	//Luces
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);	//Luz cielo1
	glEnable(GL_LIGHT1);	//Luz cielo2
	glEnable(GL_LIGHT2);	//Luz cielo3
	glEnable(GL_LIGHT3);	//Luz cielo4
	glEnable(GL_LIGHT4);	//Luz foco 1
	glEnable(GL_LIGHT5);	//Luz foco 2
	glEnable(GL_LIGHT6);	//Luz foco 3
	glEnable(GL_LIGHT7);	//Luz foco 4
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	//Texturas
	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);

	//Limpiar
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
}

void inicializarLuz() {
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzCielo1.ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzCielo1.lambert);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzCielo1.phong);
	glLightfv(GL_LIGHT0, GL_POSITION, luzCielo1.posicion);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, luzCielo1.direccion);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, luzCielo1.apertura);

	glLightfv(GL_LIGHT1, GL_AMBIENT, luzCielo2.ambiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzCielo2.lambert);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzCielo2.phong);
	glLightfv(GL_LIGHT1, GL_POSITION, luzCielo2.posicion);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, luzCielo2.direccion);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, luzCielo2.apertura);

	glLightfv(GL_LIGHT2, GL_AMBIENT, luzCielo3.ambiente);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, luzCielo3.lambert);
	glLightfv(GL_LIGHT2, GL_SPECULAR, luzCielo3.phong);
	glLightfv(GL_LIGHT2, GL_POSITION, luzCielo3.posicion);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, luzCielo3.direccion);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, luzCielo3.apertura);

	glLightfv(GL_LIGHT3, GL_AMBIENT, luzCielo4.ambiente);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, luzCielo4.lambert);
	glLightfv(GL_LIGHT3, GL_SPECULAR, luzCielo4.phong);
	glLightfv(GL_LIGHT3, GL_POSITION, luzCielo4.posicion);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, luzCielo4.direccion);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, luzCielo4.apertura);

	glLightfv(GL_LIGHT4, GL_AMBIENT, luzFoco1.ambiente);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, luzFoco1.lambert);
	glLightfv(GL_LIGHT4, GL_SPECULAR, luzFoco1.phong);
	glLightfv(GL_LIGHT4, GL_POSITION, luzFoco1.posicion);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, luzFoco1.direccion);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, luzFoco1.apertura);

	glLightfv(GL_LIGHT5, GL_AMBIENT, luzFoco2.ambiente);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, luzFoco2.lambert);
	glLightfv(GL_LIGHT5, GL_SPECULAR, luzFoco2.phong);
	glLightfv(GL_LIGHT5, GL_POSITION, luzFoco2.posicion);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, luzFoco2.direccion);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, luzFoco2.apertura);

	glLightfv(GL_LIGHT6, GL_AMBIENT, luzFoco3.ambiente);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, luzFoco3.lambert);
	glLightfv(GL_LIGHT6, GL_SPECULAR, luzFoco3.phong);
	glLightfv(GL_LIGHT6, GL_POSITION, luzFoco3.posicion);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, luzFoco3.direccion);
	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, luzFoco3.apertura);

	glLightfv(GL_LIGHT7, GL_AMBIENT, luzFoco4.ambiente);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, luzFoco4.lambert);
	glLightfv(GL_LIGHT7, GL_SPECULAR, luzFoco4.phong);
	glLightfv(GL_LIGHT7, GL_POSITION, luzFoco4.posicion);
	glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, luzFoco4.direccion);
	glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, luzFoco4.apertura);
}

void inicializarImagenes() {
	//Cielo
	esferaEstrellas.textura = Carga_Texturas(estrellas);

	//Avatar
	baseAvatar.textura = Carga_Texturas(cemento);

	//Pelota
	pelota.textura = Carga_Texturas(football);

	//Campo futbol
	baseCampo.textura = Carga_Texturas(soccer);

	//Suelo
	baseSuelo.textura = Carga_Texturas(field);

	//Paredes Campo
	basePared.textura = Carga_Texturas(pared);

	//Focos
	baseFoco1.textura = Carga_Texturas(iron);
	baseFoco2.textura = Carga_Texturas(iron);
	baseFoco3.textura = Carga_Texturas(iron);
	baseFoco4.textura = Carga_Texturas(iron);
	baseFocoCabeza.textura = Carga_Texturas(head);

	//Porteria
	paloIzquierda.textura = Carga_Texturas(madera);
	paloDerecha.textura = Carga_Texturas(madera);
	larguero.textura = Carga_Texturas(madera);

	//Obstaculos
	for (int i = 0; i < 10; i++) {
		obstaculos[i].textura = Carga_Texturas(cemento);
	}
}

void iniciarElementos()
{
	ancho = W_WIDTH; alto = W_HEIGHT;
	srand(10);

	//Avatar
	baseAvatar.listarender = myCubos();

	//Cielo
	esferaEstrellas.listarender = myEsfera();

	//Pelota
	pelota.listarender = myEsfera();

	//Suelo
	baseSuelo.listarender = mySueloMC();

	//Campo Futbol
	baseCampo.listarender = mySuelo();

	//Paredes Campo
	basePared.listarender = myParedes();

	//Focos
	baseFoco1.listarender = myCubos();
	baseFoco2.listarender = myCubos();
	baseFoco3.listarender = myCubos();
	baseFoco4.listarender = myCubos();
	baseFocoCabeza.listarender = myCubos();

	//Porterias
	paloIzquierda.listarender = myCubos();
	paloDerecha.listarender = myCubos();
	larguero.listarender = myCubos();

	//Obstaculos
	for (int i = 0; i < 10; i++)
		obstaculos[i].listarender = myCubos();

	//Cargar texturas
	inicializarImagenes();

	//Cargar luces
	inicializarLuz();
}

void Resize(int w, int h)
{
	//Actualizamos los valores
	ancho = w; alto = h;

	// Ajusta la vista a las dimensiones de la ventana
	glViewport(0, 0, w, h);

	// Reinicia el sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	Display();
}

int main(int argc, char **argv)
{
	SoundEngine = createIrrKlangDevice();

	SoundEngine->play2D("caust/intro.mp3", false);

	glutInit(&argc, argv);
	//Posicion de la ventana
	glutInitWindowPosition(100, 100);
	//Tamano de la ventana
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	//Tipo de color y buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//Crear la ventana
	glutCreateWindow("Proyecto");

	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(myTeclado);

	openGlInit();

	iniciarElementos();

	//Lazo principal
	glutMainLoop();

	SoundEngine->drop();

	return 0;


}