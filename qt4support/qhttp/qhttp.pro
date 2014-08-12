#load(qt_build_config)
TEMPLATE=lib

DESTDIR = ../../bin

TARGET = QtHttp
#CONFIG += static
#CONFIG -= shared
#CONFIG -= static
#CONFIG += shared
QT = core network

#MODULE_PRI = ../../modules/qt_http.pri
#MODULE = http

#load(qt_module)

# Input
HEADERS += qhttp.h qringbuffer_p.h qhttpauthenticator_p.h
SOURCES += qhttp.cpp qhttpauthenticator.cpp
