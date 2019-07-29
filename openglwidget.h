#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QMouseEvent>
#include <GL/glu.h>
#include <math.h>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "constants.h"
#include "plankgeometry.h"
#include "bevelgeometry.h"
#include "channelgeometry.h"
#include "emptyprofilegeometry.h"

class GeometryEngine;

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget();

    Object3DGeometry *geometries;

public slots:
    void setTexture(int index);
    void resizeObject(qreal length, qreal width, qreal height);

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

private:
    QOpenGLShaderProgram program;

    QOpenGLTexture *texture;

    QMatrix4x4 projection;

    QVector2D mouseLastPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;
    qreal zNear;
    qreal zFar;
    qreal fieldOfView;
    short maximalZoomIn;
    short maximalZoomOut;
    short currentZoom;
};

#endif // OPENGLWIDGET_H
