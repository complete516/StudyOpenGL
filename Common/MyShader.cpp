#include "MyShader.h"
MyShader::MyShader(const GLchar* vertexPath, const GLchar* fragmentPath,const GLchar* geometryPath) :ID(0) {
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream geometryFile;


	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	geometryFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

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
		if(geometryPath != nullptr){
			geometryFile.open(geometryPath);
			std::stringstream geometryStream;
			geometryStream<<geometryFile.rdbuf();
			geometryFile.close();
		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	unsigned vertexShader = this->CreateShader(vertexSource, GL_VERTEX_SHADER);
	unsigned fragmentShader = this->CreateShader(fragmentSource, GL_FRAGMENT_SHADER);
	unsigned geometryShader = 0;


	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	if (geometryPath != nullptr) {
		const char* geometrySource = geometryCode.c_str();
		geometryShader = this->CreateShader(geometryPath, GL_GEOMETRY_SHADER);
		glAttachShader(ID, geometryShader);
	}
	glLinkProgram(ID);

	int success = 0;
	char infoLog[512]{};
	glGetProgramiv(ID,GL_LINK_STATUS,&success);
	if (!success) {
		glGetProgramInfoLog(ID,512,NULL,infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryPath != nullptr) {
		glDeleteShader(geometryShader);
	}
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

void MyShader::Set4f(const std::string& name, float v0,float v1,float v2,float v3) const{
	glUniform4f(glGetUniformLocation(ID, name.c_str()),v0,v1,v2,v3);
}

void MyShader::SetMat4(const std::string& name,glm::mat4 mat)const {
	glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


void MyShader::SetVec3(const std::string& name, float v0, float v1, float v2) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2);
}

void MyShader::SetVec3(const std::string & name ,glm::vec3 & v3){
	glUniform3f(glGetUniformLocation(ID,name.c_str()),v3.x,v3.y,v3.z);

}


MyShader::~MyShader() {
	glDeleteProgram(ID);
}