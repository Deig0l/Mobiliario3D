#include <GL/glut.h>


float angleX = 0.0f;
float angleY = 0.0f;

// Función para dibujar la mesa
void drawTable() {
    // Dibujar la superficie de la mesa
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glScalef(2.0f, 0.1f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Dibujar las patas de la mesa
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);

    // Primera pata 
    glPushMatrix();
    glTranslatef(-0.9f, -0.45f, -0.4f);
    glScalef(0.1f, 0.9f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Segunda pata 
    glPushMatrix();
    glTranslatef(0.9f, -0.45f, -0.4f);
    glScalef(0.1f, 0.9f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tercera pata
    glPushMatrix();
    glTranslatef(-0.9f, -0.45f, 0.4f);
    glScalef(0.1f, 0.9f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Cuarta pata 
    glPushMatrix();
    glTranslatef(0.9f, -0.45f, 0.4f);
    glScalef(0.1f, 0.9f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();

    // Dibujar el murito negro entre las patas de un lado
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(0.0f, -0.3f, -0.4f);
    glScalef(1.8f, 0.5f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(3.0f, 2.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    drawTable();

    glutSwapBuffers();
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
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Mesa");

    initOpenGL();
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutMainLoop();
    return 0;
}