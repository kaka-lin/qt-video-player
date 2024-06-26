QT += qml quick multimedia
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

UI_DIR += obj
RCC_DIR += obj
MOC_DIR += obj
OBJECTS_DIR += obj
#DESTDIR = obj

SOURCES += \
    src/main.cpp \
    src/threads/backend_thread.cpp \
    src/threads/opencv_thread.cpp \
    src/app/my_media_player.cpp \

HEADERS += \
    src/threads/backend_thread.h \
    src/threads/opencv_thread.h \
    src/app/my_media_player.h \

RESOURCES += src/resources/qml.qrc

### OpenCV
# For macOS: brew install opencv
#INCLUDEPATH += /opt/homebrew/opt/opencv/include/opencv4
#LIBS += `pkg-config --cflags --libs opencv4`
# For Linux
#CONFIG += link_pkgconfig
#PKGCONFIG += opencv
LIBS += `pkg-config --cflags --libs opencv`

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
