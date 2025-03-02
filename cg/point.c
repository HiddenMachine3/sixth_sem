#include <GL/glut.h>
int p[]={21,21};
//Initialize OpenGL 
void init(void) {
    // glClearColor(1.0,1.0,1.0,0.0); 
    // glMatrixMode(GL_PROJECTION); 
    gluOrtho2D(0.0,50.0,0.0,50.0);
} 

void drawpoint(void) {
    glClear(GL_COLOR_BUFFER_BIT);  
    glColor3f(1.0,0.4,0.2); 
    glPointSize(5.0);  
	glBegin(GL_POINTS);
	glVertex2iv(p);
     glEnd();
    glFlush();
} 

int main(int argc, char** argv) {
    glutInit(&argc, argv); 
    // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    // glutInitWindowPosition(10,10); 
    // glutInitWindowSize(500,500); 
    
    glutCreateWindow("Example"); 
    init(); 
    glutDisplayFunc(drawpoint); 
    glutMainLoop();
}

