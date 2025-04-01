#include <GL/glut.h>
#include <time.h>
#include <GL/gl.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "teapot_config.h"

const int WIDTH = 500, HEIGHT = 500;

clock_t start;

#define points 100
float circle_points[points][2];

float torus_points[points][points][3];
float tetrahedron_points[4][3] = {
    {0, 1, 1},
    {1, 1, 0},
    {0, 0, 0},
    {1, 0, 1},
};
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
const float r = 1.5;
const float big_r = 4.0;
float light_dir[3] = {-1, -1, -0.5};


void normalize(float v[])
{
    // normalizing
    float mag = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= mag;
    v[1] /= mag;
    v[2] /= mag;
}

float dot(float v1[], float v2[])
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void cross(float v1[], float v2[], float res[])
{
    float a1 = v1[0], a2 = v2[0],
          b1 = v1[1], b2 = v2[1],
          c1 = v1[2], c2 = v2[2];

    res[0] = b1 * c2 - b2 * c1;
    res[1] = a2 * c1 - a1 * c2;
    res[2] = a1 * b2 - a2 * b1;
}

float max(float a, float b)
{

    return a > b ? a : b;
}

void subtract(float v1[], float v2[], float res[])
{
    res[0] = v1[0] - v2[0];
    res[1] = v1[1] - v2[1];
    res[2] = v1[2] - v2[2];
}

void load_obj_file(char *filename, float dest[])
{
}

void draw_teapot()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    clock_t curr = clock() - start;
    double s = ((double)curr) / CLOCKS_PER_SEC;
    s *= 0.5;

    float side = 0.5;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-s * 360, 1, 0, 0);
    glRotatef(-s * 360 * 0.5, 0, 0, 1);
    glRotatef(-s * 360 * 0.3, 0, 1, 0);

    side *= 0.8*sin(s);

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

        // // printf(" %f %f %f", v2[0], v2[1], v2[2]);

        normalize(v1);
        normalize(v2);

        cross(v1, v2, surface_normal);
        normalize(surface_normal);

        b = dot(surface_normal, light_dir);
        b = max(0.1, b); // clipping
        glBegin(GL_TRIANGLES);

        glColor3f(1*b, 1*b, 1*b);
        // glColor3f(1,1,1);
        glVertex3f(triangle[0][0], triangle[0][1], triangle[0][2]);
        glVertex3f(triangle[1][0], triangle[1][1], triangle[1][2]);
        glVertex3f(triangle[2][0], triangle[2][1], triangle[2][2]);

        // printf("%f %f %f", triangle[0][0], triangle[0][1], triangle[0][2]);
        // printf("%f %f %f", triangle[1][0], triangle[1][1], triangle[1][2]);
        // printf("%f %f %f", triangle[2][0], triangle[2][1], triangle[2][2]);
        glEnd();
    }

    glFlush();

    glutPostRedisplay();
}

void draw()
{
    // draw_teapot();
    draw_torus();
}

void draw_torus()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    clock_t curr = clock() - start;
    double s = ((double)curr) / CLOCKS_PER_SEC;
    s *= 0.5;

    float side = 0.1;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-s * 360, 1, 0, 0);
    glRotatef(-s * 360 * 0.5, 0, 0, 1);
    glRotatef(-s * 360 * 0.3, 0, 1, 0);

    side = sin(s) * side;

    glScalef(side, side, side);

    float b = 0;
    float surface_normal[3];
    for (int j = 0; j < points; j++)
    {
        int next_j = j != points - 1 ? j + 1 : 0;

        for (int i = 0; i < points; i++)
        {
            int next_i = i != points - 1 ? i + 1 : 0;

            float v1[3] = {torus_points[next_j][i][0] - torus_points[j][i][0],
                           torus_points[next_j][i][1] - torus_points[j][i][1],
                           torus_points[next_j][i][2] - torus_points[j][i][2]},
                  v2[3] = {torus_points[j][next_i][0] - torus_points[j][i][0],
                           torus_points[j][next_i][1] - torus_points[j][i][1],
                           torus_points[j][next_i][2] - torus_points[j][i][2]};

            normalize(v1);
            normalize(v2);

            cross(v1, v2, surface_normal);
            normalize(surface_normal);

            b = dot(surface_normal, light_dir);
            b = max(0.1, b); // clipping
            glBegin(GL_QUADS);

            glColor3f(b, b, b);
            glVertex3f(torus_points[j][i][0], torus_points[j][i][1], torus_points[j][i][2]);
            glVertex3f(torus_points[next_j][i][0], torus_points[next_j][i][1], torus_points[next_j][i][2]);
            glVertex3f(torus_points[next_j][next_i][0], torus_points[next_j][next_i][1], torus_points[next_j][next_i][2]);
            glVertex3f(torus_points[j][next_i][0], torus_points[j][next_i][1], torus_points[j][next_i][2]);
            glEnd();
        }
    }

    glFlush();

    glutPostRedisplay();

    // for (int i = 0; i < 4; i++)
    // {

    //     int next_i = (i + 1) % 4, next_next_i = (i + 2) % 4;

    //     float v1[3], v2[3];
    //     subtract(tetrahedron_points[next_i], tetrahedron_points[i], v1);
    //     subtract(tetrahedron_points[next_next_i], tetrahedron_points[next_i], v2);

    //     normalize(v1);
    //     normalize(v2);

    //     cross(v1, v2, surface_normal);
    //     normalize(surface_normal);

    //     b = dot(surface_normal, light_dir);
    //     b = max(0.1, b); // clipping
    //     glColor3f(b, b, b);
    //     glBegin(GL_TRIANGLES);

    //     // printf("%d %d %d\n", i, next_i, next_next_i);
    //     glVertex3f(tetrahedron_points[i][0], tetrahedron_points[i][1], tetrahedron_points[i][2]);
    //     glVertex3f(tetrahedron_points[next_i][0], tetrahedron_points[next_i][1], tetrahedron_points[next_i][2]);
    //     glVertex3f(tetrahedron_points[next_next_i][0], tetrahedron_points[next_next_i][1], tetrahedron_points[next_next_i][2]);

    //     glEnd();
    // }

    // for (int i = 0; i < 6; i++)
    // {

    //     float v1[3], v2[3];
    //     subtract(cube_quads[i][0], cube_quads[i][1], v1);
    //     subtract(cube_quads[i][0], cube_quads[i][3], v2);

    //     normalize(v1);
    //     normalize(v2);

    //     cross(v1, v2, surface_normal);
    //     normalize(surface_normal);

    //     b = dot(surface_normal, light_dir);
    //     b = max(0.1, b); // clipping
    //     glColor3f(b, b, b);
    //     glBegin(GL_QUADS);

    //     // printf("%d %d %d\n", i, next_i, next_next_i);
    //     for (int j = 0; j < 4; j++)
    //         glVertex3f(cube_quads[i][j][0], cube_quads[i][j][1], cube_quads[i][j][2]);
    //     glEnd();

    //     glColor3f(0, b, 0);
    //     glBegin(GL_LINE_LOOP);
    //     for (int j = 0; j < 4; j++)
    //         glVertex3f(cube_quads[i][j][0], cube_quads[i][j][1], cube_quads[i][j][2]);
    //     glEnd();
    // }

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
    glEnable(GL_DEPTH_TEST);

    start = clock();

    float theta = 0;

    for (int i = 0; i < points; i++)
    {
        theta = 2 * 3.14152 * ((float)i / points);
        float x = r * cos(theta), y = r * sin(theta);
        circle_points[i][0] = x;
        circle_points[i][1] = y;
    }

    for (int j = 0; j < points; j++)
    {
        theta = 2 * 3.14152 * (float)j / points;
        float cx = big_r * cos(theta), cz = big_r * sin(theta);

        for (int i = 0; i < points; i++)
        {
            float curr_circle_point_x = (circle_points[i][0] + big_r) * cos(theta);
            float curr_circle_point_y = circle_points[i][1];
            float curr_circle_point_z = (circle_points[i][0] + big_r) * sin(theta);
            torus_points[j][i][0] = curr_circle_point_x;
            torus_points[j][i][1] = curr_circle_point_y;
            torus_points[j][i][2] = curr_circle_point_z;
        }
    }

    // getting the center of the tetrahedron to the origin
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
            tetrahedron_points[i][j] -= 0.5;
    }

    for (int i = 0; i < 4; normalize(tetrahedron_points[i]), i++)
        ;

    // approximating a sphere using the tetrahedron
    // TODO

    normalize(light_dir);
}

int main(int argc, char **argv)
{
    setup(&argc, argv);
    glutMainLoop();
}