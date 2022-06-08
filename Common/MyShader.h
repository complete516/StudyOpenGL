#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>

class MyShader
{
public:
	unsigned int ID;
	MyShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use();
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void Set4f(const std::string& name, float v0,float v1,float v2,float v3) const;
	/// <summary>
/// 设置V3
/// </summary>
/// <param name="name">名字</param>
/// <param name="v0">第一个值</param>
/// <param name="v1">第二个值</param>
/// <param name="v2">第三个值</param>
	void SetVec3(const std::string& name, float v0, float v1, float v2) const;
	void SetMat4(const std::string& name,glm::mat4 mat) const;
	~MyShader();

private:
	unsigned int CreateShader(const char*shaderSource, GLenum shaderType);
};

