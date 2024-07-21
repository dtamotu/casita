#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

using namespace std;

class Primitiva {
public:
    float r, g, b;

    Primitiva() : r(1.0f), g(1.0f), b(1.0f) {}

    virtual void dibujar() = 0;

    void establecerColor(float rojo, float verde, float azul) {
        r = rojo;
        g = verde;
        b = azul;
    }

    void aplicarColor() {
        glColor3f(r, g, b);
    }
};
class Cuadrado : public Primitiva {
public:
    float tamano;

    Cuadrado(float tamano) : tamano(tamano) {}

    void dibujar() override {
        aplicarColor();
        glBegin(GL_QUADS);
        glVertex2f(-tamano / 2, -tamano / 2);
        glVertex2f(tamano / 2, -tamano / 2);
        glVertex2f(tamano / 2, tamano / 2);
        glVertex2f(-tamano / 2, tamano / 2);
        glEnd();
    }
};

class Rectangulo : public Primitiva {
public:
    float ancho, alto;

    Rectangulo(float ancho, float alto) : ancho(ancho), alto(alto) {}

    void dibujar() override {
        aplicarColor();
        glBegin(GL_QUADS);
        glVertex2f(-ancho / 2, -alto / 2);
        glVertex2f(ancho / 2, -alto / 2);
        glVertex2f(ancho / 2, alto / 2);
        glVertex2f(-ancho / 2, alto / 2);
        glEnd();
    }
};

// Clase Circulo derivada de Primitiva
class Circulo : public Primitiva {
public:
    float radio;

    Circulo(float radio) : radio(radio) {}

    void dibujar() override {
        aplicarColor();
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= 100; ++i) {
            float angulo = 2 * M_PI * i / 100;
            glVertex2f(radio * cos(angulo), radio * sin(angulo));
        }
        glEnd();
    }
};

// Clase Trapecio derivada de Primitiva
class Trapecio : public Primitiva {
public:
    float anchoSuperior, anchoInferior, altura;

    Trapecio(float anchoSuperior, float anchoInferior, float altura)
        : anchoSuperior(anchoInferior), anchoInferior(anchoSuperior), altura(altura) {}

    void dibujar() override {
        aplicarColor();
        glBegin(GL_QUADS);
        glVertex2f(-anchoInferior / 2, -altura / 2);
        glVertex2f(anchoInferior / 2, -altura / 2);
        glVertex2f(anchoSuperior / 2, altura / 2);
        glVertex2f(-anchoSuperior / 2, altura / 2);
        glEnd();
    }
};

float zoom = 1.0f;
float rotacion = 0.0f;
float posicionX = 0.0f;
float posicionY = 0.0f;

Primitiva* casa;

void mostrarColores() {
    cout << "Seleccione un color para la casa:\n";
    cout << "1. Rojo\n";
    cout << "2. Verde\n";
    cout << "3. Azul\n";
    cout << "4. Amarillo\n";
    cout << "5. Cian\n";
    cout << "6. Magenta\n";
    cout << "Seleccione una opcion: ";
}

void elegirColor(int opcion) {
    switch (opcion) {
    case 1:
        casa->establecerColor(1.0f, 0.0f, 0.0f);
        break;
    case 2:
        casa->establecerColor(0.0f, 1.0f, 0.0f);
        break;
    case 3:
        casa->establecerColor(0.0f, 0.0f, 1.0f);
        break;
    case 4:
        casa->establecerColor(1.0f, 1.0f, 0.0f);
        break;
    case 5:
        casa->establecerColor(0.0f, 1.0f, 1.0f);
        break;
    case 6:
        casa->establecerColor(1.0f, 0.0f, 1.0f);
        break;
    default:
        casa->establecerColor(1.0f, 1.0f, 1.0f);
        break;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glScalef(zoom, zoom, 1.0f);
    glRotatef(rotacion, 0.0f, 0.0f, 1.0f);
    glTranslatef(posicionX, posicionY, 0.0f);

    // Piso
    glBegin(GL_LINES);
    glVertex2f(-1.0f, -0.5f);
    glVertex2f(1.0f, -0.5f);
    glEnd();

    // Cuerpo
    casa->dibujar();

    // Puerta
    Rectangulo puerta(0.2f, 0.4f);
    puerta.establecerColor(0.5f, 0.25f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, -0.3f, 0.0f);
    puerta.dibujar();
    glPopMatrix();

    // Ventana lateral
    Cuadrado ventana(0.2f);
    ventana.establecerColor(0.0f, 0.5f, 1.0f);
    glPushMatrix();
    glTranslatef(-0.35f, 0.1f, 0.0f);
    ventana.dibujar();
    glPopMatrix();

    // Ventana circular frontal
    Circulo ventanaCircular(0.1f);
    ventanaCircular.establecerColor(1.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.35f, 0.1f, 0.0f);
    ventanaCircular.dibujar();
    glPopMatrix();

    // Techo
    Trapecio techo(1.2f, 1.0f, 0.5f);
    techo.establecerColor(0.8f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    techo.dibujar();
    glPopMatrix();

    glPopMatrix();
    glFlush();
}

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
    case '+':
        zoom += 0.1f;
        break;
    case '-':
        zoom -= 0.1f;
        break;
    case 'r':
        rotacion += 5.0f;
        break;
    case 'w':
        rotacion -= 5.0f;
        break;
    }
    glutPostRedisplay();
}

void teclasEspeciales(int tecla, int x, int y) {
    switch (tecla) {
    case GLUT_KEY_UP:
        posicionY += 0.1f;
        break;
    case GLUT_KEY_DOWN:
        posicionY -= 0.1f;
        break;
    case GLUT_KEY_LEFT:
        posicionX -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        posicionX += 0.1f;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    casa = new Cuadrado(1.0f);

    mostrarColores();
    int opcion;
    cin >> opcion;
    elegirColor(opcion);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Casa en OpenGL.");

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclasEspeciales);
    glutMainLoop();
    return 0;
}
