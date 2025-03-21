#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#include <stdlib.h>
#include <stdio.h>
// #include "vec.h"

const int WIDTH = 500, HEIGHT = 500;
float cameraPos[] = {0, 0, -1};
float cameraAngles[] = {0.0, 0.0, 1.0};
float cameraDir[] = {0.0, 0.0, 0.0};

float cube[9][3] = {
    {1, 1, 1},
    {1, -1, 1},
    {-1, -1, 1},
    {-1, 1, 1},
    {-1, 1, -1},
    {-1, -1, -1},
    {1, -1, -1},
    {1, 1, -1}};

float *cube_quads[6][4] = {
    {cube[0], cube[1], cube[2], cube[3]},
    {cube[0], cube[7], cube[6], cube[1]},
    {cube[0], cube[3], cube[4], cube[7]},

    {cube[5], cube[4], cube[3], cube[2]},
    {cube[5], cube[2], cube[1], cube[6]},
    {cube[5], cube[6], cube[7], cube[4]},
};

void draw_cube()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    float side = 0.5;

    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], cameraPos[0], cameraPos[1], cameraPos[2] + 1, 0, 1, 0);

    glScalef(side, side, side);

    glRotatef(cameraAngles[0], 1, 0, 0);
    glRotatef(cameraAngles[1], 0, 1, 0);
    glRotatef(cameraAngles[2], 0, 0, 1);

    for (int j = 0; j < 6; j++)
    {
        glBegin(GL_QUADS);
        int c = j + 1;
        glColor3f((c & 1) > 0, (c & 2) > 0, (c & 4) > 0);
        for (int idx = 0; idx < 4; idx++)
            glVertex3f(cube_quads[j][idx][0], cube_quads[j][idx][1], cube_quads[j][idx][2]);
        glEnd();
    }

    glPopMatrix();

    glFlush();

    glutPostRedisplay();
}

void draw()
{
    draw_cube();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        cameraAngles[0] += 0.5;
        break;
    case 'w':
        cameraAngles[0] -= 0.5;
        break;
    case 'd':
        cameraAngles[1] += 0.5;
        break;
    case 'a':
        cameraAngles[1] -= 0.5;
        break;

    case 'i':
        // add(cameraPos, cameraPos, cameraDir, 3);
        cameraPos[2] += 0.05;
        break;
    case 'k':
        cameraPos[2] -= 0.05;
        break;
    case 'j':
        cameraPos[0] -= 0.05;
        break;
    case 'l':
        cameraPos[0] += 0.05;
        break;
    }
}

void setup(int *argc, char **argv)
{
    glutInit(argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Rotating Triangle");
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    glClearColor(0, 0, 0, 0);
    glutInitDisplayMode(GL_RGB);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 1.0, 10.0);
}

int main(int argc, char **argv)
{
    setup(&argc, argv);
    glutMainLoop();
}