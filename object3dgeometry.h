#ifndef OBJECT3DGEOMETRY_H
#define OBJECT3DGEOMETRY_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class Object3DGeometry
{
public:
    Object3DGeometry() {}

    virtual void drawObjectGeometry(QOpenGLShaderProgram *program) = 0;
    virtual void setObjectGeometry(qreal length, qreal width, qreal height) = 0;

protected:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer *indexBuf;
};

#endif // OBJECT3DGEOMETRY_H
