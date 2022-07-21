
#include <iostream>

#define CONSTDATA
#define LOADTEXTURE
#include "MyDefine.h"
#include <vector>
#include <map>
#include <algorithm>
MyCamera camera(glm::vec3(0.0, 0.0, 6.0));

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

const char *Title = "Blending";

void ProcessInput(GLFWwindow *window);
void FrameSizeBuffCallback(GLFWwindow *window, int width, int height);
unsigned int loadTexture(const char *path, bool isalpha = false);

float transparentVertices[] = {
    // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
    1.0f, -0.5f, 0.0f, 1.0f, 1.0f,

    0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
    1.0f, -0.5f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.5f, 0.0f, 1.0f, 0.0f};

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, Title, NULL, NULL);

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, FrameSizeBuffCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CW);

    unsigned int cubeVAO, cubeVBO;

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);

    unsigned int planeVAO, planeVBO;
    glGenBuffers(1, &planeVBO);
    glGenVertexArrays(1, &planeVAO);

    glBindVertexArray(planeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);

    unsigned int transparentVAO, transparentVBO;
    glGenBuffers(1, &transparentVBO);
    glGenVertexArrays(1, &transparentVAO);

    glBindVertexArray(transparentVAO);

    glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);

    MyShader shader("./res/NormalShader.vs", "./res/NormalShader.fs");
    // MyShader transparentShader("./res/TransparentShader.vs", "./res/TransparentShader.fs");
    unsigned int cubeTexture = loadTexture("../res/marble.jpg");
    unsigned int planeTexture = loadTexture("../res/metal.png");
    unsigned int grassTexture = loadTexture("../res/window.png", true);

    shader.use();
    shader.SetInt("texture1", 0);

    std::vector<glm::vec3> vegetation;
    vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
    vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
    vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
    vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
    vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

    std::map<float, glm::vec3> sorted;

    for (int i = 0; i < vegetation.size(); i++)
    {
        float distance = glm::length(camera.Position - vegetation[i]);
        sorted[distance] = vegetation[i];
    }

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // render
        auto projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        auto view = camera.GetViewMatrix();

        // cubes
        shader.use();
        shader.SetMat4("projection", projection);
        shader.SetMat4("view", view);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTexture);
        glBindVertexArray(cubeVAO);

        auto model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0, 0.0, -1.0));
        shader.SetMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0, 0.0, 0.0));
        shader.SetMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // panel
        glBindTexture(GL_TEXTURE_2D, planeTexture);
        glBindVertexArray(planeVAO);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
        shader.SetMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // // grass
        // glBindTexture(GL_TEXTURE_2D, grassTexture);
        // glBindVertexArray(transparentVAO);

        // for (auto it = sorted.rbegin(); it != sorted.rend(); it++)
        // {
        //     model = glm::mat4(1.0f);
        //     model = glm::translate(model, it->second);
        //     shader.SetMat4("model", model);
        //     glDrawArrays(GL_TRIANGLES, 0, 6);
        // }
        // glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    std::cout << "Hello World!\n";
}

void ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void FrameSizeBuffCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

unsigned int loadTexture(const char *path, bool isalpha)
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
        GLint param;
        if (isalpha)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            param = GL_CLAMP_TO_EDGE;
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            param = GL_REPEAT;
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);

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