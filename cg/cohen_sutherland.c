#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void draw_rect(float xstart, float ystart, float xend, float yend)
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xstart, ystart);
    glVertex2f(xend, ystart);
    glVertex2f(xend, yend);
    glVertex2f(xstart, yend);
    glEnd();
}

void draw_points(float x1, float y1, float x2, float y2)
{
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(10.0);

    glBegin(GL_POINTS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void draw_line(float x1, float y1, float x2, float y2)
{
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void apply_cohen_sutherland(float x1, float y1, float x2, float y2, float xstart, float ystart, float xend, float yend, float *x1new, float *y1new, float *x2new, float *y2new)
{
    float m = (y2 - y1) / (x2 - x1);
    float x, y;

    // Top
    if (y1 > yend)
    {
        x = x1 + (yend - y1) / m;
        y = yend;
        x1 = x;
        y1 = y;
    }

    if (y2 > yend)
    {
        x = x2 + (yend - y2) / m;
        y = yend;
        x2 = x;
        y2 = y;
    }

    // Bottom
    if (y1 < ystart)
    {
        x = x1 + (ystart - y1) / m;
        y = ystart;
        x1 = x;
        y1 = y;
    }

    if (y2 < ystart)
    {
        x = x2 + (ystart - y2) / m;
        y = ystart;
        x2 = x;
        y2 = y;
    }

    // Right
    if (x1 > xend)
    {
        y = y1 + m * (xend - x1);
        x = xend;
        x1 = x;
        y1 = y;
    }

    if (x2 > xend)
    {
        y = y2 + m * (xend - x2);
        x = xend;
        x2 = x;
        y2 = y;
    }

    // Left
    if (x1 < xstart)
    {
        y = y1 + m * (xstart - x1);
        x = xstart;
        x1 = x;
        y1 = y;
    }

    if (x2 < xstart)
    {
        y = y2 + m * (xstart - x2);
        x = xstart;
        x2 = x;
        y2 = y;
    }

    *x1new = x1;
    *y1new = y1;
    *x2new = x2;
    *y2new = y2;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float xstart = 100, ystart = 100, xend = 250, yend = 300;
    float x1 = 80, y1 = 120, x2 = 150, y2 = 200;
    float x1new, y1new, x2new, y2new;

    apply_cohen_sutherland(x1, y1, x2, y2, xstart, ystart, xend, yend, &x1new, &y1new, &x2new, &y2new);

    draw_rect(xstart, ystart, xend, yend);
    draw_points(x1, y1, x2, y2);
    draw_line(x1new, y1new, x2new, y2new);

    glFlush();
}

void init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(400, 300);
    glutCreateWindow("Cohen Sutherland");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);

    glutDisplayFunc(display);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void main(int argc, char **argv)
{
    init(argc, argv);
    glutMainLoop();
}