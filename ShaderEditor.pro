#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T16:52:41
#
#-------------------------------------------------

QT       += core gui declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShaderEditor
TEMPLATE = app

FORMS    += QiwiMainWindow.ui

HEADERS += \
    BezierCurveView.hpp \
    Commons.hpp \
    NodeLinkView.hpp \
    NodePortView.hpp \
    NodeView.hpp \
    QiwiMainWindow.hpp \
    TemporaryPortView.hpp

SOURCES += \
    BezierCurveView.cpp \
    Commons.cpp \
    main.cpp \
    NodeLinkView.cpp \
    NodePortView.cpp \
    NodeView.cpp \
    QiwiMainWindow.cpp \
    TemporaryPortView.cpp
