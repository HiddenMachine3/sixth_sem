#include <math.h>
#include <GL/glut.h>

//Initialize OpenGL 
void init(void) {
    glClearColor(1.0,1.0,1.0,0.0); 
    glMatrixMode(GL_PROJECTION); 
    gluOrtho2D(0.0,300.0,0.0,300.0);    
} 

void drawline(void) {
    glClear(GL_COLOR_BUFFER_BIT);  
    glColor3f(1.0,0.4,0.2); 
	//glLineWidth(10.0);
     glBegin(GL_LINES);
    glVertex2d(100, 100);
    glVertex2d(150, 100);
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
    glutDisplayFunc(drawline); 
    glutMainLoop();
}

