TEMPLATE = app
TARGET = keepod-installer

CONFIG += static

DESTDIR = bin

LIBS += -L$$DESTDIR

QT += core \
    gui \
    network

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

    EXTRA_BINFILES_WIN = \
            $${CYGWIN_BINFILES} \
            $${QT_BINFILES} \
            $${CPP_BINFILES}

    DESTDIR_WIN = $$OUT_PWD/$$DESTDIR


    qtlib.path = $${DESTDIR_WIN}
    qtlib.files = $${QT_BINFILES}

    extra.path = $${DESTDIR_WIN}
    extra.files = $${CYGWIN_BINFILES}

    cpplib.path = $${DESTDIR_WIN}
    cpplib.files = $${CPP_BINFILES}

    platforms.path = $${DESTDIR_WIN}/platforms
    platforms.files = $${QT_PLATFORMS_BINFILES}

#    app.path = windows/$$DESTDIR
#    app.files = $$DESTDIR_TARGET
# Note that qmake will skip files that are executable.
# If you need to install executable files, you can unset the files' executable flags.

# add make install to Makefile
    INSTALLS +=  \
            extra \
            qtlib \
            cpplib

    greaterThan( QT_MAJOR_VERSION, 4): INSTALLS += platforms

    EXTRA_BINFILES_WIN ~= s,/,\\,g
    DESTDIR_WIN ~= s,/,\\,g

#    QMAKE_POST_LINK += $$quote(cmd /c copy /y /B /N $$DESTDIR_TARGET $${DESTDIR_WIN} $$escape_expand(\\n\\t))

#    for(FILE,EXTRA_BINFILES_WIN){
#        QMAKE_POST_LINK+= $$quote(cmd /c copy /y /B /N $${FILE} $${DESTDIR_WIN} $$escape_expand(\\n\\t))
#    }

}

