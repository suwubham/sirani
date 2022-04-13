QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection.cpp \
    homescreen.cpp \
    main.cpp \
    mainwindow.cpp \
    signup_page.cpp

HEADERS += \
    connection.h \
    homescreen.h \
    mainwindow.h \
    signup_page.h

FORMS += \
    homescreen.ui \
    mainwindow.ui \
    signup_page.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc \
    resource.qrc \
    resource.qrc
