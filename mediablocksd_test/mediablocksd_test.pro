QT += testlib
QT += network core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../mediablocksd/include

SOURCES +=  \
            ../mediablocksd/src/configuration.cpp \
    mbconfigtest.cpp

HEADERS +=  ../mediablocksd/include/configuration.hpp \
            ../mediablocksd/include/mediablocks.hpp


