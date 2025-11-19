QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

CONFIG += c++17

INCLUDEPATH += ../external/eigen-5.0.0/eigen-5.0.0
INCLUDEPATH += ../external/json-develop/json-develop/single_include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ../core/src/contenidos.cpp \
    ../core/src/plataforma.cpp \
    ../core/src/usuarios.cpp

HEADERS += \
    mainwindow.h \
    ../core/include/contenidos.h \
    ../core/include/plataforma.h \
    ../core/include/usuarios.h \
    ../core/include/EigenConfig.h \

FORMS += \
    mainwindow.ui

DISTFILES += \
    ../core/data/contenidos.json \
    ../core/data/datos_usuarios.json \
    ../core/data/etiquetas.json \
    ../core/data/secciones.json \
    ../core/data/usuarios.json

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
