//
// Created by a on 08/07/2024.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "RendererHelper.h"

Matrix4X4 RendererHelper::m_ProjectionMatrix{};
Matrix4X4 RendererHelper::m_UserMatrix[32]{};
int RendererHelper::m_UserMatrixIndex{};
GLuint RendererHelper::m_Program{};
GLint RendererHelper::m_matrixLocation{};
GLuint RendererHelper::m_vertexBuffer{};

void RendererHelper::SetProjectionMatrix(float left, float right, float top, float bottom, float far, float near)
{
    m_ProjectionMatrix = Matrix4X4{
       2.0f/(left-right), 0, 0, -((right+left)/(right-left)),
       0, 2.0f/(top-bottom), 0, -((top+bottom)/(top-bottom)),
       0, 0, -2.0f/(far-near), -((far+near)/(far-near)),
       0, 0, 0, 1
   };

    for (int i = 0; i < 32; ++i)
    {
        m_UserMatrix[i] = Matrix4X4::IdentityMatrix();
    }
}

void RendererHelper::PopMatrix()
{
    if(m_UserMatrixIndex >= 0)
    {
        --m_UserMatrixIndex;
    }
}

void RendererHelper::PushMatrix()
{
    if(m_UserMatrixIndex > 32)
    {
        throw "Use more the 32 matrix";
    }
    ++m_UserMatrixIndex;
}

void RendererHelper::IdentityMatrix()
{
    m_UserMatrix[m_UserMatrixIndex] = Matrix4X4::IdentityMatrix();
}

void RendererHelper::TranslateMatrix(float x, float y)
{
    TranslateMatrix(Vector2f{x,y});
}

void RendererHelper::TranslateMatrix(Vector2f translate)
{
    m_UserMatrix[m_UserMatrixIndex] = m_UserMatrix[m_UserMatrixIndex] * Matrix4X4::TranslationMatrix(translate);
};

void RendererHelper::ScaleMatrix(float x, float y)
{
    m_UserMatrix[m_UserMatrixIndex] = m_UserMatrix[m_UserMatrixIndex] * Matrix4X4::ScaleMatrix(x, y, 1);
}

void RendererHelper::MultiMatrix(const Matrix4X4& matrixToMulti)
{
    m_UserMatrix[m_UserMatrixIndex] = m_UserMatrix[m_UserMatrixIndex] * matrixToMulti;
}

void RendererHelper::Setup()
{
    m_Program = CreateShader();
    glUseProgram(m_Program);
    
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    
    m_matrixLocation = glGetUniformLocation(m_Program, "u_ProjectionMatrix");
    GLint posAttrib = glGetAttribLocation(m_Program, "VertexPosition");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(posAttrib);
    GLint uvAttrib = glGetAttribLocation(m_Program, "UvCoords");
    glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(uvAttrib);
}

void CheckShaderErrors(unsigned int shader)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR" << '\n' << infoLog << '\n';
    }

}

void CheckProgramErrors(unsigned int program)
{
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR" << '\n' << infoLog << '\n';
    }
}

GLuint RendererHelper::CreateShader()
{
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    // open files
    vShaderFile.open("Resources/vertexShader.vert");
    fShaderFile.open("Resources/fragmentShader.frag");
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode   = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexCodePtr = vertexCode.c_str();
    glShaderSource(vertex, 1, &vertexCodePtr, nullptr);
    glCompileShader(vertex);
    CheckShaderErrors(vertex);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentCodePtr = fragmentCode.c_str();
    glShaderSource(fragment, 1, &fragmentCodePtr, nullptr);
    glCompileShader(fragment);
    CheckShaderErrors(fragment);

    GLuint ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    CheckProgramErrors(ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return ID;
}

void RendererHelper::DrawTexture(const Rectf &positionCoords, const Rectf &uvCoords)
{
    Matrix4X4 newMatrix = m_ProjectionMatrix;
    for (int i = 0; i < m_UserMatrixIndex+1; ++i)
    {
        newMatrix = newMatrix * m_UserMatrix[i];
    }
    GLfloat array[16];
    newMatrix.OpenGlArray(array);
    glUniformMatrix4fv(m_matrixLocation, 1, true, array);

    const GLfloat meshUv[] = {
        positionCoords.left, positionCoords.top, uvCoords.left, uvCoords.top,
        positionCoords.left, positionCoords.height, uvCoords.left, uvCoords.height,
        positionCoords.width, positionCoords.height, uvCoords.width,uvCoords.height,
        positionCoords.width, positionCoords.top, uvCoords.width,uvCoords.top
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(meshUv), &meshUv, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}


