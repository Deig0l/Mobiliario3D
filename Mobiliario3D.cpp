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

//Globals for lighting
static float a = 0.2; // Intensidad de la luz ambiental global.
static int light0On = 1; // Determina si el foco blanco está prendido o apagado
static float d = 1.0; // Intensidad difusa y especular del foco blanco.

void inicializacion(void);
void displayMobiliario();
void cargarTextura(const char* filename);
void tecladoMobiliario(unsigned char key, int x, int y);
void tecladoEspecialMobiliario(int key, int x, int y);
void ratonMobiliario(int button, int state, int x, int y);
void arrastreRaton(int x, int y);
void ejes3D();
void asignarColor(Colores color);
//void prisma(float l, float h, float d, float x, float y, float z, Colores color);
//void prismaMulticolor(float l, float h, float d, float x, float y, float z,
	//Colores cf, Colores cp, Colores ci, Colores cs, Colores cli, Colores cld);
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
void imprimirControles();
//void writeBitmapString(void* font, const char* string);
//void controlesMensaje();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Mobiliario 3D");
	inicializacion();
	glutDisplayFunc(displayMobiliario);
	glutKeyboardFunc(tecladoMobiliario);
	glutSpecialFunc(tecladoEspecialMobiliario);
	glutMouseFunc(ratonMobiliario);
	glutMotionFunc(arrastreRaton);
	imprimirControles();
	glutMainLoop();
	return 0;
}

void inicializacion(void) {
	//glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Turn on OpenGL lighting.
	glEnable(GL_LIGHTING);

	// Material property vectors.
	float matAmbAndDif[] = { 1.0, 1.0, 1.0, 1.0 };//Color de luz ambiental de los materiales
	float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };
	float matShine[] = { 50.0 };

	// Material properties of mobiliario.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	//glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Cargar todas las texturas necesarias
	const char* archivosTexturas[] = {
		"imagenes/mandelbrot.bmp",	//0
		"imagenes/monitor.jpg",		//1
		"imagenes/monitor_gris.jpg",//2
		"imagenes/screen.png",		//3
		"imagenes/cpu_front.jpg",	//4
		"imagenes/cpu_back.jpg",	//5
		"imagenes/bplastic.jpg",	//6
		"imagenes/dgreyplastic.jpg",//7
		"imagenes/keyboard.jpg",	//8
		"imagenes/asiento.jpg",		//9
		"imagenes/metal_negro.jpg",	//10
		"imagenes/mouse.png"		//11
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

		// Cargar la imagen en la textura
		if (nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (nrChannels == 4) {
			// Configuración para texturas con canal alfa (transparencia)
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		// Generar mipmaps para mejorar la calidad al escalar
		
		//glGenerateMipmap(GL_TEXTURE_2D);

		texturaIDs.push_back(texturaID);
		stbi_image_free(data);
	}
	else {
		std::cerr << "Error al cargar la imagen: " << filename << std::endl;
	}
}

void displayMobiliario() {

	// Light property vectors.
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 }; //Ambiental foco blanco
	float lightDifAndSpec0[] = { d, d, d, 1.0 }; //Difuso y especular foco blanco
	float lightPos0[] = { -15.0, 20.0, 10.0, 1.0 }; //Posición foco blanco
	float globAmb[] = { a, a, a, 1.0 }; //Color luz ambiental

	// Light0 properties (foco blanco)
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

	// Turn lights off/on.
	if (light0On) glEnable(GL_LIGHT0); else glDisable(GL_LIGHT0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // Restablece la matriz de modelo-vista

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTranslatef(trasladox, trasladoy, trasladoz);

	glRotatef(angulox, 1.0, 0.0, 0.0);
	glRotatef(anguloy, 0.0, 1.0, 0.0);
	glRotatef(anguloz, 0.0, 0.0, 1.0);
	glScalef(facEsc, facEsc, facEsc);
	
	if (mostrarControles) {
		//controlesMensaje();
	}

	if (mostrarEjes) {
		ejes3D();
	}

	// Draw light spheres after disabling lighting.
	glDisable(GL_LIGHTING);

	// Light0 and its sphere positioned (foco blanco).
	glPushMatrix();
	
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
	glColor3f(d, d, d);
	if (light0On) glutWireSphere(1.0, 8, 8);
	
	glPopMatrix();

	glEnable(GL_LIGHTING);

	generarMobiSalon(-31.5, 0.0, 0.0, 4, 4, 4.0);
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
			case 'a':
				if (a > 0.0) a -= 0.05;
				glutPostRedisplay();
				break;
			case 'A':
				if (a < 1.0) a += 0.05;
				glutPostRedisplay();
				break;
			case 'w':
				if (light0On) light0On = 0; else light0On = 1;
				glutPostRedisplay();
				break;
			case 'W':
				if (light0On) light0On = 0; else light0On = 1;
				glutPostRedisplay();
				break;
			case 'd':
				if (d > 0.0) d -= 0.05;
				glutPostRedisplay();
				break;
			case 'D':
				if (d < 5.0) d += 0.05;
				glutPostRedisplay();
				break;
			default:
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
	glDisable(GL_LIGHTING);
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
	glEnable(GL_LIGHTING);
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

// Función para dibujar un prisma con la textura indicada
void prismaTextura(float l, float h, float d, float x, float y, float z, int texturaIndex) {
	if (texturaIndex < texturaIDs.size()) {
		glEnable(GL_TEXTURE_2D);
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
	glDisable(GL_TEXTURE_2D);
}

void prismaMultitexturas(float l, float h, float d, float x, float y, float z,
	int texturaFrontal, int texturaTrasera,
	int texturaSuperior, int texturaInferior,
	int texturaIzquierda, int texturaDerecha) {

	// Cara frontal
	if (texturaFrontal < texturaIDs.size()) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaFrontal]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y + h, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y, z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	// Cara trasera
	if (texturaTrasera < texturaIDs.size()) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaTrasera]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z - d);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, z - d);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y + h, z - d);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y, z - d);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	// Cara inferior
	if (texturaInferior < texturaIDs.size()) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaInferior]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y, z - d);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z - d);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	// Cara superior
	if (texturaSuperior < texturaIDs.size()) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaSuperior]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + h, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y + h, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y + h, z - d);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, z - d);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	// Cara lateral izquierda
	if (texturaIzquierda < texturaIDs.size()) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaIzquierda]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + h, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + h, z - d);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z - d);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	// Cara lateral derecha
	if (texturaDerecha < texturaIDs.size()) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texturaIDs[texturaDerecha]);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + l, y, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + l, y + h, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + l, y + h, z - d);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + l, y, z - d);
	glEnd();
	glDisable(GL_TEXTURE_2D);
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
	prismaTextura(1.6, 0.2, 1.4, 1.2 + x, 0.0 + y, 0.0 + z, 1);
	//Pantalla
	prismaMultitexturas(3.6, 2.6, 0.2, 0.2 + x, 1.2 + y, -0.5 + z, 3, 1, 1, 1, 1, 1);
	//Marco horizontal inferior
	prismaTextura(4.0, 0.2, 0.4, 0 + x, 1.0 + y, -0.3 + z, 1);
	//Marco horizontal superior
	prismaTextura(4.0, 0.2, 0.4, 0 + x, 3.8 + y, -0.3 + z, 1);
	//Marco vertical izquierdo
	prismaTextura(0.2, 2.6, 0.4, 0 + x, 1.2 + y, -0.3 + z, 1);
	//Marco vertical derecho
	prismaTextura(0.2, 2.6, 0.4, 3.8 + x, 1.2 + y, -0.3 + z, 1);
	//Cuello
	prismaTextura(0.8, 2.0, 0.3, 1.6 + x, 0.2 + y, -0.7 + z, 2);
}

void pc(float x, float y, float z) {
	prismaMultitexturas(2.0, 3.5, 4.0, 0.0 + x, 0.0 + y, -0.2 + z, 4, 5, 1, 1, 1, 1);
}

void mouse(float x, float y, float z) {
	//cuerpo principal
	prismaMultitexturas(1, 0.7, 2.3, 0 + x, 0 + y, 0 + z, 6, 6, 11, 7, 7, 7); 
	//ruedita
	prismaTextura(0.2, 0.7, 0.5, 0.0035 + x, 0.00225 + y, -0.10 + z, 7);
}

void keyboard(float x, float y, float z) {
	prismaMultitexturas(5, 0.25, 2, -1 + x, 0 + y, 0 + z, 6, 6, 8, 7, 6, 6);
}

void mesa(float x, float y, float z) {
	prismaTextura(9.0, 0.25, 4.5, x + 0.0, y + 4.5, z + 0.35, 9); //tablero de la mesa
	 
	prismaTextura(0.35, 0.8, 4.5, x + 0.3, y + 0.0, z + 0.0, 6); //pata acostada izquierda
	prismaTextura(0.35, 0.8, 4.5, x + 8.4, y + 0.0, z + 0.0, 6); //pata acostada derecha
	prismaTextura(0.35, 3.7, 0.8, x + 0.3, y + 0.8, z - 3.35, 6); //pata izquierda
	prismaTextura(0.35, 3.7, 0.8, x + 8.4, y + 0.8, z - 3.35, 6); //pata derecha
	 
	prismaTextura(7.95, 2.2, 0.1, x + 0.65, y + 2.3, z - 4.05, 9);//rectangulo

}

void silla(float x, float y, float z) {
	// Asiento 
	prismaTextura(3.0, 0.45, 2.4, x + 0.0, y + 2.0, z - 0.35, 9);

	// Patas  
	prismaTextura(0.35, 2.0, 0.35, x + 2.6, y + 0.0, z - 2.3, 10); //pata frontal derecha
	prismaTextura(0.35, 2.0, 0.35, x + 0.0, y + 0.0, z - 2.3, 10); //pata frontal izquierda
	prismaTextura(0.35, 2.9, 0.35, x + 2.6, y + 0.0, z + 0.0, 10); //pata trasera derecha
	prismaTextura(0.35, 2.9, 0.35, x + 0.0, y + 0.0, z + 0.0, 10); //pata trasera izquierda
	// Respaldo 
	prismaTextura(3.1, 2.4, 0.45, x - 0.055, y + 2.8, z + 0.05, 9);
}

void proyector(float x, float y, float z) {
	prismaTextura(0.5, 4.0, 0.5, 1.25 + x, 0.9 + y, - 1.0 + z, 2); 
	prismaMultitexturas(3.0, 0.9, 2.5, 0.0 + x, 0.0 + y, 0.0 + z, 2, 2, 2, 2, 2, 2);
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

void imprimirControles()
{
	printf("Controles:\n"); 
	printf("Presionar 'w' (o 'W') para prender/apagar el foco blanco\n");
	printf("Presionar 'd/D' para atenuar/intensificar el foco blanco\n");
	printf("Presionar 'a/A' para atenuar/intensificar la luz ambiental\n");
}