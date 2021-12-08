#ifndef TRANSFORM_H
	#define TRANSFORM_H

#include "matrix.h"

namespace grafx{
	class Transform : public Matrix4{
		private:
			Vector3* position;
			Vector3* rotation;
			Vector3* scale;
		public:
			Transform(float x, float y, float z);
			Transform(Vector3* position);
			Transform();
		
			void setPosition(float x, float y, float z);
			void setPosition(Vector3* position);
			void translate(float x, float y, float z);
			void translate(Vector3* position);
		
			void setRotation(float x, float y, float z);
			void setRotation(Vector3* rotation);
			void rotate(float x, float y, float z);
			void rotate(Vector3* rotation);
			
			void setScale(float x, float y, float z);
			void setScale(Vector3* scale);
		
			Vector3* getPosition(){ return this->position; }
			Vector3* getRotation(){ return this->rotation; }
			Vector3* getScale(){ return this->scale; }
			
			void update();
	};
}

grafx::Transform::Transform(float x, float y, float z){
	this->position = new Vector3(x, y, z);
	this->rotation = new Vector3(0, 0, 0);
	this->scale = new Vector3(1, 1, 1);
	this->update();
}

grafx::Transform::Transform(Vector3* position){
	this->position = position;
	this->rotation = new Vector3(0, 0, 0);
	this->scale = new Vector3(1, 1, 1);
	this->update();
}

grafx::Transform::Transform(){
	this->position = new Vector3(0, 0, 0);
	this->rotation = new Vector3(0, 0, 0);
	this->scale = new Vector3(1, 1, 1);
	this->update();
}

void grafx::Transform::setPosition(float x, float y, float z){
	this->position->set(x, y, z);
}

void grafx::Transform::setPosition(Vector3* position){
	this->position = position;
}

void grafx::Transform::translate(float x, float y, float z){
	this->position->add(x, y, z);
}

void grafx::Transform::translate(Vector3* position){
	this->position->add(position);
}

void grafx::Transform::setRotation(float x, float y, float z){
	this->rotation->set(x, y, z);
}

void grafx::Transform::setRotation(Vector3* rotation){
	this->rotation = rotation;
}

void grafx::Transform::rotate(float x, float y, float z){
	this->rotation->add(x, y, z);
}

void grafx::Transform::rotate(Vector3* rotation){
	this->rotation->add(rotation);
}

void grafx::Transform::setScale(float x, float y, float z){
	this->scale->set(x, y, z);
}

void grafx::Transform::setScale(Vector3* scale){
	this->scale = scale;
}

void grafx::Transform::update(){
	Matrix4* transM = TranslationMatrix(this->position->getX(), this->position->getY(), this->position->getZ());
	Matrix4* rotM = RotationMatrix(this->rotation->getX(), this->rotation->getY(), this->rotation->getZ());
	Matrix4* scaleM = ScaleMatrix(this->scale->getX(), this->scale->getY(), this->scale->getZ());
	
	this->data = transM->multiply(rotM->multiply(scaleM))->getData();
}

#endif
