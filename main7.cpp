#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

#define M_PI 3.1416
vector<float> porcentajes;
vector<vector<float>> colores = {
    {1.0f, 0.0f, 0.0f}, // rojo
    {0.0f, 1.0f, 0.0f}, // verde
    {0.0f, 0.0f, 1.0f}  // azul 
};

void dibujarSector(float angulo_i, float angulo_barrido, float radio) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (float angulo = angulo_i; angulo <= angulo_i + angulo_barrido; angulo += 1.0f) {
        float rad = angulo * M_PI / 180.0f;
        glVertex2f(radio * cos(rad), radio * sin(rad));
    }
    glVertex2f(radio * cos((angulo_i + angulo_barrido) * M_PI / 180.0f), radio * sin((angulo_i + angulo_barrido) * M_PI / 180.0f));
    glEnd();
}

void mostrar() {
    glClear(GL_COLOR_BUFFER_BIT);
    float radio = 0.5f;
    float angulo_i = 0.0f;
    int color_index = 0;
    for (size_t i = 0; i < porcentajes.size(); ++i) {
        float angulo_barrido = (porcentajes[i] / 100.0f) * 360.0f;
        glColor3f(colores[color_index][0], colores[color_index][1], colores[color_index][2]);
        dibujarSector(angulo_i, angulo_barrido, radio);
        angulo_i += angulo_barrido;
        color_index = (color_index + 1) % colores.size();
    }
    glFlush();
}

void iniciar() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    float valor;
    cout << "Ingrese los porcentajes para los sectores circulares (la suma total debe ser 100):" << endl;
    while (cin >> valor) {
        porcentajes.push_back(valor);
        if (cin.get() == '\n') break;
    }

    float suma = 0;
    for (float p : porcentajes) suma += p;
    if (suma != 100.0f) {
        cerr << "La suma de los porcentajes debe ser 100. Actualmente es: " << suma << endl;
        return -1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sectores Circulares");
    iniciar();
    glutDisplayFunc(mostrar);
    glutMainLoop();

    return 0;
}
