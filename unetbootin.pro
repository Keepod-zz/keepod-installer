TEMPLATE = app
TARGET = unetbootin
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += debug \
    static
HEADERS += unetbootin.h \
    messages.h \
    customitemdelegate.h \
    installtaskinfo.h \
    definitions.h \
    cnorimagesdiff.h \
    cusbdiskinfo.h \
    cuimain.h \
    cnorchangedblocks.h
FORMS += unetbootin.ui
SOURCES += main.cpp \
    unetbootin.cpp \
    customitemdelegate.cpp \
    installtaskinfo.cpp \
    cnorimagesdiff.cpp \
    cusbdiskinfo.cpp \
    cuimain.cpp \
    cnorchangedblocks.cpp
QT += core \
    gui \
    network
ICON = unetbootin.icns
RESOURCES += keepodinstaller.qrc
TRANSLATIONS += unetbootin.ts
DEFINES += NOSTATIC

unix:!macx:!symbian: LIBS += -lzip
