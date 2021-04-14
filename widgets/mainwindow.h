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

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();
    void initCube(float width);

private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_program;
    QOpenGLTexture * m_texture;

    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;
};

#endif // MAINWINDOW_H
