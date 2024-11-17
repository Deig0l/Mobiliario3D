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


/*
FIGURAS UTILIZANDO SOLO COLORES
*/

//void monitor(float x, float y, float z) {
//	//Base
//	prismaMulticolor(1.6, 0.2, 1.4, 1.2 + x, 0.0 + y, 0.0 + z, DGREY, DGREY, GREY, GREY, DGREY,DGREY);
//	//Pantalla
//	prismaMulticolor(3.6, 2.6, 0.2, 0.2 + x, 1.2 + y, -0.5 + z, BLACK, GREY, GREY, GREY, GREY, GREY);
//	//Marco horizontal inferior
//	prismaMulticolor(4.0, 0.2, 0.4, 0 + x, 1.0 + y, -0.3 + z, GREY, GREY, GREY, DGREY, GREY, GREY);
//	//Marco horizontal superior
//	prismaMulticolor(4.0, 0.2, 0.4, 0 + x, 3.8 + y, -0.3 + z, GREY, GREY, DGREY, GREY, GREY, GREY);
//	//Marco vertical izquierdo
//	prismaMulticolor(0.2, 2.6, 0.4, 0 + x, 1.2 + y, -0.3 + z, GREY, GREY, GREY, GREY, GREY, DGREY);
//	//Marco vertical derecho
//	prismaMulticolor(0.2, 2.6, 0.4, 3.8 + x, 1.2 + y, -0.3 + z, GREY, GREY, GREY, GREY, DGREY, GREY);
//	//Cuello
//	prisma(0.8, 2.0, 0.3, 1.6 + x, 0.2 + y, -0.7 + z, DGREY);
//
//}
//
//void pc(float x, float y, float z) {
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
//	ruedita
//	//prisma(0.2, 0.7, 0.5, 0.035 + x, 0.0025 + y, -0.10 + z, BLACK);
//}
//
//void keyboard(float x, float y, float z) {
//	prismaMulticolor(5, 0.25, 2, -1 + x, 0 + y, 0 + z, DGREY, DGREY, BLACK, GREY, DGREY, DGREY);
//}
//
//void mesa(float x, float y, float z) {
//	prisma(9.0, 0.25, 4.5, x + 0.0, y + 4.5, z + 0.35, LGREY);  // Tablero de la mesa
//	prisma(0.35, 0.8, 4.5, x + 0.3, y + 0.0, z + 0.0, BLACK); // Pata acostada izquierda 
//	prisma(0.35, 0.8, 4.5, x + 8.4, y + 0.0, z + 0.0, BLACK); // Pata acostada derecha 
//	prisma(0.35, 3.7, 0.8, x + 0.3, y + 0.8, z - 3.35, DGREY); // Pata izquierda 
//	prisma(0.35, 3.7, 0.8, x + 8.4, y + 0.8, z - 3.35, DGREY); // Pata derecha 
//	prisma(7.95, 2.2, 0.1, x + 0.65, y +2.3, z - 4.05, BLACK); // Rectangulo negro
//}
//
//void silla(float x, float y, float z) {
//	//Asiento 
//		prisma(3.0, 0.45, 2.4, x + 0.0, y + 2.0, z - 0.35, DGREY);
//	//Patas 
//	     prisma(0.35, 2.0, 0.35, x + 2.6, y + 0.0, z - 2.3, GREY); //pata frontal derecha
//	     prisma(0.35, 2.0, 0.35, x + 0.0, y + 0.0, z - 2.3, GREY); //pata frontal izquierda
//	     prisma(0.35, 2.9, 0.35, x + 2.6, y + 0.0, z + 0.0, GREY); //pata trasera derecha
//	     prisma(0.35, 2.9, 0.35, x + 0.0, y + 0.0, z + 0.0, GREY); //pata trasera izquierda
//	 //Respaldo 
//	     prisma(3.1, 2.4, 0.45, x - 0.055, y + 2.8, z + 0.05, DGREY);
//
//}
//
//void proyector(float x, float y, float z) {
//	prisma(0.5, 4.0, 0.5, 1.25 + x, 0.9 + y, -1.0 + z, BLACK);
//	prismaMulticolor(3.0, 0.9, 2.5, 0.0 + x, 0.0 + y, 0.0 + z, GREY, GREY, LGREY, LGREY, GREY, GREY);
//	cilindro(2.2 + x, 0.45 + y, -2.7 + z, 0.4, 0.2, BLACK, LBLUE);
//}