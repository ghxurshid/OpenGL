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
    auto val = calcAngle(-10, 10,10);
    qDebug() << val;
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
    camera.translate(0, 0, 80.0);

    int width = 150;
    for (int x = 0; x < 3; x ++) {
        for (int y = 0; y < 3; y ++) {
            for (int z = 0; z < 3; z ++) {
                drawables.append(new Sphera(0.4f * width, QVector3D(x * width, y * width, z * width)));
            }
        }
    }
}

void MainWindow::resizeGL(int w, int h)
{
    float aspect = w / (h ? static_cast<float>(h) : 1);
    camera.setAspect(aspect);    
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
    mauseLastPos = QVector2D(event->pos());
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QOpenGLWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QOpenGLWidget::mouseMoveEvent(event);

    QVector2D pos(event->pos());
    QVector2D center(size().width(), size().height());

    QVector2D tStart(mauseLastPos - center);
    QVector2D tEnd(pos - center);

    float angle_z = calcAngle(tStart.x(), tEnd.x(), camera.getNearPlane());
    float angle_x = calcAngle(tStart.y(), tEnd.y(), camera.getNearPlane());
    qDebug() << "angle_x = " << angle_x << " angle_z = " << angle_z;
    angle_z = (pos.x() - mauseLastPos.x()) / 10.0f;
    angle_x = (pos.y() - mauseLastPos.y()) / 10.0f;

    camera.rotate(angle_z, 0.0, 0.0, 1.0);
    camera.rotate(angle_x, camera.right());

    mauseLastPos = pos;

    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W) {
        camera.translate( camera.forward());
    } else if (event->key() == Qt::Key_S) {
        camera.translate(-camera.forward());
    } else if (event->key() == Qt::Key_A) {
        camera.translate(-camera.right());
    } else if (event->key() == Qt::Key_D) {
        camera.translate( camera.right());
    } else if (event->key() == Qt::Key_Q) {
        camera.translate(QVector3D(0.0, 0.0, -1.0));
    } else if (event->key() == Qt::Key_E) {
        camera.translate(QVector3D(0.0, 0.0,  1.0));
    } else if (event->key() == Qt::Key_Plus) {
        camera.setFov(camera.getFov() + 1.0f);
        qDebug() << camera;
    } else if (event->key() == Qt::Key_Minus) {
        camera.setFov(camera.getFov() - 1.0f);
        qDebug() << camera;
    }
    update();
}

double MainWindow::calcAngle(double start, double end, double h)
{
    double a = end - start;
    double b = sqrt(start * start + h * h);
    double c = sqrt(end * end + h * h);

    double t = (b*b + c*c - a*a) / (2*c*b);
    double alfa = acos(t);
    return alfa;
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
