////PRISMAS CON COLORES DEFINIDOS
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

//void writeBitmapString(void* font, const char* string) {
//	const char* c;
//	for (c = string; *c != '\0'; c++) {
//		glutBitmapCharacter(font, *c);
//	}
//}
//
//void controlesMensaje() {
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glRasterPos2f(-95, 85);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "Controles:");
//	glRasterPos2f(-95, 80);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "Esc -> Salir");
//	glRasterPos2f(-95, 75);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "Espacio -> Ejes");
//	glRasterPos2f(-95, 70);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "r -> Regresar");
//	glRasterPos2f(-95, 65);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "+ / - -> ZoomIn/ZoomOut");
//	glRasterPos2f(-95, 60);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "x / X -> Gira eje x");
//	glRasterPos2f(-95, 55);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "y / Y -> Gira eje y");
//	glRasterPos2f(-95, 50);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "z / Z -> Gira eje z");
//	glRasterPos2f(-95, 45);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "KeyUp -> Gira eje x+");
//	glRasterPos2f(-95, 40);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "KeyDown -> Gira eje x-");
//	glRasterPos2f(-95, 35);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "KeyRigth -> Gira eje y+");
//	glRasterPos2f(-95, 30);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "KeyLeft -> Gira eje y-");
//	glRasterPos2f(-95, 25);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "PgUp -> Gira eje z+");
//	glRasterPos2f(-95, 20);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "PgDown -> Gira eje z-");
//	glRasterPos2f(-95, 15);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "click+drag -> trasladar");
//	glRasterPos2f(-95, 10);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "Scroll -> ZoomIn/ZoomOut");
//	glRasterPos2f(-95, 5);
//	writeBitmapString(GLUT_BITMAP_HELVETICA_10, "h -> controles");
//	glutPostRedisplay();
//}


//Cargar textura anterior
//void cargarTextura(const char* filename) {
//	int width, height, nrChannels;
//	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
//	if (data) {
//		GLuint texturaID;
//		glGenTextures(1, &texturaID);
//		glBindTexture(GL_TEXTURE_2D, texturaID);
//
//		// Configurar parámetros de textura
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		// Determinar el formato de la imagen y cargarla
//		if (nrChannels == 3)
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		else if (nrChannels == 4)
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//
//		//glGenerateMipmap(GL_TEXTURE_2D);
//
//		// Agregar el ID de la textura al vector
//		texturaIDs.push_back(texturaID);
//		stbi_image_free(data);
//	}
//	else {
//		std::cerr << "Error al cargar la imagen: " << filename << std::endl;
//	}
//}