
/*
    摄像机
*/

#include "../Common/MyVertexBuffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Common/MyShader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Common/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Common/MyCamera.h"

const char *TITLE = "carme";
const int SRC_WIDTH = 800;
const int SRC_HEIGHT = 600;

/*顶点数组*/
float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

// glm::vec3 camerPos = glm::vec3(0.0f, 0.0f, 3.0f);
// glm::vec3 camerFront = glm::vec3(0.0, 0.0, -1.0f);
// glm::vec3 camerUp = glm::vec3(0.0f, 1.0f, 0.0f);

//当前帧与上一帧的时间差
float deltaTime = 0.0f;
//上一帧的时间
float lastTime = 0.0f;
//偏航角
float yaw = -90.0f;
//俯仰角
float pitch = 0.0f;
float lastX = 400;
float lastY = 300;
float fov = 45.0f;

bool firstMouse = true;

glm::mat4 TestLookAt(glm::vec3 eye, glm::vec3 frot, glm::vec3 up);

void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double x, double y);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
MyCamera camera(glm::vec3(0.0f, 0.0f, 3.0f));
int main()
{
    glfwInit();
    glfwInitHint(GLFW_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_VERSION_MINOR, 3);
    glfwInitHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, TITLE, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    MyVertexBuffer vertextbuff;
    vertextbuff.CreateBindVBO(sizeof(vertices), vertices);
    vertextbuff.VertexAttribPointer(0, 3, 5 * sizeof(float), 0);
    vertextbuff.VertexAttribPointer(1, 2, 5 * sizeof(float), 3);

    unsigned int textureArr[2] = {0};
    const char *texNameArr[] = {"../res/container.jpg", "../res/awesomeface.png"};
    stbi_set_flip_vertically_on_load(true);
    for (size_t i = 0; i < 2; i++)
    {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int twidth, theight, nrChannels;

        unsigned char *data = stbi_load(texNameArr[i], &twidth, &theight, &nrChannels, 0);
        if (i == 1)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, theight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        textureArr[i] = texture;
    }

    MyShader shaderProgram("./CameraVertexShader.vs", "./CameraFragmentShader.fs");
    shaderProgram.use();
    shaderProgram.SetInt("texture1", 0);
    shaderProgram.SetInt("texture2", 1);
    glEnable(GL_DEPTH_TEST);

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastTime;
        lastTime = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureArr[0]);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureArr[1]);

        shaderProgram.use();

        //视图
        glm::mat4 view;
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        view = camera.GetViewMatrix();
        float radius = 10.0f;

        // float camX = sin(glfwGetTime()) * radius;
        // float camZ = cos(glfwGetTime()) * radius;

        // view =  glm::lookAt(camerPos, camerPos + camerFront, camerUp);

        // view = TestLookAt(camerPos, camerPos + camerFront, camerUp);

        //透视
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.Zoom), (float)(SRC_WIDTH / SRC_HEIGHT), 0.1f, 100.0f);

        unsigned int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        shaderProgram.SetMat4("projection", projection);
        vertextbuff.BindVertexArray();

        for (size_t index = 0; index < 10; index++)
        {
            glm::mat4 model(1.0);
            model = glm::translate(model, cubePositions[index]);
            float angle = 20.0f * index;
            if (index % 3 == 0)
            {
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.2f, 0.3f));
            }
            shaderProgram.SetMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        /* code */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 1;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }

    float cameraSpeed = static_cast<float>(2.5f * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        // camerPos += cameraSpeed * camerFront;
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        // camerPos -= cameraSpeed * camerFront;
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        // camerPos -= glm::normalize(glm::cross(camerFront, camerUp)) * cameraSpeed;
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        // camerPos += glm::normalize(glm::cross(camerFront, camerUp)) * cameraSpeed;
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    // camerPos.y = 0.0f;
}

//鼠标回调
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float x = static_cast<float>(xposIn);
    float y = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float xoffset = x - lastX;
    float yoffset = lastY - y;
    lastX = x;
    lastY = y;
    // float sensitivity = 0.05f;
    // xoffset *= sensitivity;
    // yoffset *= sensitivity;
    // yaw += xoffset;
    // pitch += yoffset;

    // if (pitch > 89.0f)
    //     pitch = 89.0f;
    // if (pitch < -89.0f)
    //     pitch = -89.0f;

    // glm::vec3 front;
    // front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    // front.y = sin(glm::radians(pitch));
    // front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    // camerFront = glm::normalize(front);

    camera.ProcessMouseMovement(x, y);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    // fov -= (float)yoffset;
    // if (fov < 1.0f)
    //     fov = 1.0f;
    // if (fov > 45.0f)
    //     fov = 45.0f;
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

glm::mat4 TestLookAt(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
    glm::vec3 cameraDirection = position - target;
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraDirection, up));
    glm::vec3 cameraUp = glm::normalize(glm::cross(cameraRight, cameraDirection));

    glm::mat4 rotate(1.0f);
    glm::mat4 translation(1.0f);

    translation[3][0] = -position.x;
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;

    rotate[0][0] = cameraRight.x;
    rotate[1][0] = cameraRight.y;
    rotate[2][0] = cameraRight.z;

    rotate[0][1] = cameraUp.x;
    rotate[1][1] = cameraUp.y;
    rotate[2][1] = cameraUp.z;

    rotate[0][2] = cameraDirection.x;
    rotate[1][2] = cameraDirection.y;
    rotate[2][2] = cameraDirection.z;

    return rotate * translation;
}