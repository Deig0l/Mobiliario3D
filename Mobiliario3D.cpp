#include <vector>
#include <iostream>
#include <cmath>
//#include <GL/freeglut.h>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

enum Colores {
	BLACK, WHITE, RED, GREEN, BLUE, LBLUE, YELLOW, MAGENTA, CYAN, GREY, LGREY, DGREY
};

std::vector<GLuint> texturaIDs;
int wheelDelta = 0;
float angulox = 0.0f;
float anguloy = 0.0f;
float anguloz = 0.0f;
float trasladox = 0.0f;
float trasladoy = 0.0f;
float trasladoz = 0.0f;
float facEsc = 1;
float posX, posY;
bool mostrarEjes = true;
bool mostrarControles = true;
bool mousePresionado = false;

void inicializacion(void);
void displayMobiliario();
void cargarTextura(const char* filename);
void tecladoMobiliario(unsigned char key, int x, int y);
void tecladoEspecialMobiliario(int key, int x, int y);
void ratonMobiliario(int button, int state, int x, int y);
void arrastreRaton(int x, int y);
void ejes3D();
void asignarColor(Colores color);
void prisma(float l, float h, float d, float x, float y, float z, Colores color);
void prismaMulticolor(float l, float h, float d, float x, float y, float z,
	Colores cf, Colores cp, Colores ci, Colores cs, Colores cli, Colores cld);
void prismaTextura(float l, float h, float d, float x, float y, float z, int texturaIndex);
void prismaMultitexturas(float l, float h, float d, float x, float y, float z,
	int texturaFrontal, int texturaTrasera,
	int texturaSuperior, int texturaInferior,
	int texturaIzquierda, int texturaDerecha);
void cilindro(float x, float y, float z, float radio, float height,
	Colores lado, Colores tapa);
void monitor(float x, float y, float z);
void pc(float x, float y, float z);
void mouse(float x, float y, float z);
void keyboard(float x, float y, float z);
void mesa(float x, float y, float z);
void silla(float x, float y, float z);
void proyector(float x, float y, float z);
void unidadMobiliario(float x, float y, float z);
void generarMobiSalon(float x, float y, float z, int filas, int mesas, float espaciado);
void writeBitmapString(void* font, const char* string);
void controlesMensaje();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Mobiliario 3D");
	glutDisplayFunc(displayMobiliario);
	glutKeyboardFunc(tecladoMobiliario);
	glutSpecialFunc(tecladoEspecialMobiliario);
	glutMouseFunc(ratonMobiliario);
	glutMotionFunc(arrastreRaton);
	inicializacion();
	glutMainLoop();
	return 0;
}

void inicializacion(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Cargar todas las texturas necesarias
	const char* archivosTexturas[] = {
		"imagenes/mandelbrot.bmp",
		"imagenes/monitor.jpg",
		"imagenes/monitor_gris.jpg",
		"imagenes/screen.png",
		"imagenes/cpu_front.jpg",
		"imagenes/cpu_back.jpg",
		"imagenes/bplastic.jpg",
		"imagenes/dgreyplastic.jpg",
		"imagenes/keyboard.jpg",
		"imagenes/asiento.jpg",
		"imagenes/metal_negro.jpg"
	};

	for (const char* archivo : archivosTexturas) {
		cargarTextura(archivo);
	}
}

// Función para cargar una textura desde un archivo y añadirla al vector
void cargarTextura(const char* filename) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data) {
		GLuint texturaID;
		glGenTextures(1, &texturaID);
		glBindTexture(GL_TEXTURE_2D, texturaID);

		// Configurar parámetros de textura
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Determinar el formato de la imagen y cargarla
		if (nrChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		//glGenerateMipmap(GL_TEXTURE_2D);

		// Agregar el ID de la textura al vector
		texturaIDs.push_back(texturaID);
		stbi_image_free(data);
	}
	else {
		std::cerr << "Error al cargar la imagen: " << filename << std::endl;
	}
}

void displayMobiliario() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // Restablece la matriz de modelo-vista
	glPushMatrix();

	glTranslatef(trasladox, trasladoy, trasladoz);

	glRotatef(angulox, 1.0, 0.0, 0.0);
	glRotatef(anguloy, 0.0, 1.0, 0.0);
	glRotatef(anguloz, 0.0, 0.0, 1.0);
	glScalef(facEsc, facEsc, facEsc);
	
	if (mostrarControles) {
		controlesMensaje();
	}

	if (mostrarEjes) {
		ejes3D();
	}

	generarMobiSalon(-31.5, 0.0, 0.0, 5, 6, 4.0);
	proyector(-4.5, 15.0, 10.0);

	glPushMatrix();
	glRotatef(90, 0,1,0);
	unidadMobiliario(10,0, 8);
	glPopMatrix();
	
	glPopMatrix();

	glutSwapBuffers();
}

void tecladoMobiliario(unsigned char key, int x, int y) {
	switch (key) {
			case 27: //Esc
				exit(1);
				break;
			case 32: //Espacio
				mostrarEjes = !mostrarEjes;
				break;
			case 'r':
				//Se limpian los angulos
				angulox = 0;
				anguloy = 0;
				anguloz = 0;
				trasladox = 0;
				trasladoy = 0;
				trasladoz = 0;
				facEsc = 1;
				glLoadIdentity();
				break;
			case '+':
				facEsc += 0.1f;
				break;
			case '-':
				facEsc -= 0.1f;
				break;
			case 'x':
				angulox += 5.0f;
				break;
			case 'y':
				anguloy += 5.0f;
				break;
			case 'z':
				anguloz += 5.0f;
				break;
			case 'X':
				angulox -= 5.0f;
				break;
			case 'Y':
				anguloy -= 5.0f;
				break;
			case 'Z':
				anguloz -= 5.0f;
				break;
			case 'h':
			case 'H':
				mostrarControles = !mostrarControles;
				break;
	}
	glutPostRedisplay();
}

void tecladoEspecialMobiliario(int key, int x, int y) {
	switch (key)
	{
		case GLUT_KEY_UP:
			angulox += 5.0;
			break;
		case GLUT_KEY_DOWN:
			angulox -= 5.0;
			break;
		case GLUT_KEY_RIGHT:
			anguloy += 5.0;
			break;
		case GLUT_KEY_LEFT:
			anguloy -= 5.0;
			break;
		case GLUT_KEY_PAGE_UP:
			anguloz += 5.0;
			break;
		case GLUT_KEY_PAGE_DOWN:
			anguloz -= 5.0;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void ratonMobiliario(int btn, int state, int x, int y) {
	x = (x - 300) / 3;
	y = (300 - y) / 3;

	if (btn == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			mousePresionado = true;
			posX = static_cast<float>(x);
			posY = static_cast<float>(y);
		}
		else if (state == GLUT_UP) {
			mousePresionado = false;
		}
	}

	if (btn == 3) { // Rueda hacia arriba
		facEsc += 0.1f;
	}
	else if (btn == 4) { // Rueda hacia abajo
		facEsc -= 0.1f;
		if (facEsc < 0.1f) facEsc = 0.1f;  // Evita zoom muy pequeño
	}

	glutPostRedisplay();
}

void arrastreRaton(int x, int y) {
	if (!mousePresionado) return; // Solo realiza el arrastre si el mouse está presionado

	x = (x - 300) / 3;
	y = (300 - y) / 3;
	int deltaX = x - posX;
	int deltaY = y - posY;

	trasladox += deltaX * 0.3f; // Factor de ajuste para traslación en X
	trasladoy += deltaY * 0.3f; // Factor de ajuste para traslación en Y

	posX = x;
	posY = y;

	glutPostRedisplay();
}

void ejes3D() {
	//Lineas de los ejes
	glBegin(GL_LINES);

	//Eje x
	glColor3f(1, 0, 0);//rojo
	glVertex3f(-300, 0, 0);
	glVertex3f(300, 0, 0);

	//Eje y
	glColor3f(0, 1, 0);//verde
	glVertex3f(0, -300, 0);
	glVertex3f(0, 300, 0);

	//Eje z
	glColor3f(0, 0, 1);//azul
	glVertex3f(0, 0, -300);
	glVertex3f(0, 0, 300);

	glEnd();
}

void asignarColor(Colores color) {
	switch (color) {
	case BLACK:
		glColor3f(0.0f, 0.0f, 0.0f);
		break;
	case WHITE:
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	case RED:
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	case GREEN:
		glColor3f(0.0f, 1.0f, 0.0f);
		break;
	case BLUE:
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	case LBLUE:
		glColor3f(0.23f, 0.35f, 0.41f);
		break;
	case YELLOW:
		glColor3f(1.0f, 1.0f, 0.0f);
		break;
	case MAGENTA:
		glColor3f(1.0f, 0.0f, 1.0f);
		break;
	case CYAN:
		glColor3f(0.0f, 1.0f, 1.0f);
		break;
	case GREY:
		glColor3f(0.5f, 0.5f, 0.5f);
		break;
	case LGREY:
		glColor3f(0.6f, 0.6f, 0.6f);
		break;
	case DGREY:
		glColor3f(0.2f, 0.2f, 0.2f);
		break;
	default:
		break;
	}
};

//Una unidad son 10cm para los primas
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

// Función para dibujar un prisma con la textura indicada
void prismaTextura(float l, float h, float d, float x, float y, float z, int texturaIndex) {
	if (texturaIndex < texturaIDs.size()) {
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaIndex]);
	}
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//Cara frontal
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y + h, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y, z);
	glEnd();

	// Cara posterior
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z - d);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, z - d);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y + h, z - d);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y, z - d);
	glEnd();

	// Cara inferior
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y, z - d);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z - d);
	glEnd();

	// Cara superior
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + h, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y + h, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y + h, z - d);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, z - d);
	glEnd();

	// Cara lateral izquierda
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + h, z - d);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z - d);
	glEnd();

	// Cara lateral derecha
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + l, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + l, y + h, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y + h, z - d);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y, z - d);
	glEnd();
}

void prismaMultitexturas(float l, float h, float d, float x, float y, float z,
	int texturaFrontal, int texturaTrasera,
	int texturaSuperior, int texturaInferior,
	int texturaIzquierda, int texturaDerecha) {

	// Cara frontal
	if (texturaFrontal < texturaIDs.size()) {
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaFrontal]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y + h, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y, z);
	glEnd();

	// Cara trasera
	if (texturaTrasera < texturaIDs.size()) {
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaTrasera]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z - d);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, z - d);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y + h, z - d);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y, z - d);
	glEnd();

	// Cara inferior
	if (texturaInferior < texturaIDs.size()) {
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaInferior]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y, z - d);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z - d);
	glEnd();

	// Cara superior
	if (texturaSuperior < texturaIDs.size()) {
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaSuperior]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + h, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y + h, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y + h, z - d);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, z - d);
	glEnd();

	// Cara lateral izquierda
	if (texturaIzquierda < texturaIDs.size()) {
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaIzquierda]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + h, z - d);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z - d);
	glEnd();

	// Cara lateral derecha
	if (texturaDerecha < texturaIDs.size()) {
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaDerecha]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + l, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + l, y + h, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y + h, z - d);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y, z - d);
	glEnd();
}

void cilindro(float x, float y, float z, float radio, float height,
	Colores lado, Colores tapa) {
	glPushMatrix();
	glTranslatef(x, y, z);

	glPushMatrix();
	GLUquadricObj* cilindro;
	cilindro = gluNewQuadric();
	asignarColor(lado);
	gluCylinder(cilindro, radio, radio, height, 15, 10);
	glPopMatrix();

	glPushMatrix();
	GLUquadricObj* tapaAbajo;
	tapaAbajo = gluNewQuadric();
	asignarColor(tapa);
	gluDisk(tapaAbajo, 0, radio, 15, 10);
	glPopMatrix();

	glPushMatrix();
	GLUquadricObj* tapaArriba;
	tapaArriba = gluNewQuadric();
	glTranslatef(0.0, 0.0, height);
	asignarColor(tapa);
	gluDisk(tapaArriba, 0.0, radio, 15.0, 10.0);
	glPopMatrix();

	glPopMatrix();
}

void monitor(float x, float y, float z) {
	//Base
	//prismaMulticolor(1.6, 0.2, 1.4, 1.2 + x, 0.0 + y, 0.0 + z, DGREY, DGREY, GREY, GREY, DGREY,DGREY);
	glEnable(GL_TEXTURE_2D);
	prismaTextura(1.6, 0.2, 1.4, 1.2 + x, 0.0 + y, 0.0 + z, 1);
	glDisable(GL_TEXTURE_2D);
	//Pantalla
	//prismaMulticolor(3.6, 2.6, 0.2, 0.2 + x, 1.2 + y, -0.5 + z, BLACK, GREY, GREY, GREY, GREY, GREY);
	glEnable(GL_TEXTURE_2D);
	prismaMultitexturas(3.6, 2.6, 0.2, 0.2 + x, 1.2 + y, -0.5 + z, 3, 1, 1, 1, 1, 1);
	glDisable(GL_TEXTURE_2D);
	//Marco horizontal inferior
	//prismaMulticolor(4.0, 0.2, 0.4, 0 + x, 1.0 + y, -0.3 + z, GREY, GREY, GREY, DGREY, GREY, GREY);
	glEnable(GL_TEXTURE_2D);
	prismaTextura(4.0, 0.2, 0.4, 0 + x, 1.0 + y, -0.3 + z, 1);
	glDisable(GL_TEXTURE_2D);
	//Marco horizontal superior
	//prismaMulticolor(4.0, 0.2, 0.4, 0 + x, 3.8 + y, -0.3 + z, GREY, GREY, DGREY, GREY, GREY, GREY);
	glEnable(GL_TEXTURE_2D);
	prismaTextura(4.0, 0.2, 0.4, 0 + x, 3.8 + y, -0.3 + z, 1);
	glDisable(GL_TEXTURE_2D);
	//Marco vertical izquierdo
	//prismaMulticolor(0.2, 2.6, 0.4, 0 + x, 1.2 + y, -0.3 + z, GREY, GREY, GREY, GREY, GREY, DGREY);
	glEnable(GL_TEXTURE_2D);
	prismaTextura(0.2, 2.6, 0.4, 0 + x, 1.2 + y, -0.3 + z, 1);
	glDisable(GL_TEXTURE_2D);
	//Marco vertical derecho
	//prismaMulticolor(0.2, 2.6, 0.4, 3.8 + x, 1.2 + y, -0.3 + z, GREY, GREY, GREY, GREY, DGREY, GREY);
	glEnable(GL_TEXTURE_2D);
	prismaTextura(0.2, 2.6, 0.4, 3.8 + x, 1.2 + y, -0.3 + z, 1);
	glDisable(GL_TEXTURE_2D);
	//Cuello
	//prisma(0.8, 2.0, 0.3, 1.6 + x, 0.2 + y, -0.7 + z, DGREY);
	glEnable(GL_TEXTURE_2D);
	prismaTextura(0.8, 2.0, 0.3, 1.6 + x, 0.2 + y, -0.7 + z, 2);
	glDisable(GL_TEXTURE_2D);
	
}

void pc(float x, float y, float z) {
	//Prisma principal
	glEnable(GL_TEXTURE_2D);
	prismaMultitexturas(2.0, 3.5, 4.0, 0.0 + x, 0.0 + y, -0.2 + z, 4, 5, 1, 1, 1, 1);
	glDisable(GL_TEXTURE_2D);
	////Prisma gris frontal
	//prisma(2.0, 3.5, 0.2, 0.0 + x, 0.0 + y, 0.0 + z, GREY);
	////Ranura superior
	//prisma(1.6, 0.4, 0.1, 0.2 + x, 2.9 + y, 0.01 + z, LGREY);
	////Ranura media
	//prisma(1.6, 0.4, 0.1, 0.2 + x, 2.3 + y, 0.01 + z, LGREY);
	////Ranura inferior
	//prisma(1.6, 0.4, 0.1, 0.2 + x, 1.7 + y, 0.01 + z, LGREY);
	////Ranura posterior
	//prisma(1.6, 2.3, 0.1, 0.2 + x, 1.0 + y, -3.91 + z, BLACK);
	////Boton
	//prisma(0.2, 0.3, 0.1, 0.9 + x, 0.8 + y, 0.01 + z, BLUE);
}

void mouse(float x, float y, float z) {
	glEnable(GL_TEXTURE_2D);
	//cuerpo principal
	//prismaMulticolor(1, 0.7, 2.3, 0 + x, 0 + y, 0 + z, GREY, BLACK, BLACK, BLUE, DGREY, DGREY);
	prismaTextura(1, 0.7, 2.3, 0 + x, 0 + y, 0 + z, 6);
	//ruedita
	prismaTextura(0.2, 0.7, 0.5, 0.0035 + x, 0.00225 + y, -0.10 + z, 7);

	//prisma(0.2, 0.7, 0.5, 0.035 + x, 0.0025 + y, -0.10 + z, BLACK);
	glDisable(GL_TEXTURE_2D);
}

void keyboard(float x, float y, float z) {
	glEnable(GL_TEXTURE_2D);
	prismaMultitexturas(5, 0.25, 2, -1 + x, 0 + y, 0 + z, 6, 6, 8, 7, 6, 6);
	glDisable(GL_TEXTURE_2D);
	//prismaMulticolor(5, 0.25, 2, -1 + x, 0 + y, 0 + z, DGREY, DGREY, BLACK, GREY, DGREY, DGREY);
}

void mesa(float x, float y, float z) {
	glEnable(GL_TEXTURE_2D);

	prismaTextura(9.0, 0.25, 4.5, x + 0.0, y + 4.5, z + 0.35, 9); //tablero de la mesa
	 
	prismaTextura(0.35, 0.8, 4.5, x + 0.3, y + 0.0, z + 0.0, 6); //pata acostada izquierda
	prismaTextura(0.35, 0.8, 4.5, x + 8.4, y + 0.0, z + 0.0, 6); //pata acostada derecha
	prismaTextura(0.35, 3.7, 0.8, x + 0.3, y + 0.8, z - 3.35, 6); //pata izquierda
	prismaTextura(0.35, 3.7, 0.8, x + 8.4, y + 0.8, z - 3.35, 6); //pata derecha
	 
	prismaTextura(7.95, 2.2, 0.1, x + 0.65, y + 2.3, z - 4.05, 9);//rectangulo

	//prisma(9.0, 0.25, 4.5, x + 0.0, y + 4.5, z + 0.35, LGREY);  // Tablero de la mesa

	//prisma(0.35, 0.8, 4.5, x + 0.3, y + 0.0, z + 0.0, BLACK); // Pata acostada izquierda 
	//prisma(0.35, 0.8, 4.5, x + 8.4, y + 0.0, z + 0.0, BLACK); // Pata acostada derecha 
	//prisma(0.35, 3.7, 0.8, x + 0.3, y + 0.8, z - 3.35, DGREY); // Pata izquierda 
	//prisma(0.35, 3.7, 0.8, x + 8.4, y + 0.8, z - 3.35, DGREY); // Pata derecha 

	//prisma(7.95, 2.2, 0.1, x + 0.65, y +2.3, z - 4.05, BLACK); // Rectangulo negro

	glDisable(GL_TEXTURE_2D);

}

void silla(float x, float y, float z) {
	// Asiento 
	//prisma(3.0, 0.45, 2.4, x + 0.0, y + 2.0, z - 0.35, DGREY);
	glEnable(GL_TEXTURE_2D);
	prismaTextura(3.0, 0.45, 2.4, x + 0.0, y + 2.0, z - 0.35, 9);

	// Patas 
	//     prisma(0.35, 2.0, 0.35, x + 2.6, y + 0.0, z - 2.3, GREY); //pata frontal derecha
	prismaTextura(0.35, 2.0, 0.35, x + 2.6, y + 0.0, z - 2.3, 10);
	//     prisma(0.35, 2.0, 0.35, x + 0.0, y + 0.0, z - 2.3, GREY); //pata frontal izquierda
	prismaTextura(0.35, 2.0, 0.35, x + 0.0, y + 0.0, z - 2.3, 10);
	//     prisma(0.35, 2.9, 0.35, x + 2.6, y + 0.0, z + 0.0, GREY); //pata trasera derecha
	prismaTextura(0.35, 2.9, 0.35, x + 2.6, y + 0.0, z + 0.0, 10);
	//     prisma(0.35, 2.9, 0.35, x + 0.0, y + 0.0, z + 0.0, GREY); //pata trasera izquierda
	prismaTextura(0.35, 2.9, 0.35, x + 0.0, y + 0.0, z + 0.0, 10);
	// Respaldo 
	//     prisma(3.1, 2.4, 0.45, x - 0.055, y + 2.8, z + 0.05, DGREY);
	prismaTextura(3.1, 2.4, 0.45, x - 0.055, y + 2.8, z + 0.05, 9);
	glDisable(GL_TEXTURE_2D);
}

void proyector(float x, float y, float z) {
	prisma(0.5, 4.0, 0.5, 1.25 + x, 0.9 + y, -1.0 + z, BLACK);
	prismaMulticolor(3.0, 0.9, 2.5, 0.0 + x, 0.0 + y, 0.0 + z, GREY, GREY, LGREY, LGREY, GREY, GREY);
	cilindro(2.2 + x, 0.45 + y, -2.7 + z, 0.4, 0.2, BLACK, LBLUE);
}

void unidadMobiliario(float x, float y, float z) {
	glColor3f(1.0f, 1.0f, 1.0f);
	mesa(0.0 + x, 0.0 + y, -0.9 + z);
	silla(3.0 + x, 0.0 + y, 0.0 + z);
	pc(0.3 + x, 4.75 + y, -1.0 + z);
	monitor(3.0 + x, 4.75 + y, -3.3 + z);
	mouse(7.8 + x, 4.75 + y, -1.0 + z);
	keyboard(3.5 + x, 4.75 + y, -1.0 + z);
}

void generarMobiSalon(float x, float y, float z, int filas, int mesas, float espaciado) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < mesas; j++) {
			unidadMobiliario(0.0 + x, 0.0 + y, +5.4 + z);
			x += 9.0;
		}
		x -= (9.0 * mesas);
		z += (5.4 + espaciado);
	}
}

void writeBitmapString(void* font, const char* string) {
	const char* c;
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void controlesMensaje() {
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(-95, 85);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "Controles:");
	glRasterPos2f(-95, 80);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "Esc -> Salir");
	glRasterPos2f(-95, 75);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "Espacio -> Ejes");
	glRasterPos2f(-95, 70);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "r -> Regresar");
	glRasterPos2f(-95, 65);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "+ / - -> ZoomIn/ZoomOut");
	glRasterPos2f(-95, 60);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "x / X -> Gira eje x");
	glRasterPos2f(-95, 55);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "y / Y -> Gira eje y");
	glRasterPos2f(-95, 50);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "z / Z -> Gira eje z");
	glRasterPos2f(-95, 45);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "KeyUp -> Gira eje x+");
	glRasterPos2f(-95, 40);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "KeyDown -> Gira eje x-");
	glRasterPos2f(-95, 35);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "KeyRigth -> Gira eje y+");
	glRasterPos2f(-95, 30);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "KeyLeft -> Gira eje y-");
	glRasterPos2f(-95, 25);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "PgUp -> Gira eje z+");
	glRasterPos2f(-95, 20);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "PgDown -> Gira eje z-");
	glRasterPos2f(-95, 15);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "click+drag -> trasladar");
	glRasterPos2f(-95, 10);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "Scroll -> ZoomIn/ZoomOut");
	glRasterPos2f(-95, 5);
	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "h -> controles");
	glutPostRedisplay();
}
