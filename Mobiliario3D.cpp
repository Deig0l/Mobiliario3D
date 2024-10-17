//#include <windows.h>
//#include <cmath>
//#include <GL/glut.h>
//
//enum Colores {
//	BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GREY, LGREY, DGREY
//};
//
//float angulox = 0.0f;
//float anguloy = 0.0f;
//float anguloz = 0.0f;
//float facEsc = 1;
//
//void inicializacion(void);
//void displayMobiliario();
//void tecladoMobiliario(unsigned char key, int x, int y);
//void ejes3D();
//void asignarColor(Colores color);
//void prisma(float l, float h, float d, float x, float y, float z, Colores color);
//void prismaMulticolor(float l, float h, float d, float x, float y, float z,
//	Colores cf, Colores cp, Colores ci, Colores cs, Colores cli, Colores cld);
//void monitor(float x, float y, float z);
//void pc(float x, float y, float z);
//void mouse(float x, float y, float z);
//void keyboard(float x, float y, float z);
//void mesa(float x, float y, float z);
//void silla(float x, float y, float z);
//void unidadMobiliario(float x, float y, float z);
//void generarMobiSalon(float x, float y, float z, int filas, int mesas, float espaciado);
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(600, 600);
//	glutCreateWindow("Mobiliario 3D");
//	glutDisplayFunc(displayMobiliario);
//	glutKeyboardFunc(tecladoMobiliario);
//	inicializacion();
//	glutMainLoop();
//	return 0;
//}
//
//void inicializacion(void) {
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
//	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
//	glMatrixMode(GL_MODELVIEW);
//	glEnable(GL_DEPTH_TEST);
//}
//
//void displayMobiliario() {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//	glPushMatrix();
//
//	glRotatef(angulox, 1.0, 0.0, 0.0);
//	glRotatef(anguloy, 0.0, 1.0, 0.0);
//	glRotatef(anguloz, 0.0, 0.0, 1.0);
//
//	glScalef(facEsc, facEsc, facEsc);
//
//	ejes3D();
//	
//	generarMobiSalon(0.0, 0.0, 0.0, 9, 7, 2.0);
//	//generarMobiSalon(-3.0, 0.0, -4.0, 2, 3, 2.0);
//		
//	glPopMatrix();
//
//	glutSwapBuffers();
//}
//
//void tecladoMobiliario(unsigned char key, int x, int y) {
//	switch (key) {
//			case 27:
//				exit(1);
//				break;
//			case 'r':
//				//Se limpian los angulos
//				angulox = 0;
//				anguloy = 0;
//				anguloz = 0;
//				facEsc = 1;
//				glLoadIdentity();
//				break;
//			case '+':
//				facEsc += 0.1;
//				break;
//			case '-':
//				facEsc -= 0.1;
//				break;
//			case 'x':
//				angulox += 5.0;
//				break;
//			case 'y':
//				anguloy += 5.0;
//				break;
//			case 'z':
//				anguloz += 5.0;
//				break;
//			case 'X':
//				angulox -= 5.0;
//				break;
//			case 'Y':
//				anguloy -= 5.0;
//				break;
//			case 'Z':
//				anguloz -= 5.0;
//				break;
//	}
//	glutPostRedisplay();
//}
//
//void ejes3D() {
//	//Lineas de los ejes
//	glBegin(GL_LINES);
//
//	//Eje x
//	glColor3f(1, 0, 0);//rojo
//	glVertex3f(-300, 0, 0);
//	glVertex3f(300, 0, 0);
//
//	//Eje y
//	glColor3f(0, 1, 0);//verde
//	glVertex3f(0, -300, 0);
//	glVertex3f(0, 300, 0);
//
//	//Eje z
//	glColor3f(0, 0, 1);//azul
//	glVertex3f(0, 0, -300);
//	glVertex3f(0, 0, 300);
//
//	glEnd();
//}
//
//void asignarColor(Colores color) {
//	switch (color) {
//	case BLACK:
//		glColor3f(0.0, 0.0, 0.0);
//		break;
//	case WHITE:
//		glColor3f(1.0, 1.0, 1.0);
//		break;
//	case RED:
//		glColor3f(1.0, 0.0, 0.0);
//		break;
//	case GREEN:
//		glColor3f(0.0, 1.0, 0.0);
//		break;
//	case BLUE:
//		glColor3f(0.0, 0.0, 1.0);
//		break;
//	case YELLOW:
//		glColor3f(1.0, 1.0, 0.0);
//		break;
//	case MAGENTA:
//		glColor3f(1.0, 0.0, 1.0);
//		break;
//	case CYAN:
//		glColor3f(0.0, 1.0, 1.0);
//		break;
//	case GREY:
//		glColor3f(0.5, 0.5, 0.5);
//		break;
//	case LGREY:
//		glColor3f(0.6, 0.6, 0.6);
//		break;
//	case DGREY:
//		glColor3f(0.2, 0.2, 0.2);
//		break;
//	default:
//		break;
//	}
//};
//
////Una unidad son 10cm para los primas
//void prisma(float l, float h, float d, float x, float y, float z, Colores color) {
//	asignarColor(color);
//	//Cara frontal
//	glBegin(GL_QUADS);
//	glVertex3f(x, y, z);
//	glVertex3f(x, y + h, z);
//	glVertex3f(x + l, y + h, z);
//	glVertex3f(x + l, y, z);
//	glEnd();
//	//Cara posterior
//	glBegin(GL_QUADS);
//	glVertex3f(x, y, z - d);
//	glVertex3f(x, y + h, z - d);
//	glVertex3f(x + l, y + h, z - d);
//	glVertex3f(x + l, y, z - d);
//	glEnd();
//
//
//	//Cara inferior
//	glBegin(GL_QUADS);
//	glVertex3f(x, y, z);
//	glVertex3f(x, y, z - d);
//	glVertex3f(x + l, y, z - d);
//	glVertex3f(x + l, y, z);
//	glEnd();
//	//Cara superior
//	glBegin(GL_QUADS);
//	glVertex3f(x, y + h, z);
//	glVertex3f(x, y + h, z - d);
//	glVertex3f(x + l, y + h, z - d);
//	glVertex3f(x + l, y + h, z);
//	glEnd();
//	//Cara lateral izquierda
//	glBegin(GL_QUADS);
//	glVertex3f(x, y, z);
//	glVertex3f(x, y + h, z);
//	glVertex3f(x, y + h, z - d);
//	glVertex3f(x, y, z - d);
//	glEnd();
//	//Cara lateral derecha
//	glBegin(GL_QUADS);
//	glVertex3f(x + l, y, z);
//	glVertex3f(x + l, y + h, z);
//	glVertex3f(x + l, y + h, z - d);
//	glVertex3f(x + l, y, z - d);
//	glEnd();
//}
//
//void prismaMulticolor(float l, float h, float d, float x, float y, float z,
//	Colores cf, Colores cp, Colores ci, Colores cs, Colores cli, Colores cld) {
//	//Cara frontal
//	asignarColor(cf);
//	glBegin(GL_QUADS);
//	glVertex3f(x, y, z);
//	glVertex3f(x, y + h, z);
//	glVertex3f(x + l, y + h, z);
//	glVertex3f(x + l, y, z);
//	glEnd();
//	//Cara posterior
//	asignarColor(cp);
//	glBegin(GL_QUADS);
//	glVertex3f(x, y, z - d);
//	glVertex3f(x, y + h, z - d);
//	glVertex3f(x + l, y + h, z - d);
//	glVertex3f(x + l, y, z - d);
//	glEnd();
//	//Cara inferior
//	asignarColor(ci);
//	glBegin(GL_QUADS);
//	glVertex3f(x, y, z);
//	glVertex3f(x, y, z - d);
//	glVertex3f(x + l, y, z - d);
//	glVertex3f(x + l, y, z);
//	glEnd();
//	//Cara superior
//	asignarColor(cs);
//	glBegin(GL_QUADS);
//	glVertex3f(x, y + h, z);
//	glVertex3f(x, y + h, z - d);
//	glVertex3f(x + l, y + h, z - d);
//	glVertex3f(x + l, y + h, z);
//	glEnd();
//	//Cara lateral izquierda
//	asignarColor(cli);
//	glBegin(GL_QUADS);
//	glVertex3f(x, y, z);
//	glVertex3f(x, y + h, z);
//	glVertex3f(x, y + h, z - d);
//	glVertex3f(x, y, z - d);
//	glEnd();
//	//Cara lateral derecha
//	asignarColor(cld);
//	glBegin(GL_QUADS);
//	glVertex3f(x + l, y, z);
//	glVertex3f(x + l, y + h, z);
//	glVertex3f(x + l, y + h, z - d);
//	glVertex3f(x + l, y, z - d);
//	glEnd();
//}
//
//void monitor(float x, float y, float z) {
//	//Base
//	prismaMulticolor(1.6, 0.2, 1.4, 1.2 + x, 0.0 + y, 0.0 + z, DGREY, DGREY, GREY, GREY, DGREY,DGREY);
//	//Pantalla
//	prismaMulticolor(4.0, 3.0, 0.2, 0 + x, 1.0 + y, -0.5 + z, BLACK, GREY, GREY, GREY, GREY, GREY);
//	//Marco horizontal inferior
//	prismaMulticolor(4.0, 0.2, 0.2, 0 + x, 1.0 + y, -0.3 + z, GREY, GREY, GREY, DGREY, GREY, GREY);
//	//Marco horizontal superior
//	prismaMulticolor(4.0, 0.2, 0.2, 0 + x, 3.8 + y, -0.3 + z, GREY, GREY, DGREY, GREY, GREY, GREY);
//	//Marco vertical izquierdo
//	prismaMulticolor(0.2, 2.6, 0.2, 0 + x, 1.2 + y, -0.3 + z, GREY, GREY, GREY, GREY, GREY, DGREY);
//	//Marco vertical derecho
//	prismaMulticolor(0.2, 2.6, 0.2, 3.8 + x, 1.2 + y, -0.3 + z, GREY, GREY, GREY, GREY, DGREY, GREY);
//	//Cuello
//	prisma(0.8, 2.0, 0.3, 1.6 + x, 0.2 + y, -0.7 + z, DGREY);
//}
//
//void pc(float x, float y, float z) {
//	//Prisma principal
//	prisma(2.0, 3.5, 3.8, 0.0 + x, 0.0 + y, -0.2 + z, DGREY);
//	//Prisma gris frontal
//	prisma(2.0, 3.5, 0.2, 0.0 + x, 0.0 + y, 0.0 + z, GREY);
//	//Ranura superior
//	prisma(1.6, 0.4, 0.1, 0.2 + x, 2.9 + y, 0.01 + z, LGREY);
//	//Ranura media
//	prisma(1.6, 0.4, 0.1, 0.2 + x, 2.3 + y, 0.01 + z, LGREY);
//	//Ranura inferior
//	prisma(1.6, 0.4, 0.1, 0.2 + x, 1.7 + y, 0.01 + z, LGREY);
//	//Ranura posterior
//	prisma(1.6, 2.3, 0.1, 0.2 + x, 1.0 + y, -3.91 + z, BLACK);
//	//Boton
//	prisma(0.2, 0.3, 0.1, 0.9 + x, 0.8 + y, 0.01 + z, BLUE);
//}
//
//void mouse(float x, float y, float z) {
//	//cuerpo principal
//	prismaMulticolor(1, 0.7, 2.3, 0 + x, 0 + y, 0 + z, GREY, BLACK, BLACK, BLUE, DGREY, DGREY);
//	//ruedita
//	prisma(0.2, 0.7, 0.5, 0.035 + x, 0.0025 + y, -0.10 + z, BLACK);
//}
//
//void keyboard(float x, float y, float z) {
//	prismaMulticolor(5, 0.25, 2, -1 + x, 0 + y, 0 + z, DGREY, DGREY, BLACK, GREY, DGREY, DGREY);
//}
//
//void mesa(float x, float y, float z) {
//	prisma(9.0, 0.25, 4.5, x + 0.0, y + 4.5, z + 0.35, LGREY);  // Tablero de la mesa
//
//	prisma(0.35, 0.8, 4.5, x + 0.3, y + 0.0, z + 0.0, BLACK); // Pata acostada izquierda 
//	prisma(0.35, 0.8, 4.5, x + 8.4, y + 0.0, z + 0.0, BLACK); // Pata acostada derecha 
//	prisma(0.35, 3.7, 0.8, x + 0.3, y + 0.8, z - 3.35, DGREY); // Pata izquierda 
//	prisma(0.35, 3.7, 0.8, x + 8.4, y + 0.8, z - 3.35, DGREY); // Pata derecha 
//
//	prisma(7.95, 2.2, 0.1, x + 0.65, y +2.3, z - 4.05, BLACK); // Rectangulo negro
//
//}
//
//void silla(float x, float y, float z) {
//	// Asiento 
//	prisma(3.0, 0.45, 2.4, x + 0.0, y + 2.0, z - 0.35, DGREY);
//	// Patas 
//	prisma(0.35, 2.0, 0.35, x + 2.6, y + 0.0, z - 2.3, GREY); //pata frontal derecha
//	prisma(0.35, 2.0, 0.35, x + 0.0, y + 0.0, z - 2.3, GREY); //pata frontal izquierda
//	prisma(0.35, 2.9, 0.35, x + 2.6, y + 0.0, z + 0.0, GREY); //pata trasera derecha
//	prisma(0.35, 2.9, 0.35, x + 0.0, y + 0.0, z + 0.0, GREY); //pata trasera izquierda
//	// Respaldo 
//	prisma(3.1, 2.4, 0.45, x - 0.055, y + 2.8, z + 0.05, DGREY);
//}
//
//void unidadMobiliario(float x, float y, float z) {
//	mesa(0.0 + x, 0.0 + y, -0.9 + z);
//	silla(3.0 + x, 0.0 + y, 0.0 + z);
//	pc(0.3 + x, 4.75 + y, -1.0 + z);
//	monitor(3.0 + x, 4.75 + y, -3.3 + z);
//	mouse(7.8 + x, 4.75 + y, -1.0 + z);
//	keyboard(3.5 + x, 4.75 + y, -1.0 + z);
//}
//
//void generarMobiSalon(float x, float y, float z, int filas, int mesas, float espaciado) {
//	for (int i = 0; i < filas; i++) {
//		for (int j = 0; j < mesas; j++) {
//			unidadMobiliario(0.0 + x, 0.0 + y, +5.4 + z);
//			x += 9.0;
//		}
//		x -= (9.0 * mesas);
//		z += (5.4 + espaciado);
//	}
//}
