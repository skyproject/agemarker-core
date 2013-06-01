#-------------------------------------------------
#
# Project created by QtCreator 2013-04-29T18:18:18
#
#-------------------------------------------------

QT       -= gui

QMAKE_CXXFLAGS += -std=c++0x

TARGET = agemarker-core
TEMPLATE = lib

DEFINES += AGEMARKERCORE_LIBRARY


SOURCES += acl_agemarkercore.cpp \
           acl_math.cpp \
           acl_calculationthread.cpp \
           acl_mtrandom.cpp


HEADERS += acl_global.h \
           acl_agemarkercore.h \
           acl_mtrandom.h \
           acl_math.h \
           acl_data.h \
           acl_calculationthread.h \
           application.h


win32:RC_FILE = resources.rc


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
