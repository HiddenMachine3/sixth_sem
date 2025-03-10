#include <GL/gl.h>
#include <GL/glut.h>


void draw(){}

void setup(int *argc, char **argv)
{
    glutInit(argc, argv);

    glutInitWindowSize(700, 500);
    glutCreateWindow("My window");

    int view_port_w = 700, view_port_h = 500;
    glViewport(100, 400 - view_port_h, view_port_w, view_port_h);

    glutDisplayFunc(draw);
}

int main(int argc, char **argv)
{
    setup(&argc, argv);
    glutMainLoop();
}