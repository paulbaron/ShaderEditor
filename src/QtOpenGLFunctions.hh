#ifndef QTOPENGLFUNCTIONS_H
#define QTOPENGLFUNCTIONS_H

#include "Singleton.hpp"

#include <QOpenGLFunctions_3_1>

class QtOpenGLFunctions : public QOpenGLFunctions_3_1
{
public:
    QtOpenGLFunctions();
};

typedef Singleton<QtOpenGLFunctions> GLContext;

#endif // QTOPENGLFUNCTIONS_H
