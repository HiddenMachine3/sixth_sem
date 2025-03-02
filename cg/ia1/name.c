#include <GL/glut.h>
#include <math.h>

void draw_name()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2i(10, 10);

    char *text = "suhas 1RVU22CSE168 B";
    for (;*text != '\0';*text++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *text);
    }

    glFlush();
}

void setup(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("My Window");

    glutDisplayFunc(draw_name);

    gluOrtho2D(0.0, 50.0, 0.0, 50.0);

    glutInitWindowSize(300, 300);
}

int main(int argc, char **argv)
{
    setup(argc, argv);

    glutMainLoop();
}