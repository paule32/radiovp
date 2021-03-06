TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TOPDIR=$$PWD
SRCDIR=$${TOPDIR}/source
HDRDIR=$${SRCDIR}/includes

GENFOLDER =$${TOPDIR}/build/

UI_DIR =$${TOPDIR}/.uic
MOC_DIR=$${TOPDIR}/.moc
OBJ_DIR=$${TOPDIR}/.obj
RCC_DIR=$${TOPDIR}/.res

DEFINES += BUILDTIME=\\\"$$system(date '+%H:%M:%S')\\\"
DEFINES += BUILDDATE=\\\"$$system(date '+%Y-%m-%d')\\\"

INCLUDEPATH = \
    /usr/include \
    /usr/include/SDL \
    $${TOPDIR}/.uic

QMAKE_CXXFLAGS += \
    -fpermissive \
    -frtti -fexceptions  -std=c++17

LIBS += -L"/usr/lib/x86-64_linux-gnu" -lSDL -lSDL2 -lSDL_ttf
LIBS += -L"/usr/lib/vlc" -lcompat -lvlc
LIBS += -L"/usr/lib" -lvlccore

SOURCES += \
    main.cc \
    tsurface.cc \
    tcontrol.cc \
    iinterfacecomponentreference.cc \
    tpoint.cc \
    tcomponent.cc \
    tapplication.cc \
    tfont.cc \
    tcolor.cc \
    tpainter.cc \
    tgraphicsitem.cc \
    ttimer.cc

FORMS +=

HEADERS += \
    tsurface.h \
    tcontrol.h \
    iinterfacecomponentreference.h \
    tpoint.h \
    tcomponent.h \
    tapplication.h \
    tfont.h \
    tcolor.h \
    tpainter.h \
    tgraphicsitem.h \
    ttimer.h

DISTFILES += \
    getwin.sh

