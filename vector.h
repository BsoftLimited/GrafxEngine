#ifndef VECTOR_H
	#define VECTOR_H

#include "utils.h"

namespace grafx{
	class Data{
		protected:
			float* data;
			Data(float* data){ this->data = data; }
		public:
			float* getData(){ return data;}
	};
	
	class Vector : public Data{
		private:
			int size;
		protected:
			Vector(int n);
		public:
			float magnitude();
			Vector* normalize();
			int getSize(){ return this->size; }
			void print();
	};
	
	class Vector2 : public Vector{
		public:
			Vector2(float x, float y);
			void setX(float x){ this->data[0] = x; }
			void setY(float y){ this->data[1] = y; }
			void set(float x, float y){this->setX(x); this->setY(y); }
			
			float getX(){ return this->data[0];}
			float getY(){ return this->data[1];}
			
			Vector2* cross(Vector2* vector);
			Vector2* cross(float x, float y);
			Vector2* add(Vector2* vector);
			Vector2* add(float x, float y);
			Vector2* minus(Vector2* vector);
			Vector2* minus(float x, float y);
			Vector2* multiply(float value);
			float dot(Vector2* vector);
			float dot(float x, float y);
			Vector2* clone();
	};
	
	class Vector3 : public Vector{
		public:
			Vector3(float x, float y, float z);
			void setX(float x){ this->data[0] = x; }
			void setY(float y){ this->data[1] = y; }
			void setZ(float z){ this->data[2] = z; }
			void set(float x, float y, float z){
				this->setX(x); this->setY(y); this->setZ(z);
			}
			
			float getX(){ return this->data[0];}
			float getY(){ return this->data[1];}
			float getZ(){ return this->data[2];}
			
			
			Vector3* cross(Vector3* vector);
			Vector3* cross(float x, float y, float z);
			Vector3* add(Vector3* vector);
			Vector3* add(float x, float y, float z);
			Vector3* minus(Vector3* vector);
			Vector3* minus(float x, float y, float z);
			Vector3* multiply(float value);
			float dot(Vector3* vector);
			float dot(float x, float y, float z);
			Vector3* clone();
	};
	
	class Quantanion : public Vector{
		public:
			Quantanion(float x, float y, float z, float w);
			void setX(float x){ this->data[0] = x; }
			void setY(float y){ this->data[1] = y; }
			void setZ(float z){ this->data[2] = z; }
			void setW(float w){ this->data[3] = w; }
			
			float getX(){ return this->data[0];}
			float getY(){ return this->data[1];}
			float getZ(){ return this->data[2];}
			float getW(){ return this->data[3];}
			
			Quantanion* multiply(float value);
			float dot(Quantanion* vector);
			Quantanion* clone();
	};
	
	Vector3* ZeroVector(){ return new Vector3(0, 0, 0); }
	Vector3* UpVector(){ return new Vector3(0, 1, 0); }
}

grafx::Vector::Vector(int n) : Data(new float[n]){
	this->size = n;
	for(int i = 0; i < n; i++){
		this->data[i] = 0;
	}
}

float grafx::Vector::magnitude(){
	float init = 0;
	for(int i = 0; i < this->size; i++){
		init += this->data[i] * this->data[i];
	}
	return (float)std::pow(init, 0.5);
}

grafx::Vector* grafx::Vector::normalize(){
	float init = this->magnitude();
	for(int i = 0; i < this->size; i++){
		this->data[i] /= init;
	}
	return this;
}

void grafx::Vector::print(){
	for(int i = 0; i < this->size; i++){
		std::cout<<this->data[i]<<" ";
	}
	std::cout<<std::endl;
}

grafx::Vector2::Vector2(float x, float y) : Vector(2){
	this->data[0] = x;
	this->data[1] = y;
}

grafx::Vector2* grafx::Vector2::cross(float x, float y){
	float i = this->getY() - y;
	float j = this->getX() - x;
	this->setX(i); this->setY(-j);
	return this;
}
grafx::Vector2* grafx::Vector2::cross(Vector2* vector){
	return this->cross(vector->getX(), vector->getY());
}

grafx::Vector2* grafx::Vector2::multiply(float value){
	this->setX(this->getX() * value);
	this->setY(this->getY() * value);
	return this;
}

grafx::Vector2* grafx::Vector2::add(float x, float y){
	this->setX(this->getX() + x);
	this->setY(this->getY() + y);
	return this;
}

grafx::Vector2* grafx::Vector2::add(Vector2* vector){
	return this->add(vector->getX(), vector->getY());
}

grafx::Vector2* grafx::Vector2::minus(float x, float y){
	this->setX(this->getX() - x);
	this->setY(this->getY() - y);
	return this;
}

grafx::Vector2* grafx::Vector2::minus(Vector2* vector){
	return this->minus(vector->getX(), vector->getY());
}

float grafx::Vector2::dot(float x, float y){
	return this->getX() * x + this->getY() * y;
}

float grafx::Vector2::dot(Vector2* vector){
	return this->dot(vector->getX(), vector->getY());
}

grafx::Vector2* grafx::Vector2::clone(){
	Vector2* init = new Vector2(0, 0);
	for(int i = 0; i < init->getSize(); i++){
		init->data[i] = this->data[i];
	}
	return init;
}

grafx::Vector3::Vector3(float x, float y, float z) : Vector(3){
	this->data[0] = x;
	this->data[1] = y;
	this->data[2] = z;
}

grafx::Vector3* grafx::Vector3::cross(float x, float y, float z){
	float i = (this->getY() * z) - (this->getZ() * y);
    float j = (this->getX() * z) - (this->getZ() * x);
    float k = (this->getX() * y) - (this->getY() * x);
	this->setX(i); this->setY(-j); this->setZ(k);
	return this;
}

grafx::Vector3* grafx::Vector3::cross(Vector3* vector){
	return this->cross(vector->getX(), vector->getY(), vector->getZ());
}

grafx::Vector3* grafx::Vector3::multiply(float value){
	this->setX(this->getX() * value);
	this->setY(this->getY() * value);
	this->setZ(this->getZ() * value);
	return this;
}

grafx::Vector3* grafx::Vector3::add(float x, float y, float z){
	this->setX(this->getX() + x);
	this->setY(this->getY() + y);
	this->setY(this->getZ() + z);
	return this;
}

grafx::Vector3* grafx::Vector3::add(Vector3* vector){
	return this->add(vector->getX(), vector->getY(), vector->getZ());
}

grafx::Vector3* grafx::Vector3::minus(float x, float y, float z){
	this->setX(this->getX() - x);
	this->setY(this->getY() - y);
	this->setY(this->getZ() - z);
	return this;
}

grafx::Vector3* grafx::Vector3::minus(Vector3* vector){
	return this->minus(vector->getX(), vector->getY(), vector->getZ());
}

float grafx::Vector3::dot(float x, float y, float z){
	return this->getX() * x + this->getY() * y + this->getZ() * z;
}

float grafx::Vector3::dot(Vector3* vector){
	return this->dot(vector->getX(), vector->getY(), vector->getZ());
}

grafx::Vector3* grafx::Vector3::clone(){
	Vector3* init = ZeroVector();
	for(int i = 0; i < init->getSize(); i++){
		init->data[i] = this->data[i];
	}
	return init;
}

grafx::Quantanion::Quantanion(float x, float y, float z, float w) : Vector(4){
	this->data[0] = x;
	this->data[1] = y;
	this->data[2] = z;
	this->data[3] = w;
}

grafx::Quantanion* grafx::Quantanion::multiply(float value){
	this->setX(this->getX() * value);
	this->setY(this->getY() * value);
	this->setZ(this->getZ() * value);
	this->setW(this->getW() * value);
	return this;
}

float grafx::Quantanion::dot(Quantanion* vector){
	return this->getX() * vector->getX() + this->getY() * vector->getY() + this->getZ() * vector->getZ() + this->getW() * vector->getW();
}

grafx::Quantanion* grafx::Quantanion::clone(){
	Quantanion* init = new Quantanion(0, 0, 0, 0);
	for(int i = 0; i < init->getSize(); i++){
		init->data[i] = this->data[i];
	}
	return init;
}

#endif
