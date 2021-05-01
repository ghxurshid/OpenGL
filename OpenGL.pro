#-------------------------------------------------
#
# Project created by QtCreator 2021-04-14T18:55:37
#
#-------------------------------------------------

QT       += core gui opengl multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += widgets \
               media   \

SOURCES += \
        main.cpp \
        widgets/mainwindow.cpp \
        widgets/drawableobject.cpp \
        widgets/sphera.cpp \
        widgets/camera3d.cpp \
        media/videosurface.cpp \
    widgets/xyzaxis.cpp

HEADERS += \
        widgets/mainwindow.h \
        widgets/drawableobject.h \
        widgets/sphera.h \
        widgets/camera3d.h \
        media/videosurface.h \
    widgets/xyzaxis.h

LIBS += -lopengl32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    shaders/shaders.qrc \
    resources/textures.qrc
