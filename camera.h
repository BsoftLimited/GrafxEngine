#ifndef CAMERA_H
	#define CAMERA_H

#include "matrix.h"

namespace grafx{
	class Camera : public Matrix4{
		protected:
			Vector3* position;
		public:
			Camera(Vector3* position){ this->position = position;}
			void setPosition(float x, float y, float z);
			void setPosition(Vector3* position){this->position = position; }
			Vector3* getPosition(){ return this->position; }
	};
	
	class PerspectiveCamera : public Camera{
		private:
			Vector3* target;
		public:
			PerspectiveCamera(Vector3* position, Vector3* target);
			void update();
	};
	
	class ViewPort : public Matrix4{
		protected:
			int portWidth, portHeight;
			ViewPort(int width, int height);
		public:
			void setPortWidth(int width){ this->portWidth = width;}
			void setPortHeight(int height){ this->portHeight = height; }
			void setPort(int width, int height);
			void update(){}
	};
	
	class ViewPort3D : public ViewPort{
		private:
			float fov, far, near;
		public:
			ViewPort3D(float fov, int width, int height, float near, float far);
			ViewPort3D(float fov, int width, int height);
			void setFov(float fov){ this->fov = fov; }
			void setFar(float far){ this->far = far; }
			void setNear(float near){ this->near = near; }
			void update();
	};
}

void grafx::Camera::setPosition(float x, float y, float z){
	this->position->set(x, y, z);
}

grafx::PerspectiveCamera::PerspectiveCamera(grafx::Vector3* position, grafx::Vector3* target) : Camera(position){
	this->target = target;
	this->update();
}

void grafx::PerspectiveCamera::update(){
	this->data = LookAtMatrix(position, target)->getData();
}

grafx::ViewPort::ViewPort(int width, int height){
	this->portWidth = width;
	this->portHeight = height;
}

void grafx::ViewPort::setPort(int width, int height){
	this->portWidth = width;
	this->portHeight = height;
	this->update();
}

grafx::ViewPort3D::ViewPort3D(float fov, int width, int height, float near, float far): ViewPort(width, height){
	this->fov = fov;
	this->far = far;
	this->near = near;
	this->update();
}

grafx::ViewPort3D::ViewPort3D(float fov, int width, int height): ViewPort(width, height){
	this->fov = fov;
	this->far = 1000;
	this->near = 1;
	this->update();
}

void grafx::ViewPort3D::update(){
	this->data = ProjectionMatrix(this->fov, this->portWidth, this->portHeight, this->far, this->near)->getData();
}

#endif
