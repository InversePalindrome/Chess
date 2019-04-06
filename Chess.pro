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
    src/MainWindow.cpp \
    src/ChessScene.cpp \
    src/ChessBoardGraphicsItem.cpp \
    src/ChessBoard.cpp \
    src/ChessPiece.cpp \
    src/ChessUtility.cpp \
    src/ChessPieceGraphicsItem.cpp \
    src/ChessPosition.cpp \
    src/ChessValidation.cpp

HEADERS += \
    include/MainWindow.hpp \
    include/ChessScene.hpp \
    include/ChessBoardGraphicsItem.hpp \
    include/ChessBoard.hpp \
    include/ChessConstants.hpp \
    include/ChessPiece.hpp \
    include/ChessUtility.hpp \
    include/ChessPieceGraphicsItem.hpp \
    include/ChessPosition.hpp \
    include/ChessTransition.hpp \
    include/ChessValidation.hpp

FORMS += \
    UI/MainWindow.ui

RESOURCES += \
    Resources/resources.qrc
