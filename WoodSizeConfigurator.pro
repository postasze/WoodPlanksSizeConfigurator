#-------------------------------------------------
#
# Project created by QtCreator 2017-08-08T15:15:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WoodSizeConfigurator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    clickableimage.cpp \
    openglwidget.cpp \
    plankgeometry.cpp \
    deskakarbon.cpp \
    deskamodern.cpp \
    deskaretro.cpp \
    eurodeskaretro.cpp \
    eurodeskamodern.cpp \
    bevelkarbon.cpp \
    bevelgeometry.cpp \
    bevelretro.cpp \
    bevelmodern.cpp \
    channelgeometry.cpp \
    channelkarbon.cpp \
    channelretro.cpp \
    channelmodern.cpp \
    emptyprofilegeometry.cpp \
    emptyprofilekarbon.cpp \
    emptyprofileretro.cpp \
    emptyprofilemodern.cpp

HEADERS += \
    clickableimage.h \
    openglwidget.h \
    constants.h \
    plankgeometry.h \
    object3dgeometry.h \
    deskakarbon.h \
    deskamodern.h \
    deskaretro.h \
    eurodeskaretro.h \
    eurodeskamodern.h \
    bevelkarbon.h \
    bevelgeometry.h \
    bevelretro.h \
    bevelmodern.h \
    channelgeometry.h \
    channelkarbon.h \
    channelretro.h \
    channelmodern.h \
    emptyprofilegeometry.h \
    emptyprofilekarbon.h \
    emptyprofileretro.h \
    emptyprofilemodern.h

FORMS += \
    deskakarbon.ui \
    deskaretro.ui \
    deskamodern.ui \
    eurodeskaretro.ui \
    eurodeskamodern.ui \
    bevelkarbon.ui \
    bevelretro.ui \
    bevelmodern.ui \
    channelkarbon.ui \
    channelretro.ui \
    channelmodern.ui \
    emptyprofilekarbon.ui \
    emptyprofileretro.ui \
    emptyprofilemodern.ui

RESOURCES += \
    shaders.qrc \
    textures.qrc \
    images.qrc
