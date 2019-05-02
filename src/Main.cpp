/*
Copyright (c) 2019 Inverse Palindrome
Chess - Main.cpp
https://inversepalindrome.com/
*/


#include "MainWindow.hpp"

#include <QTimer>
#include <QApplication>
#include <QSplashScreen>


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    auto* splashScreen = new QSplashScreen(QPixmap(":/Resources/InversePalindromeLogo.jpg"), Qt::WindowStaysOnTopHint);
    splashScreen->show();

    MainWindow mainWindow;
    mainWindow.setWindowTitle("Chess");
    mainWindow.setFixedSize(1600, 1600);

    const auto SPLASH_TIME = 2000;

    QTimer::singleShot(SPLASH_TIME, splashScreen, SLOT(close()));
    QTimer::singleShot(SPLASH_TIME, &mainWindow, SLOT(show()));

    return a.exec();
}
