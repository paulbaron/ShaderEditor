#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T16:52:41
#
#-------------------------------------------------

QT       += core gui declarative opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShaderEditor
TEMPLATE = app

LIBS += -L../vendors/DevIL/lib -lDevIL -lILU -lILUT

INCLUDEPATH += ../vendors/
INCLUDEPATH += ../vendors/DevIL/include/
INCLUDEPATH += ../vendors/boost/

FORMS += \
    EditorMainWindow.ui \
    RenderPassUi.ui \
    DataStructureEditor.ui \
    DataStructure/View/ContainerView.ui \
    DataStructure/View/Mat4DataView.ui \
    DataStructure/View/Mat3DTransformView.ui \
    DataStructure/View/Mat3DLookAtView.ui \
    DataStructure/View/MatPerspectiveView.ui \
    RenderPassListUi.ui \
    DataStructure/View/BufferDataView.ui \
    DataStructure/View/RenderTextureDataView.ui \
    DataStructure/View/LoadedTextureDataView.ui \
    DataStructure/View/BaseVecView.ui

HEADERS += \
    BezierCurveView.hpp \
    Commons.hpp \
    EditorMainWindow.hpp \
    RenderPass.hh \
    RenderPassUi.h \
    DataStructureEditor.hh \
    DataStructure/DataStructureManager.hh \
    DataStructure/AbstractData.hh \
    DataStructure/View/ContainerView.hh \
    DataStructure/Vec3BufferData.hh \
    DataStructure/View/Mat4DataView.hh \
    DataStructure/View/GlmVecTableModel.hh \
    DataStructure/View/DoubleSpinBoxDelegate.hh \
    DataStructure/View/Mat3DTransformView.hh \
    DataStructure/View/Mat3DLookAtView.hh \
    DataStructure/SInstance.hh \
    RenderPassManager.hh \
    DataStructure/View/MatPerspectiveView.hh \
    InputChecker.hh \
    RenderPassListUi.hh \
    DataStructure/Vec2BufferData.hh \
    DataStructure/ABufferData.hh \
    DataStructure/IndexBufferData.hh \
    DataStructure/View/BufferDataView.hpp \
    DataStructure/View/UintSpinBoxDelegate.hh \
    DataStructure/RenderTextureData.hh \
    DataStructure/View/RenderTextureDataView.hh \
    DataStructure/LoadedTextureData.hh \
    DataStructure/ATextureData.hh \
    DataStructure/View/LoadedTextureDataView.hh \
    OpenGLTextureWidget.hh \
    OpenGLState.hh \
    DataStructure/View/GLSLHighlighter.hh \
    EditorException.hh \
    GLSLShader.hh \
    DataStructure/Mat4Data.hh \
    QtOpenGLFunctions.hh \
    Singleton.hpp \
    GlmSerialization.hh \
    DataStructure/VecData.hpp \
    DataStructure/View/BaseVecView.hh \
    DataStructure/View/VecView.hpp \
    GenerateIcoSphere.hh

SOURCES += \
    BezierCurveView.cpp \
    Commons.cpp \
    EditorMainWindow.cpp \
    main.cpp \
    RenderPass.cpp \
    RenderPassUi.cpp \
    DataStructureEditor.cpp \
    DataStructure/DataStructureManager.cpp \
    DataStructure/AbstractData.cpp \
    DataStructure/View/ContainerView.cpp \
    DataStructure/Vec3BufferData.cpp \
    DataStructure/View/Mat4DataView.cpp \
    DataStructure/View/DoubleSpinBoxDelegate.cpp \
    DataStructure/View/Mat3DTransformView.cpp \
    DataStructure/View/Mat3DLookAtView.cpp \
    DataStructure/SInstance.cpp \
    RenderPassManager.cpp \
    DataStructure/View/MatPerspectiveView.cpp \
    InputChecker.cpp \
    RenderPassListUi.cpp \
    DataStructure/Vec2BufferData.cpp \
    DataStructure/ABufferData.cpp \
    DataStructure/IndexBufferData.cpp \
    DataStructure/View/UintSpinBoxDelegate.cpp \
    DataStructure/RenderTextureData.cpp \
    DataStructure/View/RenderTextureDataView.cpp \
    DataStructure/LoadedTextureData.cpp \
    DataStructure/ATextureData.cpp \
    DataStructure/View/LoadedTextureDataView.cpp \
    OpenGLTextureWidget.cpp \
    OpenGLState.cpp \
    DataStructure/View/GLSLHighlighter.cpp \
    EditorException.cpp \
    GLSLShader.cpp \
    DataStructure/Mat4Data.cpp \
    QtOpenGLFunctions.cpp \
    DataStructure/View/BaseVecView.cpp \
    DataStructure/VecData.cpp \
    GenerateIcoSphere.cpp

LIBS += -L../vendors/boost/build/serialization -lboost_serialization-mgw49-mt-s-1_59

DEPENDPATH += ../vendors/boost/build/serialization
