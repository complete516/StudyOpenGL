#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Common/MyShader.h"
#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SRC_WIDTH = 800;
const int SRC_HEIGHT = 600;
const char *WINDOW_TITLE = "study transform";

void processInput(GLFWwindow *window);

float vertices[] = {
	-0.5, 0.0, 0.0,
	0.5, 0.0, 0.0,
	0.0, 0.5, 0.0
	};

int main()
{

	glfwInit();
	glfwInitHint(GLFW_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "failed to Create GLFW window !" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	unsigned int VAO, VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(0));
	glEnableVertexAttribArray(0);

	MyShader shaderProgram("./transformVertexShader.vs","./transformFragmentShader.fs");

	glm::vec4

	while (!glfwWindowShouldClose(window))
	{

		processInput(window);
		glClearColor(0.2, 0.3, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}