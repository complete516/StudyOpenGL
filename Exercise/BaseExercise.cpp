#include "BaseExercise.h"
#include <iostream>

BaseExercise::BaseExercise(int width, int height, const char *title) : src_width(width), src_height(height), title(title)
{
}

int BaseExercise::run()
{
	return 1;
}

int BaseExercise::Init()
{
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(src_width, src_height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}

unsigned int BaseExercise::CreateShader(const char *shaderScore,unsigned int shaderType)
{
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader,1,&shaderScore,NULL);
	glCompileShader(shader);

	int success = 0;
	char infoLog[512]{};
	glGetShaderiv(shader,GL_COMPILE_STATUS,&success);

	if(!success){
		glGetShaderInfoLog(shader,512,NULL,infoLog);
		std::cout<<"ERROR::SHADER::COMPIILE "<<infoLog<<std::endl;
	}

	return shader;
}

unsigned int BaseExercise::LinkShaderProgram(unsigned int vertexShader,unsigned int fragmentShader){
	unsigned int program = glCreateProgram();
	glAttachShader(program,vertexShader);
	glAttachShader(program,fragmentShader);
	glLinkProgram(program);

	int success = 0;
	char infoLog[512]{};
	glGetProgramiv(program,GL_LINK_STATUS,&success);

	if(!success){
		glGetProgramInfoLog(program,512,NULL,infoLog);
		std::cout<<"ERROR::SHADER::LINKPROGRAM "<<infoLog<<std::endl;
	}
	//移除shader资源
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}