TEMPLATE = app
TARGET = keepod-installer

CONFIG += static

DESTDIR = $$OUT_PWD/bin

LIBS += -L$$DESTDIR

QT += core \
    gui \
    network

# no strip for executable files
QMAKE_STRIP = echo

DEPENDPATH += .

INCLUDEPATH += .

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

SOURCES += main.cpp \
    unetbootin.cpp \
    customitemdelegate.cpp \
    installtaskinfo.cpp \
    cnorimagesdiff.cpp \
    cusbdiskinfo.cpp \
    cuimain.cpp \
    cnorchangedblocks.cpp \
    cstatusmanager.cpp

FORMS += unetbootin.ui

ICON = unetbootin.icns
TRANSLATIONS += unetbootin.ts
DEFINES += NOSTATIC
RESOURCES += keepodinstaller.qrc
RC_FILE += keepodinstaller.rc


unix:!macx:!symbian: LIBS += -lzip


# Qt4 support for Qt5
greaterThan( QT_MAJOR_VERSION, 4): {
    QT += widgets

    INCLUDEPATH += \
        qt4support/qftp \
        qt4support/qhttp

    HEADERS += \
        qt4support/qftp/qftp.h \
        qt4support/qftp/qurlinfo.h \
        qt4support/qhttp/qhttp.h

    SOURCES += \
        qt4support/qftp/qftp.cpp \
        qt4support/qftp/qurlinfo.cpp \
        qt4support/qhttp/qhttp.cpp \
        qt4support/qhttp/qhttpauthenticator.cpp
}

THIRDPARTY_PATH = $$PWD/thirdpart

INCLUDEPATH += $$THIRDPARTY_PATH/libzip/include

win32:{

    #    QT_PATH = $$(QTDIR) # it be recognized in QtCreator, not in command
    #    QT_PATH = $$[QT_INSTALL_BINS]
    !CONFIG(DEFQTPATH):     QT_PATH = $$(QTDIR)
    !CONFIG(DEFMAKEPATH):   MAKE_PATH = $$(QTDIR)

    LIBS += \
        -L"$$THIRDPARTY_PATH/libzip/lib" \
        -lzip

        CONFIG(debug, debug|release) {
            greaterThan( QT_MAJOR_VERSION, 4): {
                    QT_BINFILES += \
                            $${QT_PATH}/bin/Qt5Core*.dll \
                            $${QT_PATH}/bin/Qt5Network*.dll \
                            $${QT_PATH}/bin/Qt5Gui*.dll \
                            $${QT_PATH}/bin/Qt5Widgets*.dll \
                            $${QT_PATH}/bin/icudt*.dll \
                            $${QT_PATH}/bin/icuin*.dll \
                            $${QT_PATH}/bin/icuuc*.dll

                    QT_PLATFORMS_BINFILES += \
                            $${QT_PATH}/plugins/platforms/qwindows*.dll \
                            $${QT_PATH}/plugins/platforms/qminimal*.dll

            }else{
                    QT_BINFILES += \
                            $${QT_PATH}/bin/QtCore4*.dll \
                            $${QT_PATH}/bin/QtNetwork4*.dll \
                            $${QT_PATH}/bin/QtGui4*.dll
            }

        }else{

            greaterThan( QT_MAJOR_VERSION, 4): {
                    QT_BINFILES += \
                            $${QT_PATH}/bin/Qt5Core.dll \
                            $${QT_PATH}/bin/Qt5Network.dll \
                            $${QT_PATH}/bin/Qt5Gui.dll \
                            $${QT_PATH}/bin/Qt5Widgets.dll \
                            $${QT_PATH}/bin/icudt*.dll \
                            $${QT_PATH}/bin/icuin*.dll \
                            $${QT_PATH}/bin/icuuc*.dll

                    QT_PLATFORMS_BINFILES += \
                            $${QT_PATH}/plugins/platforms/qwindows.dll \
                            $${QT_PATH}/plugins/platforms/qminimal.dll

            }else{
                    QT_BINFILES += \
                            $${QT_PATH}/bin/QtCore4.dll \
                            $${QT_PATH}/bin/QtNetwork4.dll \
                            $${QT_PATH}/bin/QtGui4.dll
            }
        }


    CPP_BINFILES += \
        $${MAKE_PATH}/bin/libwinpthread-1.dll \
        $${MAKE_PATH}/bin/libgcc_s_dw2-1.dll \
        $${MAKE_PATH}/bin/libstdc++-6.dll      # libstdc++-6.dll
#known as QT Bug 16372 : https://bugreports.qt-project.org/browse/QTBUG-16372
#Using libstd~1.dll (DOS filename) as you said works for now as the bug is still unresolved as today (june 2014).

    CYGWIN_BINFILES += \
        $${THIRDPARTY_PATH}/cygwin/bin/cyggcc_s-1.dll \
        $${THIRDPARTY_PATH}/cygwin/bin/cygwin1.dll \
        $${THIRDPARTY_PATH}/cygwin/bin/cygz.dll \
        $${THIRDPARTY_PATH}/cygwin/bin/cygzip-3.dll

    OTHER_BINFILES += \
        $${THIRDPARTY_PATH}/dcfldd/bin/dcfldd.exe \
        $${THIRDPARTY_PATH}/dd/bin/dd.exe \
        $${THIRDPARTY_PATH}/md5sum/bin/md5sum.exe

    DESTDIR_WIN = $$DESTDIR


    qtlib.path = $${DESTDIR_WIN}
    qtlib.files = $${QT_BINFILES}

    cygwin.path = $${DESTDIR_WIN}
    cygwin.files = $${CYGWIN_BINFILES}

    cpplib.path = $${DESTDIR_WIN}
    cpplib.files = $${CPP_BINFILES}

    platforms.path = $${DESTDIR_WIN}/platforms
    platforms.files = $${QT_PLATFORMS_BINFILES}

    other.path = $${DESTDIR_WIN}
    other.files = $${OTHER_BINFILES}

# add make install to Makefile
    INSTALLS +=  \
            qtlib \
            cpplib \
            cygwin \
            other


    greaterThan( QT_MAJOR_VERSION, 4): INSTALLS += platforms

}


macx:{
#    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
    LIBS +=

#keepod-installer.app/Contents/MacOS/keepod-installer:
#	QtGui.framework/Versions/4/QtGui (compatibility version 4.8.0, current version 4.8.6)
#	QtCore.framework/Versions/4/QtCore (compatibility version 4.8.0, current version 4.8.6)
#	QtNetwork.framework/Versions/4/QtNetwork (compatibility version 4.8.0, current version 4.8.6)
#	/usr/lib/libstdc++.6.dylib (compatibility version 7.0.0, current version 60.0.0)
#	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1197.1.1)
#	/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 2577.0.0)

    cpplib.path = $$DESTDIR/keepod-installer.app/Contents/dylib
    cpplib.files += \
        /usr/lib/libstdc++.6.dylib \
        /usr/lib/libSystem.B.dylib \
        /usr/lib/libgcc_s.1.dylib

    INSTALLS += \
            cpplib
}
