#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "startscreen.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);



    StartScreen s;
    
    srand(time(NULL));


    //MainWindow w;
    //w.show();

    return a.exec();
}
