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
        mainwindow.cpp \
    objloader.cpp \
    terrain.cpp \
    TexturedModel.cpp \
    RawModel.cpp \
    shader.cpp \
    phisicstanks.cpp

HEADERS  += mainwindow.h \
    objloader.h \
    terrain.h \
    TexturedModel.h \
    RawModel.h \
    shader.h \
    PhisicsTanks.h

RESOURCES += \
    resources.qrc

DISTFILES +=
