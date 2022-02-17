#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class BaseExercise
{
public:
	BaseExercise(int width, int height, const char* title = "windows");
	int Init();
	virtual int run();
	//创建shader 
	//@shaderScore 资源
	unsigned int CreateShader(const char* shaderScore,unsigned int shaderType);
	//链接shader程序
	unsigned int LinkShaderProgram(unsigned int vertexShader,unsigned int fragmentShader);

protected:
	GLFWwindow* window;
	const int src_width = 800;
	const int src_height = 600;
	const char* title = "window";
};

