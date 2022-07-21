#ifndef _MYDEFINE_H_
#define _MYDEFINE_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Common/MyShader.h"
#include "../Common/MyCamera.h"

//定义了 
#ifdef CONSTDATA
    #include "../StudyOpenGL_15/ConstData.h"
#endif

#ifdef LOADTEXTURE
    #define STB_IMAGE_IMPLEMENTATION
    #include "../Common/stb_image.h"
#endif

#endif _MYDEFINE_H_