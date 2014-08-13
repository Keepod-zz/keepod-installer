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


win32:{

    #    QT_PATH = $$(QTDIR) # it be recognized in QtCreator, not in command
    #    QT_PATH = $$[QT_INSTALL_BINS]
    !CONFIG(DEFQTPATH):    QT_PATH = $$(QTDIR)

    THIRDPARTY_PATH = $$PWD/windows/thirdpart

    INCLUDEPATH += $$THIRDPARTY_PATH/libzip/include
    LIBS += \
        -L"$$THIRDPARTY_PATH/libzip/lib" \
        -lzip
		
	greaterThan( QT_MAJOR_VERSION, 4): {
		QT_BINFILES += \
			$${QT_PATH}/bin/Qt5Core.dll \
			$${QT_PATH}/bin/Qt5Network.dll \
			$${QT_PATH}/bin/Qt5Gui.dll \
			$${QT_PATH}/bin/Qt5Widgets.dll \
			$${QT_PATH}/bin/icudt52.dll \
			$${QT_PATH}/bin/icuin52.dll \
			$${QT_PATH}/bin/icuuc52.dll \
			$${QT_PATH}/plugins/platforms/qwindows.dll \
			$${QT_PATH}/plugins/platforms/qminimal.dll 
	}else{
		QT_BINFILES += \
			$${QT_PATH}/bin/QtCore4.dll \
			$${QT_PATH}/bin/QtNetwork4.dll \
			$${QT_PATH}/bin/QtGui4.dll
	}


    CPP_BINFILES += \
        $${QT_PATH}/bin/libwinpthread-1.dll \
        $${QT_PATH}/bin/libgcc_s_dw2-1.dll \
        $${QT_PATH}/bin/libstd~1.dll      # libstdc++-6.dll
#known as QT Bug 16372 : https://bugreports.qt-project.org/browse/QTBUG-16372
#Using libstd~1.dll (DOS filename) as you said works for now as the bug is still unresolved as today (june 2014).



    EXTRA_BINFILES += \
        $${THIRDPARTY_PATH}/win32/bin/cyggcc_s-1.dll \
        $${THIRDPARTY_PATH}/win32/bin/cygwin1.dll \
        $${THIRDPARTY_PATH}/win32/bin/cygz.dll \
        $${THIRDPARTY_PATH}/win32/bin/cygzip-3.dll

    EXTRA_BINFILES_WIN = \
            $${EXTRA_BINFILES} \
            $${QT_BINFILES} \
            $${CPP_BINFILES}

    DESTDIR_WIN = $$DESTDIR

    EXTRA_BINFILES_WIN ~= s,/,\\,g
    DESTDIR_WIN ~= s,/,\\,g

    for(FILE,EXTRA_BINFILES_WIN){
        QMAKE_POST_LINK+= $$quote(cmd /c copy /y /B /N $${FILE} $${DESTDIR_WIN} $$escape_expand(\\n\\t))
    }

}

