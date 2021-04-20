#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sphera.h"
#include "camera3d.h"
#include "drawableobject.h"

#include <QOpenGLBuffer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class MainWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void timeOut();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();
    void initTextura();
    void initSphera(float radius);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_program;

    int rotation = 0;
    int angleX = 0;
    int angleZ = 0;

    QVector3D pos;
    QPoint lastPos;

    Camera3D camera;
    QList<Sphera*> drawables;
};

#endif // MAINWINDOW_H
