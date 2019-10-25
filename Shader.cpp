

#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>


using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    ifstream vertexFile(vertexPath);
    ifstream fragmentFile(fragmentPath);

    vertexFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {

        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vertexFile.rdbuf();
        fShaderStream << fragmentFile.rdbuf();

        // 转换数据流到string
        vertexCode   = vShaderStream.str().c_str();
        fragmentCode = fShaderStream.str().c_str();

        // 关闭文件处理器
        vertexFile.close();
        fragmentFile.close();



        unsigned int vertex, fragment;


        // 顶点着色器
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexCode, NULL);
        glCompileShader(vertex);
        //frament着色器

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, & fragmentCode, NULL);
        glCompileShader(fragment);

        // 着色器程序
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);


        // 打印连接错误（如果有的话）
        int success;
        char infoLog[512];
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }


        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }catch (const std::exception& e)
    {
        std::cout<<"Open failed";
    }

}

Shader::~Shader() {

}

void Shader::use() {
    glUseProgram(ID);
}
