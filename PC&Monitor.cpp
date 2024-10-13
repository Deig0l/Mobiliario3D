//#include "stdafx.h"
#include <windows.h>
#include <cmath>
#include <GL/glut.h>

enum Colores {
	BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GREY, LGREY, DGREY
};

void asignarColor(Colores color);
void inicializacion(void);
void display_cb(void);
void plano3D();
void teclado_cb(GLubyte key, GLint x, GLint y);
void circulo(double r, float x, float y, float z, Colores color);
void cubo(int l);
void prisma(float l, float h, float d, float x, float y, float z, Colores color);
void prismaMulticolor(float l, float h, float d, float x, float y, float z,
	Colores cf, Colores cp, Colores ci, Colores cs, Colores cli, Colores cld);
void monitor(float x, float y, float z);

float angle = 0.0;
int lado = 3;
int height = 1;
int depht = 7;
int mode = 1;
float facEsc = 1;

void asignarColor(Colores color) {
	switch (color) {
	case BLACK:
		glColor3f(0.0, 0.0, 0.0);
		break;
	case WHITE:
		glColor3f(1.0, 1.0, 1.0);
		break;
	case RED:
		glColor3f(1.0, 0.0, 0.0);
		break;
	case GREEN:
		glColor3f(0.0, 1.0, 0.0);
		break;
	case BLUE:
		glColor3f(0.0, 0.0, 1.0);
		break;
	case YELLOW:
		glColor3f(1.0, 1.0, 0.0);
		break;
	case MAGENTA:
		glColor3f(1.0, 0.0, 1.0);
		break;
	case CYAN:
		glColor3f(0.0, 1.0, 1.0);
		break;
	case GREY:
		glColor3f(0.5, 0.5, 0.5);
		break;
	case LGREY:
		glColor3f(0.6, 0.6, 0.6);
		break;
	case DGREY:
		glColor3f(0.2, 0.2, 0.2);
		break;
	default:
		break;
	}
};

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cubo");
	glutDisplayFunc(display_cb); //Despliega
	glutKeyboardFunc(teclado_cb); //Controla teclado
	inicializacion();
	glutMainLoop();
	return 0;
}
void inicializacion(void) {
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void display_cb(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	plano3D();
	glPushMatrix();
	switch (mode) {
	case 1:
		glScalef(facEsc, facEsc, facEsc);
		prismaMulticolor(1.6, 3.0, 3.8, 0, 0, -0.2, DGREY, DGREY, DGREY, DGREY, DGREY, DGREY);
		prismaMulticolor(1.6, 3.0, 0.2, 0, 0, 0, GREY, GREY, GREY, GREY, GREY, GREY);
		circulo(0.2, 2.0, 1.0, 0, BLUE);
		break;
	case 2:
		glScalef(facEsc, facEsc, facEsc);
		monitor(0, 0, 0);
		break;
	}
	glPopMatrix();
	glutSwapBuffers();
}

void plano3D() {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3i(0, 0, -20);
	glVertex3i(0, 0, 20);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3i(-20, 0, 0);
	glVertex3i(20, 0, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3i(0, -20, 0);
	glVertex3i(0, 20, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3i(0, 0, -20);
	glVertex3i(0, 0, 20);
	glEnd();
	glFlush();
}

void teclado_cb(GLubyte key, GLint x, GLint y) {
	switch (key) {
	case 49:
		mode = 1;
		break;
	case 50:
		mode = 2;
		break;
	case 27:
		exit(1);
		break;
	case 'x':
		// aqui  se procesa la tecla <x>
		glRotatef(5.0, 1.0, 0.0, 0.0);//cada que se preciona x, rota 5 grados
		break;
	case 'X':
		// aqui  se procesa la tecla <X>
		glRotatef(-5.0, 1.0, 0.0, 0.0);//cada que se preciona x, rota 5 grados
		break;
	case 'y':
		// aqui  se procesa la tecla <y>
		glRotatef(5.0, 0.0, 1.0, 0.0);
		break;
	case 'Y':
		// aqui  se procesa la tecla <Y>
		glRotatef(-5.0, 0.0, 1.0, 0.0);
		break;
	case 'z':
		// aqui  se procesa la tecla <z>
		glRotatef(5.0, 0.0, 0.0, 1.0);
		break;
	case 'Z':
		// aqui  se procesa la tecla <Z>
		glRotatef(-5.0, 0.0, 0.0, 1.0);
		break;
	case 'e':
		// aqui  se procesa la tecla <e>
		glRotatef(5.0, 1.0, 1.0, 1.0);
		break;
	case 'r':
		// aqui  se procesa la tecla <r>
		glLoadIdentity();//resetea los buffers
		angle = 0.0;
		break;
	case 'a':
		// aqui  se procesa la tecla <a>
		angle += 5;
		break;
	case '+':
		if (facEsc < 2)
			facEsc += 0.1;
		break;
	case '-':
		if (facEsc > 0.1)
			facEsc -= 0.1;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void circulo(double r, float x, float y, float z, Colores color) {
	double pi = 3.14159265358979323846;
	asignarColor(color);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x, y, z);
	for (int i = 0; i <= 100; i++) {
		float theta = 2.0f * pi * float(i) / 100.f;
		float dx = r * cosf(theta);
		float dy = r * sinf(theta);
		glVertex3f(x + dx, y + dy, z);
	}
	glEnd();
}

void cubo(int l)
{
	//Cara frontal
	asignarColor(RED);
	//glColor3f(1.0, 0.0, 0.0);//rojo
	glBegin(GL_QUADS);
	glVertex3i(-l, -l, l);
	glVertex3i(-l, l, l);
	glVertex3i(l, l, l);
	glVertex3i(l, -l, l);
	glEnd();
	//Cara posterior
	asignarColor(GREEN);
	//glColor3f(0.0, 1.0, 0.0);//verde
	glBegin(GL_QUADS);
	glVertex3i(-l, -l, -l);
	glVertex3i(-l, l, -l);
	glVertex3i(l, l, -l);
	glVertex3i(l, -l, -l);
	glEnd();
	//Cara inferior
	asignarColor(BLUE);
	//glColor3f(0.0, 0.0, 1.0);//azul
	glBegin(GL_QUADS);
	glVertex3i(-l, -l, l);
	glVertex3i(-l, -l, -l);
	glVertex3i(l, -l, -l);
	glVertex3i(l, -l, l);
	glEnd();
	//Cara superior
	asignarColor(MAGENTA);
	//glColor3f(1.0, 0.0, 1.0);//magenta
	glBegin(GL_QUADS);
	glVertex3i(-l, l, l);
	glVertex3i(-l, l, -l);
	glVertex3i(l, l, -l);
	glVertex3i(l, l, l);
	glEnd();
	//Cara lateral izquierda
	asignarColor(YELLOW);
	//glColor3f(1.0, 1.0, 0.0);//amarillo
	glBegin(GL_QUADS);
	glVertex3i(-l, -l, l);
	glVertex3i(-l, l, l);
	glVertex3i(-l, l, -l);
	glVertex3i(-l, -l, -l);
	glEnd();
	//Cara lateral derecha
	asignarColor(CYAN);
	//glColor3f(0.0, 1.0, 1.0);//cyan
	glBegin(GL_QUADS);
	glVertex3i(l, -l, l);
	glVertex3i(l, l, l);
	glVertex3i(l, l, -l);
	glVertex3i(l, -l, -l);
	glEnd();
}

void prisma(float l, float h, float d, float x, float y, float z, Colores color) {
	asignarColor(color);
	//Cara frontal
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x, y + h, z);
	glVertex3f(x + l, y + h, z);
	glVertex3f(x + l, y, z);
	glEnd();
	//Cara posterior
	glBegin(GL_QUADS);
	glVertex3f(x, y, z - d);
	glVertex3f(x, y + h, z - d);
	glVertex3f(x + l, y + h, z - d);
	glVertex3f(x + l, y, z - d);
	glEnd();
	//Cara inferior
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z - d);
	glVertex3f(x + l, y, z - d);
	glVertex3f(x + l, y, z);
	glEnd();
	//Cara superior
	glBegin(GL_QUADS);
	glVertex3f(x, y + h, z);
	glVertex3f(x, y + h, z - d);
	glVertex3f(x + l, y + h, z - d);
	glVertex3f(x + l, y + h, z);
	glEnd();
	//Cara lateral izquierda
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x, y + h, z);
	glVertex3f(x, y + h, z - d);
	glVertex3f(x, y, z - d);
	glEnd();
	//Cara lateral derecha
	glBegin(GL_QUADS);
	glVertex3f(x + l, y, z);
	glVertex3f(x + l, y + h, z);
	glVertex3f(x + l, y + h, z - d);
	glVertex3f(x + l, y, z - d);
	glEnd();
}

void prismaMulticolor(float l, float h, float d, float x, float y, float z,
	Colores cf, Colores cp, Colores ci, Colores cs, Colores cli, Colores cld) {
	//Cara frontal
	asignarColor(cf);
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x, y + h, z);
	glVertex3f(x + l, y + h, z);
	glVertex3f(x + l, y, z);
	glEnd();
	//Cara posterior
	asignarColor(cp);
	glBegin(GL_QUADS);
	glVertex3f(x, y, z - d);
	glVertex3f(x, y + h, z - d);
	glVertex3f(x + l, y + h, z - d);
	glVertex3f(x + l, y, z - d);
	glEnd();
	//Cara inferior
	asignarColor(ci);
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z - d);
	glVertex3f(x + l, y, z - d);
	glVertex3f(x + l, y, z);
	glEnd();
	//Cara superior
	asignarColor(cs);
	glBegin(GL_QUADS);
	glVertex3f(x, y + h, z);
	glVertex3f(x, y + h, z - d);
	glVertex3f(x + l, y + h, z - d);
	glVertex3f(x + l, y + h, z);
	glEnd();
	//Cara lateral izquierda
	asignarColor(cli);
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x, y + h, z);
	glVertex3f(x, y + h, z - d);
	glVertex3f(x, y, z - d);
	glEnd();
	//Cara lateral derecha
	asignarColor(cld);
	glBegin(GL_QUADS);
	glVertex3f(x + l, y, z);
	glVertex3f(x + l, y + h, z);
	glVertex3f(x + l, y + h, z - d);
	glVertex3f(x + l, y, z - d);
	glEnd();
}

void monitor(float x, float y, float z) {
	//Base
	prisma(1.6, 0.2, 1.4, 1.2 + x, 0 + y, 0 + z, GREY);
	//Pantalla
	prismaMulticolor(4.0, 3.0, 0.2, 0 + x, 1.0 + y, -0.5 + z, BLACK, GREY, GREY, GREY, GREY, GREY);
	//Marco horizontal inferior
	prismaMulticolor(4.0, 0.2, 0.2, 0 + x, 1.0 + y, -0.3 + z, GREY, GREY, GREY, DGREY, GREY, GREY);
	//Marco horizontal superior
	prismaMulticolor(4.0, 0.2, 0.2, 0 + x, 3.8 + y, -0.3 + z, GREY, GREY, DGREY, GREY, GREY, GREY);
	//Marco vertical izquierdo
	prismaMulticolor(0.2, 2.6, 0.2, 0 + x, 1.2 + y, -0.3 + z, GREY, GREY, GREY, GREY, GREY, DGREY);
	//Marco vertical derecho
	prismaMulticolor(0.2, 2.6, 0.2, 3.8 + x, 1.2 + y, -0.3 + z, GREY, GREY, GREY, GREY, DGREY, GREY);
	//Cuello
	prisma(0.8, 2.0, 0.3, 1.6 + x, 0.2 + y, -0.7 + z, DGREY);
}
