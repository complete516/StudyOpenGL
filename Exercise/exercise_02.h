#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "BaseExercise.h"

/*
创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO

创建两个着色器程序，第二个程序使用一个不同的片段着色器，输出黄色；再次绘制这两个三角形，让其中一个输出为黄色
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

	/*黄色的片段着色器*/
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