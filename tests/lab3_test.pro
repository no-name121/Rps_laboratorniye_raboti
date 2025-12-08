QT += testlib gui widgets sql
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_testdatabase.cpp

# исходники
SOURCES += \
    ../lab3/mainwindow.cpp \
    ../lab3/functions.cpp \
    ../lab3/sort.cpp \
    ../lab3/signinwindow.cpp \
    ../lab3/signupwindow.cpp

HEADERS += \
    ../lab3/mainwindow.h \
    ../lab3/functions.h \
    ../lab3/sort.h \
    ../lab3/signinwindow.h \
    ../lab3/signupwindow.h

FORMS += \
    ../lab3/mainwindow.ui \
    ../lab3/signinwindow.ui \
    ../lab3/signupwindow.ui

RESOURCES += \
    ../lab3/assets.qrc

INCLUDEPATH += \
    ../lab3
