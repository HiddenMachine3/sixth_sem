#include <GL/glut.h>
#include <time.h>
#include <GL/gl.h>

#include <math.h>

const int WIDTH = 500, HEIGHT = 500;

clock_t start;

void draw()
{

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    clock_t curr = clock() - start;
    double s = ((double)curr) / CLOCKS_PER_SEC;

    float side = 0.5;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-s * 360, 0, 0, 1);
    glRotatef(-s * 360*0.5, 1, 0, 0);


    glScalef(side, side, 0);

    glBegin(GL_TRIANGLES);

    glVertex3d(0, 1, 0);
    glVertex3d(cos(3.14152 / 6.0), -sin(3.14152 / 6.0), 0);
    glVertex3d(-cos(3.14152 / 6.0), -sin(3.14152 / 6.0), 0);

    glEnd();
    glFlush();

    glutPostRedisplay();
}

void setup(int *argc, char **argv)
{
    glutInit(argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Rotating Triangle");
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glutDisplayFunc(draw);

    glClearColor(0, 0, 0, 0);
    glutInitDisplayMode(GL_RGB);

    start = clock();
}

int main(int argc, char **argv)
{
    setup(&argc, argv);
    glutMainLoop();
}