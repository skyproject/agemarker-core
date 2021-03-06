#-------------------------------------------------
#
# Project created by QtCreator 2013-04-29T18:18:18
#
#-------------------------------------------------

# Please note that the library can be compiled to use
# either "double" precision or quadruple precision
# (the latter is provided by Boost Multiprecision's
# "float128" type).
#
# See "acl_global.h" file for the preprocessor defines.

QT       -= gui

QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -fext-numeric-literals
QMAKE_CXXFLAGS_RELEASE += -O2

# When compiling the library with USING_FLOAT128,
# change TARGET (output filename) to agemarker-core-ep.
# Don't forget to do the same for the main program.
TARGET = agemarker-core

TEMPLATE = lib

DEFINES += AGEMARKERCORE_LIBRARY


SOURCES += acl_agemarkercore.cpp \
           acl_math.cpp \
           acl_mtrandom.cpp \
           acl_results.cpp \
           acl_atoms.cpp \
           acl_calculation.cpp


HEADERS += acl_global.h \
           acl_agemarkercore.h \
           acl_mtrandom.h \
           acl_math.h \
           acl_data.h \
           acl_results.h \
           acl_atoms.h \
           acl_float.h \
           acl_calculation.h


LIBS += -lquadmath

INCLUDEPATH += $$quote(c:/Users/mlabu_000.RESONANS-PC/Documents/Libs)


unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
