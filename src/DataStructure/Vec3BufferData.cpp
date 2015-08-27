#include "Vec3BufferData.hh"

#include "QtOpenGLFunctions.hh"

#include "GenerateIcoSphere.hh"

BOOST_CLASS_EXPORT_IMPLEMENT(Vec3BufferData)

Vec3BufferData::Vec3BufferData()
{
    BufferDataView<glm::vec3, DoubleSpinBoxDelegate> *bufferView =
            new BufferDataView<glm::vec3, DoubleSpinBoxDelegate>(this);
    QVector<glm::vec3> preset;

    glm::vec3 cube[8] =
    {
        glm::vec3(-0.5, 0.5, 0.5),
        glm::vec3(-0.5, 0.5, -0.5),
        glm::vec3(0.5, 0.5, -0.5),
        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(-0.5, -0.5, 0.5),
        glm::vec3(-0.5, -0.5, -0.5),
        glm::vec3(0.5, -0.5, -0.5),
        glm::vec3(0.5, -0.5, 0.5),
    };

    // Face 1
    preset.push_back(cube[0]);
    preset.push_back(cube[1]);
    preset.push_back(cube[2]);

    preset.push_back(cube[2]);
    preset.push_back(cube[3]);
    preset.push_back(cube[0]);

    // Face 2
    preset.push_back(cube[4]);
    preset.push_back(cube[5]);
    preset.push_back(cube[6]);

    preset.push_back(cube[6]);
    preset.push_back(cube[7]);
    preset.push_back(cube[4]);

    // Face 3
    preset.push_back(cube[0]);
    preset.push_back(cube[3]);
    preset.push_back(cube[7]);

    preset.push_back(cube[7]);
    preset.push_back(cube[4]);
    preset.push_back(cube[0]);

    // Face 4
    preset.push_back(cube[1]);
    preset.push_back(cube[2]);
    preset.push_back(cube[6]);

    preset.push_back(cube[6]);
    preset.push_back(cube[5]);
    preset.push_back(cube[1]);

    // Face 5
    preset.push_back(cube[1]);
    preset.push_back(cube[0]);
    preset.push_back(cube[4]);

    preset.push_back(cube[4]);
    preset.push_back(cube[5]);
    preset.push_back(cube[1]);

    // Face 6
    preset.push_back(cube[2]);
    preset.push_back(cube[3]);
    preset.push_back(cube[7]);

    preset.push_back(cube[7]);
    preset.push_back(cube[6]);
    preset.push_back(cube[2]);

    bufferView->addPreset("Cube vertices", preset);

    preset.clear();

    for (int i = 0; i < 6; ++i)
    {
        preset.push_back(glm::vec3(0, 1, 0));
    }
    for (int i = 0; i < 6; ++i)
    {
        preset.push_back(glm::vec3(0, -1, 0));
    }
    for (int i = 0; i < 6; ++i)
    {
        preset.push_back(glm::vec3(0, 0, 1));
    }
    for (int i = 0; i < 6; ++i)
    {
        preset.push_back(glm::vec3(0, 0, -1));
    }
    for (int i = 0; i < 6; ++i)
    {
        preset.push_back(glm::vec3(-1, 0, 0));
    }
    for (int i = 0; i < 6; ++i)
    {
        preset.push_back(glm::vec3(1, 0, 0));
    }

    bufferView->addPreset("Cube normals", preset);

    preset.clear();

    preset.push_back(glm::vec3(-1, -1, 0));
    preset.push_back(glm::vec3(-1, 1, 0));
    preset.push_back(glm::vec3(1, 1, 0));
    preset.push_back(glm::vec3(1, 1, 0));
    preset.push_back(glm::vec3(1, -1, 0));
    preset.push_back(glm::vec3(-1, -1, 0));

    bufferView->addPreset("Plane vertices", preset);

    preset.clear();

    preset.push_back(glm::vec3(0, 0, 1));
    preset.push_back(glm::vec3(0, 0, 1));
    preset.push_back(glm::vec3(0, 0, 1));
    preset.push_back(glm::vec3(0, 0, 1));
    preset.push_back(glm::vec3(0, 0, 1));
    preset.push_back(glm::vec3(0, 0, 1));

    bufferView->addPreset("Plane normals", preset);

    preset.clear();

    for (int i = 0; i < 8; ++i)
    {
        preset.push_back(cube[i]);
    }

    bufferView->addPreset("Cube indexed vertices", preset);

    preset.clear();

    preset.push_back(glm::vec3(-1, -1, 0));
    preset.push_back(glm::vec3(-1, 1, 0));
    preset.push_back(glm::vec3(1, 1, 0));
    preset.push_back(glm::vec3(1, -1, 0));

    bufferView->addPreset("Plane indexed vertices", preset);

    preset.clear();

    std::vector<glm::vec3> points;
    std::vector<glm::uvec1> idx;

    generateIcoSphere(1, points, idx);

    preset = QVector<glm::vec3>::fromStdVector(points);

    bufferView->addPreset("IcoSphere indexed vertices (1 recursions)", preset);

    preset.clear();
    points.clear();
    idx.clear();

    generateIcoSphere(2, points, idx);

    preset = QVector<glm::vec3>::fromStdVector(points);

    bufferView->addPreset("IcoSphere indexed vertices (2 recursions)", preset);

    preset.clear();
    points.clear();
    idx.clear();

    generateIcoSphere(3, points, idx);

    preset = QVector<glm::vec3>::fromStdVector(points);

    bufferView->addPreset("IcoSphere indexed vertices (3 recursions)", preset);

    _view = bufferView;
}

QString Vec3BufferData::getInputType() const
{
    return ("in vec3");
}

void Vec3BufferData::setInput(QString inputName, GLSLShader &program, int textureBinding)
{
    _vbo.bind();
    GLuint attributeIdx = GLContext::get()->glGetAttribLocation(program.getProgramId(), inputName.toStdString().c_str());
    GLContext::get()->glEnableVertexAttribArray(attributeIdx);
    GLContext::get()->glVertexAttribPointer(attributeIdx, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Vec3BufferData::saveChanges()
{
    BufferDataView<glm::vec3, DoubleSpinBoxDelegate> *dataView =
            static_cast<BufferDataView<glm::vec3, DoubleSpinBoxDelegate>*>(_view);
    glm::vec3 *data = dataView->getData();

    _count = dataView->getDataCount();
    _vbo.bind();
    _vbo.allocate(data, _count * 3 * sizeof(float));
}
