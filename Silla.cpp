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
//void silla(float x, float y, float z);
//
//float angle = 0.0;
//int lado = 3;
//int height = 1;
//int depht = 7;
//int mode = 1;
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
//	glutCreateWindow("Silla 3D");
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
//	silla(0.0, 0.0, 0.0);
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
//		/*case 49:
//			mode = 1;
//			break;
//		case 50:
//			mode = 2;
//			break;*/
//	case 27:
//		exit(1);
//		break;
//	case 'x':
//		// aqui  se procesa la tecla <x>
//		glRotatef(5.0, 1.0, 0.0, 0.0);//cada que se preciona x, rota 5 grados
//		break;
//	case 'X':
//		// aqui  se procesa la tecla <X>
//		glRotatef(-5.0, 1.0, 0.0, 0.0);//cada que se preciona x, rota 5 grados
//		break;
//	case 'y':
//		// aqui  se procesa la tecla <y>
//		glRotatef(5.0, 0.0, 1.0, 0.0);
//		break;
//	case 'Y':
//		// aqui  se procesa la tecla <Y>
//		glRotatef(-5.0, 0.0, 1.0, 0.0);
//		break;
//	case 'z':
//		// aqui  se procesa la tecla <z>
//		glRotatef(5.0, 0.0, 0.0, 1.0);
//		break;
//	case 'Z':
//		// aqui  se procesa la tecla <Z>
//		glRotatef(-5.0, 0.0, 0.0, 1.0);
//		break;
//	case 'e':
//		// aqui  se procesa la tecla <e>
//		glRotatef(5.0, 1.0, 1.0, 1.0);
//		break;
//	case 'r':
//		// aqui  se procesa la tecla <r>
//		glLoadIdentity();//resetea los buffers
//		angle = 0.0;
//		break;
//	case 'a':
//		// aqui  se procesa la tecla <a>
//		angle += 5;
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
//void silla(float x, float y, float z) {
//	// Asiento
//	prisma(1.4, 0.2, 1.0, x - 1.0, y, z, DGREY);
//	// Patas
//	prisma(0.2, 1.0, 0.2, x - 1.0, y - 1.0, z, GREY);
//	prisma(0.2, 1.0, 0.2, x + 0.2, y - 1.0, z, GREY);
//	prisma(0.2, 1.4, 0.2, x - 1.0, y - 1.0, z - 1.0, GREY);
//	prisma(0.2, 1.4, 0.2, x + 0.2, y - 1.0, z - 1.0, GREY);
//	// Respaldo
//	prisma(1.4, 1.0, 0.2, x - 1.0, y + 0.4, z - 1.0, DGREY);
//}
