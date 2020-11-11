QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    combobox.cpp \
    containerwidget.cpp \
    imageviewlabel.cpp \
    main.cpp \
    mainwindow.cpp \
    pushbutton.cpp \
    slidingstackedwidget.cpp \
    toolbutton.cpp \
    topbarwidget.cpp

HEADERS += \
    combobox.h \
    comboview.h \
    containerwidget.h \
    imageviewlabel.h \
    mainwindow.h \
    pushbutton.h \
    slidingstackedwidget.h \
    toolbutton.h \
    topbarwidget.h

RESOURCES += \
    res.qrc

