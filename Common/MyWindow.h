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
    const int width;
    const int height;
    float fovy;
public:
    MyWindow(const char *Title,const int width = 800,const int height = 600);
    MyWindow();
    /* 获取窗口  */
    GLFWwindow* GetWindow();

     const int Width();
   const int Height();
    float Fovy();
    static void FrameSizeBufferCallback(GLFWwindow *window,int width,int height);
    ~MyWindow();
};


#endif