#include "MyWindow.h"
#include <iostream>
#include <functional>

MyWindow::MyWindow() : MyWindow("learn OpenGL")
{
}

MyWindow::MyWindow(const char *Title,const int width , const int height )
{
    CreateWindow(width,height,Title);
}

MyWindow::~MyWindow()
{
}

void MyWindow::CreateWindow(const int width, const int height, const char *Title)
{
    Init();
    window = glfwCreateWindow(width, height, Title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to Create GLFW" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,MyWindow::FrameSizeBufferCallback);

    if(!gladLoadGLLoader( GLADloadproc (glfwGetProcAddress))){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

}


void MyWindow::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* MyWindow::GetWindow(){
    return window;
}

void  MyWindow::FrameSizeBufferCallback(GLFWwindow *window,int width,int height){
    glViewport(0,0,width,height);
}


void MyWindow::ProcessInput(){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }  
}
