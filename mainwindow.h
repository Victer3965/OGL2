#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "TexturedModel.h"
#include "objloader.h"


class MainWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initializeGL();

    void paintGL();

    void resizeGL(int w, int h);

    void keyPressEvent(QKeyEvent *event);

    void keyReleaseEvent(QKeyEvent *event);

private:
    QOpenGLShaderProgram *shader, *simpleShader;
    QMatrix4x4 m_proj;
    float camRotX, camRotY, camRotZ;
    float camPosX, camPosY, camPosZ;
    bool *keyStates;
    QTimer *timer;
    float distanceFromPlayer;
    QList<TexturedModel*> models;

    void updateScene();

    QOpenGLShaderProgram* createShader(QString vshaderName, QString fshaderName);

    void calculateCamPos(float distance);
};

#endif // MAINWINDOW_H
