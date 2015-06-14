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
    DataStructure/View/TextureDataView.ui \
    DataStructure/View/ContainerView.ui \
    DataStructure/View/Vec3BufferDataView.ui \
    DataStructure/View/Mat4DataView.ui \
    DataStructure/View/MatPerspectiveView.ui \
    DataStructure/View/Mat3DTransformView.ui \
    DataStructure/View/Mat3DLookAtView.ui

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
    DataStructure/View/TextureDataView.hh \
    DataStructure/View/ContainerView.hh \
    DataStructure/Vec3BufferData.hh \
    DataStructure/View/Vec3BufferDataView.hh \
    DataStructure/View/Mat4DataView.hh \
    DataStructure/View/GlmVecTableModel.hh \
    DataStructure/View/DoubleSpinBoxDelegate.hh \
    DataStructure/View/MatPerspectiveView.hh \
    DataStructure/View/Mat3DTransformView.hh \
    DataStructure/View/Mat3DLookAtView.hh \
    DataStructure/SInstance.hh \
    RenderPassManager.hh

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
    DataStructure/View/TextureDataView.cpp \
    DataStructure/AbstractData.cpp \
    DataStructure/View/ContainerView.cpp \
    DataStructure/Vec3BufferData.cpp \
    DataStructure/View/Vec3BufferDataView.cpp \
    DataStructure/View/Mat4DataView.cpp \
    DataStructure/View/DoubleSpinBoxDelegate.cpp \
    DataStructure/View/MatPerspectiveView.cpp \
    DataStructure/View/Mat3DTransformView.cpp \
    DataStructure/View/Mat3DLookAtView.cpp \
    DataStructure/SInstance.cpp \
    RenderPassManager.cpp
