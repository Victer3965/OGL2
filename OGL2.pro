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
    MainWindow.cpp \
    CollisionModel.cpp \
    ModelBase.cpp

HEADERS  += \
    TexturedModel.h \
    RawModel.h \
    PhisicsTanks.h \
    ChunkManager.h \
    TexturesManager.h \
    OBJLoader.h \
    Terrain.h \
    Shader.h \
    MainWindow.h \
    CollisionModel.h \
    ModelBase.h

RESOURCES += \
    resources.qrc

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lCollisionModel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lCollisionModeld

INCLUDEPATH += $$PWD/lib
DEPENDPATH += $$PWD/lib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/libCollisionModel.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/libCollisionModeld.a
