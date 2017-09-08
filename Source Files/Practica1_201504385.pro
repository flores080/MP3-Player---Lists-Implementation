#-------------------------------------------------
#
# Project created by QtCreator 2017-06-12T11:34:00
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Practica1_201504385
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
        mainwindow.cpp \
    album.c \
    albums.c \
    artista.c \
    artistas.c \
    cancion.c \
    canciones.c \
    node.c \
    stack.c \
    queue.c \
    circle_double_list.c \
    double_node.c

HEADERS += \
        mainwindow.h \
    album.h \
    albums.h \
    artista.h \
    artistas.h \
    cancion.h \
    canciones.h \
    node.h \
    stack.h \
    queue.h \
    circle_double_list.h \
    double_node.h

FORMS += \
        mainwindow.ui
