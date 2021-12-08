#ifndef RENDERER_H
	#define RENDERER_H

#include "camera.h"
#include "light.h"

namespace grafx{
	class Renderer{
		private:
			Camera* camera;
			ViewPort* port;
			std::vector<Light*> lights;
		public:
			Renderer(ViewPort* port, Camera* camera);
			void addLight(Light* light);
			void removeLight(Light* light);
			void setCamera(Camera* camera);
			void setViewPort(ViewPort* port);
			Camera* getCamera();
			ViewPort* getViewPort();
	};
}

grafx::Renderer::Renderer(ViewPort* port, Camera* camera){
	this->port = port;
}

void grafx::Renderer::addLight(Light* light){
	this->lights.push_back(light);
}

grafx::Camera* grafx::Renderer::getCamera(){
	return this->camera;
}

void grafx::Renderer::removeLight(Light* light){
	for(int i=0; i < lights.size(); i++){
		if(lights[i] == light){
			lights.erase(lights.begin() + i);
			break;
		}
	}
}

void grafx::Renderer::setCamera(Camera* camera){
	this->camera = camera;
}

void grafx::Renderer::setViewPort(ViewPort* port){
	this->port = port;
}

grafx::ViewPort* grafx::Renderer::getViewPort(){
	return this->port;
}

#endif
