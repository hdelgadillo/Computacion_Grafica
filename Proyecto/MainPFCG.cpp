//Semestre 2019-1 Computación gráfica Proyecto Final
//****************************************************************//
//****************************************************************//
//******			Proyecto Final					         *****//
//******			Alumno (s):								 *****//
//******													******//
//******			Quiroz Mendiola Metztli Ireti			******//
//******			Monterrosas Ramirez Jorge				******//
//******			Landeros Diego							******//
//******			Hugo Delgadillo Cortez					******//
//****************************************************************//
//****************************************************************//
//****************************************************************//
//****************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include <Windows.h>
#include "cmodel/CModel.h"
#include <MMSystem.h>
//Solo para Visual Studio 2015
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

CCamera objCamera; 
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 27.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

//DECLARACION DE TEXTURAS

CTexture cielo; //Cielo
CTexture pasto;
CTexture piza;
//---------------------METZTLI----------------------//
CTexture maceta;
CTexture arbol1;
CTexture pastito_ma;
CTexture teclado;
CTexture pantalla1;
CTexture madera1;
CTexture pantalla2;
CTexture mouse;
CTexture Textcasa;//Paredes blancas
CTexture adoquin;
CTexture pastor;
CTexture trans;
CTexture tierra;

//Se utilizarán para definir cada figura que el programador cree//
CFiguras f_jorge;
CFiguras f_hugo;
CFiguras f_diego;
CFiguras f_Metz;

//Modelos
CModel tren;
CModel pino;
CModel m_arbol;

//NEW// Keyframes
float arriba = 0;
float grados = 0.0;
float lado = 0.0;

#define MAX_FRAMES 30  // Cuantos cuadros capturamos por segundo
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame  // Debemos declarar la variable y otra que es su incremento
{
	//Variables para GUARDAR Key Frames
	float arriba;
	float grados;
	float lado;
	float arribaInc;
	float gradosInc;
	float ladoInc;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 20;			//introducir datos
bool play = false;  //Play en falso
int playIndex = 0;

int frame = 0, time, timebase = 0;
char s[30];
			
void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On


	/*TEXTURAS*/

	adoquin.LoadTGA("Exterior/adoquin.tga");
	adoquin.BuildGLTexture();
	adoquin.ReleaseImage();

	cielo.LoadTGA("Exterior/cielo.tga");
	cielo.BuildGLTexture();
	cielo.ReleaseImage();

	pasto.LoadTGA("Exterior/pasto.tga");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	Textcasa.LoadTGA("Exterior/Textcasa.tga");
	Textcasa.BuildGLTexture();
	Textcasa.ReleaseImage();

	piza.LoadTGA("Texturas/piza.tga");
	piza.BuildGLTexture();
	piza.ReleaseImage();

	////*********** METZ **************//

	arbol1.LoadTGA("texturas/cedro.tga");
	arbol1.BuildGLTexture();
	arbol1.ReleaseImage();

	maceta.LoadTGA("texturas/piedra2.tga");
	maceta.BuildGLTexture();
	maceta.ReleaseImage();

	pastito_ma.LoadTGA("texturas/pastoj.tga");
	pastito_ma.BuildGLTexture();
	pastito_ma.ReleaseImage();

	teclado.LoadTGA("texturas/teclado.tga");
	teclado.BuildGLTexture();
	teclado.ReleaseImage();

	pantalla1.LoadTGA("texturas/pantalla1.tga");
	pantalla1.BuildGLTexture();
	pantalla1.ReleaseImage();

	madera1.LoadTGA("texturas/madera1.tga");
	madera1.BuildGLTexture();
	madera1.ReleaseImage();

	pantalla2.LoadTGA("texturas/pantalla2.tga");
	pantalla2.BuildGLTexture();
	pantalla2.ReleaseImage();

	mouse.LoadTGA("texturas/mouse.tga");
	mouse.BuildGLTexture();
	mouse.ReleaseImage();

	pastor.LoadTGA("texturas/pastor.tga");
	pastor.BuildGLTexture();
	pastor.ReleaseImage();

	trans.LoadTGA("texturas/trans.tga");
	trans.BuildGLTexture();
	trans.ReleaseImage();

	tierra.LoadTGA("texturas/tierra.tga");
	tierra.BuildGLTexture();
	tierra.ReleaseImage();
	////***********fin  METZ **************//

	//Carga de modelos 3D
	pino._3dsLoad("modelos/pino.3ds");
	m_arbol._3dsLoad("modelos/arbol.3ds");


	////Carga de Figuras
	////kit.VertexNormals();
	//llanta._3dsLoad("k_rueda.3ds");

	//objCamera.Position_Camera(0, 2.5f, 3, 0, 10.0f, 0, 1, 1, 0);
	objCamera.Position_Camera(10, 2.5f, 13, 10, 2.5f, 10, 0, 1, 0);

	//NEW Iniciar variables de KeyFrames
	/*for(int i=0; i<MAX_FRAMES; i++)
	{
	KeyFrame[i].posX =0;
	KeyFrame[i].posY =0;
	KeyFrame[i].posZ =0;
	KeyFrame[i].incX =0;
	KeyFrame[i].incY =0;
	KeyFrame[i].incZ =0;
	KeyFrame[i].rotRodIzq =0;
	KeyFrame[i].rotInc =0;
	KeyFrame[i].giroMonito =0;
	KeyFrame[i].giroMonitoInc =0;
	KeyFrame[i].giroBrazo =0;
	KeyFrame[i].giroBrazoInc = 0;
	}*/

	//Index empezaba en 5 porque del 1 al 4 ya estan creados, siempre hara esta animacion.

	KeyFrame[0].arriba = 0.0001;
	KeyFrame[0].grados = 0.0001;
	KeyFrame[0].lado = 0.0001;


	KeyFrame[1].arriba = .2;
	KeyFrame[1].grados = 15;
	KeyFrame[1].lado = 0.4;

	KeyFrame[2].arriba = .4;
	KeyFrame[2].grados = 30;
	KeyFrame[2].lado = .8;

	KeyFrame[3].arriba = .6;
	KeyFrame[3].grados = 45;
	KeyFrame[3].lado = 1.2;

	KeyFrame[4].arriba = .8;
	KeyFrame[4].grados = 45;
	KeyFrame[4].lado = 1.6;

	KeyFrame[5].arriba = 1;
	KeyFrame[5].grados = 30;
	KeyFrame[5].lado = 2;

	KeyFrame[6].arriba = 1.2;
	KeyFrame[6].grados = 15;
	KeyFrame[6].lado = 2.4;

	KeyFrame[7].arriba = 1.4;
	KeyFrame[7].grados = 0;
	KeyFrame[7].lado = 3.2;

	KeyFrame[8].arriba = 1.6;
	KeyFrame[8].grados = -15;
	KeyFrame[8].lado = 3.4;

	KeyFrame[9].arriba = 1.8;
	KeyFrame[9].grados = 0;
	KeyFrame[9].lado = 3.6;

	KeyFrame[10].arriba = 2.0;
	KeyFrame[10].grados = 15;
	KeyFrame[10].lado = 4.0;

	KeyFrame[11].arriba = 2.2;
	KeyFrame[11].grados = 30;
	KeyFrame[11].lado = 4.4;

	KeyFrame[12].arriba = 2.4;
	KeyFrame[12].grados = 45;
	KeyFrame[12].lado = 4.8;

	KeyFrame[13].arriba = 2.6;
	KeyFrame[13].grados = 30;
	KeyFrame[13].lado = 5;

	KeyFrame[14].arriba = 2.8;
	KeyFrame[14].grados = 15;
	KeyFrame[14].lado = 5;

	KeyFrame[15].arriba = 3.2;
	KeyFrame[15].grados = 0;
	KeyFrame[15].lado = 5;

	KeyFrame[16].arriba = 3.4;
	KeyFrame[16].grados = 15;
	KeyFrame[16].lado = 5;

	KeyFrame[17].arriba = 3.6;
	KeyFrame[17].grados = 0;
	KeyFrame[17].lado = 5;
	KeyFrame[18].arriba = 3.8;
	KeyFrame[18].grados = 30;
	KeyFrame[18].lado = 5;

	KeyFrame[19].arriba = 4;
	KeyFrame[19].grados = 0;
	KeyFrame[19].lado = 5;

	KeyFrame[20].arriba = 4.2;
	KeyFrame[20].grados = 0;
	KeyFrame[20].lado = 5;

	KeyFrame[21].arriba = 4.4;
	KeyFrame[21].grados = 0;
	KeyFrame[21].lado = 5;

	KeyFrame[22].arriba = 4.6;
	KeyFrame[22].grados = 45;
	KeyFrame[22].lado = 5;

	KeyFrame[23].arriba = 4.4;
	KeyFrame[23].grados = 0;
	KeyFrame[23].lado = 5;

	KeyFrame[24].arriba = 4.8;
	KeyFrame[24].grados = 0;
	KeyFrame[24].lado = 5;

	KeyFrame[25].arriba = 5;
	KeyFrame[25].grados = 0;
	KeyFrame[25].lado = 5;
	
	//NEW//////////////////NEW//////////////////NEW//////////////////   // Despues de aqui agregamos los keyframes que queramos cada que se
	//ejecuta el programa.
}//Fin Init

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void monitor(void) {

	glPushMatrix();//1
		glScalef(1.5, 1, .1);
		f_hugo.prisma2(0, 0);
		glTranslatef(0, -.5, 0);

		glPushMatrix();//2
			glScalef(.1, .8, .1);
			f_hugo.prisma2(0, 0);
		glPopMatrix();//fin 2
		glTranslatef(0, -.4,0);
		glPushMatrix();//3
			glScalef(.5, .09, .5);
			f_hugo.prisma2(0, 0);
		glPopMatrix();// fin3 
	
		glPushMatrix();//4
			glScalef(.06, .09, 6);
			f_hugo.prisma2(0, 0);
		glPopMatrix();//fin4
	
	glPopMatrix();//fin 1
}//fin monitor

///************************************* METZ   **************************************************//
void computadora(GLuint text)
{
	glPushMatrix();
	glPushMatrix();//1
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		f_Metz.prisma_textura(2.5, 0.1, 0.5, teclado.GLindex);
		glTranslatef(1.5, 0.0, 0.0);
		f_Metz.prisma_textura(0.2, 0.1, 0.23, 0.0);
	glPopMatrix();//fin1

	glTranslatef(0.0, 0.0, -0.5);
	f_Metz.cilindro(0.2, 0.3, 23.0, 0);
	glTranslatef(0.0, 1.0, 0.0);
	glPushMatrix();
	f_Metz.prisma_textura(2.0, 1.5, 0.2, text);
	glTranslatef(0.0, 0.0, 0.1);
	f_Metz.prisma_textura(1.9, 1.0, 0.1, mouse.GLindex);
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPopMatrix();
}

void mesa(void)
{
	//tabla
	glPushMatrix();
	glPushMatrix();
	f_Metz.prisma_textura(18.0, 0.3, 2.5, madera1.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.75, 0);
	//patas
	glPushMatrix();
	glTranslatef(-8.0, -0.4, 0.5);
	f_Metz.prisma_textura(0.5, 2.5, 0.5, madera1.GLindex);
	glTranslatef(0, 0, -1.0);
	f_Metz.prisma_textura(0.5, 2.5, 0.5, madera1.GLindex);
	glTranslatef(16.0, 0, 0);
	f_Metz.prisma_textura(0.5, 2.5, 0.5, madera1.GLindex);
	glTranslatef(0, 0, 1.0);
	f_Metz.prisma_textura(0.5, 2.5, 0.5, madera1.GLindex);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}

void jardinera_trapecio(void) {

	glPushMatrix();
	glEnable(GL_ALPHA_TEST);

	f_hugo.prisma_textura1(8, .1, 4, pasto.GLindex, trans.GLindex);
	glDisable(GL_ALPHA_TEST);

	glPopMatrix();

	glPushMatrix();
	glEnable(GL_ALPHA_TEST);

	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, -6);
	f_hugo.prisma_textura1(4, .1, 4, pastor.GLindex, trans.GLindex);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	//tierra
	glPushMatrix();
	glTranslatef(0, -.01, 2);
	f_hugo.prisma_textura(8, .2, .1, tierra.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, -.01, -2);
	f_hugo.prisma_textura(12, .2, .1, tierra.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, -.01, 0);
	f_hugo.prisma_textura(.1, .2, 4, tierra.GLindex);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glTranslatef(-4.2, -.01, -4.2);
	f_hugo.prisma_textura(.1, .2, 5.7, tierra.GLindex);
	glPopMatrix();

}


void jardinera_trapeciod(void) {
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glPushMatrix();
	glEnable(GL_ALPHA_TEST);

	f_hugo.prisma_textura1(8, .1, 4, pasto.GLindex, trans.GLindex);
	glDisable(GL_ALPHA_TEST);

	glPopMatrix();

	glPushMatrix();
	glEnable(GL_ALPHA_TEST);

	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 0, -6);
	f_hugo.prisma_textura1(4, .1, 4, pastor.GLindex, trans.GLindex);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	//tierra
	glPushMatrix();
	glTranslatef(0, .14, 2);
	f_hugo.prisma_textura(8, .2, .1, tierra.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, .14, -2);
	f_hugo.prisma_textura(12, .2, .1, tierra.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, .14, 0);
	f_hugo.prisma_textura(.1, .2, 4, tierra.GLindex);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glTranslatef(-4.2, .14, -4.2);
	f_hugo.prisma_textura(.1, .2, 5.7, tierra.GLindex);
	glPopMatrix();
	glPopMatrix();
}



void mediocirculo(void) {

	glPushMatrix();
	f_hugo.cilindro(5, 1, 100, pasto.GLindex);
	f_hugo.cilindro(5.1, 0.8, 100, tierra.GLindex);
	glPopMatrix();

}


void mesa_comp(void) {
	glPushMatrix();
		mesa();
		glPushMatrix();//1

			glPushMatrix();//2
				mesa();
				glPushMatrix();//////////////////////////
				glTranslatef(2.0, 0.2, 0.0);

				glPushMatrix();///
					computadora(pantalla1.GLindex);
					glTranslatef(2.1, 1.0, 0.4);
					f_Metz.prisma_textura(1.0, 2.0, 1.8, 0);
				glPopMatrix();////
				glPopMatrix();////////////////////////

				glPushMatrix();//////////////////////////
				glTranslatef(-3.0, 0.2, 0.0);

				glPushMatrix();///
					computadora(pantalla1.GLindex);
					glTranslatef(2.1, 1.0, 0.4);
					f_Metz.prisma_textura(1.0, 2.0, 1.8, 0);
				glPopMatrix();////
				glPopMatrix();////////////////////////

				glPushMatrix();//////////////////////////
				glTranslatef(-7.0, 0.2, 0.0);

				glPushMatrix();///
					computadora(pantalla1.GLindex);
					glTranslatef(2.1, 1.0, 0.4);
					f_Metz.prisma_textura(1.0, 2.0, 1.8, 0);
				glPopMatrix();////
				glPopMatrix();////////////////////////

				glPushMatrix();//////////////////////////
				glTranslatef(6.0, 0.2, 0.0);

				glPushMatrix();///
					computadora(pantalla1.GLindex);
					glTranslatef(2.1, 1.0, 0.4);
					f_Metz.prisma_textura(1.0, 2.0, 1.8, 0);
				glPopMatrix();////
				glPopMatrix();////////////////////////

			glPopMatrix();//cierra 2
		glPopMatrix();//cierra 1
	glPopMatrix();
}
/*

	*/
void arbol(GLuint textura)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	//glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
	glAlphaFunc(GL_GREATER, 0.1);
	//glEnable(GL_BLEND);     // Turn Blending On
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	//glDisable(GL_BLEND);        // Turn Blending Off
	//glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
	glEnable(GL_LIGHTING);

	glPopMatrix();
}


void jardinera(void){
			   //      ******     JARDINERA    *****   //
	glPushMatrix();
		glRotatef(90,0,1,0);	

		glTranslatef(-30, -0.4, -25);
		f_Metz.prisma_textura(12.0, 6.0, 23.0, tierra.GLindex);
		glPushMatrix();
			glTranslatef(0.0, 3.0, 0.0);
			f_Metz.prisma_textura(12.0, 0.5, 23.0, pasto.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, -3.0, 11.5);
			f_Metz.cilindro(6, 6.0, 60, tierra.GLindex);
				glPushMatrix();
					glTranslatef(0.0, 5.8, 0.0);
					f_Metz.cilindro(6.0, 0.5, 60, pasto.GLindex);
				glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 0.0, -17.0);
			f_Metz.triang(6.0, 12.0, 11.0, tierra.GLindex);
				glPushMatrix();
					glTranslatef(0.0, 2.8, 0.0);
					f_Metz.triang(1.0, 12.0, 11.0, pasto.GLindex);
				glPopMatrix();
		glPopMatrix();

	glPopMatrix();
}

void jardinera1(void) {
	//      ******     JARDINERA    *****   //
	glPushMatrix();
	glRotatef(90, 0, 1, 0);

	glTranslatef(-30, -0.4, -25);
	f_Metz.prisma_textura(12.0, 6.0, 23.0, pasto.GLindex);//
	glPushMatrix();
	glTranslatef(0.0, 3.0, 0.0);
	f_Metz.prisma_textura(12.0, 0.5, 23.0, tierra.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -3.0, 11.5);
	f_Metz.cilindro(6, 6.0, 60,pasto.GLindex);//
	glPushMatrix();
	glTranslatef(0.0, 5.8, 0.0);
	f_Metz.cilindro(6.0, 0.5, 60, tierra.GLindex);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -17.0);
	f_Metz.triang(6.0, 12.0, 11.0, pasto.GLindex);//
	glPushMatrix();
	glTranslatef(0.0, 2.8, 0.0);
	f_Metz.triang(1.0, 12.0, 11.0, tierra.GLindex);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}

///************************************* fin METZ   **************************************************//
void pared(void) {
	glPushMatrix();
	glScalef(23, 20, 1);
	f_diego.prisma2 (Textcasa.GLindex, Textcasa.GLindex);
	glPopMatrix();
}

void pizarron(void) {
	glPushMatrix();
	glScalef(15, 10, 1);
	f_jorge.prisma2 (piza.GLindex, piza.GLindex);
	glPopMatrix();
}

void platabaja(void) {

	glPushMatrix();//inicio pared
	glTranslatef(25, 40, -10.5);
	glRotatef(180, 0, 1, 0);
	glScalef(2.45, 1, 2);
	pared();
	glPopMatrix();//fin pared

	glPushMatrix();//inicio pared
	glTranslatef(25, 40, -89.5);
	glRotatef(180, 0, 1, 0);
	glScalef(2.45, 1, 2);
	pared();
	glPopMatrix();//fin pared

	glPushMatrix();//inicio pared1
	glTranslatef(-55.1, 10, -50);
	glRotatef(90, 0, 1, 0);
	glScalef(3.5, 2, 2);
	pared();
	glPopMatrix();//fin pared1

	glPushMatrix();//inicio pared2
	glTranslatef(25, 10, -89.5);
	glRotatef(180, 0, 1, 0);
	glScalef(7, 2, 2);
	pared();
	glPopMatrix();//fin pared2

	glPushMatrix();//inicio pared3
	glTranslatef(104.5, 10, -50);
	glRotatef(90, 0, 1, 0);
	glScalef(3.5, 2, 2);
	pared();
	glPopMatrix();//fin pared3

	glPushMatrix();//inicio pared4
	glTranslatef(25, 10, -10.5);
	glRotatef(180, 0, 1, 0);
	glScalef(7, 2, 2);
	pared();
	glPopMatrix();//fin pared4
	
	glPushMatrix();//inicio pared5
	glTranslatef(0, 10, -50);
	glRotatef(90, 0, 1, 0);
	glScalef(3.5, 2, 2);
	pared();
	glPopMatrix();//fin pared5

	glPushMatrix();//inicio pared6
	glTranslatef(50, 10, -50);
	glRotatef(90, 0, 1, 0);
	glScalef(3.5, 2, 2);
	pared();
	glPopMatrix();//fin pared6

	glPushMatrix();//inicio pared7
	glTranslatef(77, 10, -50);
	glRotatef(180, 0, 1, 0);
	glScalef(2.35, 2, 2);
	pared();
	glPopMatrix();//fin pared7

	glPushMatrix();//inicio pared8
	glTranslatef(-28, 10, -50);
	glRotatef(180, 0, 1, 0);
	glScalef(2.35, 2, 2);
	pared();
	glPopMatrix();//fin pared8

	

}

void torre1(void) {


	///piso 1
	glPushMatrix();//inicio pared1
	glTranslatef(-55.1, 50, -50);
	glRotatef(90, 0, 1, 0);
	glScalef(3.5, 2, 2);
	pared();
	glPopMatrix();//fin pared1

	glPushMatrix();//inicio pared2
	glTranslatef(0, 50, -50);
	glRotatef(90, 0, 1, 0);
	glScalef(3.5, 2, 2);
	pared();
	glPopMatrix();//fin pared2

	glPushMatrix();//inicio pared3
	glTranslatef(-28, 50, -50);
	glRotatef(180, 0, 1, 0);
	glScalef(2.35, 2, 2);
	pared();
	glPopMatrix();//fin pared3


	glPushMatrix();//inicio pared4
	glTranslatef(-28, 50, -10.5);
	glRotatef(180, 0, 1, 0);
	glScalef(2.45, 2, 2);
	pared();
	glPopMatrix();//fin pared4

	glPushMatrix();//inicio pared5
	glTranslatef(-28, 50, -89.5);
	glRotatef(180, 0, 1, 0);
	glScalef(2.45, 2, 2);
	pared();
	glPopMatrix();//fin pared5
	
	glPushMatrix();//techo piso 1
	glTranslatef(-28, 69, -50);
	glRotatef(90, 1, 0, 0);
	glScalef(2.4, 4, 2);
	pared();
	glPopMatrix();//fin techo piso 1


	///fin piso 1

	///piso 2
	glPushMatrix();//inicio pared1
	glTranslatef(-55.1, 90, -50);
	glRotatef(90, 0, 1, 0);
	glScalef(3.5, 2, 2);
	pared();
	glPopMatrix();//fin pared1

	glPushMatrix();//inicio pared2
	glTranslatef(0, 90, -50);
	glRotatef(90, 0, 1, 0);
	glScalef(3.5, 2, 2);
	pared();
	glPopMatrix();//fin pared2

	glPushMatrix();//inicio pared3
	glTranslatef(-28, 90, -50);
	glRotatef(180, 0, 1, 0);
	glScalef(2.35, 2, 2);
	pared();
	glPopMatrix();//fin pared3


	glPushMatrix();//inicio pared4

	glTranslatef(-28, 90, -10.5);
	glRotatef(180, 0, 1, 0);
	glScalef(2.45, 2, 2);
	pared();
	glPopMatrix();//fin pared4

	glPushMatrix();//inicio pared5
	glTranslatef(-28, 90, -89.5);
	glRotatef(180, 0, 1, 0);
	glScalef(2.45, 2, 2);
	pared();
	glPopMatrix();//fin pared5

	glPushMatrix();//techo piso 2
	glTranslatef(-28, 109, -50);
	glRotatef(90, 1, 0, 0);
	glScalef(2.4, 4, 2);
	pared();
	glPopMatrix();//fin techo piso 2

	///Fin de piso 2

	///piso 3
	glPushMatrix();//inicio pared1
	glTranslatef(-55.1, 130, -50);
	glRotatef(90, 0, 1, 0);
	glScalef(3.5, 2, 2);
	pared();
	glPopMatrix();//fin pared1

	glPushMatrix();//inicio pared2
	glTranslatef(0, 130, -50);
	glRotatef(90, 0, 1, 0);
	glScalef(3.5, 2, 2);
	pared();
	glPopMatrix();//fin pared2

	glPushMatrix();//inicio pared3
	glTranslatef(-28, 130, -50);
	glRotatef(180, 0, 1, 0);
	glScalef(2.35, 2, 2);
	pared();
	glPopMatrix();//fin pared3


	glPushMatrix();//inicio pared4

	glTranslatef(-28, 130, -10.5);
	glRotatef(180, 0, 1, 0);
	glScalef(2.45, 2, 2);
	pared();
	glPopMatrix();//fin pared4

	glPushMatrix();//inicio pared5
	glTranslatef(-28, 130, -89.5);
	glRotatef(180, 0, 1, 0);
	glScalef(2.45, 2, 2);
	pared();
	glPopMatrix();//fin pared5

	glPushMatrix();//techo piso 3
	glTranslatef(-28, 149, -50);
	glRotatef(90, 1, 0, 0);
	glScalef(2.4, 4, 2);
	pared();
	glPopMatrix();//fin techo piso 3

	///fin de piso 3

	///piso 4
	glPushMatrix();//inicio pared1
	glTranslatef(-55.1, 170, -50);
	glRotatef(90, 0, 1, 0);
	glScalef(3.5, 2, 2);
	pared();
	glPopMatrix();//fin pared1

	glPushMatrix();//inicio pared2
	glTranslatef(0, 170, -50);
	glRotatef(90, 0, 1, 0);
	glScalef(3.5, 2, 2);
	pared();
	glPopMatrix();//fin pared2

	glPushMatrix();//inicio pared3
	glTranslatef(-28, 170, -50);
	glRotatef(180, 0, 1, 0);
	glScalef(2.35, 2, 2);
	pared();
	glPopMatrix();//fin pared3


	glPushMatrix();//inicio pared4

	glTranslatef(-28, 170, -10.5);
	glRotatef(180, 0, 1, 0);
	glScalef(2.45, 2, 2);
	pared();
	glPopMatrix();//fin pared4

	glPushMatrix();//inicio pared5
	glTranslatef(-28, 170, -89.5);
	glRotatef(180, 0, 1, 0);
	glScalef(2.45, 2, 2);
	pared();
	glPopMatrix();//fin pared5

	glPushMatrix();//techo piso 4
	glTranslatef(-28, 189, -50);
	glRotatef(90, 1, 0, 0);
	glScalef(2.4, 4, 2);
	pared();
	glPopMatrix();//fin techo piso 4

	///fin de piso 4
}


void antena(void) {

	glPushMatrix();
	glScalef(5, 5, .1);
	f_hugo.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 5);
	glScalef(5, 5, .1);
	f_hugo.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -2.5, 2.5);
	glRotatef(90, 1, 0, 0);
	glScalef(5, 5, .1);
	f_hugo.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 0, 2.5);
	glRotatef(90, 0, 1, 0);
	glScalef(5, 5, .1);
	f_hugo.prisma2(0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5, 0, 2.5);
	glRotatef(90, 0, 1, 0);
	glScalef(5, 5, .1);
	f_hugo.prisma2(0, 0);
	glPopMatrix();

	//tapa
	glPushMatrix();
	glTranslatef(lado, 2.5, 2.5);
	glRotatef(90, 1, 0, 0);
	glScalef(5, 5, .1);
	f_hugo.prisma2(0, 0);
	glPopMatrix();

	//antena
	//base 
	glPushMatrix();
	glTranslatef(0, arriba, 0);


	glPushMatrix();
	glTranslatef(0, -2.2, 2.5);
	glRotatef(90, 1, 0, 0);
	glScalef(5, 5, .1);
	f_hugo.prisma2(0, 0);
	glPopMatrix();

	//panel solar
	glPushMatrix();
	glTranslatef(0, -1.7, 1);
	glRotatef(45, 1, 0, 0);
	glScalef(2, 2, .1);
	f_hugo.prisma2(0, 0);
	glPopMatrix();

	//poste antena

	glPushMatrix();
	glTranslatef(0, -1, 3);
	glScalef(.1, 2, .1);
	f_hugo.prisma2(0, 0);

	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(.4, 0, 3);
	glRotatef(90, 0, 0, 1);
	glRotatef(grados, 1, 0, 0);
	f_hugo.cono(.5, 1.5, 200, 0);
	glPopMatrix();
	glPopMatrix();
}


void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();//1
	glRotatef(g_lookupdown, 1.0f, 0, 0);
	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
	glPushMatrix();//2

	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);

	f_hugo.skybox(1100.0, 500.0, 900.0, cielo.GLindex); //tamaño del skybox
	glEnable(GL_LIGHTING);
	glPopMatrix();//Creamos cielo

	glPushMatrix(); //Creación del Piso/pasto
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(-30.0, 0.0, 0.0);
	f_hugo.piso(1100, 1.5, 900, pasto.GLindex, pasto.GLindex, pasto.GLindex, pasto.GLindex, pasto.GLindex, pasto.GLindex);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glPopMatrix(); //Creación del Piso/pasto

	//***************************************** metz   ******************************//

	//fin plantabaja

	//      ******    salon    *****   //
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(75.0, 4.3, -65.0);
	glScalef(1.5, 1.5, 1.5);
	mesa_comp();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(75.0, 4.3, -45.0);
	glScalef(1.5, 1.5, 1.5);
	mesa_comp();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(75.0, 4.3, -25.0);
	glScalef(1.5, 1.5, 1.5);
	mesa_comp();
	glPopMatrix();
	//TERMINA LADO IZQUIERDO

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(130.0, 4.3, -65.0);
	glScalef(1.5, 1.5, 1.5);
	mesa_comp();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(130.0, 4.3, -45.0);
	glScalef(1.5, 1.5, 1.5);
	mesa_comp();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(130.0, 4.3, -25.0);
	glScalef(1.5, 1.5, 1.5);
	mesa_comp();
	glPopMatrix();

	//      ******  fin  salon    *****   //


	glPushMatrix(); //Creación del piso
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(-30.0, -40, -135);
	f_diego.piso(258, 1.7, 155, Textcasa.GLindex, Textcasa.GLindex, Textcasa.GLindex, Textcasa.GLindex, Textcasa.GLindex, Textcasa.GLindex);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glPopMatrix(); //Creación del piso

	glPushMatrix(); //Creación techo planta baja
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(0, -40, -135);
	f_diego.piso(258, 1.7, 155, Textcasa.GLindex, Textcasa.GLindex, Textcasa.GLindex, Textcasa.GLindex, Textcasa.GLindex, Textcasa.GLindex);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glPopMatrix(); //Creación techo plata baja



	//MODELOS

	glPushMatrix();//pino
		//Para que conserve sus colores

	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-90, -28, 0);
	glScalef(15.3, 15.3, 15.3);
	pino.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS										
	glPopMatrix();

	glPushMatrix();//pino
		//Para que conserve sus colores

	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(90, -28, 0);
	glScalef(15.3, 15.3, 15.3);
	pino.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS										
	glPopMatrix();
	///////////DIBUJAR
	glPushMatrix();
	glEnable(GL_LIGHTING);
	glPushMatrix();//plantabaja

	glTranslatef(0, -20, -35);
	glScalef(1.6, 1.0, 2.3);
	platabaja();
	glPopMatrix();//fin plantabaja

	glPushMatrix();//torre1
	glTranslatef(0, -20, -35);
	glScalef(1.6, 1.0, 2.3);
	torre1();
	glPopMatrix();//fin torre1

	glPushMatrix();//torre2
	glTranslatef(167, -20, -35);
	glScalef(1.6, 1.0, 2.3);
	torre1();
	glPopMatrix();//fin torre2


	glPopMatrix();

	glPushMatrix();
	glTranslatef(100, 172, -70);
	antena();
	glPopMatrix();

	glPushMatrix(); //Creación del adoquin
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(-28.0, 0.0, 0.0);
	f_jorge.piso(1000, 1.5, 800, adoquin.GLindex, adoquin.GLindex, adoquin.GLindex, adoquin.GLindex, adoquin.GLindex, adoquin.GLindex);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glPopMatrix(); //Creación del adoquin


	glPushMatrix();//pizarron
	glTranslatef(-87, 20, -100);
	glScalef(1.6, 2.3, 3.5);
	glRotatef(180, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	pizarron();
	glPopMatrix();//fin torre2

///////////DIBUJAR

	glPushMatrix();
	
	glTranslatef(220, -27, -180);
	glRotatef(270, 0, 1, 0);
			glScalef(15, 15, 15);
			jardinera_trapecio();
			glPopMatrix();

			glPushMatrix();

			glTranslatef(-150, -25, -180);
			glRotatef(270, 0, 1, 0);
			glScalef(15, 15, 15);
			jardinera_trapeciod();
			glPopMatrix();


			glPushMatrix();//jardinera
			glRotatef(180, 0, 1,0);
			glTranslatef(-20, -28,170 );
			glScalef(4, 1, 4);
			jardinera();
			
			glPopMatrix();

			glPushMatrix();
			glRotatef(180, 1, 0, 0);
			glTranslatef(50, 28, 170);
			glScalef(4, 1, 4);
			jardinera1();

			glPushMatrix();
			glTranslatef(-5, -1, -25);
			glRotatef(180, 1, 0, 0);
			glScalef(4, 4, 4);
			mediocirculo();
			glPopMatrix();

	//////////
	glPopMatrix();//Pop para todo el escenario,2


	glPopMatrix();//1
	glutSwapBuffers ( );

}

void animacion()
{
	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation

								  //Interpolaciones incremento.
								  //el incremento es la distancia entre dos cuadros, el 2 - 1 y se divide entre el 90(i_max_steps)   Se hace la interpolacion


				KeyFrame[playIndex].arribaInc = (KeyFrame[playIndex + 1].arriba - KeyFrame[playIndex].arriba) / i_max_steps;
				KeyFrame[playIndex].gradosInc = (KeyFrame[playIndex + 1].grados - KeyFrame[playIndex].grados) / i_max_steps;
				KeyFrame[playIndex].ladoInc = (KeyFrame[playIndex + 1].lado - KeyFrame[playIndex].lado) / i_max_steps;
			

			}
		}
		else
		{	//Draw information


			arriba += KeyFrame[playIndex].arribaInc;
			grados += KeyFrame[playIndex].gradosInc;
			lado += KeyFrame[playIndex].ladoInc;
			


			i_curr_steps++;
		}

	}

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s, "FPS:%4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}

	glutPostRedisplay();
}



void sonidominecraft() {

	PlaySound(TEXT("music/minecraft.wav"), NULL, SND_ASYNC|SND_LOOP);
}


void undertale() {

	PlaySound(TEXT("music/snowy.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void undertale2() {

	PlaySound(TEXT("music/ruin.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void FinalFantasy() {

	PlaySound(TEXT("music/final.wav"), NULL, SND_ASYNC | SND_LOOP);
}
void zelda() {

	PlaySound(TEXT("music/zelda.wav"), NULL, SND_ASYNC | SND_LOOP);
}
void donkeykong() {

	PlaySound(TEXT("music/donkeykong.wav"), NULL, SND_ASYNC | SND_LOOP);
}
void pokemon() {

	PlaySound(TEXT("music/pokemon.wav"), NULL, SND_ASYNC | SND_LOOP);
}
void sonic() {

	PlaySound(TEXT("music/sonic.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void witcher() {

	PlaySound(TEXT("music/witcher.wav"), NULL, SND_ASYNC | SND_LOOP);
}
void thelast() {

	PlaySound(TEXT("music/thelast.wav"), NULL, SND_ASYNC | SND_LOOP);
}




void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.4);
		printf("%f %f %f %f %f %f %f %f %f\n", objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
			objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
			objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case '0':
		undertale();
		break;
	case '1':
		sonidominecraft();
		break;
	case '2':
		undertale2();
		break;
	case '3':
		FinalFantasy();
		break;
	case '4':
		zelda();
		break;
	case '5':
		donkeykong();
		break;
	case '6':
		pokemon();
		break;
	case '7':
		sonic();
		break;
	case '8':
		witcher();
		break;
	case '9':
		thelast();
		break;
	case'j':
	case 'J':
		objCamera.Position_Camera(-397.804779f, 293.700104f, -280.190399, -395.4518, 293.700104f, -278.329315, 0.0, 1, 0);
		break;
	case'o':
	case 'O':
		objCamera.Position_Camera(376.265900, 293.700104f, -295.896515f, 374.336975, 293.700104f, -293.598907, 0, 1, 0);
		break;
	case'p':
	case 'P':
		objCamera.Position_Camera(158.774948, 293.700104f, -2.348673, 155.809784, 293.700104f, -1.893221, 0, 1, 0);
		break;
	case'L':
	case 'l':
		objCamera.Position_Camera(10, 2.5f, 13, 10, 2.5f, 10, 0, 1, 0);
		break;
	case 'r':
	case 'R':
		if (play == false && (FrameIndex > 1))
		{

			grados = KeyFrame[0].grados;
			arriba = KeyFrame[0].arriba;
			lado = KeyFrame[0].lado;

			//First Interpolation


			KeyFrame[playIndex].arribaInc = (KeyFrame[playIndex + 1].arriba - KeyFrame[playIndex].arriba) / i_max_steps;
			KeyFrame[playIndex].gradosInc = (KeyFrame[playIndex + 1].grados - KeyFrame[playIndex].grados) / i_max_steps;
			KeyFrame[playIndex].ladoInc = (KeyFrame[playIndex + 1].lado - KeyFrame[playIndex].lado) / i_max_steps;


			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;
		break;


		

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}


int main ( int argc, char** argv )   // Main Function
{
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (700, 700);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto Final CG"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  sonidominecraft();
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );
  glutMainLoop        ( );          // 
  
  return 0;
}
