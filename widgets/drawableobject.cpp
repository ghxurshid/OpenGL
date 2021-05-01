#include "drawableobject.h"

DrawableObject::DrawableObject(QQuaternion rotation, QVector3D position, QVector3D scalar)
    :  m_scalar(scalar), m_position(position), m_rotation(rotation), m_texture(nullptr), m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{

}

DrawableObject::~DrawableObject()
{

}

void DrawableObject::draw(QOpenGLShaderProgram *shader)
{
    if (!shader) return;

    m_arrayBuffer.bind();
    m_indexBuffer.bind();

    if (!m_texture) return;

    m_texture->bind();
    shader->setUniformValue("qt_Texture0", 0);

    int offset = 0;

    int vertLoc = shader->attributeLocation("qt_Vertex");
    shader->enableAttributeArray(vertLoc);
    shader->setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof (VertexData));

    offset = sizeof (QVector3D);

    int texLoc = shader->attributeLocation("qt_MultiTexCoord0");
    shader->enableAttributeArray(texLoc);
    shader->setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof (VertexData));

    glDrawElements(GL_QUADS, m_indexBuffer.size(), GL_UNSIGNED_INT, nullptr);

    m_arrayBuffer.release();
    m_indexBuffer.release();
    m_texture->release();
}

void DrawableObject::setPosition(const QVector3D &position)
{
    m_position = position;
}

void DrawableObject::setScalar(const QVector3D &scalar)
{
    m_scalar = scalar;
}

void DrawableObject::setRotation(const QQuaternion &rotation)
{
    m_rotation = rotation;
}

void DrawableObject::setTextureImage(QImage image)
{
    if (m_texture)
    {
        m_texture->destroy();
        m_texture->create();
        m_texture->setData(image);
    }
}
