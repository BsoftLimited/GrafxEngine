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
int oldTimeSinceStart = 0;

void display(){
	glClearColor(0.0,0.0,0.1,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	window->render();
	
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;
	window->update(deltaTime/1000.0);
	
	glutSwapBuffers();
}

void changeSize(int width, int height){
	glViewport(0, 0, width, height);
	window->resize(width, height);
}

void grafx::run(int argc, char **argv, Window* win){
	window = win;

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(window->getWidth(), window->getHeight());
	glutCreateWindow(window->getTitle());
	win->init();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(changeSize);
	glutMainLoop();
	win->dispose();
}

#endif