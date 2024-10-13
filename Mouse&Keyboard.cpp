#include <GL/glut.h>

float angleX = 0.0f;
float angleY = 0.0f;

// Función para dibujar la mesa
void drawMouse() {

    //Lineas de los ejes
    glBegin(GL_LINES);

    //Eje x
    glColor3f(1, 0, 0);
    glVertex3f(-300, 0, 0);
    glVertex3f(300, 0, 0);

    //Eje y
    glColor3f(0, 1, 0);
    glVertex3f(0, -300, 0);
    glVertex3f(0, 300, 0);

    //Eje z
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -300);
    glVertex3f(0, 0, 300);

    glEnd();

    // Dibujar mouse
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glScalef(0.1f, 0.05f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();


    //Teclado
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(-0.5,0,0);
    glScalef(0.3f, 0.03f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Configurar la cámara para ver el plano XY desde el eje Z positivo
    gluLookAt(0.0f, 0.0f, 1.50f,  // Posición de la cámara
        0.0f, 0.0f, 0.0f,  // Punto hacia donde mira (el origen)
        0.0f, 1.0f, 0.0f); // Vector arriba (eje Y)

    // Aplicar rotaciones según las teclas
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    drawMouse();
    glutSwapBuffers();
}

void keyboardNormal(unsigned char key, int x, int y) {
    switch (key) {
    case 'r':
        angleX = 0.0f;
        angleY = 0.0f;
        break;
    }
    glutPostRedisplay();
}

void keyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:  // Flecha izquierda
        angleY -= 5.0f;
        break;
    case GLUT_KEY_RIGHT: // Flecha derecha
        angleY += 5.0f;
        break;
    case GLUT_KEY_UP:    // Flecha arriba
        angleX -= 5.0f;
        break;
    case GLUT_KEY_DOWN:  // Flecha abajo
        angleX += 5.0f;
        break;
    }
    glutPostRedisplay();
}

void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

    // Ajuste de la proyección ortogonal
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -5, 5);  // Ajuste del volumen de visualización ortogonal

    glMatrixMode(GL_MODELVIEW);
}

// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Mouse");

    initOpenGL();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardNormal);
    glutSpecialFunc(keyboard);
    glutMainLoop();
    return 0;
}