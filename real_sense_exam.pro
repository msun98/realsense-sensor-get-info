QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
CONFIG += console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += C:\Users\rainbow\Documents\common\opencv-msvc\build\include
INCLUDEPATH += "C:\Program Files (x86)\Intel RealSense SDK 2.0\include" # 리얼센스 sdk 인클루드 폴더


# 오픈시브이용 디버그 모드이면 opencv_world455d 파일 실행. 릴리즈 모드이면 opencv_world455 파일 실행.
CONFIG(debug, debug|release):LIBS += C:\Users\rainbow\Documents\common\opencv-msvc\build\x64\vc15\lib\opencv_world455d.lib
CONFIG(release, debug|release):LIBS += C:\Users\rainbow\Documents\common\opencv-msvc\build\x64\vc15\lib\opencv_world455.lib

# 리얼센스용
CONFIG(debug, debug|release):LIBS += "C:\Program Files (x86)\Intel RealSense SDK 2.0\lib\x64\realsense2.lib"
CONFIG(release, debug|release):LIBS += "C:\Program Files (x86)\Intel RealSense SDK 2.0\lib\x64\realsense2.lib"
