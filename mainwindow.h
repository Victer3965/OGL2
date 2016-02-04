#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "TexturedModel.h"
#include "objloader.h"
#include "ChunkManager.h"
#include "PhisicsTanks.h"


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
    float camRotX, camRotY, camRotZ;

    float camPosX, camPosY, camPosZ;

    float distanceFromPlayer;

    float radiusNearby;

    bool *keyStates;

    QTimer *timer;

    QMatrix4x4 m_proj;

    ChunkManager ChunkManager;

    PhisicsTanks* player;

    QList<TexturedModel*> models, chanksNerby;

    QOpenGLShaderProgram *shader, *simpleShader;

    void updateScene();

    QOpenGLShaderProgram* createShader(QString vshaderName, QString fshaderName);

    void calculateCamPos(float distance);

    void startTimer();
};

#endif // MAINWINDOW_H
