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

#include "cmodel/CModel.h"

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
CTexture adoquin;

//Se utilizarán para definir cada figura que el programador cree//
CFiguras f_jorge;
CFiguras f_hugo;
CFiguras f_diego;
CFiguras f_metz;

			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable ( GL_COLOR_MATERIAL );

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On
    

	/*TEXTURAS*/
    
	cielo.LoadTGA("Exterior/cielo.tga");
	cielo.BuildGLTexture();
	cielo.ReleaseImage();

	pasto.LoadTGA("Exterior/pasto.tga");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	adoquin.LoadTGA("Exterior/adoquin.tga");
	adoquin.BuildGLTexture();
	adoquin.ReleaseImage();	

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

	///////////DIBUJAR
			glPushMatrix(); //Creación del adoquin
				glEnable(GL_COLOR_MATERIAL);
				glDisable(GL_LIGHTING);
				glRotatef(90, 0.0, 0.0, 1.0);
				glTranslatef(-28.0, 0.0, 0.0);
				f_jorge.piso(700, 1.5, 500, adoquin.GLindex, adoquin.GLindex, adoquin.GLindex, adoquin.GLindex, adoquin.GLindex, adoquin.GLindex);
				glDisable(GL_COLOR_MATERIAL);
				glEnable(GL_LIGHTING);
			glPopMatrix(); //Creación del adoquin
	//////////
	glPopMatrix();//Pop para todo el escenario,2


	glPopMatrix();
	glutSwapBuffers ( );

}

void animacion()
{
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
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.4 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.4));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
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
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );
  glutMainLoop        ( );          // 

  return 0;
}
