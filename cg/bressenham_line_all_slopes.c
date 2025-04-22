#include <GL/glut.h>

int draw_BLA()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(300.0 / 50.0);
    glBegin(GL_POINTS);

    int startx = 1, starty = 1, endx = 8, endy = 5;

    int dx = abs(endx - startx), dy = abs(endy - starty);
    
    int inc_x = startx < endx ? 1 : -1;
    int inc_y = starty < endy ? 1 : -1;
    int err = dx-dy;
    int e2;

    for (int x = startx, y = starty; x <= endx && y<=endy;)
    {

        glVertex2d(x, y);
        printf("%d %d\n", x, y);

        e2 = 2*err;
        if (e2 > -dy){
            x += inc_x;
            err -= dy;
        }
        if (e2 < dx){
            y += inc_y;
            err += dx;
        }
    }

    glEnd();
    glFlush();
}

void setup(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("My Window");

    glutDisplayFunc(draw_BLA);

    gluOrtho2D(-1.0, 50.0, -1.0, 50.0);

    glutInitWindowSize(300, 300);
}

int main(int argc, char **argv)
{
    setup(argc, argv);

    glutMainLoop();
}