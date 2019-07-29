#ifndef CHANNELGEOMETRY_H
#define CHANNELGEOMETRY_H

#include "object3dgeometry.h"
#include "constants.h"
#include <QVector2D>
#include <QVector3D>

class ChannelGeometry : protected QOpenGLFunctions, public Object3DGeometry
{
public:
    ChannelGeometry();
    virtual ~ChannelGeometry();

    void drawObjectGeometry(QOpenGLShaderProgram *program);
    void setObjectGeometry(qreal length, qreal width, qreal height);
};
#endif // CHANNELGEOMETRY_H
