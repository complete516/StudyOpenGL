#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "BaseExercise.h"

/*
������ͬ�����������Σ��������ǵ�����ʹ�ò�ͬ��VAO��VBO

����������ɫ�����򣬵ڶ�������ʹ��һ����ͬ��Ƭ����ɫ���������ɫ���ٴλ��������������Σ�������һ�����Ϊ��ɫ
*/

class exercise_02 :public BaseExercise {
public:
	exercise_02() :BaseExercise(800, 600, "two shader window") {}
	int run();
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow* window);

private:
	const char* vertextShaderSource =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\n";

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";

	/*��ɫ��Ƭ����ɫ��*/
	const char* fragmentShaderSource2 =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\n";

	float vertices[18] = {
		-0.8,-0.5,0,
		0.0,-0.5,0.0,
		-0.4,0.8,0.0,
		0.0,-0.5,0.0,
		0.8,-0.5,0.0,
		0.4,0.8,0.0,
	};

	float ver2[9] = {
		0.0,-0.5,0.0,
		0.8,-0.5,0.0,
		0.4,0.8,0.0,
	};
};