#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <random>
#include <QTimer>
#include <memory>
#include <time.h>
#include <iostream>
#include <QCloseEvent>
#include "startscreen.h"

class StartScreen;

/**
@class MainWindow
@brief This class creates the board and handles the cells/antigens/user of the game.

In this class, a maximum of three single/double antigen cells can be created. The board is
10x10 and the user starts out with three lives. Difficulty level is passed through the constructor,
and 0 = beginner whereas 4 = expert.

*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void updateCells();
    void randPlaceAntigens();
    void startNewGame();
    void startEasy();
    void startMedium();
    void startHard();
    void startExpert();

public:
    MainWindow(int tempDiff, int tempCounter, int tempLives);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *e);
    void updateKiller(int px, int py, int nx, int ny);

    void gameOver();
    void gameWin();
    bool win();
    void placeAntigens(int cellNumber, int cellAnt2);

private:

    bool ant1LastUpdated;

    int counter;

    QLabel* oneKilled;
    QLabel* twoKilled;
    QLabel* threeKilled;

    bool cellOneDead;
    bool cellTwoDead;
    bool cellThreeDead;
    //difficulty 0 = beginner, 4 = difficult
    int difficulty;

    //cell images
    QPixmap* killerImage;
    QPixmap* oneCellImage;
    QPixmap* twoCellImage;
    QPixmap* threeCellImage;

    //cell antigen images
    QPixmap* cellOneAnt1Image;
    QPixmap* cellOneAnt2Image;
    QPixmap* cellTwoAnt1Image;
    QPixmap* cellTwoAnt2Image;
    QPixmap* cellThreeAnt1Image;
    QPixmap* cellThreeAnt2Image;

    QPixmap* cellOneAntDisplayed;
    int cellOneAntDis;
    QPixmap* cellTwoAntDisplayed;
    int cellTwoAntDis;
    QPixmap* cellThreeAntDisplayed;
    int cellThreeAntDis;

    //item positions
    QPoint* killerPosition;
    QPoint* CellPositions; //just b/c 5 listed here doesnt mean all will be used
    QPoint* antigenPositions;

    //Cell Antigens (up to three cells on field at time)
    //absent antigens are represented by -1
    int cellOneAnt1; //ants are 0-2 0 = red, 1 = blue, 2 = yellow
    int cellOneAnt2;
    int cellTwoAnt1;
    int cellTwoAnt2;
    int cellThreeAnt1;
    int cellThreeAnt2;

    size_t numberCells;

    // Top bar variables
    int antigen1;
    int antigen2;
    QLabel* antigen1Label;
    QLabel* antigen2Label; //can hold up to two antigens

    QWidget* top;
    unsigned int livesLeft;
    QLabel** lives; //creates array

    // Board Variables
    QWidget* board;
    int boardSize;
    QLabel** labels; //creates array




};

#endif // MAINWINDOW_H
