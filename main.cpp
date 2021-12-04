#include<iostream>
#include "window.h"

class Test : public grafx::Window{
	public:
		Test(char* title) : Window(title, 800, 480){}
		void init(){
			grafx::SimpleMaterial material;
			//std::cout<<material.getProgram();
		}
		void render(){}
		void resize(int width, int height){}
		void update(float deltaTime){ }
		void dispose(){}
};

int main(int argc,char **argv){
	char title[] = "Grafx Engine";
	Test test(title);
	grafx::run(argc, argv, &test);
	return 0;
}