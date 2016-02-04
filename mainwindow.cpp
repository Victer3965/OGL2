#include <QFile>
#include <QTimer>
#include <QCursor>
#include <math.h>

#include "MainWindow.h"
#include "shader.h"

#define KEY_FORWARD 0
#define KEY_BACKWARD 1
#define KEY_LEFT 2
#define KEY_RIGHT 3
#define KEY_CAM_FORWARD 4
#define KEY_CAM_BACKWARD 5
#define KEY_CAM_LEFT 6
#define KEY_CAM_RIGHT 7
#define KEY_CAM_TURN_LEFT 8
#define KEY_CAM_TURN_RIGHT 9
#define KEY_CAM_TURN_UP 10
#define KEY_CAM_TURN_DOWN 11
#define KEY_CAM_CLOSER 12
#define KEY_CAM_FARTHER 13


MainWindow::MainWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{
    shader=0;
    distanceFromPlayer = 20;
    keyStates = new bool [14];
    memset(keyStates, 0, sizeof(bool)*14);
    startTimer();
    radiusNearby=100.0;
}


MainWindow::~MainWindow()
{
    makeCurrent();
    delete shader;
    doneCurrent();
}

void MainWindow::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500.0, 500.0, 500.0, 500.0, -500.0, 500.0);
    glViewport( 0, 0, w, h);
    m_proj.setToIdentity();
    m_proj.perspective(90.0f, GLfloat(w) / h, 0.01f, radiusNearby);
}



void MainWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1, 0.1, 0.1, 1.0);

    RawModel *modeltank = OBJLoader::Load("t-54_wot/T-54");

    TexturedModel* tank = new TexturedModel(modeltank, ":/res/t-54_wot/T-54.dds");

    player = new PhisicsTanks(tank);
    models.append(tank);
    models.append(new TexturedModel(modeltank, ":/res/t-54_wot/T-54_crash.dds"));
    models.append(new TexturedModel(OBJLoader::Load("box/box"), ":/res/box/grass.dds"));

    tank->RotateModel(0, 0, 180);
    tank->MoveModel(0, 0, 0.55);
    camRotX = -45;
    camRotY = 0;
    camRotZ = 0;
    calculateCamPos(distanceFromPlayer);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    shader = Shader::createShader("vertexshader", "fragmentshader", this);
    simpleShader = Shader::createShader("vertexshader", "solidcolor", this);

}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 ViewMatrix;

    ViewMatrix.rotate(-camRotX-90 , 1.0f, 0.0f, 0.0f);
    ViewMatrix.rotate(camRotY , 0.0f, 1.0f, 0.0f);
    ViewMatrix.rotate(camRotZ , 0.0f, 0.0f, 1.0f);
    ViewMatrix.translate(-camPosX, -camPosY, -camPosZ);

    shader->bind();
    shader->setUniformValue("projMatrix", m_proj);
    shader->setUniformValue("ViewMatrix", ViewMatrix);

    chanksNerby = ChunkManager.getChunksNearby(models[0]->GetPos().x(),
                                               models[0]->GetPos().y(),
                                               radiusNearby);

    for (int i=0; i < chanksNerby.size(); i++)
    {
        chanksNerby[i]->PaintModel(shader);
    }

    for (int i=0; i < models.size()-1; i++){
        models[i]->PaintModel(shader);
    }

//    models.last()->PaintModel(shader);
    shader->release();

    simpleShader->bind();
    simpleShader->setUniformValue("projMatrix", m_proj);
    simpleShader->setUniformValue("ViewMatrix", ViewMatrix);

    QMatrix4x4 identityMatrix;
    identityMatrix.setToIdentity();
    simpleShader->setUniformValue("modelMatrix",identityMatrix);
    glLineWidth(2.5);
    glColor3f(1.0, 0.5, 0.5);
    glBegin(GL_LINES);
    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(15, 0, 0);
    glEnd();

    glColor3f(0.5, 1.0, 0.5);
    glBegin(GL_LINES);
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(0, 15, 0);
    glEnd();

    glColor3f(0.5, 0.5, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -1.0);
    glVertex3f(0, 0, 15);
    glEnd();
    simpleShader->release();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_W : keyStates[KEY_FORWARD] = 1;    break;
        case Qt::Key_S : keyStates[KEY_BACKWARD] = 1;   break;
        case Qt::Key_A : keyStates[KEY_LEFT] = 1;       break;
        case Qt::Key_D : keyStates[KEY_RIGHT] = 1;      break;
    }
    switch (event->nativeScanCode())
    {
        case 72: keyStates[KEY_CAM_FORWARD] = 1;        break;
        case 76: keyStates[KEY_CAM_BACKWARD] = 1;       break;
        case 75: keyStates[KEY_CAM_LEFT] = 1;           break;
        case 77: keyStates[KEY_CAM_RIGHT] = 1;          break;
        case 71: keyStates[KEY_CAM_TURN_LEFT] = 1;      break;
        case 73: keyStates[KEY_CAM_TURN_RIGHT] = 1;     break;
        case 74: keyStates[KEY_CAM_FARTHER] = 1;        break;
        case 78: keyStates[KEY_CAM_CLOSER] = 1;         break;
        case 329: keyStates[KEY_CAM_TURN_UP] = 1;       break;
        case 337: keyStates[KEY_CAM_TURN_DOWN] = 1;     break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_W : keyStates[KEY_FORWARD] = 0;    break;
        case Qt::Key_S : keyStates[KEY_BACKWARD] = 0;   break;
        case Qt::Key_A : keyStates[KEY_LEFT] = 0;       break;
        case Qt::Key_D : keyStates[KEY_RIGHT] = 0;      break;

    }
    switch (event->nativeScanCode())
    {
        case 72: keyStates[KEY_CAM_FORWARD] = 0;        break;
        case 76: keyStates[KEY_CAM_BACKWARD] = 0;       break;
        case 75: keyStates[KEY_CAM_LEFT] = 0;           break;
        case 77: keyStates[KEY_CAM_RIGHT] = 0;          break;
        case 71: keyStates[KEY_CAM_TURN_LEFT] = 0;      break;
        case 73: keyStates[KEY_CAM_TURN_RIGHT] = 0;     break;
        case 74: keyStates[KEY_CAM_FARTHER] = 0;        break;
        case 78: keyStates[KEY_CAM_CLOSER] = 0;         break;
        case 329: keyStates[KEY_CAM_TURN_UP] = 0;       break;
        case 337: keyStates[KEY_CAM_TURN_DOWN] = 0;     break;

    }
}


void MainWindow::updateScene()
{

    if (keyStates[KEY_FORWARD])
    {
        player->setAcceleration(0.1);
    }
    if (keyStates[KEY_BACKWARD])
    {
        player->setAcceleration(-0.1);
    }

    if (!keyStates[KEY_FORWARD] && !keyStates[KEY_BACKWARD])
    {
        player->setAcceleration(0);
    }

    if (keyStates[KEY_LEFT])
    {
        models[0]->RotateModel(0, 0, 1);
        camRotZ-=1;
    }
    if (keyStates[KEY_RIGHT])
    {
        models[0]->RotateModel(0, 0, -1);
        camRotZ+=1;
    }
    if (keyStates[KEY_CAM_FORWARD])
    {
        camPosX+=0.2*sin(camRotZ/180*M_PI);
        camPosY+=0.2*cos(camRotZ/180*M_PI);
    }
    if (keyStates[KEY_CAM_BACKWARD])
    {
        camPosX+=-0.2*sin(camRotZ/180*M_PI);
        camPosY+=-0.2*cos(camRotZ/180*M_PI);
    }
    if (keyStates[KEY_CAM_LEFT])
    {
        camPosX+=-0.2*cos(camRotZ/180*M_PI);
        camPosY+=0.2*sin(camRotZ/180*M_PI);
    }
    if (keyStates[KEY_CAM_RIGHT])
    {
        camPosX+=0.2*cos(camRotZ/180*M_PI);
        camPosY+=-0.2*sin(camRotZ/180*M_PI);
    }
    if (keyStates[KEY_CAM_TURN_LEFT])
    {
        camRotZ-=1;
    }
    if (keyStates[KEY_CAM_TURN_RIGHT])
    {
        camRotZ+=1;
    }
    if (keyStates[KEY_CAM_TURN_UP] && camRotX<90)
    {
        camRotX+=1;
    }
    if (keyStates[KEY_CAM_TURN_DOWN] && camRotX>-90)
    {
        camRotX-=1;
    }
    if (keyStates[KEY_CAM_CLOSER] /*&& camRotX>-90*/)
    {
        distanceFromPlayer-=0.5;
//        camRotX+=1;
    }
    if (keyStates[KEY_CAM_FARTHER] /*&& camRotX>-90*/)
    {
        distanceFromPlayer+=0.5;
//        camRotX-=1;
    }
    player->move();
    calculateCamPos(distanceFromPlayer);
    update();
}

void MainWindow::calculateCamPos(float distance)
{
    float horizDistnce = -distance*cos(camRotX/180*M_PI);
    float vertDistance = -distance*sin(camRotX/180*M_PI);

    camPosX = models[0]->GetPos().x() + horizDistnce*sin(camRotZ/180*M_PI);
    camPosY = models[0]->GetPos().y() + horizDistnce*cos(camRotZ/180*M_PI);
    camPosZ = models[0]->GetPos().z() + vertDistance;
}

void MainWindow::startTimer()
{
    timer = new QTimer(this);
    connect (timer, &QTimer::timeout, this, &MainWindow::updateScene);
    timer->start(20);
}
