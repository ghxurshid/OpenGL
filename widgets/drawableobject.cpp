#include "drawableobject.h"

DrawableObject::DrawableObject()
    :  m_texture(nullptr), m_indexBuffer(QOpenGLBuffer::IndexBuffer)
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
