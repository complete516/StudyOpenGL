#ifndef _MYWINDOW_H_
#define _MYWINDOW_H_ 

#include <glad/glad.h>
#include<GLFW/glfw3.h>

class MyWindow
{
private:
    GLFWwindow * window;
    /** 初始化 */
    void Init();
    void CreateWindow(const int width,const int height,const char *Title);
public:
    MyWindow(const char *Title,const int width = 800,const int height = 600);
    MyWindow();
    /* 获取窗口  */
    GLFWwindow* GetWindow();

    void ProcessInput();
    static void FrameSizeBufferCallback(GLFWwindow *window,int width,int height);

    // std::function<void(GLFWwindow *window,int width,int height)> FrameSizeBufferFunc;
    // std::function<void (GLFWwindow * window)> ProcessInputFunc;
    ~MyWindow();
};


#endif