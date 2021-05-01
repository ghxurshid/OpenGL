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
    DrawableObject(QQuaternion rotation = QQuaternion(0.0f, 0.0f, 0.0f, 0.0f),
                   QVector3D position = QVector3D(0, 0, 0),
                   QVector3D scalar = QVector3D(1.0f, 1.0f, 1.0f));
    virtual ~DrawableObject();
    void draw(QOpenGLShaderProgram * shader);

    void setPosition(const QVector3D &position);
    void setScalar(const QVector3D &scalar);
    void setRotation(const QQuaternion &rotation);
    void setTextureImage(QImage image);

protected:
    QVector3D     m_scalar;
    QVector3D   m_position;
    QQuaternion m_rotation;

    QOpenGLTexture *  m_texture;
    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;

    virtual void calculate() = 0;
};

#endif // DRAWABLEOBJECT_H
