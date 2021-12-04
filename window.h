#ifndef WINDOW_H
	#define WINDOW_H
	
#include<GL/freeglut.h>

namespace grafx{
	class Window{
		private:
			char* title;
			int width, height;
		public:
			Window(char* title, int width, int height);
			virtual void init() = 0;
			virtual void render() = 0;
			virtual void update(float deltaTime) = 0;
			virtual void resize(int width, int height) = 0;
			int getWidth();
			int getHeight();
			char* getTitle();
			virtual void dispose() = 0;
	};
	
	void run(int argc, char **argv, Window* win);
}

grafx::Window::Window(char* title, int width, int height){
	this->title = title;
	this->width = width;
	this->height = height;
}

int grafx::Window::getWidth(){ return this->width; }
int grafx::Window::getHeight(){ return this->height; }
char* grafx::Window::getTitle(){ return this->title; }

grafx::Window* window;

void display(){
	glClearColor(0.0,0.0,0.1,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	window->render();
	glFlush();
}

void grafx::run(int argc, char **argv, Window* win){
	window = win;

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(window->getWidth(), window->getHeight());
	glutCreateWindow(window->getTitle());
	win->init();

	glutDisplayFunc(display);
	glutMainLoop();
	win->dispose();
}

#endif