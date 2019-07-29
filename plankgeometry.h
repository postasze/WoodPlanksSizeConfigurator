#ifndef PLANKGEOMETRY_H
#define PLANKGEOMETRY_H

#include "object3dgeometry.h"
#include "constants.h"
#include <QVector2D>
#include <QVector3D>

class PlankGeometry : protected QOpenGLFunctions, public Object3DGeometry
{
public:
    PlankGeometry();
    virtual ~PlankGeometry();

    void drawObjectGeometry(QOpenGLShaderProgram *program);
    void setObjectGeometry(qreal length, qreal width, qreal height);
};

#endif // PLANKGEOMETRY_H
