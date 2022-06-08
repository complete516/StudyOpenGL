#ifndef VERTEXT_BUFFER_H
#define VERTEXT_BUFFER_H 1
#include<iostream>
#include<vector>

class MyVertexBuffer
{
private:
    /* data */
    std::vector<unsigned int> VAOVector;
    std::vector<unsigned int> VBOVector;
    std::vector<unsigned int> EBOVector;

public:
    MyVertexBuffer();
    ~MyVertexBuffer();

    //顶点属性
    /// index 序号对应顶点着色器中的location
    /// size 大小
    /// stride 步长
    /// offset偏移多少
    void VertexAttribPointer(int index, int size, int stride, int offset);
    //绑定顶点数组
    void BindVertexArray();
    //创建索引缓冲对象 element buffer object
    void CreateBindEBO(int size,const void* indices);
    //创建顶点对象 size 顶点数组大小 data 顶点数组
    void CreateBindVBO(int size, const void *data);
};
#endif //~VERTEXT_BUFFER_H
