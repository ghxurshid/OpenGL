#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

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

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void initShaders();
    void initSphera(float radius);

private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_program;
    QOpenGLTexture * m_texture;

    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;

    int rotation = 0;
    int angleX = 0;
    int angleZ = 0;
    QPoint lastPos;

    QVector3D pos;

    QVector3D calcPoint(int longitude, int latidude);
};

#endif // MAINWINDOW_H
