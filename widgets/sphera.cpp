#include <math.h>

#include "sphera.h"

using namespace std;

static double g2rad(int angle)
{
    return (angle / 180.0) * M_PI;
}

static QVector3D calcPoint(int longitude, int latidude)
{
    double latCoeff = cos(g2rad(latidude));
    double y = sin(g2rad(latidude));
    double x = latCoeff * cos(g2rad(longitude));
    double z = latCoeff * sin(g2rad(longitude));

    return QVector3D(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

Sphera::Sphera(double radius, int arc, int highLat, int lowLat,
               QQuaternion rotation, QVector3D position, QVector3D scalar) :
               DrawableObject (rotation, position, scalar)
{
    m_radius = fabs(radius);       
    m_arc = arc % 360 == 0 ? 360 : arc % 360;
    m_highLatitude = max(min(90, highLat), -90);
    m_lowLatitude  = max(min(90, lowLat ), -90);
    if (m_highLatitude < m_lowLatitude) {
        m_highLatitude += m_lowLatitude;
        m_lowLatitude = m_highLatitude - m_lowLatitude;
        m_highLatitude = m_highLatitude - m_lowLatitude;
    } else if (m_lowLatitude == m_highLatitude) {
        m_highLatitude = min(m_highLatitude + 1, 90);
        m_lowLatitude  = max(m_lowLatitude - 1, -90);
    }

    m_texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);

    setTextureImage(QImage(":/fisheye.png").mirrored());
    calculate();
}

Sphera::~Sphera()
{

}

void Sphera::calculate()
{
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    int lonStep = 1;
    int latStep = 1;
    int arc_div_2 = m_arc / 2;

    for (int lat = m_lowLatitude; lat < m_highLatitude; lat += latStep) {
        for (int lon = 90 - arc_div_2; lon < 90 + arc_div_2; lon += lonStep) {
             vertexes.append(calcVertex(lon, lat));
             vertexes.append(calcVertex(lon + lonStep, lat));
             vertexes.append(calcVertex(lon + lonStep, lat + latStep));
             vertexes.append(calcVertex(lon, lat + latStep));
        }
    }

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
}

VertexData Sphera::calcVertex(int longitude, int latidude)
{
    auto verCoord = calcPoint(longitude, latidude);
    auto texCoord = QVector2D((verCoord.x() + 1) / 2.0f, (verCoord.y() + 1) / 2.0f);
    auto vertData = VertexData(m_rotation.rotatedVector(verCoord * static_cast<float>(m_radius) * m_scalar) + m_position, texCoord);
    return vertData;
}
