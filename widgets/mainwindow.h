#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sphera.h"
#include "camera3d.h"
#include "videosurface.h"
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
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>

class MainWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeTexture();

public slots:
    void timeOut();
    void image

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

    void showEvent(QShowEvent *event);

private: 
    Camera3D camera;
    QVector2D mauseLastPos;
    QList<DrawableObject*> drawables;
    QOpenGLShaderProgram m_program;

    QMediaPlayer   * player;
    VideoSurface   * surface;
    QMediaPlaylist * playlist;
    QVideoWidget   * videoWidget;

    double calcAngle(double start, double end, double h);

};

#endif // MAINWINDOW_H
