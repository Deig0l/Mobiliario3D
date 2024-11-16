#ifndef TEXTURAS_H
#define TEXTURAS_H

#include <GL/glut.h>

class Texturas {
public:
    GLuint textureID;
    unsigned long width;
    unsigned long height;
    char* data;

    // Constructor
    Texturas(GLuint textureID, unsigned long width, unsigned long heigth);

    // Destructor
    ~Texturas();

    // Método para cargar la imagen desde un archivo BMP
    bool load(const char* filename);

    // Método para crear la textura en OpenGL
    void createGLTexture();
};

#endif // TEXTURAS_H