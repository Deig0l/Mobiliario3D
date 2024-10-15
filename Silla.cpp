//#include <GL/glut.h>
//
//float angleX = 0.0f;
//float angleY = 0.0f;
//
//// Función para dibujar la silla
//void drawChair() {
//    // Dibujar el asiento de la silla
//    glPushMatrix();
//    glColor3f(0.0f, 0.0f, 0.0f); // Color negro
//    glTranslatef(0.0f, 0.5f, 0.0f);
//    glScalef(1.0f, 0.12f, 1.01f);
//    glutSolidCube(1.0f);
//    glPopMatrix();
//
//    // Dibujar el respaldo de la silla
//    glPushMatrix();
//    glColor3f(0.0f, 0.0f, 0.0f); // Color negro
//    glTranslatef(0.0f, 1.1f, -0.45f);
//    glScalef(1.0f, 0.7f, 0.12f);
//    glutSolidCube(1.0f);
//    glPopMatrix();
//
//    // Dibujar las patas de la silla
//    glPushMatrix();
//    glColor3f(0.5f, 0.5f, 0.5f); // Color gris
//
//    // Primera pata
//    glPushMatrix();
//    glTranslatef(-0.4f, 0.3f, -0.45f);
//    glScalef(0.1f, 1.3f, 0.1f);
//    glutSolidCube(1.0f);
//    glPopMatrix();
//
//    // Segunda pata
//    glPushMatrix();
//    glTranslatef(0.4f, 0.3f, -0.45f);
//    glScalef(0.1f, 1.3f, 0.1f);
//    glutSolidCube(1.0f);
//    glPopMatrix();
//
//    // Tercera pata
//    glPushMatrix();
//    glTranslatef(-0.4f, 0.1f, 0.4f);
//    glScalef(0.1f, 0.9f, 0.1f);
//    glutSolidCube(1.0f);
//    glPopMatrix();
//
//    // Cuarta pata
//    glPushMatrix();
//    glTranslatef(0.4f, 0.1f, 0.4f);
//    glScalef(0.1f, 0.9f, 0.1f);
//    glutSolidCube(1.0f);
//    glPopMatrix();
//
//    glPopMatrix();
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    gluLookAt(3.0f, 2.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
//
//    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
//    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
//
//    drawChair();
//
//    glutSwapBuffers();
//}
//
//void keyboardNormal(unsigned char key, int x, int y) {
//    switch (key) {
//    case 'r':
//        angleX = 0.0f;
//        angleY = 0.0f;
//        break;
//    }
//    glutPostRedisplay();
//}
//
//void keyboard(int key, int x, int y) {
//    switch (key) {
//    case GLUT_KEY_LEFT:  // Flecha izquierda
//        angleY -= 5.0f;
//        break;
//    case GLUT_KEY_RIGHT: // Flecha derecha
//        angleY += 5.0f;
//        break;
//    case GLUT_KEY_UP:    // Flecha arriba
//        angleX -= 5.0f;
//        break;
//    case GLUT_KEY_DOWN:  // Flecha abajo
//        angleX += 5.0f;
//        break;
//    }
//    glutPostRedisplay();
//}
//
//void initOpenGL() {
//    glEnable(GL_DEPTH_TEST);
//    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
//    glMatrixMode(GL_PROJECTION);
//    gluPerspective(45.0, 1.0, 1.0, 100.0);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//// Main
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(600, 600);
//    glutCreateWindow("Silla");
//
//    initOpenGL();
//    glutDisplayFunc(display);
//    glutKeyboardFunc(keyboardNormal);
//    glutSpecialFunc(keyboard);
//    glutMainLoop();
//    return 0;
//}