#include "sphera.h"
#include "mainwindow.h"

#include <math.h>

#include <QTimer>
#include <QInputEvent>
#include <QOpenGLFunctions>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QOpenGLWidget (parent)
{

}

MainWindow::~MainWindow()
{
    makeCurrent();
    doneCurrent();
}

void MainWindow::timeOut()
{

}

void MainWindow::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    initShaders();
    glEnable(GL_DEPTH_TEST);

    int width = 30;
    for (int x = -width; x <= width; x += 10) {
        for (int y = -width; y <= width; y += 10) {
            for (int z = -width; z <= width; z += 10) {
                drawables.append(new Sphera(5.0, QVector3D(x, y, z)));
            }
        }
    }
}

void MainWindow::resizeGL(int w, int h)
{
    float aspect = w / (h ? static_cast<float>(h) : 1);

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(90, aspect, 5.0f, 1500.0f);
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 modelViewMatrix;

    modelViewMatrix.rotate(angleX, 1.0, 0.0, 0.0);
    modelViewMatrix.rotate(angleZ, 0.0, 0.0, 1.0);
    modelViewMatrix.translate(pos);

    m_program.setUniformValue("qt_ModelViewProjectionMatrix", m_projectionMatrix * modelViewMatrix);

    for (auto drawable : drawables) {
        drawable->draw(&m_program);
    }
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
    angleX -= (pos.y() - lastPos.y()) / 2.0f;
    angleZ -= (pos.x() - lastPos.x()) / 2.0f;
    lastPos = pos;
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    double speed = 5.0;

    QVector3D dPos(speed * std::cos(angleZ * M_PI / 180) * std::sin(angleX * M_PI / 180),
                   speed * std::sin(angleZ * M_PI / 180) * std::sin(angleX * M_PI / 180),
                   speed * std::cos(angleX * M_PI / 180));

    if (event->key() == Qt::Key_W) {
        pos -= QVector3D(0, 5, 0);
    } else if (event->key() == Qt::Key_S) {
        pos += QVector3D(0, 5, 0);
    } else if (event->key() == Qt::Key_A) {
        pos += QVector3D(5, 0, 0);
    } else if (event->key() == Qt::Key_D) {
        pos -= QVector3D(5, 0, 0);
    } else if (event->key() == Qt::Key_Q) {
        pos -= QVector3D(0, 0, 5);
    } else if (event->key() == Qt::Key_E) {
        pos += QVector3D(0, 0, 5);
    }
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

    if (!m_program.bind())
        close();
}
