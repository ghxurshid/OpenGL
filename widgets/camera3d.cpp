#include "camera3d.h"

#include <QDebug>

const QVector3D Camera3D::LocalForward(0.0f, 0.0f, -1.0f);
const QVector3D Camera3D::LocalUp(0.0f, 1.0f, 0.0f);
const QVector3D Camera3D::LocalRight(1.0f, 0.0f, 0.0f);

// Transform By (Add/Scale)
void Camera3D::translate(const QVector3D &dt)
{
  if (!dt.isNull())
  {
    m_dirty = true;
    m_translation += dt;
  }
}

void Camera3D::rotate(const QQuaternion &dr)
{
  if (!dr.isIdentity())
  {
    m_dirty = true;
    m_rotation = dr * m_rotation;
  }
}

// Transform To (Setters)
void Camera3D::setTranslation(const QVector3D &t)
{
  if (t != m_translation)
  {
    m_dirty = true;
    m_translation = t;
  }
}

void Camera3D::setRotation(const QQuaternion &r)
{
  if (r != m_rotation)
  {
    m_dirty = true;
    m_rotation = r;
  }
}

void Camera3D::setProjection(const QMatrix4x4 &proj) const
{
  if (proj != m_projection)
  {
    m_dirty = true;
    m_projection = proj;
  }
}

// Accessors
const QMatrix4x4 Camera3D::toMatrix()
{
  clean();
  return  m_projection * m_world;
}

bool Camera3D::dirty() const
{
  return m_dirty;
}

// Queries
QVector3D Camera3D::forward() const
{
  return m_rotation.rotatedVector(LocalForward);
}

QVector3D Camera3D::up() const
{
  return m_rotation.rotatedVector(LocalUp);
}

QVector3D Camera3D::right() const
{
  return m_rotation.rotatedVector(LocalRight);
}

void Camera3D::setFov(float value)
{
    m_dirty = true;
    fov = value;
}

void Camera3D::setAspect(float value)
{
    m_dirty = true;
    aspect = value;
}

void Camera3D::setNearPlane(float value)
{
    m_dirty = true;
    nearPlane = value;
}

void Camera3D::setFarPlane(float value)
{
    m_dirty = true;
    farPlane = value;
}

void Camera3D::clean() const
{
    if (m_dirty)
    {
        m_dirty = false;
        m_world.setToIdentity();
        m_world.rotate(m_rotation.conjugated());
        m_world.translate(-m_translation);

        m_projection.setToIdentity();
        m_projection.perspective(fov, aspect, nearPlane, farPlane);
    }
}

// Qt Streams
QDebug operator<<(QDebug dbg, const Camera3D &transform)
{
  dbg << "Camera3D\n{\n";
  dbg << "Position: <" << transform.translation().x() << ", " << transform.translation().y() << ", " << transform.translation().z() << ">\n";
  dbg << "Rotation: <" << transform.rotation().x() << ", " << transform.rotation().y() << ", " << transform.rotation().z() << " | " << transform.rotation().scalar() << ">\n}";
  return dbg;
}

QDataStream &operator<<(QDataStream &out, const Camera3D &transform)
{
  out << transform.m_translation;
  out << transform.m_rotation;
  return out;
}

QDataStream &operator>>(QDataStream &in, Camera3D &transform)
{
  in >> transform.m_translation;
  in >> transform.m_rotation;
  transform.m_dirty = true;
  return in;
}

