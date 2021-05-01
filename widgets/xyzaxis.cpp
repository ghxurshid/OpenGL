#include "xyzaxis.h"

XYZAxis::XYZAxis(float length)
{
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    float depth = 0.15f;

                                    /*Coordinates for X axis (view from Z)*/
    //top
    vertexes.append(VertexData(QVector3D(-length/5.0f,  depth,  depth), QVector2D(0.0f , 0.0f)));
    vertexes.append(VertexData(QVector3D( length     ,  depth,  depth), QVector2D(0.33f, 0.0f)));
    vertexes.append(VertexData(QVector3D( length     ,  depth, -depth), QVector2D(0.33f, 1.0f)));
    vertexes.append(VertexData(QVector3D(-length/5.0f,  depth, -depth), QVector2D(0.0f , 1.0f)));

    //front
    vertexes.append(VertexData(QVector3D(-length/5.0f,  depth,  depth), QVector2D(0.0f , 0.0f)));
    vertexes.append(VertexData(QVector3D( length     ,  depth,  depth), QVector2D(0.33f, 0.0f)));
    vertexes.append(VertexData(QVector3D( length     , -depth,  depth), QVector2D(0.33f, 1.0f)));
    vertexes.append(VertexData(QVector3D(-length/5.0f, -depth,  depth), QVector2D(0.0f , 1.0f)));

    //bottom
    vertexes.append(VertexData(QVector3D(-length/5.0f, -depth,  depth), QVector2D(0.0f , 0.0f)));
    vertexes.append(VertexData(QVector3D( length     , -depth,  depth), QVector2D(0.33f, 0.0f)));
    vertexes.append(VertexData(QVector3D( length     , -depth, -depth), QVector2D(0.33f, 1.0f)));
    vertexes.append(VertexData(QVector3D(-length/5.0f, -depth, -depth), QVector2D(0.0f , 1.0f)));

    //back
    vertexes.append(VertexData(QVector3D(-length/5.0f,  depth, -depth), QVector2D(0.0f , 0.0f)));
    vertexes.append(VertexData(QVector3D( length     ,  depth, -depth), QVector2D(0.33f, 0.0f)));
    vertexes.append(VertexData(QVector3D( length     , -depth, -depth), QVector2D(0.33f, 1.0f)));
    vertexes.append(VertexData(QVector3D(-length/5.0f, -depth, -depth), QVector2D(0.0f , 1.0f)));

                                /*Coordinates for Y axis (view from X)*/
    //top
    vertexes.append(VertexData(QVector3D( depth, -length/5.0f,  depth), QVector2D(0.34f, 0.0f)));
    vertexes.append(VertexData(QVector3D( depth,  length     ,  depth), QVector2D(0.66f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-depth,  length     ,  depth), QVector2D(0.66f, 1.0f)));
    vertexes.append(VertexData(QVector3D(-depth, -length/5.0f,  depth), QVector2D(0.34f, 1.0f)));

    //front
    vertexes.append(VertexData(QVector3D( depth, -length/5.0f,  depth), QVector2D(0.34f, 0.0f)));
    vertexes.append(VertexData(QVector3D( depth,  length     ,  depth), QVector2D(0.66f, 0.0f)));
    vertexes.append(VertexData(QVector3D( depth,  length     , -depth), QVector2D(0.66f, 1.0f)));
    vertexes.append(VertexData(QVector3D( depth, -length/5.0f, -depth), QVector2D(0.34f, 1.0f)));

    //bottom
    vertexes.append(VertexData(QVector3D( depth, -length/5.0f, -depth), QVector2D(0.34f, 0.0f)));
    vertexes.append(VertexData(QVector3D( depth,  length     , -depth), QVector2D(0.66f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-depth,  length     , -depth), QVector2D(0.66f, 1.0f)));
    vertexes.append(VertexData(QVector3D(-depth, -length/5.0f, -depth), QVector2D(0.34f, 1.0f)));

    //back
    vertexes.append(VertexData(QVector3D(-depth, -length/5.0f,  depth), QVector2D(0.34f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-depth,  length     ,  depth), QVector2D(0.66f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-depth,  length     , -depth), QVector2D(0.66f, 1.0f)));
    vertexes.append(VertexData(QVector3D(-depth, -length/5.0f, -depth), QVector2D(0.34f, 1.0f)));

                                /*Coordinates for X axis (view from Z)*/
    //front
    vertexes.append(VertexData(QVector3D( depth,  depth, -length/5.0f), QVector2D(0.67f, 0.0f)));
    vertexes.append(VertexData(QVector3D( depth,  depth,  length     ), QVector2D(1.0f , 0.0f)));
    vertexes.append(VertexData(QVector3D(-depth,  depth,  length     ), QVector2D(1.0f , 1.0f)));
    vertexes.append(VertexData(QVector3D(-depth,  depth, -length/5.0f), QVector2D(0.67f, 1.0f)));

    //back
    vertexes.append(VertexData(QVector3D( depth, -depth, -length/5.0f), QVector2D(0.67f, 0.0f)));
    vertexes.append(VertexData(QVector3D( depth, -depth,  length     ), QVector2D(1.0f , 0.0f)));
    vertexes.append(VertexData(QVector3D(-depth, -depth,  length     ), QVector2D(1.0f , 1.0f)));
    vertexes.append(VertexData(QVector3D(-depth, -depth, -length/5.0f), QVector2D(0.67f, 1.0f)));

    //bottom
    vertexes.append(VertexData(QVector3D(-depth,  depth, -length/5.0f), QVector2D(0.67f, 0.0f)));
    vertexes.append(VertexData(QVector3D(-depth,  depth,  length     ), QVector2D(1.0f , 0.0f)));
    vertexes.append(VertexData(QVector3D(-depth, -depth,  length     ), QVector2D(1.0f , 1.0f)));
    vertexes.append(VertexData(QVector3D(-depth, -depth, -length/5.0f), QVector2D(0.67f, 1.0f)));

    //top
    vertexes.append(VertexData(QVector3D( depth,  depth, -length/5.0f), QVector2D(0.67f, 0.0f)));
    vertexes.append(VertexData(QVector3D( depth,  depth,  length     ), QVector2D(1.0f , 0.0f)));
    vertexes.append(VertexData(QVector3D( depth, -depth,  length     ), QVector2D(1.0f , 1.0f)));
    vertexes.append(VertexData(QVector3D( depth, -depth, -length/5.0f), QVector2D(0.67f, 1.0f)));


    for (int i = 0; i < vertexes.size(); i ++) {
        indexes.push_back(static_cast<uint>(i));
    }

    if (m_arrayBuffer.isCreated()) m_arrayBuffer.destroy();
    if (m_indexBuffer.isCreated()) m_indexBuffer.destroy();

    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.allocate(vertexes.constData(), static_cast<int>(vertexes.size()) * static_cast<int>(sizeof (VertexData)));
    m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(), static_cast<int>(indexes.size()) * static_cast<int>(sizeof (GLuint)));
    m_indexBuffer.release();

    m_texture = new QOpenGLTexture(QImage(":/axis.png"));
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

void XYZAxis::calculate()
{

}
