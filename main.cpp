#include<iostream>
#include "shape.h"
#include "window.h"

class Test : public grafx::Window{
	private:
		grafx::Plane* model;
		grafx::Renderer* renderer;
	public:
		Test(char* title) : Window(title, 800, 480){}
		void init(){
			grafx::SimpleMaterial material;
			this->model = new grafx::Plane(&material);
			
			grafx::PerspectiveCamera * camera = new grafx::PerspectiveCamera(new grafx::Vector3(0, 0, 3), grafx::ZeroVector());
			grafx::ViewPort3D* port = new grafx::ViewPort3D(67, 480, 800);
			
			this->renderer = new grafx::Renderer(port, camera);
		}
		void render(){
			this->model->draw(renderer);
		}
		void resize(int width, int height){}
		void update(float deltaTime){ }
		void dispose(){
			this->model->dispose();
		}
};

int main(int argc,char **argv){
	char title[] = "Grafx Engine";
	Test test(title);
	grafx::run(argc, argv, &test);
	return 0;
}