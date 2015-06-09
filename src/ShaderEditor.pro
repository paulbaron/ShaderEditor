#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T16:52:41
#
#-------------------------------------------------

QT       += core gui declarative opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShaderEditor
TEMPLATE = app

FORMS += \
    EditorMainWindow.ui \
    RenderPassUi.ui \
    DataStructureEditor.ui \
    DataStructure/View/TextureDataView.ui

HEADERS += \
    BezierCurveView.hpp \
    Commons.hpp \
    EditorMainWindow.hpp \
    NodeLinkView.hpp \
    NodePortView.hpp \
    NodeView.hpp \
    RenderPass.hh \
    RenderPassUi.h \
    RenderPassView.hh \
    TemporaryPortView.hpp \
    DataStructureEditor.hh \
    DataStructureManager.hh \
    DataStructure/DataStructureManager.hh \
    DataStructure/AbstractData.hh \
    DataStructure/TextureData.hh \
    DataStructure/VectorData.hh \
    DataStructure/Mat2Data.hh \
    DataStructure/Mat3Data.hh \
    DataStructure/Mat4Data.hh \
    DataStructure/VertexBufferData.hh \
    DataStructure/View/TextureDataView.hh \
    DataStructure/ContainerData.hh

SOURCES += \
    BezierCurveView.cpp \
    Commons.cpp \
    EditorMainWindow.cpp \
    main.cpp \
    NodeLinkView.cpp \
    NodePortView.cpp \
    NodeView.cpp \
    RenderPass.cpp \
    RenderPassUi.cpp \
    RenderPassView.cpp \
    TemporaryPortView.cpp \
    DataStructureEditor.cpp \
    DataStructure/DataStructureManager.cpp \
    DataStructure/TextureData.cpp \
    DataStructure/VectorData.cpp \
    DataStructure/Mat2Data.cpp \
    DataStructure/Mat3Data.cpp \
    DataStructure/Mat4Data.cpp \
    DataStructure/VertexBufferData.cpp \
    DataStructure/View/TextureDataView.cpp \
    DataStructure/ContainerData.cpp
