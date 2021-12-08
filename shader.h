#ifndef SHADER_H
	#define SHADER_H

#include "renderer.h"
#include <GL/glew.h>
#include<GL/freeglut.h>

namespace grafx{
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
		std::cout<<source<<std::endl;
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
		std::cout<<"linking glsl error : "<<messages<<std::endl;
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
		"#version 140 \n"
		
        "in vec3 position; \n"
        
        "void main(){ \n"
         "   gl_Position = vec4(position, 1.0) * 0.5; \n"
        "}";
	const char* fragment =
		"#version 140 \n"
		
		"out  vec4 colorFinal; \n"
		"void main() { \n"
			"colorFinal = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
		"}";
	this->init(vertex, fragment);
}

void grafx::Material::use(){
	this->bind();
}

#endif
