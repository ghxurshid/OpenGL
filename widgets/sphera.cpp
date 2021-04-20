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
    double z = sin(g2rad(latidude));
    double x = latCoeff * cos(g2rad(longitude));
    double y = latCoeff * sin(g2rad(longitude));

    return QVector3D(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

Sphera::Sphera(double radius, QVector3D position)
{
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    int lonStep = 1;
    int latStep = 1;

    for (int lat = -90; lat < -20; lat += latStep) {
        for (int lon = 0; lon < 360; lon += lonStep) {
            double rr = radius;
            auto verCoord1 = calcPoint(lon, lat);
            auto texCoord1 = QVector2D((verCoord1.x() + 1) / 2.0f, (verCoord1.y() + 1) / 2.0f);
            auto vertData1 = VertexData(verCoord1 * rr + position, texCoord1);
            vertexes.append(vertData1);

            auto verCoord2 = calcPoint(lon + lonStep, lat);
            auto texCoord2 = QVector2D((verCoord2.x() + 1) / 2.0f, (verCoord2.y() + 1) / 2.0f);
            auto vertData2 = VertexData(verCoord2 * rr + position, texCoord2);
            vertexes.append(vertData2);


            auto verCoord3 = calcPoint(lon + lonStep, lat + latStep);
            auto texCoord3 = QVector2D((verCoord3.x() + 1) / 2.0f, (verCoord3.y() + 1) / 2.0f);
            auto vertData3 = VertexData(verCoord3 * rr + position, texCoord3);
            vertexes.append(vertData3);

            auto verCoord4 = calcPoint(lon, lat + latStep);
            auto texCoord4 = QVector2D((verCoord4.x() + 1) / 2.0f, (verCoord4.y() + 1) / 2.0f);
            auto vertData4 = VertexData(verCoord4 * rr + position, texCoord4);
            vertexes.append(vertData4);
        }
    }

    for (int i = 0; i < vertexes.size(); i ++) {
        indexes.push_back(static_cast<uint>(i));
    }

    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.allocate(vertexes.constData(), static_cast<int>(vertexes.size()) * static_cast<int>(sizeof (VertexData)));
    m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(), static_cast<int>(indexes.size()) * static_cast<int>(sizeof (GLuint)));
    m_indexBuffer.release();

    m_texture = new QOpenGLTexture(QImage(":/fisheye.png").mirrored());
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
}
