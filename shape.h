#ifndef SHAPE_H
	#define SHAPE_H

#include "model.h"

namespace grafx{
	class Plane : public Model{
		public:
			Plane(Material* material);
	};
}

grafx::Plane::Plane(Material* material) : Model(material){
	const GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,
	};
	
	const GLint indices[] = { 0, 1, 2 };
	this->setVertexCount(28);
	this->setIndexCount(3);
	this->setBuffers(vertices, indices);
}

#endif
