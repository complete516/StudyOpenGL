#include "MyShader.h"
MyShader::MyShader(const GLchar* vertexPath, const GLchar* fragmentPath) :ID(0) {
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vertexStream, fragmentStream;

		vertexStream << vShaderFile.rdbuf();
		fragmentStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	unsigned vertexShader = this->CreateShader(vertexSource, GL_VERTEX_SHADER);
	unsigned fragmentShader = this->CreateShader(vertexSource, GL_VERTEX_SHADER);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

unsigned int MyShader::CreateShader(const char* shaderSource, GLenum shaderType) {
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int success = 0;
	char infoLog[512]{};
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::" << (shaderType == GL_VERTEX_SHADER ? "VERTEX_SHADER" : "FRAGMENT_SHADER") << std::endl;
	}
	return shader;
}

void MyShader::use() {
	glUseProgram(ID);
}


void MyShader::SetBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void MyShader::SetInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void MyShader::SetFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

MyShader::~MyShader() {
	glDeleteProgram(ID);
}