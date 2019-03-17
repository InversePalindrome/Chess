# Copyright (c) 2019 Inverse Palindrome
# Chess - Chess.pro
# https://inversepalindrome.com/


QT += core gui widgets

TARGET = Chess
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++1z

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/Main.cpp \
    src/MainWindow.cpp

HEADERS += \
    include/MainWindow.hpp

FORMS += \
    UI/MainWindow.ui

RESOURCES += \
    Resources/resources.qrc
