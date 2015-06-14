#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include "AbstractData.hh"
#include "View/TextureDataView.hh"

class TextureData : public AbstractData
{
public:
    TextureData();
    ~TextureData();

    GLenum getInternalFormat() const;

public slots:
    void saveChanges();

private:
    // Useful functions
    GLenum getPixelFormatFromIndex(int idx) const;
    int getIndexFromPixelFormat(GLenum format) const;
    GLenum getWrapModeFromIndex(int idx) const;
    int getIndexFromWrapMode(GLenum format) const;
    GLenum getFilterModeFromIndex(int idx) const;
    int getIndexFromFilterMode(GLenum format) const;
    void getFormatInfo(GLenum internalFormat, GLenum &format, GLenum &type);

    void updateUi();
    void updateOpenGLParameters();

    // Actual texture data
    GLuint _id;
    GLenum _format;
    GLenum _magFilter;
    GLenum _minFilter;
    GLenum _verticalWrapMode;
    GLenum _horizontalWrapMode;
    GLuint _width;
    GLuint _height;
};

#endif // TEXTUREDATA_H
