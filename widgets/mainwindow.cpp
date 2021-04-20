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

    int width = 10;
    for (int x = 0; x < 3; x ++) {
        for (int y = 0; y < 3; y ++) {
            for (int z = 0; z < 3; z ++) {
                drawables.append(new Sphera(0.8f * width, QVector3D(x * width, y * width, z * width)));
            }
        }
    }
}

void MainWindow::resizeGL(int w, int h)
{
    float aspect = w / (h ? static_cast<float>(h) : 1);

    QMatrix4x4 projMat;
    projMat.setToIdentity();
    projMat.perspective(90, aspect, 0.1f, 1500.0f);

    camera.setProjection(projMat);
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program.setUniformValue("qt_ModelViewProjectionMatrix", camera.toMatrix());

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
    float angle_x = -(pos.y() - lastPos.y()) / 2.0f;
    float angle_z = -(pos.x() - lastPos.x()) / 2.0f;

    camera.rotate(angle_x, 1.0, 0.0, 0.0);
    camera.rotate(angle_z, 0.0, 0.0, 1.0);

    lastPos = pos;
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    double speed = 5.0;

    if (event->key() == Qt::Key_W) {
        camera.translate( camera.forward());
    } else if (event->key() == Qt::Key_S) {
        camera.translate(-camera.forward());
    } else if (event->key() == Qt::Key_A) {
        camera.translate(-camera.right());
    } else if (event->key() == Qt::Key_D) {
        camera.translate( camera.right());
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
