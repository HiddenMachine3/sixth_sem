#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

int r, cx, cy;

void plot_symmetric_points(int x, int y, int cx, int cy)
{
    glVertex2i(x + cx, y + cy);
    glVertex2i(x + cx, -y + cy);
    glVertex2i(-x + cx, -y + cy);
    glVertex2i(-x + cx, y + cy);

    glVertex2i(y + cx, x + cy);
    glVertex2i(y + cx, -x + cy);
    glVertex2i(-y + cx, -x + cy);
    glVertex2i(-y + cx, x + cy);
}
void draw_circle()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    glColor3d(1.0, 1.0, 1.0);
    glPointSize(5);
    

    int x = 0, y = r;
    int p = (5 / 4) - r;

    for (; x <y; x++)
    {
        plot_symmetric_points(x, y, cx, cy);

        if (p < 0)
            p = p + 2 * (x + 1) + 1;
        else
        {
            p = p + 2 * (x + 1) + 1 - 2 * (y - 1);
            y--;
        }
    }
    
    
    glEnd();
    glFlush();
}

void setup(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("My Window");

    glutDisplayFunc(draw_circle);

    gluOrtho2D(0.0, 300.0, 0.0, 300.0);

    glutInitWindowSize(300, 300);
}

int main(int argc, char **argv)
{
    printf("Enter radius, center x and center y separated by spaces : ");

    scanf("%d %d %d", &r, &cx, &cy);

    setup(argc, argv);

    glutMainLoop();
}