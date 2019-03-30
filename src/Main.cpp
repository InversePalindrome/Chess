/*
Copyright (c) 2019 Inverse Palindrome
Chess - Main.cpp
https://inversepalindrome.com/
*/


#include "ChessBoard.hpp"
#include "MainWindow.hpp"

#include <QTimer>
#include <QApplication>
#include <QSplashScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto* splashScreen = new QSplashScreen(QPixmap(":/Resources/InversePalindromeLogo.jpg"), Qt::WindowStaysOnTopHint);
    splashScreen->show();

    ChessBoard chessBoard;

    MainWindow mainWindow(chessBoard);
    mainWindow.setWindowTitle("Chess");
    mainWindow.setFixedSize(1600, 1600);

    auto const SPLASH_TIME = 2000;

    QTimer::singleShot(SPLASH_TIME, splashScreen, SLOT(close()));
    QTimer::singleShot(SPLASH_TIME, &mainWindow, SLOT(show()));

    return a.exec();
}
