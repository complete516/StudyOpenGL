
/*
    摄像机
*/

#include "../Common/MyVertexBuffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Common/MyShader.h"

const char *TITLE = "carme";
const int SRC_WIDTH = 800;
const int SRC_HEIGHT = 600;

/*顶点数组*/
float vertices[] = {
	/*顶点*/   
	-0.5,-0.5,0.0, 
	0.5,-0.5,0.0, 
	0.0,0.5,0.0,  
};


int main()
{

    glfwInit();
    glfwInitHint(GLFW_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_VERSION_MINOR, 3);
    glfwInitHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, TITLE, NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    MyVertexBuffer vertextbuff;
    vertextbuff.CreateBindVBO(sizeof(vertices),vertices);
    vertextbuff.VertexAttribPointer(0,3,3*sizeof(float),0);

    MyShader shaderProgram("./CameraVertexShader.vs","./CameraFragmentShader.fs");
    

    while (!glfwWindowShouldClose(window))
    {   
        glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        vertextbuff.BindVertexArray();
        glDrawArrays(GL_TRIANGLES,0,3);

        /* code */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 1;
}
