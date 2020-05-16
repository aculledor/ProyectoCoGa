#include <windows.h>

#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "Header.h"

// Es necesario para que el stb_image funcione
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/*
* Funciones externas
*/


/*
* Estructuras usadas
*/
cubo baseCubo = { 0, 0, TAMCUBO, 1.5f, 0.001f, 0.0f, 0.0f, {1.0f, .2f, .33f} };
staff paloGrande = { 0.25f , 3.0f, 0.0f, {1.0f, 1.0f, 1.0f} };
esfera esferaGrande = { 0, 0,  TAMCUBO,  0.4f, 0.6f, {1.0f, 1.0f, 1.0f} };
esfera esferaPequenha = { 0, 0, 3.0f, 0.5f, 0.8f, {1.0f, 1.0f, 1.0f} };
staff paloPequenho = { 0.1f, 2.0f, 90.0f, {1.0f, 1.0f, 1.0f} };


/*Pelota
*/
esfera pelota = { 3, 3,  TAMPELOTA,  TAMPELOTA, 0.0f, {1.0f, 1.0f, 1.0f} };

/*Cielo
*/
esfera esferaEstrellas = { 0, 0,  0,  TAMCIELO, 0.0f, {1.0f, 1.0f, 1.0f} };

/*Paredes
*/


/*Suelo
*/
strutSuelo baseCampo = { -ANCHOSUELO, ANCHOSUELO, -LARGOSUELO, LARGOSUELO / 4, 0.5f, {1.0f, 1.0f, 1.0f} };
strutSuelo baseSuelo = { -TAMCIELO*1.5, TAMCIELO*1.5, -TAMCIELO * 1.5, TAMCIELO*1.5 / 4, 0.0f, {1.0f, 1.0f, 1.0f} };
strutSuelo basePared = { -ALTOPARED, ALTOPARED, -ANCHOSUELO, ANCHOSUELO, 0.0f, {1.0f, 1.0f, 1.0f} };

/*
*	Charco
*/
int listaRenderCharco = 0;
int agua = 0;
char foto[FRAMESUELO][18] = { "caust/caust00.png","caust/caust01.png","caust/caust02.png","caust/caust03.png","caust/caust04.png","caust/caust05.png","caust/caust06.png",
"caust/caust07.png","caust/caust08.png","caust/caust09.png","caust/caust10.png","caust/caust12.png","caust/caust13.png","caust/caust14.png","caust/caust15.png" };

char estrellas[14] = "caust/sku.jpg";
char hierba[16] = "caust/grass.jpg";
char ejes[15] = "caust/gear.jpg";
char cemento[17] = "caust/cement.jpg";
char madera[15] = "caust/wood.jpg";
char football[15] = "caust/bell.jpg";
char chan[15] = "caust/chan.png";
char pared[16] = "caust/vric.jpg";
char soccer[19] = "caust/soccerG.jpg";
char field[16] = "caust/field.png";

/*
* Variables globales
*/
int ancho, alto, camara = 0;
float alpha = 0, beta = 0.8f;

GLfloat posicionFoco[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat direccionFoco[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat luz_lambert[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
//GLfloat luz_ambiente[4] = { .3f, .3f, .3f, .2f };


void myTeclado(unsigned char tras, int x, int y)
{
	switch (tras) {
		//PARTE DE ABAJO
	case 'w':
		baseCubo.velocidad -= baseCubo.aceleracion;
		break;
	case 's':
		baseCubo.velocidad += baseCubo.aceleracion;
		break;
	case 'a':
		baseCubo.angulo_giro += baseCubo.vel_giro;
		break;
	case 'd':
		baseCubo.angulo_giro -= baseCubo.vel_giro;
		break;
		//PARTE DE ABAJO
	case 't':
		esferaGrande.X -= esferaGrande.vel_giro;
		break;
	case 'g':
		esferaGrande.X += esferaGrande.vel_giro;
		break;
	case 'f':
		esferaGrande.Z += esferaGrande.vel_giro;
		break;
	case 'h':
		esferaGrande.Z -= esferaGrande.vel_giro;
		break;
		//PARTE DE ARRIBA
	case 'i':
		esferaPequenha.X += esferaPequenha.vel_giro;
		break;
	case 'k':
		esferaPequenha.X -= esferaPequenha.vel_giro;
		break;
	case 'j':
		esferaPequenha.Z += esferaPequenha.vel_giro;
		break;
	case 'l':
		esferaPequenha.Z -= esferaPequenha.vel_giro;
		break;
	case 'c':
		camara++; if (camara > 2) camara -= 3;
		break;
	default:
		break;
	}
	// Se se modificou algo redebúxase
	glutPostRedisplay();
}

void myTeclasespeciales(int cursor, int x, int y)
{
	switch (cursor)
	{
		//Giros:
	case GLUT_KEY_UP:
		beta += INCREMENTO;
		break;
	case GLUT_KEY_DOWN:
		beta -= INCREMENTO;
		break;
	case GLUT_KEY_RIGHT:
		alpha -= INCREMENTO;
		break;
	case GLUT_KEY_LEFT:
		alpha += INCREMENTO;
		break;
	default:
		break;
	}

	if (alpha >= PI * 2.0 && alpha <= 0) alpha = 0;
	if (beta >= PI * 2.0 && beta <= 0) beta = 0; //hay que repasarlo para evitar el salto


	glutPostRedisplay();
}

void myEjes() 
{
	//AZUL ES X
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, 0.0f);

	//ROJO ES Y
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.5f, 0.0f);

	//VERDE ES Z
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0, 1.5f);

	//Diagonal
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(.75f, .75f, .75f);

	glEnd();

}

void myCamara() 
{

	/**/
	glMatrixMode(GL_PROJECTION);//Configuración de la matriz de proyeccion
	glLoadIdentity();
	glOrtho(-ancho/200, ancho / 200, -alto/200, alto / 200, -60.0f, 60.0f);    //proyeccion ortografica

	gluLookAt(((float)DISTANCIA*(float)sin(alpha)*cos(beta)),
		((float)DISTANCIA*(float)sin(beta)),
		((float)DISTANCIA*cos(alpha)*cos(beta)),
		0, 0, 0,
		0, 1, 0);

}

void myTerceraPersona() 
{

	/**/
	glMatrixMode(GL_PROJECTION);//Configuración de la matriz de proyeccion
	glLoadIdentity();


	gluPerspective(FOV, ancho/(1.2*alto), .1f, 60.0f);

	gluLookAt(baseCubo.X + 5*sin(baseCubo.angulo_giro*GradosToRadianes),
		(float)esferaPequenha.translate,
		baseCubo.Z + 5 * cos(baseCubo.angulo_giro*GradosToRadianes),


		baseCubo.X - 5*sin(baseCubo.angulo_giro*GradosToRadianes),
		(float)esferaPequenha.translate,
		baseCubo.Z - 5* cos(baseCubo.angulo_giro*GradosToRadianes),

		0, 1, 0);

}

void myPrimeraPersona() 
{

	/**/
	glMatrixMode(GL_PROJECTION);//Configuración de la matriz de proyeccion
	glLoadIdentity();

	gluPerspective(FOV, ancho / (1.2*alto), .1f, 60.0f);

	gluLookAt(baseCubo.X - TAMCUBO * sin(baseCubo.angulo_giro*GradosToRadianes),
		TAMCUBO,
		baseCubo.Z - TAMCUBO * cos(baseCubo.angulo_giro*GradosToRadianes),


		baseCubo.X - TAMCUBO * 3 * sin(baseCubo.angulo_giro*GradosToRadianes),
		TAMCUBO,
		baseCubo.Z - TAMCUBO * 3 * cos(baseCubo.angulo_giro*GradosToRadianes),

		0, 1, 0);

}

unsigned int Carga_Texturas(char *nombre, boolean estrella) {
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
		if (estrella)glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data); //con mimap 

	}
	
	else
	{
		//std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	return textura;

}


void suelo() 
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
	//glScalef(TAMCIELO*10, 0.1f, TAMCIELO*10);
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
}

void charco() {
	glBindTexture(GL_TEXTURE_2D, baseCampo.imagenes[agua]);
	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();
	glTranslatef(0.0f, 0.01f, 0.0f);
	glCallList(listaRenderCharco);
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

void funcionCubo(cubo objeto, float desplazamientoY) {
	glBindTexture(GL_TEXTURE_2D, objeto.textura);
	glTranslatef(objeto.X, desplazamientoY, objeto.Z);
	glRotatef(objeto.angulo_giro, 0.0f, 1.0f, 0.0f);
	glColor3f(objeto.color.x, objeto.color.y, objeto.color.z);
	glCallList(objeto.listarender);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void funcionEsfera(esfera objeto) {
	glTranslatef(0.0f, objeto.translate, 0.0f);
	glRotatef(objeto.X, 1.0f, 0.0f, 0.0f);
	glRotatef(objeto.Z, 0.0f, 1.0f, 0.0f);
	glScalef(objeto.tamanho, objeto.tamanho, objeto.tamanho);
	glColor3f(objeto.color.x, objeto.color.y, objeto.color.z);
	glBindTexture(GL_TEXTURE_2D, objeto.textura);
	glCallList(objeto.listarender);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void funcionPalo(staff objeto, float desplazamientoY, float desplazamientoZ) {
	glBindTexture(GL_TEXTURE_2D, objeto.texture);
	glTranslatef(0.0f, desplazamientoY, desplazamientoZ);
	glRotatef(objeto.rotacion, 1.0f, 0.0f, 0.0f);
	glScalef(objeto.ancho, objeto.alto, objeto.ancho);
	glColor3f(objeto.color.x, objeto.color.y, objeto.color.z);
	glCallList(objeto.listarender);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void calculoLuz() {
	posicionFoco[0] = 0.0f; posicionFoco[1] = -paloPequenho.ancho - TAMCUBO; posicionFoco[2] = -paloPequenho.alto - 0.3f;
	direccionFoco[0] = 0.0f; direccionFoco[1] = -paloPequenho.ancho - TAMCUBO; direccionFoco[2] = -paloPequenho.alto - 5;

	glLightfv(GL_LIGHT0, GL_POSITION, posicionFoco); //Posicion de la luz
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direccionFoco); //Direccion de la luz
}

void grua() 
{
	glPushMatrix();
		//Base
		funcionCubo(baseCubo, TAMCUBO);

		glPushMatrix();
			//Esfera Grande
			funcionEsfera(esferaGrande);

			glPushMatrix();
				//Palo Grande
				funcionPalo(paloGrande, esferaGrande.tamanho * 3, 0.0f);
			glPopMatrix();
			
			glPushMatrix();
				//Esfera Pequeña
				funcionEsfera(esferaPequenha);
				
				glPushMatrix();
					//Cilindro Pequeño
					funcionPalo(paloPequenho, esferaPequenha.tamanho - TAMCUBO, -esferaPequenha.tamanho - TAMCUBO);
				glPopMatrix();
				
				//Calculo de la posicion y direccion de la luz
				calculoLuz();
			
				glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

boolean espacioProhibido(float X, float Z) {
	if ((X < TAMCHARCO + TAMCUBO && X > -TAMCHARCO - TAMCUBO) && ( Z < -TAMCHARCO + TAMCUBO && Z > -TAMCHARCO*3 - TAMCUBO))
		return TRUE;
	/*else if (Z < TAMCHARCO + TAMCUBO && Z > -TAMCHARCO - TAMCUBO)
		return TRUE;*/
	else if (X > ANCHOSUELO || X < -ANCHOSUELO || Z > ANCHOSUELO || Z < -ANCHOSUELO)
		return TRUE;
	else return FALSE;
}

void movimiento() 
{
	if (!espacioProhibido(baseCubo.X + baseCubo.velocidad*sin(baseCubo.angulo_giro*GradosToRadianes), baseCubo.Z + baseCubo.velocidad*cos(baseCubo.angulo_giro*GradosToRadianes))) {
		baseCubo.X += baseCubo.velocidad*sin(baseCubo.angulo_giro*GradosToRadianes);
		baseCubo.Z += baseCubo.velocidad*cos(baseCubo.angulo_giro*GradosToRadianes);
	}
	else baseCubo.velocidad = 0;
	agua++; if (agua > FRAMESUELO-1) agua -= FRAMESUELO;
}

void myEstrellas() {
	glBindTexture(GL_TEXTURE_2D, esferaEstrellas.textura);

	glPushMatrix();
	glScalef(esferaEstrellas.tamanho, esferaEstrellas.tamanho, esferaEstrellas.tamanho);
	glCallList(esferaEstrellas.listarender);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
}

// Función de display
void Display(void) 
{
	movimiento();
	
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (camara){
	case 0:
		myCamara();
		break;
	case 1:
		myTerceraPersona();
		break;
	case 2:
		myPrimeraPersona();
		break;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//SUELO
	glFrontFace(GL_CW);
	myEstrellas();
	glFrontFace(GL_CCW);
	
	suelo();

	//Charco
	//charco();

	//Grua
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	grua();

	//Pelota
	funcionEsfera(pelota);

	myEjes();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void openGlInit() 
{
	//Habilito aqui el depth en vez de arriba para los usuarios de linux y mac mejor arriba
	//Incializaciones varias
	glClearDepth(1.0f); //Valor z-buffer
	glEnable(GL_DEPTH_TEST); // z-buffer
	glEnable(GL_CULL_FACE); //ocultacion caras back
	glutInitDisplayMode(GLUT_DEPTH);
	glEnable(GL_NORMALIZE);

	//Luces
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);	//Luz numero 0
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	//Texturas
	glEnable(GL_TEXTURE_2D);
	glFrontFace(GL_CCW);


	//Limpiar
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // valor limpieza buffer color
}

void inicializarImagenes() {
	for (int i = 0; i < FRAMESUELO; i++) {
		baseCampo.imagenes[i] = Carga_Texturas(foto[i], 0);
	}
	esferaEstrellas.textura = Carga_Texturas(estrellas, 1);
	esferaGrande.textura = Carga_Texturas(ejes, 1);
	esferaPequenha.textura = Carga_Texturas(ejes, 1);
	baseCubo.textura = Carga_Texturas(cemento, 1);
	paloGrande.texture = Carga_Texturas(madera, 1);
	paloPequenho.texture = Carga_Texturas(madera, 1);

	pelota.textura = Carga_Texturas(football, 1);
	baseCampo.textura = Carga_Texturas(soccer, 1);
	baseSuelo.textura = Carga_Texturas(field, 0);
	basePared.textura = Carga_Texturas(pared, 1);
}

void iniciarElementos() 
{
	ancho = W_WIDTH; alto = W_HEIGHT;

	baseCubo.listarender = myCubos();
	esferaGrande.listarender = myEsfera();
	paloGrande.listarender = myCubos();
	esferaPequenha.listarender = myEsfera();
	paloPequenho.listarender = myCubos();
	listaRenderCharco = myCharco();
	esferaEstrellas.listarender = myEsfera();

	pelota.listarender = myEsfera();
	
	baseSuelo.listarender = mySueloMC();

	baseCampo.listarender = mySuelo();
	basePared.listarender = myParedes();

	inicializarImagenes();

	//glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_lambert); //Valores difusos de la luz
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, ANGFOCO);
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
	glutInit(&argc, argv);
	//Posicion de la ventana
	glutInitWindowPosition(100, 100);
	//Tamano de la ventana
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	//Tipo de color y buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );
	//Crear la ventana
	glutCreateWindow("Proyecto");

	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutSpecialFunc(myTeclasespeciales);
	glutKeyboardFunc(myTeclado);

	openGlInit();

	iniciarElementos();

	//Lazo principal
	glutMainLoop();

	return 0;


}