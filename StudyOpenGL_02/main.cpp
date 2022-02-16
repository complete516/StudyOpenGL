#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int width = 800;
const int height = 600;
const char* title = "test gl";

float vertices[] = {
	-0.5f,-0.5,0.0,
	0.5f,-0.5,0.0,
	0.0f,0.5,0.0,
};

/*顶点着色器*/
const char* vertexShaderSource = "#version 330 core\n" 
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


void frame_buff_size_callback(GLFWwindow* window,int width,int height);
void processInput(GLFWwindow * window);
void shaderComplete(unsigned int shader);

int main() {
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow(width,height,title,NULL,NULL);
	if (window == NULL) {
		std::cout << "Failed to GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	glViewport(0,0,width,height);
	glfwSetFramebufferSizeCallback(window,frame_buff_size_callback);
	//创建并绑定一个顶点缓冲对象
	unsigned int VBO ,VAO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	//解除绑定
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	unsigned int vertextShader;
	vertextShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertextShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertextShader);
	
	shaderComplete(vertextShader);


	unsigned int fragmetShader;
	fragmetShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmetShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmetShader);
	shaderComplete(fragmetShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertextShader);
	glAttachShader(shaderProgram,fragmetShader);
	glLinkProgram(shaderProgram);

	int success = 0;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(vertextShader,512,NULL,infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	
	glDeleteShader(vertextShader);
	glDeleteShader(fragmetShader);




	while (!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}

/*屏幕大小改变*/
void frame_buff_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

/*输入*/
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window,true);
	}
}

void shaderComplete(unsigned int shader) {
	int success = 0;
	char infoLog[512];
	glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
	if (!success) {
		glGetShaderInfoLog(shader,512,NULL,infoLog);
		std::cout << infoLog << std::endl;
	}
}