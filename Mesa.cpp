//#include <windows.h>
//#include <cmath>
//#include <GL/glut.h>
//
//enum Colores {
//	BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GREY, LGREY, DGREY
//};
//
//// Prototipos de funciones
//void asignarColor(Colores color);
//void inicializacion(void);
//void display_cb(void);
//void plano3D();
//void teclado_cb(GLubyte key, GLint x, GLint y);
//void prisma(float l, float h, float d, float x, float y, float z, Colores color);
//void mesa(float x, float y, float z);
//
//float angle = 0.0;
//float facEsc = 1;
//
//void asignarColor(Colores color) {
//	switch (color) {
//	case BLACK: glColor3f(0.0, 0.0, 0.0); break;
//	case WHITE: glColor3f(1.0, 1.0, 1.0); break;
//	case RED: glColor3f(1.0, 0.0, 0.0); break;
//	case GREEN: glColor3f(0.0, 1.0, 0.0); break;
//	case BLUE: glColor3f(0.0, 0.0, 1.0); break;
//	case YELLOW: glColor3f(1.0, 1.0, 0.0); break;
//	case MAGENTA: glColor3f(1.0, 0.0, 1.0); break;
//	case CYAN: glColor3f(0.0, 1.0, 1.0); break;
//	case GREY: glColor3f(0.5, 0.5, 0.5); break;
//	case LGREY: glColor3f(0.6, 0.6, 0.6); break;
//	case DGREY: glColor3f(0.2, 0.2, 0.2); break;
//	default: break;
//	}
//}
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(500, 500);
//	glutCreateWindow("Mesa 3D");
//	glutDisplayFunc(display_cb);
//	glutKeyboardFunc(teclado_cb);
//	inicializacion();
//	glutMainLoop();
//	return 0;
//}
//
//void inicializacion(void) {
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
//	glMatrixMode(GL_MODELVIEW);
//	glEnable(GL_DEPTH_TEST);
//}
//
//void display_cb(void) {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	plano3D();
//	glPushMatrix();
//	glScalef(facEsc, facEsc, facEsc);
//	mesa(0.0, 0.0, 0.0);
//	glPopMatrix();
//	glutSwapBuffers();
//}
//
//void plano3D() {
//	glBegin(GL_LINES);
//	glColor3f(1.0, 0.0, 1.0); glVertex3i(0, 0, -20); glVertex3i(0, 0, 20);
//	glColor3f(1.0, 0.0, 0.0); glVertex3i(-20, 0, 0); glVertex3i(20, 0, 0);
//	glColor3f(0.0, 1.0, 0.0); glVertex3i(0, -20, 0); glVertex3i(0, 20, 0);
//	glEnd();
//	glFlush();
//}
//
//void teclado_cb(GLubyte key, GLint x, GLint y) {
//	switch (key) {
//	case 27:
//		exit(1);
//		break;
//	case 'x':
//		glRotatef(5.0, 1.0, 0.0, 0.0);
//		break;
//	case 'X':
//		glRotatef(-5.0, 1.0, 0.0, 0.0);
//		break;
//	case 'y':
//		glRotatef(5.0, 0.0, 1.0, 0.0);
//		break;
//	case 'Y':
//		glRotatef(-5.0, 0.0, 1.0, 0.0);
//		break;
//	case 'z':
//		glRotatef(5.0, 0.0, 0.0, 1.0);
//		break;
//	case 'Z':
//		glRotatef(-5.0, 0.0, 0.0, 1.0);
//		break;
//	case '+':
//		if (facEsc < 2)
//			facEsc += 0.1;
//		break;
//	case '-':
//		if (facEsc > 0.1)
//			facEsc -= 0.1;
//		break;
//	default:
//		break;
//	}
//	glutPostRedisplay();
//}
//
//void prisma(float l, float h, float d, float x, float y, float z, Colores color) {
//	asignarColor(color);
//	glBegin(GL_QUADS);
//	// Cara frontal
//	glVertex3f(x, y, z);
//	glVertex3f(x, y + h, z);
//	glVertex3f(x + l, y + h, z);
//	glVertex3f(x + l, y, z);
//	glEnd();
//	// Cara posterior
//	glBegin(GL_QUADS);
//	glVertex3f(x, y, z - d);
//	glVertex3f(x, y + h, z - d);
//	glVertex3f(x + l, y + h, z - d);
//	glVertex3f(x + l, y, z - d);
//	glEnd();
//	// Cara inferior
//	glBegin(GL_QUADS);
//	glVertex3f(x, y, z);
//	glVertex3f(x, y, z - d);
//	glVertex3f(x + l, y, z - d);
//	glVertex3f(x + l, y, z);
//	glEnd();
//	// Cara superior
//	glBegin(GL_QUADS);
//	glVertex3f(x, y + h, z);
//	glVertex3f(x, y + h, z - d);
//	glVertex3f(x + l, y + h, z - d);
//	glVertex3f(x + l, y + h, z);
//	glEnd();
//	// Lados
//	glBegin(GL_QUADS);
//	glVertex3f(x, y, z);
//	glVertex3f(x, y + h, z);
//	glVertex3f(x, y + h, z - d);
//	glVertex3f(x, y, z - d);
//	glEnd();
//	glBegin(GL_QUADS);
//	glVertex3f(x + l, y, z);
//	glVertex3f(x + l, y + h, z);
//	glVertex3f(x + l, y + h, z - d);
//	glVertex3f(x + l, y, z - d);
//	glEnd();
//}
//
//void mesa(float x, float y, float z) {
//	// Tablero de la mesa
//	prisma(5.0, 0.2, 2.5, x - 2.5, y, z, GREY);
//
//	prisma(0.2, 0.4, 2.5, x - 2.4, y - 3.0, z + 0.2, BLACK); // Pata acostada ajustada
//	prisma(0.2, 0.4, 2.5, x + 2.2, y - 3.0, z + 0.2, BLACK); // Pata acostada ajustada
//
//	prisma(0.2, 3.0, 0.6, x - 2.4, y - 3.0, z + 0.0, DGREY); // Pata de la mesa Izquierda
//	prisma(0.2, 3.0, 0.6, x + 2.2, y - 3.0, z + 0.0, DGREY); // Pata de la mesa Derecha
//
//	// Rectángulo negro
//	prisma(4.8, 1.4, 0.1, x - 2.4, y - 1.4, z - 0.05, BLACK);
//}
