
#include"exercise_01.h"
#include<iostream>
#include <functional>

int exercise_01::run() {



	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	unsigned int  VAO, VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	unsigned int vertexShader, fragmentShader, program;
	
	vertexShader = this->CreateShader(vertextShaderSource,GL_VERTEX_SHADER);
	fragmentShader = this->CreateShader(fragmentShaderSource,GL_FRAGMENT_SHADER);
	program = this->LinkShaderProgram(vertexShader,fragmentShader);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(program);


	glfwTerminate();
	return 0;
}

void exercise_01::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void exercise_01::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
