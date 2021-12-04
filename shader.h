#ifndef SHADER_H
	#define SHADER_H

#include "matrix.h"
#include <GL/glew.h>
#include<GL/freeglut.h>

namespace grafx{
	struct Vertex{ float Position[3]; float Color[4]; };
	class Shader{
		private:
			GLuint program;
			GLuint BuildShader(const char *source, GLenum shaderType);
		protected:
			void init(const char* vertexShader, const char* fragmentShader);
			void bind();
			void dispose();
			GLuint getProgram();
		public:
			GLuint getAttributeLocation(const char* name);
			void setUniformMatrix(const char* name, float* matrix);
			~Shader();
	};
	
	class Material : public Shader{
		public:
			void use();
	};
	
	class SimpleMaterial : public Material{
		public:
			SimpleMaterial();
	};
}


GLuint grafx::Shader::BuildShader(const char *source, GLenum shaderType){
	GLuint shaderHandle = glCreateShader(shaderType);
	glShaderSource(shaderHandle, 1, &source, 0);
	glCompileShader(shaderHandle);
	GLint compileSuccess;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);

	if (compileSuccess == GL_FALSE){
		GLchar messages[256];
		glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
		std::cout<<"compile glsl error : "<<messages<<std::endl;
	}
	return shaderHandle;
}

void grafx::Shader::init(const char* vertexShader, const char* fragmentShader){
	GLuint vertex = BuildShader(vertexShader, GL_VERTEX_SHADER);
	GLuint fragment = BuildShader(fragmentShader, GL_FRAGMENT_SHADER);

	this->program = glCreateProgram();
	glAttachShader(this->program, vertex);
	glAttachShader(this->program, fragment);
	glLinkProgram(this->program);

	GLint linkSuccess;
	glGetProgramiv(this->program, GL_LINK_STATUS, &linkSuccess);
	if (linkSuccess == GL_FALSE){
		GLchar messages[256];
		glGetProgramInfoLog(this->program, sizeof(messages), 0, &messages[0]);
		std::cout<<"compile glsl error : "<<messages<<std::endl;
	}
}

grafx::Shader::~Shader(){
	this->dispose();
}

void grafx::Shader::bind(){
	glUseProgram(this->program);
}

void grafx::Shader::dispose(){
	glDeleteProgram(this->program);
	this->program = 0;
}

void grafx::Shader::setUniformMatrix(const char* name, float* matrix){
	GLint modelviewUniform = glGetUniformLocation(this->program, name);
	glUniformMatrix4fv(modelviewUniform, 1, 0, &matrix[0]);
}

GLuint grafx::Shader::getProgram(){
	return this->program;
}

GLuint grafx::Shader::getAttributeLocation(const char* name){
	return glGetAttribLocation(this->program, name);
}

grafx::SimpleMaterial::SimpleMaterial(){
	const char* vertex =
		"uniform mat4 u_transform;"
		"uniform mat4 u_projection;"
		"uniform mat4 u_view;"

		"attribute vec3 a_Position;"
		"attribute vec4 a_Color;"
		
		"varying vec4 frag_Color;"
		
		"void main(void) {"
		    "frag_Color = a_Color;"
		    "gl_Position = vec4(a_Position, 1.0);"
		"}";
	const char* fragment =
		"varying  vec4 frag_Color;"

		"void main() {"
			"gl_FragColor = frag_Color;"
		"}";
	this->init(vertex, fragment);
}

void grafx::Material::use(){
	this->bind();
}

#endif
