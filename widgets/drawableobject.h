#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <QVector3D>
#include <QVector2D>
#include <QQuaternion>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

struct VertexData
{
    VertexData() {}
    VertexData(QVector3D p, QVector2D t) :
        position(p), texCoord(t)
    {
    }
    QVector3D position;
    QVector2D texCoord;
};

class DrawableObject
{
public:
    DrawableObject();
    void draw(QOpenGLShaderProgram * shader);

    void setPosition(const QVector3D &position);

protected:
    QVector3D     m_position;
    QQuaternion   m_rotation;

    QOpenGLTexture *  m_texture;
    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;
};

#endif // DRAWABLEOBJECT_H
