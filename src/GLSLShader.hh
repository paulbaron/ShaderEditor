#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>
#include <QString>
#include <QMap>

#include <QOpenGLContext>

class GLSLShader
{
public:
    enum EShaderType
    {
        VERTEX_SHADER = GL_VERTEX_SHADER,
        FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
        GEOMETRY_ID = GL_GEOMETRY_SHADER
    };

public:
    GLSLShader();
    virtual ~GLSLShader();
    // Bind the shader as the current used shader
    void bind();
    // Get the OpenGL program ID
    GLuint getProgramId() const;
    // Load a vertex or a fragment shader from a file
    void load(const QString &code, EShaderType type);
    // Get the location of a constant variable in the shader
    GLuint getUniformId(const QString &k);

    // Setters for the different kind of constant variables
    bool setUniform(const QString &k, glm::vec1 const &v);
    bool setUniform(const QString &k, glm::vec2 const &v);
    bool setUniform(const QString &k, glm::vec3 const &v);
    bool setUniform(const QString &k, glm::vec4 const &v);
    bool setUniform(const QString &k, glm::mat2 const &v);
    bool setUniform(const QString &k, glm::mat3 const &v);
    bool setUniform(const QString &k, glm::mat4 const &v);
    bool setUniform(const QString &k, glm::ivec2 const &v);
    bool setUniform(const QString &k, glm::ivec3 const &v);
    bool setUniform(const QString &k, glm::ivec4 const &v);
    bool setUniform(const QString &k, glm::uvec2 const &v);
    bool setUniform(const QString &k, glm::uvec3 const &v);
    bool setUniform(const QString &k, glm::uvec4 const &v);
    bool setUniform(const QString &k, float v);
    bool setUniform(const QString &k, unsigned int v);
    bool setUniform(const QString &k, int v);

    // Build and link the shader
    void build();
    // Bind a shader attribute to a location
    void bindAttribLocation(GLuint location, QString const &attribName);
    // Bind a sampler to the binding point texUnit
    bool bindTextureUnit(GLuint texUnit, QString const &samplerName);

protected:
    void _build();

    // Compile the shader
    void _compileShader(GLuint shaderId);
    // Link the program
    void _linkProgram();

private:

    GLuint _programId;
    GLuint _vertexId;
    GLuint _fragmentId;
    GLuint _geoId;
};
