#include<iostream>
#include "window.h"

class Test : public grafx::Window{
	public:
		Test(char* title) : Window(title, 800, 480){}
		void init(){}
		void render(){}
		void resize(int width, int height){}
		void update(float deltaTime){ std::cout<<1/deltaTime<<std::endl; }
		void dispose(){}
};

int main(int argc,char **argv){
	char title[] = "Grafx Engine";
	Test test(title);
	grafx::run(argc, argv, &test);
	return 0;
}