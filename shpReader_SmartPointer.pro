#-------------------------------------------------
#
# Project created by QtCreator 2018-06-16T09:40:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shpReader_SmartPointer
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

INCLUDEPATH += RJPclass

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    shapelib/dbfopen.cpp \
    shapelib/shpopen.cpp \
    shapelib/shptree.cpp \
    main.cpp \
    mainwindow.cpp \
    shapelib/dbfopen.cpp \
    shapelib/shpopen.cpp \
    shapelib/shptree.cpp \
    main.cpp \
    mainwindow.cpp \
    RJPclass/mapbuilder.cpp \
    shapelib/dbfopen.cpp \
    shapelib/shpopen.cpp \
    shapelib/shptree.cpp \
    main.cpp \
    mainwindow.cpp \
    RJPclass/shpview.cpp \
    RJPclass/dockwidget.cpp \
    RJPclass/rjp_shape.cpp \
    RJPclass/rjp_dataset.cpp \
    RJPclass/rjp_shapes.cpp \
    RJPclass/rjp_factory.cpp \
    RJPclass/mapwindow.cpp \
    RJPclass/mapview.cpp \
    RJPclass/mapdatabase.cpp

HEADERS += \
        mainwindow.h \
    shapelib/shapefil.h \
    mainwindow.h \
    shapelib/shapefil.h \
    mainwindow.h \
    RJPclass/mapbuilder.h \
    shapelib/shapefil.h \
    mainwindow.h \
    RJPclass/shpview.h \
    RJPclass/dockwidget.h \
    RJPclass/rjp_shape.h \
    RJPclass/rjp_dataset.h \
    RJPclass/rjp_shapes.h \
    RJPclass/rjp_factory.h \
    RJPclass/mapwindow.h \
    RJPclass/mapview.h \
    RJPclass/mapdatabase.h \
    RJPclass/rjp_shapes_command.hpp

FORMS += \
        mainwindow.ui \
    RJPclass/dockwidget.ui
