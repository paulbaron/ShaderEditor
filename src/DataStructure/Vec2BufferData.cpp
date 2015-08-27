#include "Vec2BufferData.hh"

#include "QtOpenGLFunctions.hh"

BOOST_CLASS_EXPORT_IMPLEMENT(Vec2BufferData)

Vec2BufferData::Vec2BufferData()
{
    BufferDataView<glm::vec2, DoubleSpinBoxDelegate> *bufferView =
            new BufferDataView<glm::vec2, DoubleSpinBoxDelegate>(this);
    QVector<glm::vec2> preset;

    preset.push_back(glm::vec2(-1, -1));
    preset.push_back(glm::vec2(-1, 1));
    preset.push_back(glm::vec2(1, 1));
    preset.push_back(glm::vec2(1, 1));
    preset.push_back(glm::vec2(1, -1));
    preset.push_back(glm::vec2(-1, -1));

    bufferView->addPreset("Plane vertices", preset);

    preset.clear();

    preset.push_back(glm::vec2(0, 0));
    preset.push_back(glm::vec2(0, 1));
    preset.push_back(glm::vec2(1, 1));
    preset.push_back(glm::vec2(1, 1));
    preset.push_back(glm::vec2(1, 0));
    preset.push_back(glm::vec2(0, 0));

    bufferView->addPreset("Plane uvs", preset);

    preset.clear();

    // Face top and bottom
    for (int i = 0; i < 2; ++i)
    {
        preset.push_back(glm::vec2(0, 0));
        preset.push_back(glm::vec2(0, 1));
        preset.push_back(glm::vec2(1, 1));

        preset.push_back(glm::vec2(1, 1));
        preset.push_back(glm::vec2(1, 0));
        preset.push_back(glm::vec2(0, 0));
    }

    // Side faces
    for (int i = 0; i < 4; ++i)
    {
        preset.push_back(glm::vec2(0, 1));
        preset.push_back(glm::vec2(1, 1));
        preset.push_back(glm::vec2(1, 0));

        preset.push_back(glm::vec2(1, 0));
        preset.push_back(glm::vec2(0, 0));
        preset.push_back(glm::vec2(0, 1));
    }

    bufferView->addPreset("Cube uvs", preset);

    preset.clear();

    preset.push_back(glm::vec2(-1, -1));
    preset.push_back(glm::vec2(-1, 1));
    preset.push_back(glm::vec2(1, 1));
    preset.push_back(glm::vec2(1, -1));

    bufferView->addPreset("Plane indexed vertices", preset);

    _view = bufferView;
}

QString Vec2BufferData::getInputType() const
{
    return ("in vec2");
}

void Vec2BufferData::setInput(QString inputName, GLSLShader &program, int textureBinding)
{
    _vbo.bind();
    GLuint attributeIdx = GLContext::get()->glGetAttribLocation(program.getProgramId(), inputName.toStdString().c_str());
    GLContext::get()->glEnableVertexAttribArray(attributeIdx);
    GLContext::get()->glVertexAttribPointer(attributeIdx, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Vec2BufferData::saveChanges()
{
    BufferDataView<glm::vec2, DoubleSpinBoxDelegate> *dataView =
            static_cast<BufferDataView<glm::vec2, DoubleSpinBoxDelegate>*>(_view);
    glm::vec2 *data = dataView->getData();

    _count = dataView->getDataCount();
    _vbo.bind();
    _vbo.allocate(data, _count * 2 * sizeof(float));
}
