#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#include <stdlib.h>
#include <stdio.h>

const int WIDTH = 500, HEIGHT = 500;
float cameraPos[] = {0, 0, -5};
float cameraDir[] = {0.0, 0.0, 1.0};

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
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(cameraDir[0], 1, 0, 0);
    glRotatef(cameraDir[1], 0, 1, 0);
    glRotatef(cameraDir[2], 0, 0, 1);

    glScalef(side, side, side);

    for (int j = 0; j < 6; j++)
    {
        glBegin(GL_QUADS);
        int c = j + 1;
        glColor3f((c & 1) > 0, (c & 2) > 0, (c & 4) > 0);
        for (int idx = 0; idx < 4; idx++)
            glVertex3f(cube_quads[j][idx][0], cube_quads[j][idx][1], cube_quads[j][idx][2]);
        glEnd();
    }

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
        cameraDir[0] += 0.5;
        break;
    case 'w':
        cameraDir[0] -= 0.5;
        break;
    case 'd':
        cameraDir[1] += 0.5;
        break;
    case 'a':
        cameraDir[1] -= 0.5;
        break;
    
    // case 'i':
    //     cameraPos[2] += 0.01;
    //     break;
    // case 'k':
    //     cameraPos[2] -= 0.01;
    //     break;
    // case 'j':
    //     cameraPos[0] -= 0.01;
    //     break;
    // case 'l':
    //     cameraDir[0] += 0.01;
    //     break;
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
}

int main(int argc, char **argv)
{
    setup(&argc, argv);
    glutMainLoop();
}