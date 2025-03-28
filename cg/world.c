#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "teapot_config.h"
#include "cube_config.h"
#include "vec.h"

const int WIDTH = 500, HEIGHT = 500;
const float pi = 3.141527;

float cameraPos[] = {0, 0, -2};
float cameraAngles[] = {0.0, 0.0, 0.0};
float cameraDir[3] = {0, 0, 1}, right[3] = {1, 0, 0}, up[3] = {0, 1, 0},
      origCameraDir[] = {0, 0, 1}, origUp[] = {0, 1, 0}, origRight[] = {1, 0, 0},
    center[3] = {0, 0, 0};
float light_dir[3] = {0, 1, 1};

clock_t start;

void draw_cube()
{
    float side = 0.5;
    glScalef(side, side, side);

    glTranslatef(-5, 0, 0);

    glColor3f(1.0, 1.0, 1.0);

    for (int j = 0; j < 6; j++)
    {
        glBegin(GL_QUADS);
        int c = j + 1;
        glColor3f((c & 1) > 0, (c & 2) > 0, (c & 4) > 0);
        for (int idx = 0; idx < 4; idx++)
            glVertex3f(cube_quads[j][idx][0], cube_quads[j][idx][1], cube_quads[j][idx][2]);
        glEnd();
    }
    glTranslatef(+5, 0, 0);
}

void draw_teapot()
{
    clock_t curr = clock() - start;
    double s = ((double)curr) / CLOCKS_PER_SEC;
    s *= 0.5;

    float side = 0.5;
    glTranslatef(3, 0, 0);

    glRotatef(-s * 360, 1, 0, 0);
    glRotatef(-s * 360 * 0.5, 0, 0, 1);
    glRotatef(-s * 360 * 0.3, 0, 1, 0);

    glScalef(side, side, side);

    float b = 0;
    float surface_normal[3];
    for (int j = 0; j < 6320; j++)
    {
        int *idxs = teapot_faces[j];
        float *triangle[3] = {teapot_points[idxs[0] - 1], teapot_points[idxs[1] - 1], teapot_points[idxs[2] - 1]};

        float v1[3] = {triangle[1][0] - triangle[0][0],
                       triangle[1][1] - triangle[0][1],
                       triangle[1][2] - triangle[0][2]},
              v2[3] = {triangle[2][0] - triangle[0][0],
                       triangle[2][1] - triangle[0][1],
                       triangle[2][2] - triangle[0][2]};

        normalize(v1, v1, 3);
        normalize(v2, v2, 3);

        cross(surface_normal, v1, v2, 3);
        normalize(surface_normal, surface_normal, 3);

        b = dot(surface_normal, light_dir, 3);
        // printf("b : %d ", b);
        b = max(0.1, b); // clipping
        glBegin(GL_TRIANGLES);

        glColor3f(1 * b, 1 * b, 1 * b);
        glVertex3f(triangle[0][0], triangle[0][1], triangle[0][2]);
        glVertex3f(triangle[1][0], triangle[1][1], triangle[1][2]);
        glVertex3f(triangle[2][0], triangle[2][1], triangle[2][2]);
        glEnd();
    }
    glTranslatef(-3, 0, 0);
}

void cameraTransformations()
{
    add(center, cameraPos, cameraDir, 3);
    gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2],
              center[0], center[1], center[2], up[0], up[1], up[2]);
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    cameraTransformations();

    draw_cube();
    draw_teapot();

    glFlush();
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'k':
        cameraAngles[0] += 0.5;
        // cameraAngles[0] %= 2*pi;
        break;
    case 'i':
        cameraAngles[0] -= 0.5;
        break;
    case 'l':
        cameraAngles[1] -= 0.5;
        break;
    case 'j':
        cameraAngles[1] += 0.5;
        break;

    case 'w':
        add(cameraPos, cameraPos, cameraDir, 3);
        // printf("cameraDir : (%f,%f,%f), cameraPos : (%f,%f,%f) cameraAngles : (%f,%f,%f)\n", cameraDir[0], cameraDir[1], cameraDir[2], cameraPos[0], cameraPos[1], cameraPos[2], cameraAngles[0], cameraAngles[1], cameraAngles[2]);
        break;
    case 's':
        sub(cameraPos, cameraPos, cameraDir, 3);
        break;
    case 'd':
        sub(cameraPos, cameraPos, right, 3);
        break;
    case 'a':
        add(cameraPos, cameraPos, right, 3);
        break;
    case ' ':
        add(cameraPos, cameraPos, up, 3);
        break;
    case 'c':
        sub(cameraPos, cameraPos, up, 3);
        break;
    }

    rotate(cameraDir, origCameraDir, cameraAngles);
    rotate(up, origUp, cameraAngles);
    rotate(right, origRight, cameraAngles);
}

void setup(int *argc, char **argv)
{
    init_vec();
    start = clock();
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
    gluPerspective(90.0, 1.0, 1.0, 100.0);
}

int main(int argc, char **argv)
{
    setup(&argc, argv);
    glutMainLoop();
}