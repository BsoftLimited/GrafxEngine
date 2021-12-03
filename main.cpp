#include <GLFW/glfw3.h>

#include<GL/freeglut.h>

//Program to create an empty Widdow
void init(){
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);	//Line C
	glutInitWindowSize(800,480);
	glutCreateWindow("Grafx Engine");
}

void display(){
	glClearColor(0.0,0.0,0.1,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc,char **argv){
	glutInit(&argc,argv);			//Line A
	init();					//Line B
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}