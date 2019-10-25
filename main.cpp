
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cstdio>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Shader.h"

using namespace glm;

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

}


float vertices[] = {
        -0.5f,  -0.5f, 0.0f, 1.0f, 0,    0,
         0.5f,  -0.5f, 0.0f, 0,    1.0f, 0,
         0.0f,   0.5f, 0.0f, 0,    0,    1.0f

};

unsigned indices[] ={
        0, 1, 2
};




const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec4 vertexColor;       \n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "    vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0f);  \n"
        "}";


const char* fragmentShaderSource =
        "#version 330 core\n"
        "in vec4 vertexColor; \n"
        "out vec4 FragColor;\n"
        "uniform vec4 ourColor; \n"
        "void main()\n"
        "{\n"
        "    FragColor = vertexColor;\n"
        "} ";





int main()
{
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
// 译注：下面就是矩阵初始化的一个例子，如果使用的是0.9.9及以上版本
// 下面这行代码就需要改为:
// glm::mat4 trans = glm::mat4(1.0f)
// 之后将不再进行提示
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;
}


int main1() {

    //Shader* shader = new Shader("../vertexSource.txt", "../fragmentSource.txt");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL



    GLFWwindow* window = glfwCreateWindow(800, 600, "Totorial 01", NULL, NULL);
    if (window == NULL)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);



    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glViewport(0, 0, 800, 600);




    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, & vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, & fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);



    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3* sizeof(float)));   // id  一次挖几个...  一次扫描几个  偏移量
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {


        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue)/2 + 0.5;

        int ourColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        glUseProgram(shaderProgram);

        glUniform4f(ourColorLocation, 0, greenValue, 0, 1.0f);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);







        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
