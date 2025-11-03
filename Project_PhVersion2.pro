QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# Définir les chemins d'inclusion
INCLUDEPATH += $$PWD/Headers

# Sources
SOURCES += \
    Src/client/cl.cpp \
    Src/fournisseur/fr.cpp \
    Src/main.cpp \
    Src/mainwindow.cpp \

# Headers
HEADERS += \
    Headers/mainwindow.h \
    Headers/client/client.h \
    Headers/fournisseur/fourn.h \

# Forms
FORMS += \
    forms/client/toolbox.ui \
    forms/fournisseur/toolbox.ui \
    forms/mainwindow.ui \

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
