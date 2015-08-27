#include <GLSLShader.hh>
#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "QtOpenGLFunctions.hh"

#include "EditorException.hh"

GLSLShader::GLSLShader()
		: _programId(0)
		, _vertexId(0)
		, _fragmentId(0)
		, _geoId(0)
{
    _programId = GLContext::get()->glCreateProgram();
}

GLSLShader::~GLSLShader()
{
    if (_programId != 0)
        GLContext::get()->glDeleteProgram(_programId);
}

void GLSLShader::bind()
{
    GLContext::get()->glUseProgram(_programId);
}

GLuint GLSLShader::getProgramId() const
{
    return _programId;
}

void GLSLShader::load(const QString &code, EShaderType type)
{
    std::string tmpCode;
    GLchar const *content;
    GLint fileSize;
    GLuint shaderId;

    tmpCode = code.toStdString();
    fileSize = tmpCode.size();
    content = tmpCode.c_str();
    shaderId = GLContext::get()->glCreateShader(type);
    GLContext::get()->glShaderSource(shaderId, 1,
        const_cast<const GLchar**>(&content),
        const_cast<const GLint*>(&fileSize));
    _compileShader(shaderId);
    switch (type)
    {
    case VERTEX_SHADER:
        if (_vertexId != 0)
        {
            GLContext::get()->glDeleteShader(_vertexId);
        }
        _vertexId = shaderId;
        break;
    case FRAGMENT_SHADER:
        if (_fragmentId != 0)
        {
            GLContext::get()->glDeleteShader(_fragmentId);
        }
        _fragmentId = shaderId;
        break;
    case GEOMETRY_ID:
        if (_geoId != 0)
        {
            GLContext::get()->glDeleteShader(_geoId);
        }
        _geoId = shaderId;
        break;
    default:
        assert("This shader type does not exist.");
        break;
    }
}

void GLSLShader::_compileShader(GLuint shaderId)
{
    GLint         compileRet = 0;
    GLsizei       msgLenght;
    GLchar        *errorMsg;

    GLContext::get()->glCompileShader(shaderId);
    GLContext::get()->glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileRet);
    if (compileRet == GL_FALSE)
    {
        GLContext::get()->glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &msgLenght);
        errorMsg = new GLchar[msgLenght];
        GLContext::get()->glGetShaderInfoLog(shaderId, msgLenght,
            &msgLenght, errorMsg);
        QString title = "Shader compilation error.";
        QString details = errorMsg;
        delete[] errorMsg;
        throw EditorException(title, details);
    }
}

void GLSLShader::_linkProgram()
{
    GLint         linkRet = 0;
    GLsizei       msgLength;
    GLchar        *errorMsg;

    GLContext::get()->glLinkProgram(_programId);
    GLContext::get()->glGetProgramiv(_programId, GL_LINK_STATUS, &linkRet);
    if (linkRet == GL_FALSE)
    {
        GLContext::get()->glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &msgLength);
        errorMsg = new GLchar[msgLength];
        GLContext::get()->glGetProgramInfoLog(_programId, msgLength,
            &msgLength, errorMsg);
        QString title = "Shader link error.";
        QString details = errorMsg;
        delete[] errorMsg;
        throw EditorException(title, details);
    }
    if (_vertexId != 0)
    {
        GLContext::get()->glDetachShader(_programId, _vertexId);
        GLContext::get()->glDeleteShader(_vertexId);
        _vertexId = 0;
    }
    if (_fragmentId != 0)
    {
        GLContext::get()->glDetachShader(_programId, _fragmentId);
        GLContext::get()->glDeleteShader(_fragmentId);
        _fragmentId = 0;
    }
    if (_geoId != 0)
    {
        GLContext::get()->glDetachShader(_programId, _geoId);
        GLContext::get()->glDeleteShader(_geoId);
        _geoId = 0;
    }
}

void GLSLShader::_build()
{
    if (_programId != 0)
        GLContext::get()->glDeleteProgram(_programId);
    _programId = GLContext::get()->glCreateProgram();

    if (_vertexId != 0)
    {
        GLContext::get()->glAttachShader(_programId, _vertexId);
    }
    if (_fragmentId != 0)
    {
        GLContext::get()->glAttachShader(_programId, _fragmentId);
    }
    if (_geoId != 0)
    {
        GLContext::get()->glAttachShader(_programId, _geoId);
    }
}

GLuint GLSLShader::getUniformId(const QString &k)
{
    return GLContext::get()->glGetUniformLocation(_programId, k.toStdString().c_str());
}

void GLSLShader::bindAttribLocation(GLuint location, QString const &attribName)
{
    GLContext::get()->glBindAttribLocation(_programId, location, attribName.toStdString().c_str());
}

void GLSLShader::build()
{
    _build();
    _linkProgram();
}

bool GLSLShader::bindTextureUnit(GLuint texUnit, QString const &samplerName)
{
    GLint samplerLocation = GLContext::get()->glGetUniformLocation(_programId, samplerName.toStdString().c_str());
    if (samplerLocation == -1)
        return (false);
    GLContext::get()->glUniform1i(samplerLocation, texUnit);
    return (true);
}

bool GLSLShader::setUniform(const QString &k, glm::vec1 const &v)
{
    return (setUniform(k, v.x));
}

bool GLSLShader::setUniform(const QString &k, glm::vec2 const &v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniform2fv(l, 1, glm::value_ptr(v));
    return true;
}

bool GLSLShader::setUniform(const QString &k, glm::vec3 const &v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniform3fv(l, 1, glm::value_ptr(v));
    return true;
}

bool GLSLShader::setUniform(const QString &k, glm::vec4 const &v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniform4fv(l, 1, glm::value_ptr(v));
    return true;
}

bool GLSLShader::setUniform(const QString &k, glm::mat2 const &v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniformMatrix2fv(l, 1, false, glm::value_ptr(v));
    return true;
}

bool GLSLShader::setUniform(const QString &k, glm::mat3 const &v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniformMatrix3fv(l, 1, false, glm::value_ptr(v));
    return true;
}

bool GLSLShader::setUniform(const QString &k, glm::mat4 const &v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniformMatrix4fv(l, 1, false, glm::value_ptr(v));
    return true;
}

bool GLSLShader::setUniform(const QString &k, glm::ivec2 const &v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniform2iv(l, 1, glm::value_ptr(v));
    return true;
}

bool GLSLShader::setUniform(const QString &k, glm::ivec3 const &v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniform3iv(l, 1, glm::value_ptr(v));
    return true;
}

bool GLSLShader::setUniform(const QString &k, glm::ivec4 const &v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniform4iv(l, 1, glm::value_ptr(v));
    return true;
}

bool GLSLShader::setUniform(const QString &k, glm::uvec2 const &v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniform2uiv(l, 1, glm::value_ptr(v));
    return true;
}

bool GLSLShader::setUniform(const QString &k, glm::uvec3 const &v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniform3uiv(l, 1, glm::value_ptr(v));
    return true;
}

bool GLSLShader::setUniform(const QString &k, glm::uvec4 const &v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniform4uiv(l, 1, glm::value_ptr(v));
    return true;
}

bool GLSLShader::setUniform(const QString &k, float v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniform1f(l, v);
    return true;
}

bool GLSLShader::setUniform(const QString &k, unsigned int v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniform1ui(l, v);
    return true;
}

bool GLSLShader::setUniform(const QString &k, int v)
{
    GLint l = getUniformId(k);
    if (l == -1)
        return false;
    GLContext::get()->glUniform1i(l, v);
    return true;
}
