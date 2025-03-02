#include <GL/glut.h>
#include <time.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>

clock_t start;
int draw_DDA()
{

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(300.0 / 50.0);

    glBegin(GL_POINTS);

    int startx = 0, starty = 0, endx = 10, endy = 5;
    int dx = endx - startx, dy = endy - starty;

    int steps = dx > dy ? dx : dy;
    double incx = (double)dx / steps, incy = (double)dy / steps;
    double x = startx, y = starty;
    for (int i = 0; i < steps; i++)
    {
        glVertex2d((int)round(x), (int)round(y));
        x += incx;
        y += incy;
    }

    glEnd();
    glFlush();
}

int draw_BLA()
{

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(300.0 / 50.0);

    glBegin(GL_POINTS);

    int startx = 1, starty = 1, endx = 8, endy = 5;
    int dx = endx - startx, dy = endy - starty;
    int x = startx, y = starty;

    int p = 2 * dy - dx;
    int d = p >= 0 ? 1 : 0;
    for (x = startx; x <= endx; x++)
    {

        glVertex2d(x, y);
        printf("%d %d\n", x, y);

        y += d;

        p = p + 2 * dy - 2 * dx * d;
        d = p >= 0 ? 1 : 0;
    }

    glEnd();
    glFlush();
}

void draw_name()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2i(10, 10);

    char *text = "suhas";
    while (*text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *text++);
    }

    glFlush();
}

void draw_circle()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_LOOP);
    glColor3d(1.0, 1.0, 1.0);

    double cx = 20, cy = 20, r = 10;
    double time_passed = ((clock() - start)*0.0001);
    cx += time_passed;
    // printf("time : %d", ((int)start));
    // time_t curr_time = time(0) - start;
    // printf(curr_time);
    for (double angle = 0, x, y; angle < 2 * 3.1415; angle += 0.01)
    {
        x = cos(angle) * r + cx;
        y = sin(angle) * r + cy;
        glVertex2d(x, y);
    }

    glEnd();
    glFlush();
}

int draw()
{
    // draw_BLA();
    // draw_name();
    draw_circle();
}

void setup(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("My Window");

    glutDisplayFunc(draw);

    gluOrtho2D(-1.0, 50.0, -1.0, 50.0);

    glutInitWindowSize(300, 300);
}

int main(int argc, char **argv)
{
    start = clock();
    
    setup(argc, argv);

    glutMainLoop();
}