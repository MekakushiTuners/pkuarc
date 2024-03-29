#-------------------------------------------------
#
# Project created by QtCreator 2023-04-26T11:40:29
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia  multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
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

CONFIG += resources_big

SOURCES += \
    basescene.cpp \
        main.cpp \
    button.cpp \
    track.cpp \
    gamescene.cpp \
    mainscene.cpp \
    introscene.cpp \
    songselect.cpp \
    utils.cpp \
    resultscene.cpp \
    chapterselect.cpp

HEADERS += \
    basescene.h \
    config.h \
    button.h \
    track.h \
    gamescene.h \
    mainscene.h \
    introscene.h \
    songselect.h \
    utils.h \
    resultscene.h \
    chapterselect.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += res.qrc

FORMS +=

DISTFILES += \
    res/Malody Regular dan10/mrv20.ogg \
    res/Malody Regular dan10/r1000.jpg \
    res/Malody Regular dan10/1584338873.mc
