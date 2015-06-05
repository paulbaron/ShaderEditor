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
    RenderPassUi.ui

HEADERS += \
    BezierCurveView.hpp \
    Commons.hpp \
    EditorMainWindow.hpp \
    NodeLinkView.hpp \
    NodePortView.hpp \
    NodeView.hpp \
    OpenGLContext.hh \
    RenderPass.hh \
    RenderPassUi.h \
    RenderPassView.hh \
    TemporaryPortView.hpp

SOURCES += \
    BezierCurveView.cpp \
    Commons.cpp \
    EditorMainWindow.cpp \
    main.cpp \
    NodeLinkView.cpp \
    NodePortView.cpp \
    NodeView.cpp \
    OpenGLContext.cpp \
    RenderPass.cpp \
    RenderPassUi.cpp \
    RenderPassView.cpp \
    TemporaryPortView.cpp
