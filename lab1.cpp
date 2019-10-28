
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdio>

int speed = 300;

int waitSpeed = 100;


using namespace glm;

//quit after the esc button is pressed
void processInput(GLFWwindow* window);
//draw the UI
void display();
//init something about the glfw
void myGlfwInit();
//make the vertex and fragment shader
unsigned int generateShader();

void bind();


//the triangle on the top
GLfloat triangle1[] = {
    -0.75f, 0.75f, 0,   1.0f, 1.0f, 1.0f,
    -0.5f,     0.5f,    0,   1.0f, 1.0f, 1.0f,
    -0.25f,  0.75f, 0,   1.0f, 1.0f, 1.0f
};

//the triangle on the left
GLfloat triangle2[] = {
    -0.75f,  0.75f,  0,   0.0f, 1.0f, 0.0f,
    -0.5f,      0.5f,     0,   0.0f, 1.0f, 0.0f,
    -0.75f,  0.25f, 0,   0.0f, 1.0f, 0.0f
};


//the triangle on the right down
GLfloat triangle3[] = {
        -0.25f,  0.5f,  0,   0.0f, 1.0f, 1.0f,
        -0.25f,   0.25f, 0,   0.0f, 1.0f, 1.0f,
        -0.5f,  0.25f, 0,   0.0f, 1.0f, 1.0f
};

//the triangle on the up down
GLfloat triangle4[] = {
        -0.25f,  0.75f,  0,   0.0f, 0.0f, 1.0f,
        -0.375f,  0.625f,  0,   0.0f, 0.0f, 1.0f,
        -0.25f,  0.5f,  0,   0.0f, 0.0f, 1.0f
};

//the triangle on the middle
GLfloat triangle5[] = {
        -0.375f,  0.375f,  0,   1.0f, 1.0f, 0.0f,
        -0.5f,    0.5f,     0,   1.0f, 1.0f, 0.0f,
        -0.625f,  0.375f, 0,   1.0f, 1.0f, 0.0f
};


//the square
GLfloat square[] = {
        -0.375f,  0.375f,  0,   1.0f, 0.0f, 0.0f,
        -0.5f,      0.5,     0,   1.0f, 0.0f, 0.0f,
        -0.375f,  0.625f, 0,     1.0f, 0.0f, 0.0f,
        -0.25f,  0.5f, 0,     1.0f, 0.0f, 0.0f
};


//the parallelogram
GLfloat  parallelogram[] = {
        -0.375f,  0.375f,  0,     1.0f, 0.0f, 1.0f,
        -0.5f,      0.25f, 0,     1.0f, 0.0f, 1.0f,
        -0.75f,  0.25f, 0,     1.0f, 0.0f, 1.0f,
        -0.625f,  0.375f, 0,     1.0f, 0.0f, 1.0f
};

//the indices about the square
unsigned int indicesSquare[] = {
        0, 1, 3,
        1, 2, 3
};


//the indices about the square
unsigned int indicesParallelogram[] = {
        0, 1, 3,
        1, 2, 3
};


//vertexShaderSource
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

//fragmentShaderSource
const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 myColor; \n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(myColor, 1.0f);\n"
        "} ";





GLuint VBOs[7], VAOs[7], EBO[2]; // create VBO and VAO arrays for the two triangles
GLFWwindow* window;   //the GLFWwindow
unsigned int shaderProgram;  // the shader program

//the base trans
glm::mat4 trans = glm::mat4(1.0f);


//the transform for each shape when rendering
glm::mat4 trans1, trans2, trans3, trans4, trans5, trans6, trans7;


// the movement from the origin position to the destination for each shape
glm::vec3  move1(1.25f, -1.25f, 1.0f);
glm::vec3  move2(0.0f, -1.00f, 1.0f);
glm::vec3  move3(0.5f, 0.205f, 1.0f);
glm::vec3  move4(-0.375f, -0.875f, 1.0f);
glm::vec3  move5(0.375f, 0.125f, 1.0f);
glm::vec3  move6(-0.125f, -0.325f, 1.0f);
glm::vec3  move7(0.875f, -0.875f, 1.0f);





int order = 0;
int waitTime = 0;

int main() {




    myGlfwInit();



    bind();



    shaderProgram = generateShader();

    // render loop
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        display();

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void bind()
{


    //bind the VAO and VBO


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

    if(waitTime > 0)
    {
        waitTime--;
    } else
    {
        order = (order+1)%(speed+1);
        if(order == 0 || order == speed )
            waitTime = waitSpeed;
    }

    float a = (order)*1.0/speed;

    float first, second;


    if(order > speed/2)
    {
        first = 1.0f;
        second = 2*a-1;
    } else
    {
        first = a*2;
        second = 0.0f;
    }


    trans1 = glm::translate(trans, move1*glm::vec3(a,a,a));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans1));
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    trans2 = glm::rotate(trans, glm::radians(90.0f*first), glm::vec3(0, 0, 1.0f));
    trans2 = glm::translate(trans2, move2*glm::vec3(second,second,second));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans2));
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    trans3 = glm::translate(trans, move3*glm::vec3(first, first, first));
    trans3 = glm::rotate(trans3, glm::radians(135.0f*second), glm::vec3(0, 0, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans3));
    glBindVertexArray(VAOs[2]);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    trans4 = glm::rotate(trans, glm::radians(90.0f*first), glm::vec3(0, 0, 1.0f));
    trans4 = glm::translate(trans4, move4*glm::vec3(second,second,second));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans4));
    glBindVertexArray(VAOs[3]);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    trans5 = glm::rotate(trans, glm::radians(180.0f*first), glm::vec3(0, 0, 1.0f));
    trans5 = glm::translate(trans5, move5*glm::vec3(second,second,second));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans5));
    glBindVertexArray(VAOs[4]);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    trans6 = glm::translate(trans, move6*glm::vec3(first, first, first));
    trans6 = glm::rotate(trans6, glm::radians(225.0f*second), glm::vec3(0, 0, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans6));
    glBindVertexArray(VAOs[5]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    trans7 = glm::translate(trans, move7*glm::vec3(a,a,a));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans7));
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