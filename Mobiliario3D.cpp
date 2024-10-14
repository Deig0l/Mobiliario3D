#include <windows.h>
#include <cmath>
#include <GL/glut.h>

void inicializacion(void);
void displayMobiliario();
void tecladoMobiliario(unsigned char key, int x, int y);

enum Colores {
	BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GREY, LGREY, DGREY
};

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cubo");
	glutDisplayFunc(displayMobiliario);
	glutKeyboardFunc(tecladoMobiliario);
	inicializacion();
	glutMainLoop();
	return 0;
}

void inicializacion(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void displayMobiliario() {
}

void tecladoMobiliario(unsigned char key, int x, int y) {

}