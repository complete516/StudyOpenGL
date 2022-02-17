#pragma once

/*
��Ӹ��ඥ�㵽�����У�ʹ��glDrawArrays�����Ի��������˴�������������
*/

#include "BaseExercise.h"
class  exercise_01:public BaseExercise  {
public:

	exercise_01() :BaseExercise(800,600, "TWO TRIANGLES WINDOWS") {
	}
	int run();

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow* window);
private:

	//const int src_width = 800;
	//const int src_height = 600;
	//const char* title = "TWO TRIANGLES WINDOWS";

	float vertices[18] = {
		-0.8,-0.5,0,
		0.0,-0.5,0.0,
		-0.4,0.8,0.0,
		0.0,-0.5,0.0,
		0.8,-0.5,0.0,
		0.4,0.8,0.0,
	};

	/*������ɫ��*/
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
};