

#ifndef OPENGLTEST_SHADER_H
#define OPENGLTEST_SHADER_H


class Shader {
public:
    virtual ~Shader();

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    const char* fragmentCode;
    const char* vertexCode;
    unsigned int ID;
    void use();
};


#endif //OPENGLTEST_SHADER_H
