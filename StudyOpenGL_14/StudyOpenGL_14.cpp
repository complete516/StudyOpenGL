// StudyOpenGL_12.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Common/MyCamera.h"
#include "../Common/MyShader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Common/stb_image.h"

#include "../Common/Model.h"

MyCamera camera(glm::vec3(0.0f,0.0f,6.0f));

const char* Title = "load Model";

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos = glm::vec3(1.2f,0.2f,0.5f);

void frameBufferSizeCallback(GLFWwindow *window,int width,int height);
void processInput(GLFWwindow * window);
unsigned int loadTexture(const char *path);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);




 float vertices[] = {
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


    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,Title,NULL,NULL);
    if(window == NULL){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,frameBufferSizeCallback);
    glfwSetCursorPosCallback(window,mouseCallback);
    glfwSetScrollCallback(window, scroll_callback);
    if(!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress))){
        return -1;
    }
    stbi_set_flip_vertically_on_load(false);
    glEnable(GL_DEPTH_TEST);

    unsigned int boxVAO,VBO;
    glGenVertexArrays(1,&boxVAO);
    glGenBuffers(1,&VBO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);


    glBindVertexArray(boxVAO);
    //vertex
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(0));
    glEnableVertexAttribArray(0);
    
    //normal
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    //texture Coords
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightCubeVAO ;
    glGenVertexArrays(1,&lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindVertexArray(lightCubeVAO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(0));
    glEnableVertexAttribArray(0);


    MyShader boxShader("./Res/LightCasterVS.vs","./Res/LightCasterFS.fs");
    MyShader lightShader("./Res/lightVS.vs","./Res/lightFS.fs");
    MyShader modelShader("./Res/ModelVS.vs","./Res/ModelFS.fs");
    
    unsigned int diffuseMap =   loadTexture("../res/container2.png");
    unsigned int specularMap =   loadTexture("../res/container2_specular.png");
    unsigned int testMap =   loadTexture("../res/test_111.jpg");
    
    boxShader.use();
    boxShader.SetInt("material.diffuse",0);
    boxShader.SetInt("material.specular",1);
    boxShader.SetInt("material.testMap",2);


    Model ourModel("../res/nanosuit/nanosuit.obj");


    while (! glfwWindowShouldClose(window))
    {

        pointLightPositions[0].x = sin(glfwGetTime());
        pointLightPositions[0].z = cos(glfwGetTime());
        //camera.Position.z = cos(glfwGetTime())*10;
        
        processInput(window);

        //render
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),(float)(SCR_WIDTH)/(float)SCR_HEIGHT,0.1f,100.0f);
        glm::mat4 view = camera.GetViewMatrix();


        // boxShader.use();
        // boxShader.SetMat4("projection",projection);
        // boxShader.SetMat4("view",view);

        // boxShader.SetVec3("viewPos",camera.Position);

        // boxShader.SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        // boxShader.SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        // boxShader.SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        // boxShader.SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

        // // point light 1
        // boxShader.SetVec3("pointLights[0].position", pointLightPositions[0]);
        // boxShader.SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        // boxShader.SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        // boxShader.SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        // boxShader.SetFloat("pointLights[0].constant", 1.0f);
        // boxShader.SetFloat("pointLights[0].linear", 0.09f);
        // boxShader.SetFloat("pointLights[0].quadratic", 0.032f);
        // // point light 2
        // boxShader.SetVec3("pointLights[1].position", pointLightPositions[1]);
        // boxShader.SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        // boxShader.SetVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        // boxShader.SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        // boxShader.SetFloat("pointLights[1].constant", 1.0f);
        // boxShader.SetFloat("pointLights[1].linear", 0.09f);
        // boxShader.SetFloat("pointLights[1].quadratic", 0.032f);
        // // point light 3
        // boxShader.SetVec3("pointLights[2].position", pointLightPositions[2]);
        // boxShader.SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        // boxShader.SetVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        // boxShader.SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        // boxShader.SetFloat("pointLights[2].constant", 1.0f);
        // boxShader.SetFloat("pointLights[2].linear", 0.09f);
        // boxShader.SetFloat("pointLights[2].quadratic", 0.032f);
        // // point light 4
        // boxShader.SetVec3("pointLights[3].position", pointLightPositions[3]);
        // boxShader.SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        // boxShader.SetVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        // boxShader.SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        // boxShader.SetFloat("pointLights[3].constant", 1.0f);
        // boxShader.SetFloat("pointLights[3].linear", 0.09f);
        // boxShader.SetFloat("pointLights[3].quadratic", 0.032f);
        // // spotLight
        // boxShader.SetVec3("spotLight.position", camera.Position);
        // boxShader.SetVec3("spotLight.direction", camera.Front);
        // boxShader.SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        // boxShader.SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        // boxShader.SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        // boxShader.SetFloat("spotLight.constant", 1.0f);
        // boxShader.SetFloat("spotLight.linear", 0.09f);
        // boxShader.SetFloat("spotLight.quadratic", 0.032f);
        // boxShader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        // boxShader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f))); 


        // boxShader.SetFloat("material.shininess", 32.0f);
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D,diffuseMap);

        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D,specularMap);

        
        // glActiveTexture(GL_TEXTURE2);
        // glBindTexture(GL_TEXTURE_2D,testMap);

        // glBindVertexArray(boxVAO);

        // for(int i = 0;i<10;i++){
        //     glm::mat4 model = glm::mat4(1.0f);
 
        //     model = glm::translate(model,cubePositions[i]);
        //     float angle = 20*(i);
        //     model = glm::rotate(model,glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));

        //     boxShader.SetMat4("model",model);

        //     glDrawArrays(GL_TRIANGLES,0,36);
        // }

        
         lightShader.use();
         view = camera.GetViewMatrix();
        
         lightShader.SetMat4("projection",projection);
         lightShader.SetMat4("view",view);

         glBindVertexArray(lightCubeVAO);
        //  for(int i = 0;i<4;i++){
            glm::mat4 model = glm::mat4(1.0f);
         
            model = glm::translate(model,pointLightPositions[0]);
            model = glm::scale(model,glm::vec3(0.2));
            lightShader.SetMat4("model",model);
            glDrawArrays(GL_TRIANGLES,0,36);
        //  }

        
        modelShader.use();
        modelShader.SetMat4("projection",projection);
        modelShader.SetMat4("view",view);

        // glm::mat4 
        model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(0.0f,0.0f,0.0f));
        model = glm::scale(model,glm::vec3(0.1));
        modelShader.SetMat4("model",model);
        modelShader.SetVec3("light.position",pointLightPositions[0]);
        modelShader.SetFloat("light.constant",1.0f);
        modelShader.SetFloat("light.linear",0.09f);
        modelShader.SetFloat("light.quadratic",0.032f);

        ourModel.Draw(modelShader);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    



    std::cout << "Hello World!\n";
}

void processInput(GLFWwindow * window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,true);
    }
}

void frameBufferSizeCallback(GLFWwindow *window,int width,int height){
    glViewport(0,0,width,height);
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
