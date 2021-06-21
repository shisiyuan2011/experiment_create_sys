QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    a_exptap_choose.cpp \
    b_mission.cpp \
    ca_exppara.cpp \
    cb_rewrite.cpp \
    d_matiralinfo.cpp \
    dispatch.cpp \
    e_missionup.cpp \
    main.cpp \
    mainwindow.cpp \
    matiral.cpp \
    myserver620.cpp \
    myserverthread620.cpp \
    mysocket620.cpp

HEADERS += \
    a_exptap_choose.h \
    b_mission.h \
    ca_exppara.h \
    cb_rewrite.h \
    d_matiralinfo.h \
    dispatch.h \
    e_missionup.h \
    mainwindow.h \
    matiral.h \
    myserver620.h \
    myserverthread620.h \
    mysocket620.h

FORMS += \
    a_exptap_choose.ui \
    b_mission.ui \
    ca_exppara.ui \
    cb_rewrite.ui \
    d_matiralinfo.ui \
    dispatch.ui \
    e_missionup.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
