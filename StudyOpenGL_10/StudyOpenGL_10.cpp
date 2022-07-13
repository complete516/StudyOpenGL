// StudyOpenGL_10.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "../Common/MyShader.h"
#include  "../Common/MyCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char *TITLE = "Material";
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

// #define STB_IMAGE_IMPLEMENTATION

MyCamera camera(glm::vec3(0.0f,0.0f,6.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f; 
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//glm::vec3 cublePos(1.2f, 1.0f, -2.0f);

void frameBufferSizeCallback(GLFWwindow * window,int width,int height);
void processInput(GLFWwindow * window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

 float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    };


int main()
{

    // Init GLFW

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, TITLE, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,frameBufferSizeCallback);
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetScrollCallback(window,scroll_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    unsigned  int cubeVAO,VBO;

    glGenVertexArrays(1,&cubeVAO);
    glGenBuffers(1,&VBO);


    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
 
    glBindVertexArray(cubeVAO);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    // glEnableVertexAttribArray(2);


    //create lightVAO
    unsigned int  lightVAO;
    glGenVertexArrays(1,&lightVAO);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(0));
    glEnableVertexAttribArray(0);




    //create shader
    MyShader material("./res/MaterialVS.vs","./res/MaterialFS.fs");
    MyShader light("./res/LightVS.vs","./res/LightFS.fs");


    //render loop;

    while(!glfwWindowShouldClose(window)){

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    glm::vec3 lightColor;
    lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0f));
    lightColor.y = sin(glfwGetTime() * 0.7f);
    lightColor.z = sin(glfwGetTime() * 1.3f);

    glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // 降低影响
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响


        //lightPos.x = static_cast<float>(sin(glfwGetTime()));
        //lightPos.z = static_cast<float>(cos(glfwGetTime()));


        material.use();   
        material.SetVec3("material.ambient",1.0f,0.5f,0.31f);
        material.SetVec3("material.diffuse",1.0f,0.5f,0.31f);
        material.SetVec3("material.specular",0.5f,0.5f,0.5f);
        material.SetFloat("material.shininess",32.0f);

        material.SetVec3("light.ambient",ambientColor);
        material.SetVec3("light.diffuse",diffuseColor);
        material.SetVec3("light.specular",1.0f,1.0f,1.0f);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        material.SetMat4("projection",projection);
        material.SetMat4("view",camera.GetViewMatrix());

        material.SetVec3("viewPos",camera.Position);
        material.SetVec3("lightPos",lightPos);
        material.SetVec3("lightColor",1.0f,1.0f,1.0f);

        glm::mat4 model = glm::mat4(1.0f);
         //model = glm::translate(model, cublePos);
        model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f,0.5f,1.0f));
        material.SetMat4("model", model);

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES,0,36);


        light.use();
        light.SetMat4("projection",projection);
        light.SetMat4("view",camera.GetViewMatrix());
        model = glm::mat4(1.0f);
        model = glm::translate(model,lightPos);
        model = glm::scale(model,glm::vec3(0.2f));

        light.SetMat4("model",model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES,0,36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    std::cout << "Hello World!\n";
}

void frameBufferSizeCallback(GLFWwindow * window,int width,int height){
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow * window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) ==GLFW_PRESS){
        glfwShowWindow(window);
    } 
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
