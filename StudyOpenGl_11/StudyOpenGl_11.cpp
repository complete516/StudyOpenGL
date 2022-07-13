// StudyOpenGl_11.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../Common/stb_image.h";


#include "../Common/MyShader.h"
#include "../Common/MyCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


const char *Title = "Material";
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

MyCamera camera( glm::vec3(0.0,0.0,5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


// glm::vec3 lightPos = glm::vec3(1.0f,1.2f,2.0f);
glm::vec3 lightPos = glm::vec3(1.0f,0.0f,2.0f);



float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow * window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
unsigned int loadTexture(const char *path);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, Title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create  GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window,mouseCallback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    unsigned int cubleVAO,VBO;
    glGenVertexArrays(1,&cubleVAO);
    glGenBuffers(1,&VBO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindVertexArray(cubleVAO);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVAO;
    glGenVertexArrays(1,&lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindVertexArray(lightVAO);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(0));
    glEnableVertexAttribArray(0);

    unsigned diffuseMap  = loadTexture("../res/container2.png");
    unsigned specularMap = loadTexture("../res/container2_specular.png");
    unsigned matrixMap = loadTexture("../res/matrix.jpg");


    MyShader lightCubShader("./res/lightTextureMaterialVS.vs","./res/lightTextureMaterialFS.fs");
    MyShader lightShader("./res/lightVS.vs","./res/lightFS.fs");


    lightCubShader.use();
    lightCubShader.SetInt("material.diffuse",0);
    lightCubShader.SetInt("material.specular",1);
    lightCubShader.SetInt("material.emission",2);


    while(!glfwWindowShouldClose(window)){

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        lightPos.x = sin(glfwGetTime());
        lightPos.z = cos(glfwGetTime());
            
        //std::cout << "x=" << lightPos.x <<",z=" << lightPos.z << std::endl;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //render
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),(float)SCR_WIDTH/(float)SCR_HEIGHT,0.1f,100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);

    //render cube
        lightCubShader.use();
        lightCubShader.SetVec3("light.position",lightPos);
        lightCubShader.SetVec3("viewPos",camera.Position);

        // light properties
        lightCubShader.SetVec3("light.ambient", 0.2f, 0.2f, 0.2f); 
        lightCubShader.SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        lightCubShader.SetVec3("light.specular", 1.0f, 1.0f, 1.0f);
        // material properties
        // lightCubShader.SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
        lightCubShader.SetFloat("material.shininess", 64.0f);

        lightCubShader.SetMat4("projection",projection);
        lightCubShader.SetMat4("view",view);

        model = glm::rotate(model,glm::radians(60.0f),glm::vec3(0.0f,1.0f,0.0f));

        lightCubShader.SetMat4("model",model);
       
        lightCubShader.SetFloat("moveStep", glfwGetTime());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,diffuseMap);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

         glActiveTexture(GL_TEXTURE2);
         glBindTexture(GL_TEXTURE_2D, matrixMap);

        glBindVertexArray(cubleVAO);
        glDrawArrays(GL_TRIANGLES,0,36);


        //render light;
        lightShader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model,lightPos);
        model = glm::scale(model,glm::vec3(0.2f));
        lightShader.SetMat4("projection",projection);
        lightShader.SetMat4("view",view);
        lightShader.SetMat4("model",model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES,0,36);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }


    glDeleteVertexArrays(1,&cubleVAO);
    glDeleteBuffers(1,&VBO);

    std::cout << "Hello World!\n";
}

unsigned int loadTexture(const char *path)
{
    unsigned int textureID;
    glGenTextures(1,&textureID);

    int width,height,nrComponents;
    // stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path,&width,&height,&nrComponents,0);
    if(data != NULL){

        GLenum format = 0;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D,textureID);
        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }else{
        std::cout<<"Failed to loadTexture"<<std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)== GLFW_PRESS)
    {
        glfwShowWindow(window);
    }
    
}

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn){
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}