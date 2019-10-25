
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdio>
#include "Shader.h"

using namespace glm;

void processInput(GLFWwindow* window);
void display();
void myGlfwInit();
unsigned int generateShader();
void bind();


GLfloat triangle1[] = {
    -2.0f, 2.0f, 0,   1.0f, 1.0f, 1.0f,
    0,     0,    0,   1.0f, 1.0f, 1.0f,
    2.0f,  2.0f, 0,   1.0f, 1.0f, 1.0f
};

GLfloat triangle2[] = {
    -2.0f,  2.0f,  0,   0.0f, 1.0f, 0.0f,
    0,      0,     0,   0.0f, 1.0f, 0.0f,
    -2.0f,  -2.0f, 0,   0.0f, 1.0f, 0.0f
};

GLfloat triangle3[] = {
        2.0f,  0.0f,  0,   0.0f, 1.0f, 1.0f,
        2.0,   -2.0f, 0,   0.0f, 1.0f, 1.0f,
        0.0f,  -2.0f, 0,   0.0f, 1.0f, 1.0f
};

GLfloat triangle4[] = {
        2.0f,  2.0f,  0,   0.0f, 0.0f, 1.0f,
        1.0f,  1.0f,  0,   0.0f, 0.0f, 1.0f,
        2.0f,  0.0f,  0,   0.0f, 0.0f, 1.0f
};

GLfloat triangle5[] = {
        1.0f,  -1.0f,  0,   1.0f, 1.0f, 0.0f,
        0,      0,     0,   1.0f, 1.0f, 0.0f,
        -1.0f,  -1.0f, 0,   1.0f, 1.0f, 0.0f
};

GLfloat square[] = {
        1.0f,  -1.0f,  0,   1.0f, 0.0f, 0.0f,
        0,      0,     0,   1.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 0,     1.0f, 0.0f, 0.0f,
        2.0f,  0.0f, 0,     1.0f, 0.0f, 0.0f
};


GLfloat  parallelogram[] = {
        1.0f,  -1.0f,  0,     1.0f, 0.0f, 1.0f,
        0,      -2.0f, 0,     1.0f, 0.0f, 1.0f,
        -2.0f,  -2.0f, 0,     1.0f, 0.0f, 1.0f,
        -1.0f,  -1.0f, 0,     1.0f, 0.0f, 1.0f
};


unsigned int indicesSquare[] = {
        0, 1, 3,
        1, 2, 3
};


unsigned int indicesParallelogram[] = {
        0, 1, 3,
        1, 2, 3
};
const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 color;\n"

        "uniform mat4 transform;  \n"

        "out vec3 myColor;       \n"
        "void main()\n"
        "{\n"
        "    gl_Position = transform*vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
        "    myColor = color; "
        "}";


const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 myColor; \n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(myColor, 1.0f);\n"
        "} ";


void normalize(GLfloat shape[], int len)
{
    for(int i = 0; i < len; i++)
    {
        if(i%6 == 0)
        {
            shape[i] -= 4;
        } else if(i%6 == 1)
        {
            shape[i] += 4;
        }

        if(i%6 == 0 || i%6 == 1)
            shape[i] = shape[i]/8;
    }
}


GLuint VBOs[7], VAOs[7], EBO[2]; // create VBO and VAO arrays for the two triangles
GLFWwindow* window;
unsigned int shaderProgram;


glm::mat4 trans = glm::mat4(1.0f);


int main() {
    //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));


    normalize(triangle1, sizeof(triangle1)/ sizeof(GLfloat));
    normalize(triangle2, sizeof(triangle2)/ sizeof(GLfloat));
    normalize(triangle3, sizeof(triangle3)/ sizeof(GLfloat));
    normalize(triangle4, sizeof(triangle4)/ sizeof(GLfloat));
    normalize(triangle5, sizeof(triangle5)/ sizeof(GLfloat));
    normalize(square, sizeof(square)/ sizeof(GLfloat));
    normalize(parallelogram, sizeof(parallelogram )/ sizeof(GLfloat));


    myGlfwInit();



    bind();



    shaderProgram = generateShader();



    while (!glfwWindowShouldClose(window))
    {


        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        display();



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void bind()
{
    glGenVertexArrays(7, VAOs);
    glGenBuffers(7, VBOs);
    glGenBuffers(2, EBO);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle3), triangle3, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAOs[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle4), triangle4, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle5), triangle5, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAOs[5]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesSquare), indicesSquare, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAOs[6]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[6]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(parallelogram), parallelogram, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesParallelogram), indicesParallelogram, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}




void display()
{

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(VAOs[2]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(VAOs[3]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(VAOs[4]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(VAOs[5]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(VAOs[6]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


unsigned int generateShader()
{
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

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}



void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

}


void myGlfwInit()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL



    window = glfwCreateWindow(800, 800, "Totorial 01", NULL, NULL);
    if (window == NULL)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);



    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(-1);
    }

    glViewport(0, 0, 800, 800);
}