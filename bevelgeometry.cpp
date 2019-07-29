#include "bevelgeometry.h"

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

BevelGeometry::BevelGeometry()
{
    initializeOpenGLFunctions();

    indexBuf = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf->create();

    // Initializes bevel geometry and transfers it to VBOs
    setObjectGeometry(INITIAL_BEVEL_LENGTH/SCALE, INITIAL_BEVEL_WIDTH/SCALE, INITIAL_BEVEL_HEIGHT/SCALE);
}

BevelGeometry::~BevelGeometry()
{
    arrayBuf.destroy();
    indexBuf->destroy();
}

void BevelGeometry::setObjectGeometry(qreal length, qreal width, qreal height)
{
    qreal thick = DEFAULT_WOOD_THICKNESS/SCALE;

    // For cuboid we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(length * -1.0f, width * -1.0f, height + thick * 1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D(length * 1.0f, width * -1.0f,  height + thick * 1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(length * -1.0f, width * 1.0f,  height + thick * 1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D(length * 1.0f, width * 1.0f,  height + thick * 1.0f), QVector2D(0.33f, 0.5f)},  // v3

        // Vertex data for face 1
        {QVector3D(length * 1.0f, width * -1.0f, height + thick * 1.0f), QVector2D( 0.0f, 0.5f)},  // v4
        {QVector3D(length * 1.0f, width * -1.0f, height + thick * -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D(length * 1.0f, width * 1.0f, height + thick * 1.0f), QVector2D(0.0f, 1.0f)},    // v6
        {QVector3D(length * 1.0f, width * 1.0f, height + thick * -1.0f), QVector2D(0.33f, 1.0f)},  // v7

        // Vertex data for face 2
        {QVector3D(length * 1.0f, width * -1.0f, height + thick * -1.0f), QVector2D(0.66f, 0.5f)},  // v8
        {QVector3D(length * -1.0f, width * -1.0f, height + thick * -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D(length * 1.0f, width * 1.0f, height + thick * -1.0f), QVector2D(0.66f, 1.0f)},   // v10
        {QVector3D(length * -1.0f, width * 1.0f, height + thick * -1.0f), QVector2D(1.0f, 1.0f)},   // v11

        // Vertex data for face 3
        {QVector3D(length * -1.0f, width * -1.0f, height + thick * -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(length * -1.0f, width * -1.0f, height + thick * 1.0f), QVector2D(1.0f, 0.0f)},   // v13
        {QVector3D(length * -1.0f, width * 1.0f, height + thick * -1.0f), QVector2D(0.66f, 0.5f)},  // v14
        {QVector3D(length * -1.0f, width * 1.0f, height + thick * 1.0f), QVector2D(1.0f, 0.5f)},    // v15

        // Vertex data for face 4
        {QVector3D(length * -1.0f, width * -1.0f, height + thick * -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D(length * 1.0f, width * -1.0f, height + thick * -1.0f), QVector2D(0.66f, 0.0f)},  // v17
        {QVector3D(length * -1.0f, width * -1.0f, height + thick * 1.0f), QVector2D(0.33f, 0.5f)},  // v18
        {QVector3D(length * 1.0f, width * -1.0f, height + thick * 1.0f), QVector2D(0.66f, 0.5f)},   // v19

        // Vertex data for face 5
        {QVector3D(length * -1.0f, width * 1.0f, height + thick * 1.0f), QVector2D(0.33f, 0.5f)},  // v20
        {QVector3D(length * 1.0f, width * 1.0f, height + thick * 1.0f), QVector2D(0.66f, 0.5f)},   // v21
        {QVector3D(length * -1.0f, width * 1.0f, height + thick * -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D(length * 1.0f, width * 1.0f, height + thick * -1.0f), QVector2D(0.66f, 1.0f)},   // v23


        // Vertex data for face 6
        {QVector3D(length * -1.0f, width * -1.0f - 2*thick, height + thick * 1.0f), QVector2D(0.0f, 0.0f)},  // v24
        {QVector3D(length * 1.0f, width * -1.0f - 2*thick,  height + thick * 1.0f), QVector2D(0.33f, 0.0f)}, // v25
        {QVector3D(length * -1.0f, width * -1.0f,  height + thick * 1.0f), QVector2D(0.0f, 0.5f)},  // v26
        {QVector3D(length * 1.0f, width * -1.0f,  height + thick * 1.0f), QVector2D(0.33f, 0.5f)},  // v27

        // Vertex data for face 7
        {QVector3D(length * 1.0f, width * -1.0f - 2*thick, height + thick * 1.0f), QVector2D( 0.0f, 0.5f)},  // v28
        {QVector3D(length * 1.0f, width * -1.0f - 2*thick, thick * 1.0f - height), QVector2D(0.33f, 0.5f)}, // v29
        {QVector3D(length * 1.0f, width * -1.0f, height + thick * 1.0f), QVector2D(0.0f, 1.0f)},    // v30
        {QVector3D(length * 1.0f, width * -1.0f, thick * 1.0f - height), QVector2D(0.33f, 1.0f)},  // v31

        // Vertex data for face 8
        {QVector3D(length * 1.0f, width * -1.0f - 2*thick, thick * 1.0f - height), QVector2D(0.66f, 0.5f)},  // v32
        {QVector3D(length * -1.0f, width * -1.0f - 2*thick, thick * 1.0f - height), QVector2D(1.0f, 0.5f)},  // v33
        {QVector3D(length * 1.0f, width * -1.0f, thick * 1.0f - height), QVector2D(0.66f, 1.0f)},   // v34
        {QVector3D(length * -1.0f, width * -1.0f, thick * 1.0f - height), QVector2D(1.0f, 1.0f)},   // v35

        // Vertex data for face 9
        {QVector3D(length * -1.0f, width * -1.0f - 2*thick, thick * 1.0f - height), QVector2D(0.66f, 0.0f)}, // v36
        {QVector3D(length * -1.0f, width * -1.0f - 2*thick, height + thick * 1.0f), QVector2D(1.0f, 0.0f)},   // v37
        {QVector3D(length * -1.0f, width * -1.0f, thick * 1.0f - height), QVector2D(0.66f, 0.5f)},  // v38
        {QVector3D(length * -1.0f, width * -1.0f, height + thick * 1.0f), QVector2D(1.0f, 0.5f)},    // v39

        // Vertex data for face 10
        {QVector3D(length * -1.0f, width * -1.0f - 2*thick, thick * 1.0f - height), QVector2D(0.33f, 0.0f)}, // v40
        {QVector3D(length * 1.0f, width * -1.0f - 2*thick, thick * 1.0f - height), QVector2D(0.66f, 0.0f)},  // v41
        {QVector3D(length * -1.0f, width * -1.0f - 2*thick, height + thick * 1.0f), QVector2D(0.33f, 0.5f)},  // v42
        {QVector3D(length * 1.0f, width * -1.0f - 2*thick, height + thick * 1.0f), QVector2D(0.66f, 0.5f)},   // v43

        // Vertex data for face 11
        {QVector3D(length * -1.0f, width * -1.0f, height + thick * 1.0f), QVector2D(0.33f, 0.5f)},  // v44
        {QVector3D(length * 1.0f, width * -1.0f, height + thick * 1.0f), QVector2D(0.66f, 0.5f)},   // v45
        {QVector3D(length * -1.0f, width * -1.0f, thick * 1.0f - height), QVector2D(0.33f, 1.0f)}, // v46
        {QVector3D(length * 1.0f, width * -1.0f, thick * 1.0f - height), QVector2D(0.66f, 1.0f)}   // v47
    };

    // Indices for drawing cuboid faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3, 3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23, 23, // Face 5 - triangle strip (v20, v21, v22, v23)

        24, 24, 25, 26, 27, 27, // Face 6 - triangle strip ( v24,  v25,  v26,  v27)
        28, 28, 29, 30, 31, 31, // Face 7 - triangle strip ( v28,  v29,  v30,  v31)
        32, 32, 33, 34, 35, 35, // Face 8 - triangle strip ( v32,  v33, v34, v35)
        36, 36, 37, 38, 39, 39, // Face 9 - triangle strip (v36, v37, v38, v39)
        40, 40, 41, 42, 43, 43, // Face 10 - triangle strip (v40, v41, v42, v43)
        44, 44, 45, 46, 47      // Face 11 - triangle strip (v44, v45, v46, v47)
    };

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 48 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf->bind();
    indexBuf->allocate(indices, 70 * sizeof(GLushort));
}

void BevelGeometry::drawObjectGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf->bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cuboid geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 70, GL_UNSIGNED_SHORT, 0);
}
