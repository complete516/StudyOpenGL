// StudyOpenGL_15.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "./ConstData.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "../Common/stb_image.h"

#include "../Common/MyShader.h"
#include "../Common/MyCamera.h"

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

const char *Title = "Depth Test";

void framBufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
unsigned int loadTexture(const char *path);

// MyCamera camera(glm::vec3(-2.0, 0.0, 1.5f));
MyCamera camera(glm::vec3(0.0, 0.0, 6.0f));

float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
    glfwSetFramebufferSizeCallback(window, framBufferSizeCallback);
    glfwSetScrollCallback(window,scroll_callback);
    glfwSetCursorPosCallback(window,mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glDepthFunc(GL_LESS);

    unsigned cubleVAO, cubleVBO;

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
    unsigned panelVAO, panelVBO;

    glGenVertexArrays(1, &panelVAO);
    glGenBuffers(1, &panelVBO);

    glBindVertexArray(panelVAO);

    glBindBuffer(GL_ARRAY_BUFFER, panelVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(0));

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    MyShader cubleShader("./res/cubleVertex.vs", "./res/cubleFragment.fs");
    MyShader panelShader("./res/cubleVertex.vs", "./res/cubleFragment.fs");

    unsigned int cubleMap = loadTexture("../res/marble.jpg");
    unsigned int panelMap = loadTexture("../res/metal.png");
    cubleShader.use();
    panelShader.use();
    cubleShader.SetInt("cubleTexture", 0);
    panelShader.SetInt("PanelTexture", 0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        cubleShader.use();
        cubleShader.SetMat4("projection", projection);
        cubleShader.SetMat4("view", view);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubleMap);
        glBindVertexArray(cubleVAO);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        cubleShader.SetMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.0f));
        cubleShader.SetMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // floor
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, panelMap);
        glBindVertexArray(panelMap);

        panelShader.SetMat4("projection", projection);
        panelShader.SetMat4("view", view);
        model = glm::mat4(1.0f);
        panelShader.SetMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &cubleVAO);
    glDeleteVertexArrays(1, &panelVAO);
    glDeleteBuffers(1, &cubleVBO);
    glDeleteBuffers(1, &panelVBO);

    glfwTerminate();
    std::cout << "Hello World!\n";
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

void framBufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
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

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}