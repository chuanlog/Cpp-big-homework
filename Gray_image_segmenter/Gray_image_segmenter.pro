QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Diagonal_Priority.cpp \
    main.cpp \
    widget.cpp\


HEADERS += \
    Header_Diagonal_Priority.h \
    Header_Diagonal_Priority.h \
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
INCLUDEPATH += D:\opencv\opencv\OpenCV-CMakeBuild\install\include
LIBS += D:\opencv\opencv\OpenCV-CMakeBuild\install\x64\mingw\bin\libopencv_*.dll
# 以上两行在开发时换上自己的路径,这里"libopencv_*.dll"代表bin文件夹下所有以libopencv_开头的ddl文件，找到bin文件夹路径后照抄最后的"libopencv_*.dll"即可
}
#ps:为方便起见，提交至github时应该删去上方路径，可以将自己的路径以注释形式写在下面，便于opencv库的快速导入

#E:\openCV4.7.0\opencv\opencv-build\install\include
#E:\openCV4.7.0\opencv\opencv-build\install\x64\mingw\bin\libopencv_*.dll
#这是陈永川的路径

#D:\opencv\opencv\OpenCV-CMakeBuild\install\include
#D:\opencv\opencv\OpenCV-CMakeBuild\install\x64\mingw\bin\libopencv_*.dll
#这是潘昊的路径
