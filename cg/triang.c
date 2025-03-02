
#include <GL/glut.h>

//Initialize OpenGL 
void init(void) {
    glClearColor(1.0,1.0,1.0,0.0); 
    glMatrixMode(GL_PROJECTION); 
    gluOrtho2D(0.0,300.0,0.0,300.0);    
} 

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);  
    glColor3f(0.0,1.0,0.0); 
    glLineWidth(3.0);
    glBegin(GL_TRIANGLES);
    glVertex2d(100, 100);
    glVertex2d(150, 150);
    glVertex2d(200, 150);
 
     glEnd();
    glFlush();
} 

int main(int argc, char** argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowPosition(10,10); 
    glutInitWindowSize(500,500); 
    
    glutCreateWindow("Example"); 
    init(); 
    glutDisplayFunc(draw); 
    glutMainLoop();
}

