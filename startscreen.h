#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include <QCoreApplication>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "mainwindow.h"

class MainWindow;

/**
@class StartScreen
@brief This class creates a window that displays an instructions QPushButton, beginner through expert difficulty
settings (QRadioButtons), and a START QPushButton.

This class functions to serve as a way to connect the difficulty selection process to the desired MainWindow
difficulty setting.
*/
class StartScreen : public QWidget
{
    Q_OBJECT

public:
    StartScreen();


public slots:
    void setDifficulty();
    void createGame();
    void displayInstructions();

private:


    QLabel* welcome;
    QPushButton* instructions;
    QLabel* diffSelect;
    QRadioButton* beginner;
    QRadioButton* easy;
    QRadioButton* medium;
    QRadioButton* hard;
    QRadioButton* expert;
    QRadioButton* story;

    QPushButton* start;

    int difficulty;

    QPixmap* killerImage;
    QPixmap* singleAntExample;
    QPixmap* doubleAntExample;
    QPixmap* antExample;
    QPixmap* antExample2;


};

#endif // STARTSCREEN_H
