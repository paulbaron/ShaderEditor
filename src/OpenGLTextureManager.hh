#ifndef OPENGLTEXTUREMANAGER_H
#define OPENGLTEXTUREMANAGER_H

#include <QList>
#include <QString>
#include <QOpenGLContext>

class OpenGLTextureManager
{
public:
    struct STextureData
    {
        GLuint id;
        QString name;
        GLenum format;
        GLenum magFilter;
        GLenum minFilter;
        GLenum verticalWrapMode;
        GLenum horizontalWrapMode;
        int width, height;

        STextureData();
    };

    static OpenGLTextureManager *getManager();

    void removeTexture(GLuint id);
    STextureData const *getTextureData(GLuint id) const;
    void removeTexture(QString name);
    STextureData const *getTextureData(QString name) const;
    void setTextureData(STextureData const &data);

    GLenum getFormatFromIndex(int index) const;
    int getIndexFromFormat(GLenum format) const;

private:
    OpenGLTextureManager();

    void getFormatInfo(GLenum internalFormat, GLenum &format, GLenum &type);

    static OpenGLTextureManager *_singleton;

    static GLenum _textureFormatTable[][3];

    QList<STextureData> _textures;
};

#endif // OPENGLTEXTUREMANAGER_H
