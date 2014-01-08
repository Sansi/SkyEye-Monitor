#-------------------------------------------------
#
# Project created by QtCreator 2013-11-16T09:37:35
#
#-------------------------------------------------

QT       += core gui sql

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SQLExample
TEMPLATE = app


SOURCES += main.cpp\
        sqlexample.cpp

HEADERS  += sqlexample.h

FORMS    += sqlexample.ui

OTHER_FILES += \
    config.json

RESOURCES += \
    res.qrc

EXTRA_FILES += \
        config.json
for(FILE,EXTRA_FILES){
    QMAKE_POST_LINK += $$quote(cp $${PWD}/$${FILE} $${OUT_PWD}$$escape_expand(\n\t))
}
