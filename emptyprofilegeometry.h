#ifndef EMPTYPROFILEGEOMETRY_H
#define EMPTYPROFILEGEOMETRY_H

#include "object3dgeometry.h"
#include "constants.h"
#include <QVector2D>
#include <QVector3D>

class EmptyProfileGeometry : protected QOpenGLFunctions, public Object3DGeometry
{
public:
    EmptyProfileGeometry();
    virtual ~EmptyProfileGeometry();

    void drawObjectGeometry(QOpenGLShaderProgram *program);
    void setObjectGeometry(qreal length, qreal width, qreal height);
};
#endif // EMPTYPROFILEGEOMETRY_H
