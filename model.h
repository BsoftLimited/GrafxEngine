#ifndef MODEL_H
	#define MODEL_H

#include "transform.h"
#include "shader.h"
#include "renderer.h"

namespace grafx{	
	class Model{
		private:
			GLuint vertexBuffer, indexBuffer, vertexArray;
			GLsizei indexCount, vertexCount;
			Material* material;
			Transform* transform;
			void setupVertexBuffer(const GLfloat* vertices);
			void setupIndexBuffer(const GLint* indices);
		protected:
			void setBuffers(const GLfloat* vertices, const GLint* indices);
			void setVertexCount(GLsizei vertexCount){ this->vertexCount = vertexCount; }
			void setIndexCount(GLsizei indexCount){ this->indexCount = indexCount; }
		public:
			Model(Material* material);
			void draw(Renderer* renderer);
			void dispose();
			Transform* getTransform(){ return this->transform; }
	};
}


grafx::Model::Model(Material* material){
	this->material = material;
	this->transform = new Transform();
}

void grafx::Model::setBuffers(const GLfloat* vertices, const GLint* indices){
	glGenVertexArrays(1, &this->vertexArray);
	glBindVertexArray(this->vertexArray);
	this->material->use();
	
	this->setupVertexBuffer(vertices);
	this->setupIndexBuffer(indices);
	
	GLsizei stride = sizeof(GLfloat) * 7;
	
	GLuint positionSlot = material->getAttributeLocation("position");
	glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, 12, (GLvoid*)0);
	glEnableVertexAttribArray(positionSlot);
}

void grafx::Model::setupVertexBuffer(const GLfloat* vertices){
	GLfloat vertice[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };
	
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(GLfloat), &vertices, GL_STATIC_DRAW);
}

void grafx::Model::setupIndexBuffer(const GLint* indices){
	GLint indice[] = { 0, 1, 2 };
	
	glGenBuffers(1, &this->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexCount * sizeof(GLint), indice, GL_STATIC_DRAW);
}

void grafx::Model::draw(Renderer* renderer){
	glBindVertexArray(this->vertexArray);
	this->material->use();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

void grafx::Model::dispose(){}

#endif
