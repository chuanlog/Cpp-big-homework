QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#此处是opencv库的引入
win32
{
INCLUDEPATH += E:\openCV4.7.0\opencv\opencv-build\install\include
LIBS += E:\openCV4.7.0\opencv\opencv-build\install\x64\mingw\bin\libopencv_*.dll
# 以上两行在开发时换上自己的路径,这里"libopencv_*.dll"代表bin文件夹下所有以libopencv_开头的ddl文件，找到bin文件夹路径后照抄最后的"libopencv_*.dll"即可
}
