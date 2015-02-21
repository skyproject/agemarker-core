#-------------------------------------------------
#
# Project created by QtCreator 2013-04-29T18:18:18
#
#-------------------------------------------------

QT       -= gui

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS_RELEASE += -O2

TARGET = agemarker-core
TEMPLATE = lib

DEFINES += AGEMARKERCORE_LIBRARY


SOURCES += acl_agemarkercore.cpp \
           acl_math.cpp \
           acl_calculationthread.cpp \
           acl_mtrandom.cpp \
           acl_results.cpp \
           acl_atoms.cpp


HEADERS += acl_global.h \
           acl_agemarkercore.h \
           acl_mtrandom.h \
           acl_math.h \
           acl_data.h \
           acl_calculationthread.h \
           acl_results.h \
           acl_atoms.h


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
