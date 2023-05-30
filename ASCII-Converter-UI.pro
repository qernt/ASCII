QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    directoryselection.cpp \
    draganddrop.cpp \
    main.cpp \
    mainwindow.cpp \
    statusbar.cpp

HEADERS += \
    directoryselection.h \
    draganddrop.h \
    mainwindow.h \
    statusbar.h

FORMS += \
    directoryselection.ui \
    draganddrop.ui \
    mainwindow.ui \
    statusbar.ui

INCLUDEPATH += /opt/homebrew/opt/imagemagick/include/ImageMagick-7

QMAKE_CXXFLAGS += -Xpreprocessor -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16
QMAKE_LFLAGS += -Xpreprocessor -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16
LIBS += -L/opt/homebrew/Cellar/imagemagick/7.1.1-9/lib -lMagick++-7.Q16HDRI -lMagickWand-7.Q16HDRI -lMagickCore-7.Q16HDRI
INCLUDEPATH += /opt/homebrew/Cellar/imagemagick/7.1.1-9/include/ImageMagick-7
DISTFILES += $$PWD/Fonts/consolas.ttf


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
