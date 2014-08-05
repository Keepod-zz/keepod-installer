TEMPLATE = app
TARGET = keepod-installer
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
    cnorchangedblocks.h \
    cstatusmanager.h
FORMS += unetbootin.ui
SOURCES += main.cpp \
    unetbootin.cpp \
    customitemdelegate.cpp \
    installtaskinfo.cpp \
    cnorimagesdiff.cpp \
    cusbdiskinfo.cpp \
    cuimain.cpp \
    cnorchangedblocks.cpp \
    cstatusmanager.cpp
QT += core \
    gui \
    network
ICON = unetbootin.icns
TRANSLATIONS += unetbootin.ts
DEFINES += NOSTATIC
RESOURCES += keepodinstaller.qrc

unix:!macx:!symbian: LIBS += -lzip
