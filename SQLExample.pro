#-------------------------------------------------
#
# Project created by QtCreator 2013-11-16T09:37:35
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SQLExample
TEMPLATE = app


SOURCES += main.cpp\
        sqlexample.cpp \
    sqltool.cpp

HEADERS  += sqlexample.h \
    sqltool.h

FORMS    += sqlexample.ui
