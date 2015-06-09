#ifndef VERTEXBUFFERDATA_H
#define VERTEXBUFFERDATA_H


class VertexBufferData : public AbstractData
{
public:
    VertexBufferData();

    QWidget *getTypeEditor();

public slots:
    void saveChanges();
};

#endif // VERTEXBUFFERDATA_H
