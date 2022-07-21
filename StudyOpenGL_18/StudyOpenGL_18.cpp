// StudyOpenGL_18.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#define CONSTDATA
#define LOADTEXTURE

#include "../Common/MyDefine.h"

#include "../Common/MyWindow.h"

int main()
{
    
    MyWindow mWin("Framebuffers");

    while (!glfwWindowShouldClose(mWin.GetWindow()))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f,0.1f,0.1f,1.0f);

        glfwSwapBuffers(mWin.GetWindow());
        glfwPollEvents();
    }
    
    std::cout << "Hello World!\n";
}


