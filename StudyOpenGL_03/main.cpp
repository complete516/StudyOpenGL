#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Common/MyShader.h"

const int src_width = 800;
const int src_height = 600;
const char* title = "learn shader";

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

/*顶点数组*/
float vertices[] = {
	/*顶点*/       //颜色
	-0.5,-0.5,0.0, 1.0,0.0,0.0,
	0.5,-0.5,0.0,  0.0,1.0,0.0,
	0.0,0.5,0.0,   0.0,0.0,1.0
};

int main() {
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(src_width, src_height,title,NULL,NULL);
	if (window == NULL) {
		std::cout << "Failed to Create GLFW Create Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	unsigned int VAO, VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);


	//MyShader shaderprogram("E:\\StartProject\\MyStudy\\StudyOpenGL\\StudyOpenGL_03\\VertexShader.vs","E:\\StartProject\\MyStudy\\StudyOpenGL\\StudyOpenGL_03\\FrgamentShader.fs");
	//MyShader shaderprogram("./VertexShader.vs", "./FrgamentShader.fs");
	// 
	//使用uniform定义一个水平偏移量，在顶点着色器中使用这个偏移量把三角形移动到屏幕右侧
	MyShader shaderprogram("./VertexToFragmentVertexShader.vs","./FrgamentShader.fs");
	
	glfwSetFramebufferSizeCallback(window,framebufferSizeCallback);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2,0.3,0.3,1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//随时间变化颜色
		// float time = glfwGetTime();
		// float greenColor = (sin(time)/2 + 0.5);
		// shaderprogram.Set4f("ourColor",0,greenColor,0,1.0);

		shaderprogram.use();
		//使用uniform定义一个水平偏移量，在顶点着色器中使用这个偏移量把三角形移动到屏幕右侧
		//shaderprogram.SetFloat("xPos",1.0);

		float time = glfwGetTime();
		float x = sin(time);
		shaderprogram.SetFloat("offsx",x);
	

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window,true);
	}
}