// StudyOpenGL16.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Common/MyShader.h"
#include "../Common/MyCamera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Common/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../StudyOpenGL_15/ConstData.h"

// define
const char *Title = "Stencil Test";
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

MyCamera camera(glm::vec3(0.0f, 0.0f, 6.0f));
void FrameSizeBufferCallback(GLFWwindow *window, int width, int height);
void ProcessInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);
int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, Title, NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FrameSizeBufferCallback);

    if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
    {
        std::cout << "Failed to GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    unsigned int cubleVAO, cubleVBO;

    glGenVertexArrays(1, &cubleVAO);
    glGenBuffers(1, &cubleVBO);

    glBindVertexArray(cubleVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    glBindVertexArray(0);

    unsigned int planeVAO,planeVBO;
    glGenBuffers(1,&planeVBO);
    glGenVertexArrays(1,&planeVAO);

    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER,planeVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(planeVertices),planeVertices,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glBindVertexArray(0);

    MyShader cubleShader("./res/StencilVertex.vs","./res/StencilFragment.fs");
    std::cout<<("11111111");
    MyShader planeShader("./res/StencilPlaneVertex.vs","./res/StencilPlaneFragment.fs");

    unsigned int cubleMap = loadTexture("../res/marble.jpg");
    unsigned int planeMap = loadTexture("../res/metal.png");

    cubleShader.use();
    planeShader.use();
    cubleShader.SetInt("boxSampler",0);
    planeShader.SetInt("planeSampler",0);


    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);
        // render
        // render end
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),float(SCR_WIDTH)/float(SCR_HEIGHT),0.1f,100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        cubleShader.use();
        
        cubleShader.SetMat4("projection",projection);
        cubleShader.SetMat4("view",view);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,cubleMap);
        glBindVertexArray(cubleVAO);

        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(-1.0f,0.0f,-1.0f));
        cubleShader.SetMat4("model",model);
        glDrawArrays(GL_TRIANGLES,0,36);

        model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(0.0f, 0.0f, 2.0f));
        model = glm::rotate(model,glm::radians(30.0f),glm::vec3(1.0f,0.0f,1.0f));
        cubleShader.SetMat4("model",model);
        glDrawArrays(GL_TRIANGLES,0,36);


        //plane
        
        planeShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,planeMap);
        glBindVertexArray(planeVAO);

        planeShader.SetMat4("projection",projection);
        planeShader.SetMat4("view",view);

        model = glm::mat4(1.0f);
        planeShader.SetMat4("model",model);
        glDrawArrays(GL_TRIANGLES,0,6);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    std::cout << "Hello World!\n";
}

void FrameSizeBufferCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

unsigned int loadTexture(const char *path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    // stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data != NULL)
    {

        GLenum format = 0;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to loadTexture" << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}