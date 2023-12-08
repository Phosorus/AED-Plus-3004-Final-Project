QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battery.cpp \
    main.cpp \
    mainwindow.cpp \
    mastercontrol.cpp \
    patient.cpp \
    signalanalyser.cpp \
    compressionsensor.cpp \
    heartsensor.cpp \
    sensorpads.cpp \
    pads.cpp \
    shockers.cpp \


HEADERS += \
    battery.h \
    mainwindow.h \
    mastercontrol.h \
    patient.h \
    signalanalyser.h \
    compressionsensor.h \
    heartsensor.h \
    sensorpads.h \
    pads.h \
    shockers.h \


FORMS += \
    mainwindow.ui

RESOURCES += \
    assets.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
