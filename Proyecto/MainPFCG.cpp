//Semestre 2019-1 Computación gráfica Proyecto Final
//****************************************************************//
//****************************************************************//
//******			Proyecto Final					         *****//
//******			Alumno (s):								 *****//
//******													******//
//******			Metztli				******//
//******			Monterrosas Ramirez Jorge				******//
//******			Landeros Cerecero Diego							******//
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


#define MAX_FRAMES 5
int i_max_steps = 90;
int i_curr_steps = 0;
DWORD dwFrames = 0;
DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;
float  movY = 0.0;
float pirueta = 0.0;
float angRot = 0.0;
float movKitX = 0.0;
float movKitY = 0.0;
float movKitZ = 0.0;
float rotKit = 0.0;
float rotTires = 0.0;
float rotKitv = 0.0;
boolean g_fanimacion = false;
boolean regresa = false;

bool circuito = false;
bool circuito_inverso = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;
bool recorrido1_inv = true;
bool recorrido2_inv = false;
bool recorrido3_inv = false;
bool recorrido4_inv = false;
bool recorrido5_inv = false;
bool recorrido6_inv = false;
bool recorrido7_inv = false;
bool recorrido8_inv = false;
bool g_avanza = false;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ


	float  arriba = 0.0;
	float arribaInc = 0.0;

	



}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 20;			//introducir datos
bool play = false;
int playIndex = 0;
int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];



GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 27.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};


int juego;
int juego1 = 0;
int mundo;
float arriba = 0.0;
float  arribaInc = 0.0;
float horizontal = 0;
float vertical = 1.24;
float profundidad = -25;
float giro = 0;



//Se utilizarán para definir cada figura que el programador cree//

CFiguras f_hugo;

//texturas
CTexture cielo;
CTexture pasto;

//CFiguras fig2;
CModel avion;

////Figuras de 3D Studio
//CModel kit;   //DEclarar modelo 
//CModel llanta;
//
//float rot;
////Animación del coche
//float movKit = 0.0;
//bool g_fanimacion = false;
//bool g_fanimacion2 = false;
bool giro_ventilador = false;
float rotVentilador = 0.0;
			
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
    

	pasto.LoadTGA("Exterior/pasto.tga");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	cielo.LoadTGA("Exterior/cielo.tga");//arriba
	cielo.BuildGLTexture();
	cielo.ReleaseImage();

	




	//fin 


	//objCamera.Position_Camera(0, 2.5f, 3, 0, 10.0f, 0, 1, 1, 0);
	objCamera.Position_Camera(10, 2.5f, 13, 10, 2.5f, 10, 0, 1 , 0);

	for (int i = 0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		
	}


}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
	//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}
	



void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	glPushMatrix();

	glRotatef(g_lookupdown, 1.0f, 0, 0);
	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	f_hugo.skybox(300.0, 220.0, 300.0, cielo.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Creación del Piso/pasto
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(-30.0, 0.0, 0.0);
	f_hugo.piso(300.8, 1.5, 300, pasto.GLindex, pasto.GLindex, pasto.GLindex, pasto.GLindex, pasto.GLindex, pasto.GLindex);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	
	





		glPopMatrix();
		glPopMatrix();//fin
		
	glutSwapBuffers ( );
	
}



void animacion()
{
	if (giro_ventilador) {
		rotVentilador += 1.0;
	}

	// Calculate the number of frames per one second:
	//dwFrames++;
	dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

	if (dwElapsedTime >= 30)
	{
		juego = (juego - 11) % 360;




		dwLastUpdateTime = dwCurrentTime;
	}

	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>FrameIndex - 2)	//end of total animation?
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
			

			}
		}
		else
		{	//Draw information


			arriba += KeyFrame[playIndex].arribaInc;
		



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




	if (circuito)
	{
		if (recorrido1)
		{
			movKitZ++;
			if (movKitZ>550)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2)
		{	
			
			rotKit = 90;
			movKitX++;
			if (movKitX > 305)
			{
				recorrido2 = false;
				recorrido3 = true;

			}
		}
		if (recorrido3)
		{
			rotKit = 180;
			pirueta += 5.0;
			movY--;
			movKitZ--;
			printf("%f", movY);
			if (movY < -60) {

				movY ++;
				printf("%f", movY);

				if (movKitZ < -305)
				{
					recorrido3 = false;
					recorrido4 = true;
				}
			}
		}
		if (recorrido4)
		{
			rotKit = 270;
			movKitX--;
			if (movKitX<0)
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}
		if (recorrido5)
		{
			rotKit = 0;
			movKitZ++;
			if (movKitZ>0)
			{
				recorrido5 = false;
				recorrido1 = true;
			}
		}
	}



	glutPostRedisplay();
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
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 400.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.4);

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

	case 'v':
	case 'V':
		giro_ventilador ^= true;
		break;
	case 'u':
	case 'U':
		
		giro_ventilador ^= true;
		break;

	case't':
	case'T':
		circuito ^= true; //Activamos/desactivamos la animacíon
		g_fanimacion = false;
		break;
	case'l':
	case'L':
		if (play == false && (FrameIndex > 1))
		{

			arriba = KeyFrame[0].arriba;
		

			//First Interpolation


			KeyFrame[playIndex].arribaInc = (KeyFrame[playIndex + 1].arriba - KeyFrame[playIndex].arriba) / i_max_steps;
			

			
			//KeyFrame[playIndex].tije2Inc = (KeyFrame[playIndex + 1].tije2 - KeyFrame[playIndex].tije2) / i_max_steps;

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

		break;


	
		//case ' ':		//Poner algo en movimiento
		//	g_fanimacion = true; //Activamos/desactivamos la animacíon
		//	break;

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


/*
	//		glPushMatrix();
	//			//Para que el coche conserve sus colores
	//				glDisable(GL_COLOR_MATERIAL);
	//				glRotatef(90, 0, 1, 0);
	//				glScalef(0.3, 0.3, 0.3);

	//				if (movKit > 100)
	//				{
	//					g_fanimacion = false;
	//					g_fanimacion2 = true;
	//				
	//				}

	//				if (movKit == 0)
	//				{
	//					g_fanimacion2 = false;
	//					g_fanimacion = false;
	//				}


	//				glTranslatef(0, 4, movKit); //movkit
	//				//Pongo aquí la carroceria del carro
	//				kit.GLrender(NULL,_SHADED,1.0);  //_WIRED O _POINTS //Mandar a llamar al carro

	//				glPushMatrix();
	//					glTranslatef(-6.0, -1.0, 7.5);
	//					glRotatef(rot, 1, 0, 0);
	//					llanta.GLrender(NULL,_SHADED,1.0); //LLanta del lado derecho
	//				glPopMatrix();

	//				glPushMatrix();
	//					glTranslatef(6.0, -1.0, 7.5); //Lanta izquierda
	//					glRotatef(180, 0, 1, 0);
	//					glRotatef(-rot, 1, 0, 0);
	//					llanta.GLrender(NULL, _SHADED, 1.0);
	//				glPopMatrix();

	//				glPushMatrix();
	//					glTranslatef(6.0, -1.0, -9.5);//Lanta trasera
	//					glRotatef(180, 0, 1, 0);
	//					glRotatef(-rot, 1, 0, 0);
	//					llanta.GLrender(NULL, _SHADED, 1.0);
	//				glPopMatrix();

	//				glPushMatrix();
	//					glTranslatef(-6.0, -1.0, -9.5); //Llanta trasera
	//					glRotatef(rot, 1, 0, 0);
	//					llanta.GLrender(NULL, _SHADED, 1.0);
	//				glPopMatrix();
	//		glPopMatrix();

	//		//Para que el comando glColor funcione con iluminacion
	//		glEnable(GL_COLOR_MATERIAL);
	//		
	//	glPopMatrix();
	//glPopMatrix();*/



	//			casa();
	//			//glPushMatrix();
	//			//	glEnable(GL_BLEND); //Para las ventanas usar esto
	//			//	glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_COLOR);
	//			//	glRotatef(90, 1.0, 0.0, 0.0);
	//			//	glTranslatef(0.0, 0.0, 0.0);
	//			//	f_enrique.prisma(5.0,8.0,3.0,ventana.GLindex);
	//			//	glDisable(GL_BLEND);
	//			//glPopMatrix();