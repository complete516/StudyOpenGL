#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class MyShader
{
public:
	unsigned int ID;
	MyShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use();
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

	~MyShader();

private:
	unsigned int CreateShader(const char*shaderSource, GLenum shaderType);
};

