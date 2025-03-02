
#include <GL/glut.h>
/*float p1[]={100.0,100.0};
float p2[]={150.0,200.0};*/
// Initialize OpenGL
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    /*glVertex2fv(p1);
    glVertex2fv(p2);*/
    glVertex2d(100, 100);
    glVertex2d(150, 100);
    glVertex2d(200, 150);
    glVertex2d(180, 200);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Example");
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
}
