#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    texture(0),
    angularSpeed(3),
    zNear(0.1),
    zFar(10.0),
    fieldOfView(60.0),
    maximalZoomIn(10),
    maximalZoomOut(-10),
    currentZoom(0)
{
}

OpenGLWidget::~OpenGLWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
    doneCurrent();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mouseLastPosition = QVector2D(e->localPos());
}

void OpenGLWidget::wheelEvent(QWheelEvent *e)
{
    int w = this->width();
    int h = this->height();

    if(e->delta() > 0 && currentZoom < maximalZoomIn)
        currentZoom++;
    else if(e->delta() < 0 && currentZoom > maximalZoomOut)
        currentZoom--;

    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fieldOfView + 2*currentZoom, aspect, zNear, zFar);

    update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    // Mouse release position - last mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mouseLastPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Calculate difference relative to the length of the mouse sweep
    qreal difference = diff.length() / 100.0;

    // Calculate new rotation axis
    rotationAxis = (n * difference).normalized();

    // Update rotation and mouse position
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    mouseLastPosition = QVector2D(e->localPos());

    update();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(230.0f/255.0f, 210.0f/255.0f, 170.0f/255.0f, 0.5f);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    switch(currentObject3D)
    {
    case 0: // Plank - deska
        geometries = new PlankGeometry(); // rotate the object so that it is viewed in perspective
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(1.0, -1.0, -1.0), 45);
        break;
    case 1: // Channel - ceownik
        geometries = new ChannelGeometry(); // rotate object so that it is viewed in perspective
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(-2.0, -2.0, -1.0), 80);
        break;
    case 2: // FullProfile - profil pelny
        break;
    case 3: // EmptyProfile - profil przelotowy
        geometries = new EmptyProfileGeometry(); // rotate object so that it is viewed in perspective
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(-2.0, -2.0, -1.0), 80);
        break;
    case 4: // Bevel - katownik
        geometries = new BevelGeometry(); // rotate object so that it is viewed in perspective
        rotation = QQuaternion::fromAxisAndAngle(QVector3D(-2.0, -2.0, -1.0), 80);
        break;
    }
}

void OpenGLWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void OpenGLWidget::initTextures()
{
    // Load initial texture image
    switch(currentWoodType)
    {
    case 0: // Karbon
        texture = new QOpenGLTexture(QImage(":/textures/jasny_braz4.jpg").mirrored()); // braz jasny
        break;
    case 1: // Retro
        if(euroPlank)
            texture = new QOpenGLTexture(QImage(":/textures/gray5.jpg").mirrored()); // retro surowy
        else
            texture = new QOpenGLTexture(QImage(":/textures/dark5.jpg").mirrored()); // retro braz
        break;
    case 2: // Modern
        if(euroPlank)
            texture = new QOpenGLTexture(QImage(":/textures/gray.jpg").mirrored()); // modern surowy
        else
            texture = new QOpenGLTexture(QImage(":/textures/dark10.jpg").mirrored()); // modern braz
        break;
    }

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void OpenGLWidget::setTexture(int index)
{
    switch(index)
    {
    case 0: // bagienny ciemny
        texture = new QOpenGLTexture(QImage(":/textures/dark1.jpg").mirrored());
        break;
    case 1: // bagienny jasny
        texture = new QOpenGLTexture(QImage(":/textures/dark9.jpg").mirrored());
        break;
    case 2: // bialy
        texture = new QOpenGLTexture(QImage(":/textures/white2.jpg").mirrored());
        break;
    case 3: // braz ciemny
        texture = new QOpenGLTexture(QImage(":/textures/dark3.jpg").mirrored());
        break;
    case 4: // braz jasny
        texture = new QOpenGLTexture(QImage(":/textures/jasny_braz4.jpg").mirrored());
        break;
    case 5: // exotic
        texture = new QOpenGLTexture(QImage(":/textures/dark2.jpg").mirrored());
        break;
    case 6: // purpura ciemna
        texture = new QOpenGLTexture(QImage(":/textures/purple2.jpg").mirrored());
        break;
    case 7: // pupura jasna
        texture = new QOpenGLTexture(QImage(":/textures/dark4.jpg").mirrored());
        break;
    case 8: // retro braz
        texture = new QOpenGLTexture(QImage(":/textures/dark5.jpg").mirrored());
        break;
    case 9: // retro purpura
        texture = new QOpenGLTexture(QImage(":/textures/medium6.jpg").mirrored());
        break;
    case 10: // retro surowy
        texture = new QOpenGLTexture(QImage(":/textures/gray5.jpg").mirrored());
        break;
    case 11: // retro bagienny
        texture = new QOpenGLTexture(QImage(":/textures/dark6.jpg").mirrored());
        break;
    case 12: // modern braz
        texture = new QOpenGLTexture(QImage(":/textures/dark10.jpg").mirrored());
        break;
    case 13: // modern purpura
        texture = new QOpenGLTexture(QImage(":/textures/purple5.jpg").mirrored());
        break;
    case 14: // modern surowy
        texture = new QOpenGLTexture(QImage(":/textures/gray.jpg").mirrored());
        break;
    case 15: // modern bagienny
        texture = new QOpenGLTexture(QImage(":/textures/dark11.jpg").mirrored());
        break;
    }
    update();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fieldOfView, aspect, zNear, zFar);
}

void OpenGLWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);

    // Use texture unit 0 which contains textures
    program.setUniformValue("texture", 0);

    // Draw object geometry
    geometries->drawObjectGeometry(&program);
}

void OpenGLWidget::resizeObject(qreal length, qreal width, qreal height)
{
    geometries->setObjectGeometry(length, width, height);
    update();
}
