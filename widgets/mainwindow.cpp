#include "mainwindow.h"

#include <math.h>

#include <QTimer>
#include <QInputEvent>

using namespace std;

struct VertexData
{
    VertexData() {}
    VertexData(QVector3D p, QVector2D t, QVector3D n) :
        position(p), texCoord(t), normal(n)
    {
    }
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;   
};

MainWindow::MainWindow(QWidget *parent)
    : QOpenGLWidget (parent), m_texture(nullptr), m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{

}

MainWindow::~MainWindow()
{

}

void MainWindow::timeOut()
{

}

void MainWindow::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    initShaders();
    initSphera(4.0f);
}

void MainWindow::resizeGL(int w, int h)
{
    float aspect = w / (h ? static_cast<float>(h) : 1);

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(55, aspect, 0.1f, 10.0f);

}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(0.0, 0.0, -4.5);
    modelViewMatrix.rotate(angleX, 1.0, 0.0, 0.0);
    modelViewMatrix.rotate(angleY, 0.0, 1.0, 0.0);

    m_texture->bind(0);

    m_program.bind();
    m_program.setUniformValue("qt_ModelViewProjectionMatrix", m_projectionMatrix * modelViewMatrix);
    m_program.setUniformValue("qt_Texture0", 0);

    m_arrayBuffer.bind();

    int offset = 0;

    int vertLoc = m_program.attributeLocation("qt_Vertex");
    m_program.enableAttributeArray(vertLoc);
    m_program.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof (VertexData));

    offset = sizeof (QVector3D);

    int texLoc = m_program.attributeLocation("qt_MultiTexCoord0");
    m_program.enableAttributeArray(texLoc);
    m_program.setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof (VertexData));

    m_indexBuffer.bind();

    glDrawElements(GL_QUADS, m_indexBuffer.size(), GL_UNSIGNED_INT, nullptr);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QOpenGLWidget::mousePressEvent(event);
    lastPos = event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QOpenGLWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QOpenGLWidget::mouseMoveEvent(event);
    auto pos = event->pos();
    angleX += (pos.y() - lastPos.y()) / 2.0f;
    angleY += (pos.x() - lastPos.x()) / 2.0f;
    lastPos = pos;
    update();
}

void MainWindow::initShaders()
{
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))
        close();

    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh"))
        close();

    if (!m_program.link())
        close();
}

void MainWindow::initSphera(float width)
{
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    int lonStep = 1;
    int latStep = 1;

    for (int lat = -90; lat < 0; lat += latStep) {
        for (int lon = 0; lon < 360; lon += lonStep) {
            auto verCoord1 = calcPoint(lon, lat);
            auto texCoord1 = QVector2D((verCoord1.x() + 1) / 2.0f, (verCoord1.y() + 1) / 2.0f);
            auto vertData1 = VertexData(verCoord1 * width, texCoord1, QVector3D(0.0, 0.0, 1.0));
            vertexes.append(vertData1);            

            auto verCoord2 = calcPoint(lon + lonStep, lat);
            auto texCoord2 = QVector2D((verCoord2.x() + 1) / 2.0f, (verCoord2.y() + 1) / 2.0f);
            auto vertData2 = VertexData(verCoord2 * width, texCoord2, QVector3D(0.0, 0.0, 1.0));
            vertexes.append(vertData2);


            auto verCoord3 = calcPoint(lon + lonStep, lat + latStep);
            auto texCoord3 = QVector2D((verCoord3.x() + 1) / 2.0f, (verCoord3.y() + 1) / 2.0f);
            auto vertData3 = VertexData(verCoord3 * width, texCoord3, QVector3D(0.0, 0.0, 1.0));
            vertexes.append(vertData3);            

            auto verCoord4 = calcPoint(lon, lat + latStep);
            auto texCoord4 = QVector2D((verCoord4.x() + 1) / 2.0f, (verCoord4.y() + 1) / 2.0f);
            auto vertData4 = VertexData(verCoord4 * width, texCoord4, QVector3D(0.0, 0.0, 1.0));
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

static double g2rad(int angle)
{
    return (angle / 180.0) * M_PI;
}
QVector3D MainWindow::calcPoint(int longitude, int latidude)
{
    double latCoeff = cos(g2rad(latidude));
    double z = sin(g2rad(latidude));
    double x = latCoeff * cos(g2rad(longitude));
    double y = latCoeff * sin(g2rad(longitude));

    return QVector3D(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}
