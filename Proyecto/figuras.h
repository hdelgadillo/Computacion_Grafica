//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void prisma_textura(float altura, float largo, float profundidad, GLuint text);
	void piso(float altura, float largo, float profundidad, GLuint front, GLuint right, GLuint back, GLuint left, GLuint bottom, GLuint top);
	void triang(float altura, float largo, float profundidad, GLuint text);
	void prismaExterior(float altura, float largo, float profundidad, GLuint text, float x, GLuint text2, GLuint text3);  //Funcion creacion prisma
	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Func�on creacion esfera
	void media_esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Func�on creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Func�on creacion cilindro
	void cono(float altura, float radio, int resolucion, GLuint text);		//Func�on creacion cono
	void prisma_anun (GLuint text, GLuint text2);							//Func�on creacion movimiento
	void prisma (float altura, float largo, float profundidad, GLuint text, float x);//Func�on creacion prisma
	void prisma2 (GLuint text, GLuint text2);
	void skybox(float altura, float largo, float profundidad, GLuint text);	//Funcion creacion cielo
	void skybox2 (float altura, float largo, float profundidad, GLuint text);
	void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos);
	void prisma_textura1(float largo, float altura, float profundidad, GLuint text, GLuint text2);
	void cilindro1(float radio, float altura, int resolucion, GLuint text, GLuint text2, GLuint text3);
};
