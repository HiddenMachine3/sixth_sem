#include <GL/glut.h>

//Initialize OpenGL 
void init(void) {
    glClearColor(1.0,1.0,1.0,0.0); 
    glMatrixMode(GL_PROJECTION); 
    glOrtho(-300.0,300.0,-300.0,300.0,-300.0,300.0);    
} 

void drawpoint(void) {
    glClear(GL_COLOR_BUFFER_BIT);  
    glColor3f(1.0,0.0,0.0); 
    glPointSize(2.0);
    glBegin(GL_POINTS);
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
    glutDisplayFunc(drawpoint); 
    glutMainLoop();
}

