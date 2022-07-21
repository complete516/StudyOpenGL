
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "MyVertexBuffer.h"

MyVertexBuffer::MyVertexBuffer()
{
}

void MyVertexBuffer::CreateBindVBO(int size, const void *data)
{

    unsigned int VAO, VBO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    VAOVector.push_back(VAO);
    VBOVector.push_back(VBO);
}

void MyVertexBuffer::CreateBindEBO(int size, const void *indices)
{
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    EBOVector.push_back(EBO);
}

void MyVertexBuffer::VertexAttribPointer(int index, int size, int stride, int offset)
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void *)(sizeof(float) * offset));
}

void MyVertexBuffer::BindVertexArray()
{
    for (auto it = VAOVector.begin(); it != VAOVector.end(); it++)
    {
		glBindVertexArray(*it);
    }
}

MyVertexBuffer::~MyVertexBuffer()
{
    for (auto it = VAOVector.begin(); it != VAOVector.end(); it++)
    {
        glDeleteVertexArrays(1, &(*it));
    }

    for (auto it = VBOVector.begin(); it != VBOVector.end(); it++)
    {
        glDeleteBuffers(1, &(*it));
    }

    for (auto it = EBOVector.begin(); it != EBOVector.end(); it++)
    {
        glDeleteBuffers(1, &(*it));
    }
}
