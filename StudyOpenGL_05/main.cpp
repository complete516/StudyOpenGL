#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Common/MyShader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SRC_WIDTH = 800;
const int SRC_HEIGHT = 600;
const char *WINDOW_TITLE = "study transform";

#define STB_IMAGE_IMPLEMENTATION
#include "../Common/stb_image.h"

void processInput(GLFWwindow *window);

// float vertices[] = {
// 	-0.5, 0.0, 0.0,
// 	0.5, 0.0, 0.0,
// 	0.0, 0.5, 0.0};

float vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	  // 右上
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 右下
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
	-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f	  // 左上
};

unsigned int indices[] = {
	0, 1, 3, // 第一个三角形
	1, 2, 3	 // 第二个三角形
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

	unsigned int VAO, VBO, EBO, texture;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	MyShader shaderProgram("./transformVertexShader.vs", "./transformFragmentShader.fs");

	glm::vec4 vec(1.0, 0.0, 0.0, 1.0);
	// glm::mat4 trans(1.0);
	// trans = glm::translate(trans, glm::vec3(-0.5, 0.2, 0.0));
	// trans =  glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0,0.0,1.0));
	// trans = glm::scale(trans,glm::vec3(0.5,1.0f,1.0f));
	// 4x4 4x1   4x1
	//[					[
	// 1,0,0,0			1
	// 0,1,0,0    x  	1
	// 0,0,1,0			1
	// 0,0,0,1			1
	// ]				]

	// vec = trans * vec;
	// std::cout << vec.x << vec.y << vec.z << std::endl;

	int textureWidth, textureHeight, channels;
	unsigned char *data;
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("../res/container.jpg", &textureWidth, &textureHeight, &channels, 0);
	if (data == NULL)
	{
		std::cout << "failed load Texture" << std::endl;
		return -1;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	shaderProgram.SetInt("texture1", texture);

	while (!glfwWindowShouldClose(window))
	{

		processInput(window);
		glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		// glm::mat4 trans(1.0);
		// trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0.0));
		// trans = glm::rotate(trans, float(glfwGetTime()), glm::vec3(0.0, 0.0, 1.0));

		// std::cout << glfwGetTime() << std::endl;
		shaderProgram.use();
		// glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 3);

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