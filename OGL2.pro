#-------------------------------------------------
#
# Project created by QtCreator 2015-12-05T19:08:54
#
#-------------------------------------------------

QT       += core gui
LIBS += -lopengl32 -lglu32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OGL2
TEMPLATE = app


SOURCES += main.cpp\
    TexturedModel.cpp \
    RawModel.cpp \
    ChunkManager.cpp \
    TexturesManager.cpp \
    PhisicsTanks.cpp \
    OBJLoader.cpp \
    Terrain.cpp \
    Shader.cpp \
    MainWindow.cpp

HEADERS  += \
    TexturedModel.h \
    RawModel.h \
    PhisicsTanks.h \
    ChunkManager.h \
    TexturesManager.h \
    OBJLoader.h \
    Terrain.h \
    Shader.h \
    MainWindow.h

RESOURCES += \
    resources.qrc

DISTFILES +=
