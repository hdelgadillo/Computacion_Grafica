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

CTexture cielo; //Cielo
CTexture pasto;

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

//Se utilizarán para definir cada figura que el programador cree//
CFiguras f_jorge;
CFiguras f_hugo;
CFiguras f_diego;
CFiguras f_Metz;

//Modelos
CModel tren;
CModel pino;
CModel m_arbol;

			
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

	Textcasa.LoadTGA("Torre/Textcasa.tga");
	Textcasa.BuildGLTexture();
	Textcasa.ReleaseImage();

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
	////***********fin  METZ **************//

	//tren._3dsLoad("modelos/tren/tren.3ds");
	pino._3dsLoad("modelos/pino.3ds");
	m_arbol._3dsLoad("modelos/arbol.3ds");
	

	////Carga de Figuras
	////kit.VertexNormals();
	//llanta._3dsLoad("k_rueda.3ds");

	//objCamera.Position_Camera(0, 2.5f, 3, 0, 10.0f, 0, 1, 1, 0);
	objCamera.Position_Camera(10, 2.5f, 13, 10, 2.5f, 10, 0, 1 , 0);

}

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

	glPushMatrix();
		glScalef(1.5, 1, .1);
		f_hugo.prisma2(0, 0);
		glTranslatef(0, -.5, 0);
	glPushMatrix();
		glScalef(.1, .8, .1);
		f_hugo.prisma2(0, 0);
	glPopMatrix();
	glTranslatef(0, -.4,0);
	glPushMatrix();
		glScalef(.5, .09, .5);
		f_hugo.prisma2(0, 0);
	glPopMatrix();
	
	glPushMatrix();
	
		glScalef(.06, .09, 6);
		f_hugo.prisma2(0, 0);
	glPopMatrix();
	
	glPopMatrix();





	

}

///************************************* METZ   **************************************************//
void computadora(GLuint text)
{
	glPushMatrix();
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	f_Metz.prisma_textura(2.5, 0.1, 0.5, teclado.GLindex);
	glTranslatef(1.5, 0.0, 0.0);
	f_Metz.prisma_textura(0.2, 0.1, 0.23, 0.0);
	glPopMatrix();

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
}


void mesa(GLfloat xPosMesa, GLfloat yPosMesa, GLfloat zPosMesa)
{
	//tabla
	glPushMatrix();
	glTranslatef(xPosMesa, yPosMesa, zPosMesa);
	glPushMatrix();
	f_Metz.prisma_textura(15.0, 0.3, 2.5, madera1.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.75, 0);
	//patas
	glPushMatrix();
	glTranslatef(-7.0, 0.0, 0.5);
	f_Metz.prisma_textura(0.5, 1.0, 0.5, madera1.GLindex);
	glTranslatef(0, 0, -1.0);
	f_Metz.prisma_textura(0.5, 1.0, 0.5, madera1.GLindex);
	glTranslatef(14.0, 0, 0);
	f_Metz.prisma_textura(0.5, 1.0, 0.5, madera1.GLindex);
	glTranslatef(0, 0, 1.0);
	f_Metz.prisma_textura(0.5, 1.0, 0.5, madera1.GLindex);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}

void mesa_comp(GLfloat xPosMes, GLfloat yPosMes, GLfloat zPosMes) {
	glPushMatrix();
	glTranslatef(xPosMes, yPosMes, zPosMes);
	glPushMatrix();
	mesa(0.0, 0.0, 0.0);
	glTranslatef(2.6, 0.3, 0.0);
	glPushMatrix();

	computadora(pantalla1.GLindex);
	glTranslatef(2.1, 0.0, 0.4);
	f_Metz.prisma_textura(1.0, 2.0, 1.8, 0);
	glPopMatrix();

	glTranslatef(-4.0, 0.0, 0.0);
	glPushMatrix();
	computadora(pantalla2.GLindex);
	glTranslatef(2.1, 0.0, 0.4);
	f_Metz.prisma_textura(1.0, 2.0, 1.8, 0);
	glPopMatrix();

	glTranslatef(-4.0, 0.0, 0.0);
	glPushMatrix();
	computadora(pantalla1.GLindex);
	glTranslatef(2.1, 0.0, 0.4);
	f_Metz.prisma_textura(1.0, 2.0, 1.8, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}


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
		f_Metz.prisma_textura(12.0, 6.0, 23.0, maceta.GLindex);
		glPushMatrix();
			glTranslatef(0.0, 3.0, 0.0);
			f_Metz.prisma_textura(12.0, 0.5, 23.0, pasto.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, -3.0, 11.5);
			f_Metz.cilindro(6, 6.0, 60, maceta.GLindex);
				glPushMatrix();
					glTranslatef(0.0, 5.8, 0.0);
					f_Metz.cilindro(6.0, 0.5, 60, pasto.GLindex);
				glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 0.0, -17.0);
			f_Metz.triang(6.0, 12.0, 11.0, maceta.GLindex);
				glPushMatrix();
					glTranslatef(0.0, 2.8, 0.0);
					f_Metz.triang(1.0, 12.0, 11.0, pasto.GLindex);
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
				
				f_hugo.skybox(800.0, 500.0, 600.0, cielo.GLindex); //tamaño del skybox
				glEnable(GL_LIGHTING);
			glPopMatrix();//Creamos cielo
	
			glPushMatrix(); //Creación del Piso/pasto
				glEnable(GL_COLOR_MATERIAL);
				glDisable(GL_LIGHTING);
				glRotatef(90, 0.0, 0.0, 1.0);
				glTranslatef(-30.0, 0.0, 0.0);
				f_hugo.piso(800, 1.5, 600, pasto.GLindex, pasto.GLindex, pasto.GLindex, pasto.GLindex, pasto.GLindex, pasto.GLindex);
				glDisable(GL_COLOR_MATERIAL);
				glEnable(GL_LIGHTING);
			glPopMatrix(); //Creación del Piso/pasto

			//***************************************** metz   ******************************//

			glPushMatrix();//jardinera
				glTranslatef(0, 0, 0);
				glScalef(1.0, 1.5, 1.0);
				jardinera();
			glPopMatrix();//fin plantabaja

			//      ******    salon    *****   //
			mesa_comp(3.9, 0.0, 12.0);
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
				glTranslatef(0, 0, 0);
				glScalef(1.3, 1.3, 1.3);
				pino.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS										
			glPopMatrix();
			
	///////////DIBUJAR
			
			glPushMatrix();//plantabaja
			glTranslatef(0, -20, -35);
			glScalef(1.6, 1, 2);
			platabaja();
			glPopMatrix();//fin plantabaja

			glPushMatrix();//torre1
			glTranslatef(0, -20, -35);
			glScalef(1.6, 1, 2);
			torre1();
			glPopMatrix();//fin torre1

			glPushMatrix();//torre2
			glTranslatef(167, -20, -35);
			glScalef(1.6, 1, 2);
			torre1();
			glPopMatrix();//fin torre2
			

			glPushMatrix(); //Creación del adoquin
				glEnable(GL_COLOR_MATERIAL);
				glDisable(GL_LIGHTING);
				glRotatef(90, 0.0, 0.0, 1.0);
				glTranslatef(-28.0, 0.0, 0.0);
				f_jorge.piso(700, 1.5, 500, adoquin.GLindex, adoquin.GLindex, adoquin.GLindex, adoquin.GLindex, adoquin.GLindex, adoquin.GLindex);
				glDisable(GL_COLOR_MATERIAL);
				glEnable(GL_LIGHTING);
			glPopMatrix(); //Creación del adoquin


	///////////DIBUJAR


	//////////
	glPopMatrix();//Pop para todo el escenario,2


	glPopMatrix();//1
	glutSwapBuffers ( );

}

void animacion()
{
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
		objCamera.Position_Camera(-397.804779f, 293.700104f, -280.190399, -395.4518, 293.700104f, -278.329315,0.0,  1, 0);
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
