
#include "exercise_02.h"
#include <functional>
#include <iostream>

int exercise_02::run() {

	//glfwInit();
	//glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//GLFWwindow* window = glfwCreateWindow(src_width, src_height, title, NULL, NULL);
	//if (window == NULL) {
	//	std::cout << "Failed to glfw CreateWindow" << std::endl;
	//	glfwTerminate();
	//	return -1;
	//}

	//glfwMakeContextCurrent(window);

	//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	//	std::cout << "Failed to initialize GLAD" << std::endl;
	//	return -1;
	//}

	unsigned int VAO[2];
	unsigned int VBO[2];

	glGenBuffers(2, VBO);
	glGenVertexArrays(2, VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBindVertexArray(VAO[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBindVertexArray(VAO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(0);


	unsigned int vertextShader, fragmentShader, fragmentShader2, program[2];
	vertextShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);

	program[0] = glCreateProgram();
	program[1] = glCreateProgram();

	glShaderSource(vertextShader, 1, &vertextShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);

	glCompileShader(fragmentShader);
	glCompileShader(fragmentShader2);
	glCompileShader(vertextShader);

	glAttachShader(program[0], vertextShader);
	glAttachShader(program[0], fragmentShader);
	glLinkProgram(program[0]);

	glAttachShader(program[1], vertextShader);
	glAttachShader(program[1], fragmentShader2);
	glLinkProgram(program[1]);


	glDeleteShader(vertextShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader2);


	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2, 0.2, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program[0]);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(program[1]);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glDeleteShader(program[0]);
	glfwTerminate();

	return 0;
}


void exercise_02::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void exercise_02::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}