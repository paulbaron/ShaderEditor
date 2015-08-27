#include "IndexBufferData.hh"

#include "GenerateIcoSphere.hh"

BOOST_CLASS_EXPORT_IMPLEMENT(IndexBufferData)

IndexBufferData::IndexBufferData() :
    ABufferData(QOpenGLBuffer::IndexBuffer)
{
    BufferDataView<glm::uvec1, UintSpinBoxDelegate> *bufferView =
            new BufferDataView<glm::uvec1, UintSpinBoxDelegate>(this);
    QVector<glm::uvec1> preset;

    // Face 1
    preset.push_back(glm::uvec1(0));
    preset.push_back(glm::uvec1(1));
    preset.push_back(glm::uvec1(2));
    preset.push_back(glm::uvec1(2));
    preset.push_back(glm::uvec1(3));
    preset.push_back(glm::uvec1(0));

    // Face 2
    preset.push_back(glm::uvec1(4));
    preset.push_back(glm::uvec1(5));
    preset.push_back(glm::uvec1(6));
    preset.push_back(glm::uvec1(6));
    preset.push_back(glm::uvec1(7));
    preset.push_back(glm::uvec1(4));

    // Face 3
    preset.push_back(glm::uvec1(0));
    preset.push_back(glm::uvec1(3));
    preset.push_back(glm::uvec1(7));
    preset.push_back(glm::uvec1(7));
    preset.push_back(glm::uvec1(4));
    preset.push_back(glm::uvec1(0));

    // Face 4
    preset.push_back(glm::uvec1(1));
    preset.push_back(glm::uvec1(2));
    preset.push_back(glm::uvec1(6));
    preset.push_back(glm::uvec1(6));
    preset.push_back(glm::uvec1(5));
    preset.push_back(glm::uvec1(1));

    // Face 5
    preset.push_back(glm::uvec1(1));
    preset.push_back(glm::uvec1(0));
    preset.push_back(glm::uvec1(4));
    preset.push_back(glm::uvec1(4));
    preset.push_back(glm::uvec1(5));
    preset.push_back(glm::uvec1(1));

    // Face 6
    preset.push_back(glm::uvec1(2));
    preset.push_back(glm::uvec1(3));
    preset.push_back(glm::uvec1(7));
    preset.push_back(glm::uvec1(7));
    preset.push_back(glm::uvec1(6));
    preset.push_back(glm::uvec1(2));

    bufferView->addPreset("Cube Indices", preset);
    preset.clear();

    preset.push_back(glm::uvec1(0));
    preset.push_back(glm::uvec1(1));
    preset.push_back(glm::uvec1(2));
    preset.push_back(glm::uvec1(2));
    preset.push_back(glm::uvec1(3));
    preset.push_back(glm::uvec1(0));

    bufferView->addPreset("Plane Indices", preset);

    preset.clear();

    std::vector<glm::vec3> points;
    std::vector<glm::uvec1> idx;

    generateIcoSphere(1, points, idx);

    preset = QVector<glm::uvec1>::fromStdVector(idx);

    bufferView->addPreset("IcoSphere index (1 recursions)", preset);

    preset.clear();
    points.clear();
    idx.clear();

    generateIcoSphere(2, points, idx);

    preset = QVector<glm::uvec1>::fromStdVector(idx);

    bufferView->addPreset("IcoSphere index (2 recursions)", preset);

    preset.clear();
    points.clear();
    idx.clear();

    generateIcoSphere(3, points, idx);

    preset = QVector<glm::uvec1>::fromStdVector(idx);

    bufferView->addPreset("IcoSphere index (3 recursions)", preset);

    _view = bufferView;
}

QString IndexBufferData::getInputType() const
{
    return ("- NO TYPE -");
}

void IndexBufferData::setInput(QString inputName, GLSLShader &program, int textureBinding)
{
    _vbo.bind();
}

void IndexBufferData::saveChanges()
{
    BufferDataView<glm::uvec1, UintSpinBoxDelegate> *dataView =
            static_cast<BufferDataView<glm::uvec1, UintSpinBoxDelegate>*>(_view);
    glm::uvec1 *data = dataView->getData();

    _count = dataView->getDataCount();
    _vbo.bind();
    _vbo.allocate(data, _count * sizeof(unsigned int));
}
