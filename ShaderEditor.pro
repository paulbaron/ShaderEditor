#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T16:52:41
#
#-------------------------------------------------

QT       += core gui declarative opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShaderEditor
TEMPLATE = app

FORMS    += \
    EditorMainWindow.ui \
    RenderPassUi.ui

HEADERS += \
    BezierCurveView.hpp \
    Commons.hpp \
    NodeLinkView.hpp \
    NodePortView.hpp \
    NodeView.hpp \
    TemporaryPortView.hpp \
    EditorMainWindow.hpp \
    RenderPass.hh \
    RenderPassUi.h \
    RenderPassView.hh \
    OpenGLContext.hh

SOURCES += \
    BezierCurveView.cpp \
    Commons.cpp \
    main.cpp \
    NodeLinkView.cpp \
    NodePortView.cpp \
    NodeView.cpp \
    TemporaryPortView.cpp \
    EditorMainWindow.cpp \
    RenderPass.cpp \
    RenderPassUi.cpp \
    RenderPassView.cpp \
    OpenGLContext.cpp
