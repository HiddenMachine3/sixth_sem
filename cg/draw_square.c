/* Menus*/
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

void init()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluOrtho2D(0.0,500.0,0.0,500.0);
}


void display()
 {  
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glLineWidth(3.0);
         glBegin(GL_POLYGON);
	 glVertex2i(100,100);
	 glVertex2i(250,100);
	 glVertex2i(250,300);
	 glVertex2i(100,300);
     	glEnd();
	glFlush();                
}

void main(int argc,char** argv)
{   
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(400,300);
	glutCreateWindow("Draw square");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

