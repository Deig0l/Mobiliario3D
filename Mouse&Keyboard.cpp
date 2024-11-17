#include <vector>
#include <windows.h>
#include <cmath>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

std::vector<GLuint> texturaIDs;
float facEsc = 1;
float angulox = 0.0f;
float anguloy = 0.0f;
float anguloz = 0.0f;

enum Colores {
	BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GREY, LGREY, DGREY
};

void inicializacion(void);
void cargarTextura(const char* filename);
void displayMK();
void tecladoMK(unsigned char key, int x, int y);
void asignarColor(Colores color);
void prisma(float l, float h, float d, float x, float y, float z, Colores color);
void prismaMulticolor(float l, float h, float d, float x, float y, float z,
	Colores cf, Colores cp, Colores ci, Colores cs, Colores cli, Colores cld);
void prismaTextura(float l, float h, float d, float x, float y, float z, int texturaIndex);
void prismaMultitexturas(float l, float h, float d, float x, float y, float z,
	int texturaFrontal, int texturaTrasera,
	int texturaSuperior, int texturaInferior,
	int texturaIzquierda, int texturaDerecha);
void ejes3D();
void mouse(float x, float y, float z);
void keyboard(float x, float y, float z);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Mouse & Keyboard 3D");
	glutDisplayFunc(displayMK);
	glutKeyboardFunc(tecladoMK);
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

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);

	// Cargar todas las texturas necesarias
	const char* archivosTexturas[] = {
		"imagenes/madera.jpg"
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
		if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else if (nrChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		//glGenerateMipmap(GL_TEXTURE_2D);

		// Agregar el ID de la textura al vector
		texturaIDs.push_back(texturaID);
		stbi_image_free(data);
	}
	else {
		std::cerr << "Error al cargar la imagen: " << filename << std::endl;
		std::cerr << "Razón: " << stbi_failure_reason() << std::endl;
	}
}

void displayMK() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(angulox, 1.0, 0.0, 0.0);
	glRotatef(anguloy, 0.0, 1.0, 0.0);
	glRotatef(anguloz, 0.0, 0.0, 1.0);
	ejes3D();
	glScalef(facEsc, facEsc, facEsc);

	// Dibuja el "mouse" sin texturas
	mouse(-2, 0, -2);

	// Dibuja el "keyboard" con texturas
	glEnable(GL_TEXTURE_2D);
	keyboard(4, 0, -2);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glutSwapBuffers();
}


void tecladoMK(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':
		//Se limpian los angulos
		angulox = 0;
		anguloy = 0;
		anguloz = 0;
		facEsc = 1;
		glLoadIdentity();
		break;
	case '+':
		facEsc += 0.1;
		break;
	case '-':
		facEsc -= 0.1;
		break;
	case 'x':
		angulox += 5.0;
		break;
	case 'y':
		anguloy += 5.0;
		break;
	case 'z':
		anguloz += 5.0;
		break;
	case 'X':
		angulox -= 5.0;
		break;
	case 'Y':
		anguloy -= 5.0;
		break;
	case 'Z':
		anguloz -= 5.0;
		break;
	}
	glutPostRedisplay();
}

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
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

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

void mouse(float x, float y, float z) {
	//cuerpo principal
	prismaMulticolor(1, 0.25, 1.8, -1, 0, -2.0, LGREY, BLACK, BLACK, BLUE, DGREY, DGREY);
	//ruedita
	prisma(0.2, 0.2, 0.5, -0.6, 0.2, -2.25, BLACK);
}

//void keyboard(float x, float y, float z) {
//	prismaMulticolor(5, 0.25, 2, 2, 0, -2.0, DGREY, DGREY, BLACK, DGREY, DGREY, DGREY);
//}

void keyboard(float x, float y, float z) {
	prismaTextura(5,0.25,2,2,0,-2.0,0);
}
