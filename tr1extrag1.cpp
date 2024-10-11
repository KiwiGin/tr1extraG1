#include <GL/glut.h>
#include <iostream>

//LINEA EN 3D - TECLADO

// Prototipos
void inicio(void);
void display(void);
void myreshape(int, int);
void dibujarPiso();
void teclado(unsigned char key, int x, int y);

// Variables globales
float lineaPunto1[3] = { -5.0f, 0.0f, -5.0f }; // Primer punto de la línea
float lineaPunto2[3] = { 5.0f, 0.0f, -5.0f };  // Segundo punto de la línea
float anguloYaw = 0.0f;  // Rotación en el eje Y (horizontal)
float anguloPitch = -10.0f; // Rotación en el eje X (vertical)
float distanciaCamara = 20.0f; // Distancia de la cámara al objeto


void dibujarPiso() {

    glBegin(GL_QUADS);

    glColor3f(0.2, 0.5, 0.2); // Verde oscuro (suelo)
    // Pared inferior (suelo)

    glVertex3f(-50.0f, -50.0f, 100.0f);// Esquina inferior izquierda
    glVertex3f(50.0f, -50.0f, 100.0f);// Esquina inferior derecha
    glVertex3f(50.0f, -50.0f, -100.0f);// Esquina superior derecha
    glVertex3f(-50.0f, -50.0f, -100.0f);// Esquina superior izquierda

    glEnd();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Línea 3D con OpenGL");


    inicio();
    glutDisplayFunc(display);
    glutReshapeFunc(myreshape);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}

void inicio(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Mantener la cámara estática
    gluLookAt(0.0, 15.0, 20.0,  // Posición de la cámara (puedes ajustar si es necesario)
        0.0, 0.0, 0.0,   // Punto donde mira la cámara
        0.0, 1.0, 0.0);  // Vector 'arriba'

    // Dibujar el skybox y la línea
    dibujarPiso();
    // Aplicar la rotación SOLO a la línea
    glPushMatrix();  // Guardar la matriz actual
    // Rotar la línea según los ángulos de 'yaw' y 'pitch'
    glRotatef(anguloYaw * (180.0 / 3.14159), 0.0f, 1.0f, 0.0f);  // Rotación alrededor del eje Y
    glRotatef(anguloPitch * (180.0 / 3.14159), 1.0f, 0.0f, 0.0f); // Rotación alrededor del eje X


    glColor3f(1.0, 0.0, 0.0);  // Rojo
    glBegin(GL_LINES);
    glVertex3f(lineaPunto1[0], lineaPunto1[1], lineaPunto1[2]);  // Primer punto
    glVertex3f(lineaPunto2[0], lineaPunto2[1], lineaPunto2[2]);  // Segundo punto
    glEnd();
    glPopMatrix();  // Restaurar la matriz

    glFlush();
}

void teclado(unsigned char key, int x, int y) {
    float velocidadRotacion = 0.05f; // Velocidad de rotación

    switch (key) {
    case 'a': // Girar hacia la izquierda
        anguloYaw -= velocidadRotacion;
        break;
    case 'd': // Girar hacia la derecha
        anguloYaw += velocidadRotacion;
        break;
    case 'w': // Inclinar hacia arriba
        anguloPitch += velocidadRotacion;
        break;
    case 's': // Inclinar hacia abajo
        anguloPitch -= velocidadRotacion;
        break;
    case '+': // Acercar la cámara
        distanciaCamara -= 0.5f;
        if (distanciaCamara < 2.0f) distanciaCamara = 2.0f; // Limitar distancia mínima
        break;
    case '-': // Alejar la cámara
        distanciaCamara += 0.5f;
        break;
    }

    // Redibuja la escena
    glutPostRedisplay();
}


void myreshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (GLfloat)w / (GLfloat)h;

    gluPerspective(45.0, aspect, 0.1, 100.0); // Proyección perspectiva

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
