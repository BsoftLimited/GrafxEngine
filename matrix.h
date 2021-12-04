#ifndef MATRIX_H
	#define MATRIX_H

#include "vector.h"

namespace grafx{
	class Matrix : public Data{
		private:
			int size;
		protected:
			Matrix(int n);
		public:
			int getSize(){ return this->size; }
			Matrix* transpose();
			void set(int row, int col, float value){ this->data[row * this->size + col] = value; }
			float get(int row, int col){ return this->data[row * this->size + col]; }
			void print();
	};
	
	class Matrix4 : public Matrix{
		public :
			Matrix4(): Matrix(4){}
			Matrix4* multiply(Matrix* matrix);
	};
	
	Matrix4* UnityMatrix(){
		Matrix4* init = new Matrix4();
		init->set(0, 0, 1); init->set(1, 1, 1);  init->set(2, 2, 1);  init->set(3, 3, 1);
		return init;
	}
	
	Matrix4* ScaleMatrix(float x, float y, float z){
		Matrix4* init = new Matrix4();
		init->set(0, 0, x); init->set(1, 1, y);  init->set(2, 2, z);  init->set(3, 3, 1);
		return init;
	}
	
	Matrix4* TranslationMatrix(float x, float y, float z){
		Matrix4* init = UnityMatrix();
		init->set(0, 3, x); init->set(1, 3, y);  init->set(2, 3, z);
		return init;
	}
	
	Matrix4* RotationXMatrix(float x){
		Matrix4* init = UnityMatrix();
		double rad = toRadians((double)x);
		float cosValue  =(float) std::cos(rad);
		float sinValue  =(float) std::sin(rad);
		init->set(1, 1, cosValue); init->set(1, 2, - sinValue);
		init->set(2, 1, sinValue); init->set(2, 2, cosValue);
		return init;
	}
	
	Matrix4* RotationYMatrix(float y){
		Matrix4* init = UnityMatrix();
		double rad = toRadians((double)y);
		float cosValue  =(float) std::cos(rad);
		float sinValue  =(float) std::sin(rad);
		init->set(0, 0, cosValue);  init->set(0, 2,  -sinValue);
		init->set(2, 0, -sinValue); init->set(2, 2, cosValue);
		return init;
	}
	
	Matrix4* RotationZMatrix(float z){
		Matrix4* init = UnityMatrix();
		double rad = toRadians((double)z);
		float cosValue  =(float) std::cos(rad);
		float sinValue  =(float) std::sin(rad);
		init->set(0, 0, cosValue); init->set(0, 1, - sinValue);
		init->set(1, 0, sinValue); init->set(1, 1, cosValue);
		return init;
	}
	
	Matrix4* RotationMatrix(float x, float y, float z){
		return RotationXMatrix(x)->multiply(RotationYMatrix(y)->multiply(RotationZMatrix(z)));
	}
	
	Matrix4* LookAtMatrix(Vector3* up, Vector3* position, Vector3* target){
		Vector3* direction = (Vector3*) position->clone()->minus(target)->normalize();
		Vector3* right = (Vector3*) up->cross(direction->clone())->normalize();
		Vector3* initUp = (Vector3*) direction->clone()->cross(right->clone())->normalize();
			
		Matrix4* init = UnityMatrix();
		init->set(0, 0, right->getX());		init->set(0, 1, right->getY());  init->set(0, 2, right->getZ());
		init->set(1, 0, initUp->getX());	init->set(1, 1, initUp->getY());  init->set(1, 2, initUp->getZ());
		init->set(2, 0, direction->getX()); init->set(2, 1, direction->getY());  init->set(2, 2, direction->getZ());
			
		Matrix4* initB = UnityMatrix();
		initB->set(0, 3, - position->getX());  initB->set(1, 3, - position->getY());  initB->set(2, 3, - position->getZ());
			
		return init->multiply(initB);
	}
	
	
	Matrix4* LookAtMatrix( Vector3* position, Vector3* target){
		return LookAtMatrix(UpVector(), position, target);
	}
	
	Matrix4* ProjectionMatrix(float fov, float width, float height, float far, float near){
		Matrix4* init = new Matrix4();
		
		float aspect = width / height;
		float tangent = (float) std::tan(toRadians((double)fov)/2);
		float sum = far + near;
		float length =  far - near;
		float product = far * near;
		
		init->set(0, 0, 1 / ( aspect * tangent));
		init->set(1, 1,  1 / tangent);
		init->set(2, 2, - sum / length);
		init->set(2, 3, -2 * product / length);
		init->set(3, 2, -1);
		
		return init;
	}
}

grafx::Matrix::Matrix(int n) : Data(new float[n*n]){
	this->size = n;
	for(int i = 0; i < n*n; i++){
		this->data[i] = 0;
	}
}

grafx::Matrix* grafx::Matrix::transpose(){
	for(int i = 1; i < this->size; i++){
		for(int j = 0; j < i; j++){
			if(i != j){
				float a = this->get(i, j), b = this->get(j, i);
				this->set(i, j, b); this->set(j, i, a);
			}
		}
	}
	return this;
}

void grafx::Matrix::print(){
	for(int i = 0; i < this->size; i++){
		for(int j = 0; j < this->size; j++){
			printf("%f ", this->data[i]);
		}
	}
}

grafx::Matrix4* grafx::Matrix4::multiply(Matrix* matrix){
	float a00 = (this->get(0, 0) * matrix->get(0, 0)) + (this->get(0, 1) * matrix->get(1, 0)) + (this->get(0, 2) * matrix->get(2, 0)) + (this->get(0, 3) * matrix->get(3, 0));
	float a01 = (this->get(0, 0) * matrix->get(0, 1)) + (this->get(0, 1) * matrix->get(1, 1)) + (this->get(0, 2) * matrix->get(2, 1)) + (this->get(0, 3) * matrix->get(3, 1));
	float a02 = (this->get(0, 0) * matrix->get(0, 2)) + (this->get(0, 1) * matrix->get(1, 2)) + (this->get(0, 2) * matrix->get(2, 2)) + (this->get(0, 3) * matrix->get(3, 2));
	float a03 = (this->get(0, 0) * matrix->get(0, 3)) + (this->get(0, 1) * matrix->get(1, 3)) + (this->get(0, 2) * matrix->get(2, 3)) + (this->get(0, 3) * matrix->get(3, 3));
				
	float a10 = (this->get(1, 0) * matrix->get(0, 0)) + (this->get(1, 1) * matrix->get(1, 0)) + (this->get(1, 2) * matrix->get(2, 0)) + (this->get(1, 3) * matrix->get(3, 0));
	float a11 = (this->get(1, 0) * matrix->get(0, 1)) + (this->get(1, 1) * matrix->get(1, 1)) + (this->get(1, 2) * matrix->get(2, 1)) + (this->get(1, 3) * matrix->get(3, 1));
	float a12 = (this->get(1, 0) * matrix->get(0, 2)) + (this->get(1, 1) * matrix->get(1, 2)) + (this->get(1, 2) * matrix->get(2, 2)) + (this->get(1, 3) * matrix->get(3, 2));
	float a13 = (this->get(1, 0) * matrix->get(0, 3)) + (this->get(1, 1) * matrix->get(1, 3)) + (this->get(1, 2) * matrix->get(2, 3)) + (this->get(1, 3) * matrix->get(3, 3));
				
	float a20 = (this->get(2, 0) * matrix->get(0, 0)) + (this->get(2, 1) * matrix->get(1, 0)) + (this->get(2, 2) * matrix->get(2, 0)) + (this->get(2, 3) * matrix->get(3, 0));
	float a21 = (this->get(2, 0) * matrix->get(0, 1)) + (this->get(2, 1) * matrix->get(1, 1)) + (this->get(2, 2) * matrix->get(2, 1)) + (this->get(2, 3) * matrix->get(3, 1));
	float a22 = (this->get(2, 0) * matrix->get(0, 2)) + (this->get(2, 1) * matrix->get(1, 2)) + (this->get(2, 2) * matrix->get(2, 2)) + (this->get(2, 3) * matrix->get(3, 2));
	float a23 = (this->get(2, 0) * matrix->get(0, 3)) + (this->get(2, 1) * matrix->get(1, 3)) + (this->get(2, 2) * matrix->get(2, 3)) + (this->get(2, 3) * matrix->get(3, 3));
				
	float a30 = (this->get(3, 0) * matrix->get(0, 0)) + (this->get(3, 1) * matrix->get(1, 0)) + (this->get(3, 2) * matrix->get(2, 0)) + (this->get(3, 3) * matrix->get(3, 0));
	float a31 = (this->get(3, 0) * matrix->get(0, 1)) + (this->get(3, 1) * matrix->get(1, 1)) + (this->get(3, 2) * matrix->get(2, 1)) + (this->get(3, 3) * matrix->get(3, 1));
	float a32 = (this->get(3, 0) * matrix->get(0, 2)) + (this->get(3, 1) * matrix->get(1, 2)) + (this->get(3, 2) * matrix->get(2, 2)) + (this->get(3, 3) * matrix->get(3, 2));
	float a33 = (this->get(3, 0) * matrix->get(0, 3)) + (this->get(3, 1) * matrix->get(1, 3)) + (this->get(3, 2) * matrix->get(2, 3)) + (this->get(3, 3) * matrix->get(3, 3));
				
	this->set(0, 0, a00); this->set(0, 1, a01); this->set(0, 2, a02); this->set(0, 3, a03);
	this->set(1, 0, a10); this->set(1, 1, a11); this->set(1, 2, a12); this->set(1, 3, a13);
	this->set(2, 0, a20); this->set(2, 1, a21); this->set(2, 2, a22); this->set(2, 3, a23);
	this->set(3, 0, a30); this->set(3, 1, a31); this->set(3, 2, a32); this->set(3, 3, a33);
	
	return this;
}

#endif
