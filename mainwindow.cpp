#include "mainwindow.h"


/**
This MainWindow constructor creates a game with with the inputted difficulty setting.
Most of the private variables declared in the class are defined here, as well as the timers
that indicate when SLOT functions are called. The images for the objects used are
set up in this constructor.

@param tempDiff is the difficulty being passed to the game
@param tempCounter is used to specify difficulty in story mode
@param tempLives is the lives left which can change between story mode levels
*/
MainWindow::MainWindow(int tempDiff, int tempCounter, int tempLives) :
    difficulty(tempDiff), counter(tempCounter), livesLeft(tempLives)
{


    if (difficulty == 0)
    {
        cellOneDead = false;
        cellTwoDead = true;
        cellThreeDead = true;
        this->setWindowTitle("Beginner");
    }
    else if (difficulty == 1 || difficulty == 2)
    {
        if (difficulty == 1)
            this->setWindowTitle("Easy");
        if (difficulty == 2)
            this->setWindowTitle("Medium");
        cellOneDead = false;
        cellTwoDead = false;
        cellThreeDead = true;
    }
    else if (difficulty == 3 || difficulty == 4)
    {
        if (difficulty == 3)
            this->setWindowTitle("Hard");
        if (difficulty == 4)
            this->setWindowTitle("Expert");
        cellOneDead = false;
        cellTwoDead = false;
        cellThreeDead = false;
    }
    else //difficulty == 5
    {
        if (counter == 0)
        {
            cellOneDead = false;
            cellTwoDead = true;
            cellThreeDead = true;
            this->setWindowTitle("Beginner");
        }
        else if (counter == 1 || counter == 2)
        {

            if (counter == 1)
            {
                this->setWindowTitle("Easy");
            }
            if (counter == 2)
            {
                this->setWindowTitle("Medium");
            }
            cellOneDead = false;
            cellTwoDead = false;
            cellThreeDead = true;
        }
        else if (counter == 3 || counter == 4)
        {
            if (counter == 3)
            {
                this->setWindowTitle("Hard");
            }
            if (counter == 4)
            {
                this->setWindowTitle("Expert");
            }
            cellOneDead = false;
            cellTwoDead = false;
            cellThreeDead = false;
        }
    }



    boardSize = 10;

    //create bottom bar that will hold enemies killed
    QHBoxLayout *bottomBar = new QHBoxLayout;

    QLabel* txt = new QLabel("Cells killed:");
    oneKilled = new QLabel;
    oneKilled->setScaledContents(true);
    oneKilled->setFixedSize(50,50);
    twoKilled = new QLabel;
    twoKilled->setScaledContents(true);
    twoKilled->setFixedSize(50,50);
    threeKilled = new QLabel;
    threeKilled->setScaledContents(true);
    threeKilled->setFixedSize(50,50);

    bottomBar->addWidget(txt,Qt::AlignLeft);
    bottomBar->addWidget(oneKilled,Qt::AlignLeft);
    bottomBar->addWidget(twoKilled,Qt::AlignLeft);
    bottomBar->addWidget(threeKilled,Qt::AlignLeft);



    top = new QWidget;
    top->setStyleSheet("QLabel { background-color : black; color : white; }");

    QHBoxLayout *topBar = new QHBoxLayout(top);



    //make image file here

    QString killer("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\T.jpg");
    killerImage = new QPixmap(killer);


    lives = new QLabel*[livesLeft]; //creates array of QLabel Pointers


    QLabel* livesText = new QLabel("Lives:");
    livesText->setFixedSize(40,40);
    topBar->addWidget(livesText);

    // Set the labels to have KillerT image, add to the top bar layout.
    for(size_t i=0;i<livesLeft;i++)
    {
        lives[i] = new QLabel;
        lives[i]->setStyleSheet("QLabel { background-color : black; color : white; }");
        lives[i]->setPixmap(*killerImage);
        lives[i]->setMinimumSize(40,40);
        lives[i]->setMaximumSize(40,40);
        lives[i]->setScaledContents(true);
        topBar->addWidget(lives[i]);
    }


    // Add space
    QSpacerItem* spacer = new QSpacerItem(100,10);

    topBar->addSpacerItem(spacer);


    QLabel* antigensHave = new QLabel("Antigens: ");
    antigensHave->setFixedSize(40,40);
    antigen1Label = new QLabel(); //start with no antigens
    antigen2Label = new QLabel();
    antigen1Label->setFixedSize(40,40);
    antigen2Label->setFixedSize(40,40);
    antigen1 = -1;
    antigen2 = -1;

    topBar->addWidget(antigensHave);
    topBar->addWidget(antigen1Label);
    topBar->addWidget(antigen2Label);


    // This code Creates the Board
    board = new QWidget;
    labels = new QLabel*[boardSize*boardSize]; //creates array
    QGridLayout *grid = new QGridLayout(board);

    grid->setGeometry(QRect());
    grid->setSpacing(0);

    // Create each label for the board
    for(int i=0;i<boardSize;i++)
    {
        for(int j=0;j<boardSize;j++)
        {

            // Create label and set properties.
            labels[i*boardSize+j] = new QLabel;
            labels[i*boardSize+j]->setFixedSize(40,40);
            labels[i*boardSize+j]->setStyleSheet("QLabel { background-color : black; color : white; }");
            labels[i*boardSize+j]->setFrameStyle(3);
            labels[i*boardSize+j]->setAlignment(Qt::AlignCenter);
            labels[i*boardSize+j]->setScaledContents(true);

            // Add label to the layout
            grid -> addWidget(labels[i*boardSize+j] ,i,j);

        }
    }

    // Initialize the killerT at the top left corner, coordinate (0,0).
    killerPosition = new QPoint(0,0);
    labels[0]->setPixmap(*killerImage);
    labels[0]->setScaledContents(true);

    board->setFixedSize(400,400);


    QWidget* window = new QWidget;

    setFixedSize(500,550);

    QVBoxLayout *vLayout = new QVBoxLayout;

    vLayout->addWidget(top,Qt::AlignCenter);
    vLayout->addWidget(board,0,Qt::AlignCenter);
    vLayout->addLayout(bottomBar,Qt::AlignCenter);

    window->setLayout(vLayout);
    //window->setStyleSheet("QLabel { background-color : black; color : white; }");

    setCentralWidget(window);


    //depending on difficulty create different # and types of infected cells

    antigenPositions = new QPoint[6]; //since each cell can have two antigens
    antigenPositions[0].setX(-1);
    antigenPositions[0].setY(-1);
    antigenPositions[1].setX(-1);
    antigenPositions[1].setY(-1);
    antigenPositions[2].setX(-1);
    antigenPositions[2].setY(-1);
    antigenPositions[3].setX(-1);
    antigenPositions[3].setY(-1);
    antigenPositions[4].setX(-1);
    antigenPositions[4].setY(-1);
    antigenPositions[5].setX(-1);
    antigenPositions[5].setY(-1);
    antigenPositions[6].setX(-1);
    antigenPositions[6].setY(-1);

    if (difficulty == 0 || counter == 0)
    {

        numberCells = 1;
        CellPositions = new QPoint[numberCells];
        antigenPositions = new QPoint[2*numberCells];
        antigenPositions[0].setX(-1);
        antigenPositions[0].setY(-1);


        cellOneAnt1 = rand()%3;
        cellOneAnt2 = -1; //negative means not present
        cellTwoAnt1 = -1;
        cellTwoAnt2 = -1;
        cellThreeAnt1 = -1;
        cellThreeAnt2 = -1;



        //set infected cell on other half of board
        CellPositions[0].setX(rand()%(boardSize/2-1) + boardSize/2);
        CellPositions[0].setY(rand()%(boardSize/2-1) + boardSize/2);
    }
    else if (difficulty == 1 || counter == 1)
    {

        numberCells = 2;
        CellPositions = new QPoint[numberCells];
        antigenPositions = new QPoint[2*numberCells];

        antigenPositions[0].setX(-1);
        antigenPositions[0].setY(-1);
        antigenPositions[1].setX(-1);
        antigenPositions[1].setY(-1);

        cellOneAnt1 = rand()%3;
        cellOneAnt2 = -1; //negative means not present
        cellTwoAnt1 = rand()%3; //dont want repeat single antigen
        while (cellOneAnt1 == cellTwoAnt1)
            cellTwoAnt1 = rand()%3;

        cellTwoAnt2 = -1;
        cellThreeAnt1 = -1;
        cellThreeAnt2 = -1;

        //set infected cell on other half of board
        CellPositions[0].setX(rand()%(boardSize/2-1) + boardSize/2);
        CellPositions[0].setY(rand()%(boardSize/2-1) + boardSize/2);

        //make sure doesnt spawn on occupied space
        bool valid = false;


        while (!valid)
        {
            valid = true;
            int proposedX = rand()%(boardSize/2-1) + boardSize/2;
            int proposedY = rand()%(boardSize/2-1) + boardSize/2;
            for (size_t i = 0; i < numberCells; i++)
            {
                if (CellPositions[i].rx() == proposedX && CellPositions[i].ry() == proposedY)
                    valid = false;
            }
            if (valid)
            {
                CellPositions[1].setX(proposedX);
                CellPositions[1].setY(proposedY);
            }
        }
    }
    else if (difficulty == 2 || counter == 2)
    {

        numberCells = 2;
        CellPositions = new QPoint[numberCells];
        antigenPositions = new QPoint[2*numberCells];
        antigenPositions[0].setX(-1);
        antigenPositions[0].setY(-1);
        antigenPositions[1].setX(-1);
        antigenPositions[1].setY(-1);

        cellOneAnt1 = rand()%3;
        cellOneAnt2 = -1; //negative means not present

        cellTwoAnt1 = rand()%3; //dont want repeat single antigen
        while (cellOneAnt1 == cellTwoAnt1)
            cellTwoAnt1 = rand()%3;

        //dont want same antigen as first antigen
        cellTwoAnt2 = rand()%3;
        while (cellTwoAnt2 == cellTwoAnt1)
            cellTwoAnt2 = rand()%3;

        cellThreeAnt1 = -1;
        cellThreeAnt2 = -1;

        //set infected cell on other half of board
        CellPositions[0].setX(rand()%(boardSize/2-1) + boardSize/2);
        CellPositions[0].setY(rand()%(boardSize/2-1) + boardSize/2);

        //make sure doesnt spawn on occupied space
        bool valid = false;


        while (!valid)
        {
            valid = true;
            int proposedX = rand()%(boardSize/2-1) + boardSize/2;
            int proposedY = rand()%(boardSize/2-1) + boardSize/2;
            for (size_t i = 0; i < numberCells; i++)
            {
                if (CellPositions[i].rx() == proposedX && CellPositions[i].ry() == proposedY)
                    valid = false;
            }
            if (valid)
            {
                CellPositions[1].setX(proposedX);
                CellPositions[1].setY(proposedY);
            }
        }
    }
    else if (difficulty == 3 || counter == 3)
    {
        numberCells = 3;
        CellPositions = new QPoint[numberCells];
        antigenPositions = new QPoint[2*numberCells];

        antigenPositions[0].setX(-1);
        antigenPositions[0].setY(-1);
        antigenPositions[1].setX(-1);
        antigenPositions[1].setY(-1);
        antigenPositions[2].setX(-1);
        antigenPositions[2].setY(-1);

        cellOneAnt1 = rand()%3;
        cellOneAnt2 = -1; //negative means not present

        cellTwoAnt1 = rand()%3; //dont want repeat single antigen
        while (cellOneAnt1 == cellTwoAnt1)
            cellTwoAnt1 = rand()%3;

        //dont want same antigen as first antigen
        cellTwoAnt2 = -1;

        cellThreeAnt1 = rand()%3;
        cellThreeAnt2 = rand()%3;

        //make sure antigens arent same
        while(cellThreeAnt2 == cellThreeAnt1)
            cellThreeAnt2 = rand()%3;

        while ((cellThreeAnt1 == cellTwoAnt1 && cellThreeAnt2 == cellTwoAnt2)
               || (cellThreeAnt1 == cellTwoAnt2 && cellThreeAnt2 == cellTwoAnt1))
        {
            cellThreeAnt1 = rand()%3;
            //make sure antigens arent same
            while(cellThreeAnt2 == cellThreeAnt1)
                cellThreeAnt2 = rand()%3;

        }

        //set infected cell on other half of board
        CellPositions[0].setX(rand()%(boardSize/2-1) + boardSize/2);
        CellPositions[0].setY(rand()%(boardSize/2-1) + boardSize/2);

        //make sure doesnt spawn on occupied space
        bool valid1 = false;
        bool valid2 = false;

        while (!valid1)
        {
            valid1 = true;
            int proposedX = rand()%(boardSize/2-1) + boardSize/2;
            int proposedY = rand()%(boardSize/2-1) + boardSize/2;
            for (size_t i = 0; i < numberCells; i++)
            {
                if (CellPositions[i].rx() == proposedX && CellPositions[i].ry() == proposedY)
                    valid1 = false;
            }
            if (valid1)
            {
                CellPositions[1].setX(proposedX);
                CellPositions[1].setY(proposedY);
            }
        }
        while (!valid2)
                {
                    valid2 = true;
                    int proposedX = rand()%(boardSize/2-1) + boardSize/2;
                    int proposedY = rand()%(boardSize/2-1) + boardSize/2;
                    for (size_t i = 0; i < numberCells; i++)
                    {
                        if (CellPositions[i].rx() == proposedX && CellPositions[i].ry() == proposedY)
                            valid2 = false;
                    }
                    if (valid2)
                    {
                        CellPositions[2].setX(proposedX);
                        CellPositions[2].setY(proposedY);
                    }
                }
    }
    else if (difficulty == 4 || counter == 4)
    {


        numberCells = 3;
        CellPositions = new QPoint[numberCells];
        antigenPositions = new QPoint[2*numberCells];

        antigenPositions[0].setX(-1);
        antigenPositions[0].setY(-1);
        antigenPositions[1].setX(-1);
        antigenPositions[1].setY(-1);
        antigenPositions[2].setX(-1);
        antigenPositions[2].setY(-1);

        cellOneAnt1 = rand()%3;
        cellOneAnt2 = -1; //negative means not present

        cellTwoAnt1 = rand()%3; //dont want repeat single antigen
        while (cellOneAnt1 == cellTwoAnt1)
            cellTwoAnt1 = rand()%3;

        //dont want same antigen as first antigen
        cellTwoAnt2 = rand()%3; //dont want repeat double antigen
        while (cellTwoAnt2 == cellTwoAnt1)
            cellTwoAnt2 = rand()%3;

        cellThreeAnt1 = rand()%3;
        cellThreeAnt2 = rand()%3;
        while(cellThreeAnt2 == cellThreeAnt1)
            cellThreeAnt2 = rand()%3;

        while ((cellThreeAnt1 == cellTwoAnt1 && cellThreeAnt2 == cellTwoAnt2)
             || (cellThreeAnt1 == cellTwoAnt2 && cellThreeAnt2 == cellTwoAnt1))
        {
            while(cellThreeAnt2 == cellThreeAnt1)
                cellThreeAnt2 = rand()%3;
        }


        //set infected cell on other half of board
        CellPositions[0].setX(rand()%(boardSize/2-1) + boardSize/2);
        CellPositions[0].setY(rand()%(boardSize/2-1) + boardSize/2);

        //make sure doesnt spawn on occupied space
        bool valid1 = false;
        bool valid2 = false;

        while (!valid1)
        {
            valid1 = true;
            int proposedX = rand()%(boardSize/2-1) + boardSize/2;
            int proposedY = rand()%(boardSize/2-1) + boardSize/2;
            for (size_t i = 0; i < numberCells; i++)
            {
                if (CellPositions[i].rx() == proposedX && CellPositions[i].ry() == proposedY)
                    valid1 = false;
            }
            if (valid1)
            {
                CellPositions[1].setX(proposedX);
                CellPositions[1].setY(proposedY);
            }
        }
        while (!valid2)
        {
             valid2 = true;
             int proposedX = rand()%(boardSize/2-1) + boardSize/2;
             int proposedY = rand()%(boardSize/2-1) + boardSize/2;
             for (size_t i = 0; i < numberCells; i++)
             {
                if (CellPositions[i].rx() == proposedX && CellPositions[i].ry() == proposedY)
                     valid2 = false;
             }
             if (valid2)
             {
                 CellPositions[2].setX(proposedX);
                 CellPositions[2].setY(proposedY);
             }
        }

    }

    if ((cellOneAnt1 == 0 && cellOneAnt2 == -1)||(cellOneAnt1 == -1 && cellOneAnt2 == 0))
    {
        QString redCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\red.png");
        oneCellImage = new QPixmap(redCell);
        QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
        cellOneAnt1Image = new QPixmap (redAnt);

    }
    else if ((cellOneAnt1 == 1 && cellOneAnt2 == -1)||(cellOneAnt1 == -1 && cellOneAnt2 == 1))
    {
        QString blueCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blue.png");
        oneCellImage = new QPixmap(blueCell);
        QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
        cellOneAnt1Image = new QPixmap (blueAnt);


    }
    else if ((cellOneAnt1 == 2 && cellOneAnt2 == -1)||(cellOneAnt1 == -1 && cellOneAnt2 == 2))
    {
        QString yellowCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellow.png");
        oneCellImage = new QPixmap(yellowCell);
        QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
        cellOneAnt1Image = new QPixmap (yellowAnt);
    }
    else if ((cellOneAnt1 == 0 && cellOneAnt2 == 1)||(cellOneAnt1 == 1 && cellOneAnt2 == 0))
    {
        if (cellOneAnt1 == 0 && cellOneAnt2 == 1)
        {
            QString purpleCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\purple.png");
            oneCellImage = new QPixmap(purpleCell);
            QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
            cellOneAnt1Image = new QPixmap (redAnt);
            QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
            cellOneAnt2Image = new QPixmap (blueAnt);
        }
        else
        {
            QString purpleCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\purple.png");
            oneCellImage = new QPixmap(purpleCell);
            QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
            cellOneAnt2Image = new QPixmap (redAnt);
            QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
            cellOneAnt1Image = new QPixmap (blueAnt);
        }
    }
    else if ((cellOneAnt1 == 0 && cellOneAnt2 == 2)||(cellOneAnt1 == 2 && cellOneAnt2 == 0))
    {
        if (cellOneAnt1 == 0 && cellOneAnt2 == 2)
        {
            QString orangeCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\orange.png");
            oneCellImage = new QPixmap(orangeCell);
            QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
            cellOneAnt1Image = new QPixmap (redAnt);
            QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
            cellOneAnt2Image = new QPixmap (yellowAnt);
        }
        else
        {
            QString orangeCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\orange.png");
            oneCellImage = new QPixmap(orangeCell);
            QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
            cellOneAnt2Image = new QPixmap (redAnt);
            QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
            cellOneAnt1Image = new QPixmap (yellowAnt);
        }
    }
    else if ((cellOneAnt1 == 1 && cellOneAnt2 == 2)||(cellOneAnt1 == 2 && cellOneAnt2 == 1))
    {
        if (cellOneAnt1 == 1 && cellOneAnt2 == 2)
        {
            QString greenCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\green.png");
            oneCellImage = new QPixmap(greenCell);
            QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
            cellOneAnt1Image = new QPixmap (blueAnt);
            QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
            cellOneAnt2Image = new QPixmap (yellowAnt);
        }
        else
        {
            QString greenCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\green.png");
            oneCellImage = new QPixmap(greenCell);
            QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
            cellOneAnt2Image = new QPixmap (blueAnt);
            QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
            cellOneAnt1Image = new QPixmap (yellowAnt);
        }
    }


    if ((cellTwoAnt1 == 0 && cellTwoAnt2 == -1)||(cellTwoAnt1 == -1 && cellTwoAnt2 == 0))
    {
        QString redCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\red.png");
        twoCellImage = new QPixmap(redCell);
        QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
        cellTwoAnt1Image = new QPixmap (redAnt);
    }
    else if ((cellTwoAnt1 == 1 && cellTwoAnt2 == -1)||(cellTwoAnt1 == -1 && cellTwoAnt2 == 1))
    {
        QString blueCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blue.png");
        twoCellImage = new QPixmap(blueCell);
        QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
        cellTwoAnt1Image = new QPixmap (blueAnt);
    }
    else if ((cellTwoAnt1 == 2 && cellTwoAnt2 == -1)||(cellTwoAnt1 == -1 && cellTwoAnt2 == 2))
    {
        QString yellowCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellow.png");
        twoCellImage = new QPixmap(yellowCell);
        QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
        cellTwoAnt1Image = new QPixmap (yellowAnt);
    }
    else if ((cellTwoAnt1 == 0 && cellTwoAnt2 == 1)||(cellTwoAnt1 == 1 && cellTwoAnt2 == 0))
    {
        if (cellTwoAnt1 == 0 && cellTwoAnt2 == 1)
        {
            QString purpleCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\purple.png");
            twoCellImage = new QPixmap(purpleCell);
            QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
            cellTwoAnt1Image = new QPixmap (redAnt);
            QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
            cellTwoAnt2Image = new QPixmap (blueAnt);
        }
        else
        {
            QString purpleCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\purple.png");
            twoCellImage = new QPixmap(purpleCell);
            QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
            cellTwoAnt2Image = new QPixmap (redAnt);
            QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
            cellTwoAnt1Image = new QPixmap (blueAnt);
        }
    }
    else if ((cellTwoAnt1 == 0 && cellTwoAnt2 == 2)||(cellTwoAnt1 == 2 && cellTwoAnt2 == 0))
    {
        if (cellTwoAnt1 == 0 && cellTwoAnt2 == 2)
        {
            QString orangeCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\orange.png");
            twoCellImage = new QPixmap(orangeCell);
            QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
            cellTwoAnt1Image = new QPixmap (redAnt);
            QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
            cellTwoAnt2Image = new QPixmap (yellowAnt);
        }
        else
        {
            QString orangeCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\orange.png");
            twoCellImage = new QPixmap(orangeCell);
            QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
            cellTwoAnt2Image = new QPixmap (redAnt);
            QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
            cellTwoAnt1Image = new QPixmap (yellowAnt);
        }
    }
    else if ((cellTwoAnt1 == 1 && cellTwoAnt2 == 2)||(cellTwoAnt1 == 2 && cellTwoAnt2 == 1))
    {
        if (cellTwoAnt1 == 1 && cellTwoAnt2 == 2)
        {
            QString greenCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\green.png");
            twoCellImage = new QPixmap(greenCell);
            QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
            cellTwoAnt1Image = new QPixmap (blueAnt);
            QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
            cellTwoAnt2Image = new QPixmap (yellowAnt);
        }
        else
        {
            QString greenCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\green.png");
            twoCellImage = new QPixmap(greenCell);
            QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
            cellTwoAnt2Image = new QPixmap (blueAnt);
            QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
            cellTwoAnt1Image = new QPixmap (yellowAnt);
        }
    }



    if ((cellThreeAnt1 == 0 && cellThreeAnt2 == -1)||(cellThreeAnt1 == -1 && cellThreeAnt2 == 0))
    {
        QString redCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\red.png");
        threeCellImage = new QPixmap(redCell);
        QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
        cellThreeAnt1Image = new QPixmap (redAnt);
    }
    else if ((cellThreeAnt1 == 1 && cellThreeAnt2 == -1)||(cellThreeAnt1 == -1 && cellThreeAnt2 == 1))
    {
        QString blueCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blue.png");
        threeCellImage = new QPixmap(blueCell);
        QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
        cellThreeAnt1Image = new QPixmap (blueAnt);
    }
    else if ((cellThreeAnt1 == 2 && cellThreeAnt2 == -1)||(cellThreeAnt1 == -1 && cellThreeAnt2 == 2))
    {

        QString yellowCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellow.png");
        threeCellImage = new QPixmap(yellowCell);
        QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
        cellThreeAnt1Image = new QPixmap (yellowAnt);

    }
    else if ((cellThreeAnt1 == 0 && cellThreeAnt2 == 1) ||(cellThreeAnt1 == 1 && cellThreeAnt2 == 0))
    {
        if (cellThreeAnt1 == 0 && cellThreeAnt2 == 1)
        {
            QString purpleCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\purple.png");
            threeCellImage = new QPixmap(purpleCell);
            QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
            cellThreeAnt1Image = new QPixmap (redAnt);
            QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
            cellThreeAnt2Image = new QPixmap (blueAnt);
        }
        else
        {
            QString purpleCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\purple.png");
            threeCellImage = new QPixmap(purpleCell);
            QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
            cellThreeAnt2Image = new QPixmap (redAnt);
            QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
            cellThreeAnt1Image = new QPixmap (blueAnt);
        }
    }
    else if ((cellThreeAnt1 == 0 && cellThreeAnt2 == 2) ||(cellThreeAnt1 == 2 && cellThreeAnt2 == 0))
    {
        if (cellThreeAnt1 == 0 && cellThreeAnt2 == 2)
        {
            QString orangeCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\orange.png");
            threeCellImage = new QPixmap(orangeCell);
            QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
            cellThreeAnt1Image = new QPixmap (redAnt);
            QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
            cellThreeAnt2Image = new QPixmap (yellowAnt);
        }
        else
        {
            QString orangeCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\orange.png");
            threeCellImage = new QPixmap(orangeCell);
            QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
            cellThreeAnt2Image = new QPixmap (redAnt);
            QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
            cellThreeAnt1Image = new QPixmap (yellowAnt);
        }
    }
    else if ((cellThreeAnt1 == 1 && cellThreeAnt2 == 2)||(cellThreeAnt1 == 2 && cellThreeAnt2 == 1))
    {
        if (cellThreeAnt1 == 1 && cellThreeAnt2 == 2)
        {
            QString greenCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\green.png");
            threeCellImage = new QPixmap(greenCell);
            QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
            cellThreeAnt1Image = new QPixmap (blueAnt);
            QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
            cellThreeAnt2Image = new QPixmap (yellowAnt);
        }
        else
        {
            QString greenCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\green.png");
            threeCellImage = new QPixmap(greenCell);
            QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
            cellThreeAnt2Image = new QPixmap (blueAnt);
            QString yellowAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\yellowAnt.jpg");
            cellThreeAnt1Image = new QPixmap (yellowAnt);
        }
    }

    QTimer* timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateCells()));
    timer->start(450);

    QTimer* antigenTimer = new QTimer(this);

    connect(antigenTimer,SIGNAL(timeout()),this,SLOT(randPlaceAntigens()));
    antigenTimer->start(3500);

}

/**
This MainWindow member function handles all key presses during the game.

@param event is the QKeyEvent
*/
void MainWindow::keyPressEvent(QKeyEvent *event)
{

    int x = killerPosition->rx();
    int y = killerPosition->ry();

    switch (event->key()) {
    case Qt::Key_Left:
        if(killerPosition->rx() != 0)
            updateKiller(x,y,x-1,y);

        break;
    case Qt::Key_Right:
        if(killerPosition->rx() != boardSize-1)
            updateKiller(x,y,x+1,y);

        break;
    case Qt::Key_Up:
        if(killerPosition->ry() != 0)
            updateKiller(x,y,x,y-1);

        break;
    case Qt::Key_Down:
        if(killerPosition->ry() != boardSize-1)
            updateKiller(x,y,x,y+1);

        break;


    default:
        QWidget::keyPressEvent(event);


    }

    //since killerT has new position, check to see if can kill and if can do so
    if (!cellOneDead)
    {
        if (CellPositions[0].rx() == killerPosition->rx() && CellPositions[0].ry() == killerPosition->ry())
        {
            //if single antigen cell
            if (cellOneAnt2 == -1 && cellOneAnt1 != -1)
            {
                //if user has right antigen
                if (cellOneAnt1 == antigen1 || cellOneAnt1 == antigen2)
                {
                    //kill cell (so move to unseen location
                    CellPositions[0].setX(-1);
                    CellPositions[0].setX(-1);

                    //only clear if on board...if y is -1 then so is x
                    if (antigenPositions[0].ry() != -1)//if one is -1 then both are
                        labels[antigenPositions[0].ry()*boardSize+antigenPositions[0].rx()]->clear();

                    antigenPositions[0].setX(-1);
                    antigenPositions[0].setY(-1);

                    cellOneDead = true;
                    oneKilled->setPixmap(*oneCellImage);
                }
                else
                {
                    if (livesLeft > 0)
                    {
                        lives[livesLeft-1]->clear();
                        livesLeft--;
                    }
                }
            }
            else //double ant cell
            {
                if ((cellOneAnt1 == antigen1 && cellOneAnt2 == antigen2) || (cellOneAnt1 == antigen2 && cellOneAnt2 == antigen1))
                {


                    //kill cell (so move to unseen location
                    CellPositions[0].setX(-1);
                    CellPositions[0].setY(-1);

                    //only clear if on board...if y is -1 then so is x
                    if (antigenPositions[0].ry() != -1)
                        labels[antigenPositions[0].ry()*boardSize+antigenPositions[0].rx()]->clear();

                    antigenPositions[0].setX(-1);
                    antigenPositions[0].setY(-1);
                    cellOneDead = true;
                    oneKilled->setPixmap(*oneCellImage);

                }
                else
                {
                    if (livesLeft > 0)
                    {
                        lives[livesLeft-1]->clear();
                        livesLeft--;
                    }
                }
            }
        }


    }
    if (!cellTwoDead)
    {
        if (CellPositions[1].rx() == killerPosition->rx() && CellPositions[1].ry() == killerPosition->ry())
        {
            //if single antigen cell
            if (cellTwoAnt2 == -1 && cellTwoAnt1 != -1)
            {
                //if user has right antigen
                if (cellTwoAnt1 == antigen1 || cellTwoAnt1 == antigen2)
                {
                    //kill cell (so move to unseen location
                    CellPositions[1].setX(-1);
                    CellPositions[1].setX(-1);

                    //only clear if on board...if y is -1 then so is x
                    if (antigenPositions[1].ry() != -1)
                        labels[antigenPositions[1].ry()*boardSize+antigenPositions[1].rx()]->clear();

                    antigenPositions[1].setX(-1);
                    antigenPositions[1].setY(-1);
                    cellTwoDead = true;
                    twoKilled->setPixmap(*twoCellImage);
                }
                else
                {
                    if (livesLeft > 0)
                    {
                        lives[livesLeft-1]->clear();
                        livesLeft--;
                    }
                }
            }
            else //double ant cell
            {
                if ((cellTwoAnt1 == antigen1 && cellTwoAnt2 == antigen2) || (cellTwoAnt1 == antigen2 && cellTwoAnt2 == antigen1))
                {


                    //kill cell (so move to unseen location
                    CellPositions[1].setX(-1);
                    CellPositions[1].setY(-1);

                    //only clear if on board...if y is -1 then so is x
                    if (antigenPositions[1].ry() != -1)
                        labels[antigenPositions[1].ry()*boardSize+antigenPositions[1].rx()]->clear();

                    antigenPositions[1].setX(-1);
                    antigenPositions[1].setY(-1);
                    cellTwoDead = true;
                    twoKilled->setPixmap(*twoCellImage);

                }
                else
                {
                    if (livesLeft > 0)
                    {
                        lives[livesLeft-1]->clear();
                        livesLeft--;
                    }
                }
            }
        }


    }
    if (!cellThreeDead)
    {
        if (CellPositions[2].rx() == killerPosition->rx() && CellPositions[2].ry() == killerPosition->ry())
        {
            //if single antigen cell
            if (cellThreeAnt2 == -1 && cellThreeAnt1 != -1)
            {
                //if user has right antigen
                if (cellThreeAnt1 == antigen1 || cellThreeAnt1 == antigen2)
                {
                    //kill cell (so move to unseen location
                    CellPositions[2].setX(-1);
                    CellPositions[2].setX(-1);

                    //only clear if on board...if y is -1 then so is x
                    if (antigenPositions[2].ry() != -1)
                        labels[antigenPositions[2].ry()*boardSize+antigenPositions[2].rx()]->clear();

                    antigenPositions[2].setX(-1);
                    antigenPositions[2].setY(-1);
                    cellThreeDead = true;
                    threeKilled->setPixmap(*threeCellImage);
                }
                else
                {
                    if (livesLeft > 0)
                    {
                        lives[livesLeft-1]->clear();
                        livesLeft--;
                    }
                }
            }
            else //double ant cell
            {
                if ((cellThreeAnt1 == antigen1 && cellThreeAnt2 == antigen2) || (cellThreeAnt1 == antigen2 && cellThreeAnt2 == antigen1))
                {


                    //kill cell (so move to unseen location
                    CellPositions[2].setX(-1);
                    CellPositions[2].setY(-1);

                    //only clear if on board...if y is -1 then so is x
                    if (antigenPositions[2].ry() != -1)
                        labels[antigenPositions[2].ry()*boardSize+antigenPositions[2].rx()]->clear();

                    antigenPositions[2].setX(-1);
                    antigenPositions[2].setY(-1);
                    cellThreeDead = true;
                    threeKilled->setPixmap(*threeCellImage);

                }
                else
                {
                    if (livesLeft > 0)
                    {
                        lives[livesLeft-1]->clear();
                        livesLeft--;
                    }
                }
            }
        }


    }



    //want to add antigens picked up to bar
    if (numberCells == 1)
    {
        int kx = killerPosition->rx();
        int ky = killerPosition->ry();
        int ax1 = antigenPositions[0].rx();
        int ay1 = antigenPositions[0].ry();

        //antigen should disappear when land on
        if (ax1 == kx && ay1 == ky)
        {

            antigenPositions[0].setX(-1);
            antigenPositions[0].setY(-1);
            //first time put antigen in first position
            if (antigen1 == -1 && antigen2 == -1)
            {
                antigen1Label->setPixmap(*cellOneAntDisplayed);
                antigen1Label->setScaledContents(true);
                antigen1 = cellOneAntDis;
                ant1LastUpdated = true;
            }
            else if (ant1LastUpdated)
            {
                if (antigen1 != cellOneAntDis)
                {
                    antigen2Label->setPixmap(*cellOneAntDisplayed);
                    antigen2Label->setScaledContents(true);
                    antigen2 = cellOneAntDis;
                    ant1LastUpdated = false;
                }
            }
            else
            {
                if (antigen2 != cellOneAntDis)
                {
                    antigen1Label->setPixmap(*cellOneAntDisplayed);
                    antigen1Label->setScaledContents(true);
                    antigen1 = cellOneAntDis;
                    ant1LastUpdated = true;
                }
            }
        }
    }
    else if (numberCells == 2)
    {
        int kx = killerPosition->rx();
        int ky = killerPosition->ry();
        int ax1 = antigenPositions[0].rx();
        int ay1 = antigenPositions[0].ry();
        int ax2 = antigenPositions[1].rx();
        int ay2 = antigenPositions[1].ry();


        if (ax1 == kx && ay1 == ky)
        {

            antigenPositions[0].setX(-1);
            antigenPositions[0].setY(-1);
            //first time put antigen in first position
            if (antigen1 == -1 && antigen2 == -1)
            {
                antigen1Label->setPixmap(*cellOneAntDisplayed);
                antigen1Label->setScaledContents(true);
                antigen1 = cellOneAntDis;
                ant1LastUpdated = true;
            }
            else if (ant1LastUpdated)
            {
                if (antigen1 != cellOneAntDis && antigen2 != cellOneAntDis)
                {
                    antigen2Label->setPixmap(*cellOneAntDisplayed);
                    antigen2Label->setScaledContents(true);
                    antigen2 = cellOneAntDis;
                    ant1LastUpdated = false;
                }
            }
            else
            {
                if (antigen1 != cellOneAntDis && antigen2 != cellOneAntDis)
                {
                    antigen1Label->setPixmap(*cellOneAntDisplayed);
                    antigen1Label->setScaledContents(true);
                    antigen1 = cellOneAntDis;
                    ant1LastUpdated = true;
                }
            }
        }
        if (ax2 == kx && ay2 == ky)
        {

            antigenPositions[1].setX(-1);
            antigenPositions[1].setY(-1);
            //first time put antigen in first position
            if (antigen1 == -1 && antigen2 == -1)
            {
                antigen1Label->setPixmap(*cellTwoAntDisplayed);
                antigen1Label->setScaledContents(true);
                antigen1 = cellTwoAntDis;
                ant1LastUpdated = true;
            }
            else if (ant1LastUpdated)
            {
                if (antigen1 != cellTwoAntDis && antigen2 != cellTwoAntDis)
                {
                    antigen2Label->setPixmap(*cellTwoAntDisplayed);
                    antigen2Label->setScaledContents(true);
                    antigen2 = cellTwoAntDis;
                    ant1LastUpdated = false;
                }
            }
            else
            {
                if (antigen1 != cellTwoAntDis && antigen2 != cellTwoAntDis)
                {
                    antigen1Label->setPixmap(*cellTwoAntDisplayed);
                    antigen1Label->setScaledContents(true);
                    antigen1 = cellTwoAntDis;
                    ant1LastUpdated = true;
                }
            }
        }

    }
    else if (numberCells == 3)
    {
        int kx = killerPosition->rx();
        int ky = killerPosition->ry();
        int ax1 = antigenPositions[0].rx();
        int ay1 = antigenPositions[0].ry();
        int ax2 = antigenPositions[1].rx();
        int ay2 = antigenPositions[1].ry();
        int ax3 = antigenPositions[2].rx();
        int ay3 = antigenPositions[2].ry();


        if (ax1 == kx && ay1 == ky)
        {

            antigenPositions[0].setX(-1);
            antigenPositions[0].setY(-1);
            //first time put antigen in first position
            if (antigen1 == -1 && antigen2 == -1)
            {
                antigen1Label->setPixmap(*cellOneAntDisplayed);
                antigen1Label->setScaledContents(true);
                antigen1 = cellOneAntDis;
                ant1LastUpdated = true;
            }
            else if (ant1LastUpdated)
            {
                if (antigen1 != cellOneAntDis && antigen2 != cellOneAntDis)
                {
                    antigen2Label->setPixmap(*cellOneAntDisplayed);
                    antigen2Label->setScaledContents(true);
                    antigen2 = cellOneAntDis;
                    ant1LastUpdated = false;
                }
            }
            else
            {
                if (antigen1 != cellOneAntDis && antigen2 != cellOneAntDis)
                {
                    antigen1Label->setPixmap(*cellOneAntDisplayed);
                    antigen1Label->setScaledContents(true);
                    antigen1 = cellOneAntDis;
                    ant1LastUpdated = true;
                }
            }
        }
        if (ax2 == kx && ay2 == ky)
        {

            antigenPositions[1].setX(-1);
            antigenPositions[1].setY(-1);
            //first time put antigen in first position
            if (antigen1 == -1 && antigen2 == -1)
            {
                antigen1Label->setPixmap(*cellTwoAntDisplayed);
                antigen1Label->setScaledContents(true);
                antigen1 = cellTwoAntDis;
                ant1LastUpdated = true;
            }
            else if (ant1LastUpdated)
            {
                if (antigen1 != cellTwoAntDis && antigen2 != cellTwoAntDis)
                {
                    antigen2Label->setPixmap(*cellTwoAntDisplayed);
                    antigen2Label->setScaledContents(true);
                    antigen2 = cellTwoAntDis;
                    ant1LastUpdated = false;
                }
            }
            else
            {
                if (antigen1 != cellTwoAntDis && antigen2 != cellTwoAntDis)
                {
                    antigen1Label->setPixmap(*cellTwoAntDisplayed);
                    antigen1Label->setScaledContents(true);
                    antigen1 = cellTwoAntDis;
                    ant1LastUpdated = true;
                }
            }
        }
        if (ax3 == kx && ay3 == ky)
        {

            antigenPositions[2].setX(-1);
            antigenPositions[2].setY(-1);
            //first time put antigen in first position
            if (antigen1 == -1 && antigen2 == -1)
            {
                antigen1Label->setPixmap(*cellThreeAntDisplayed);
                antigen1Label->setScaledContents(true);
                antigen1 = cellThreeAntDis;
                ant1LastUpdated = true;
            }
            else if (ant1LastUpdated)
            {
                if (antigen1 != cellThreeAntDis && antigen2 != cellThreeAntDis)
                {
                    antigen2Label->setPixmap(*cellThreeAntDisplayed);
                    antigen2Label->setScaledContents(true);
                    antigen2 = cellThreeAntDis;
                    ant1LastUpdated = false;
                }
            }
            else
            {
                if (antigen1 != cellThreeAntDis && antigen2 != cellThreeAntDis)
                {
                    antigen1Label->setPixmap(*cellThreeAntDisplayed);
                    antigen1Label->setScaledContents(true);
                    antigen1 = cellThreeAntDis;
                    ant1LastUpdated = true;
                }
            }
        }

    }


    //end game if cells are dead or you are dead


    if (this->win())
    {
        this->gameWin();
    }
    if (livesLeft <= 0)
        this->gameOver();


    QCoreApplication::processEvents();
    repaint();
}

/**
This MainWindow member function repaints all cells and antigens whenever called.

@param e is an unused QPaintEvent object required to overload the paint event handler
*/
void MainWindow::paintEvent(QPaintEvent *e)
{
    int x = killerPosition->rx();
    int y = killerPosition->ry();

    //redisplay cells
    if (numberCells == 1)
    {

        if (antigenPositions[0].rx() >= 0 && antigenPositions[0].rx() < boardSize)
        {
            if (x != antigenPositions[0].rx() && y != antigenPositions[0].ry())
                labels[antigenPositions[0].ry()*boardSize+antigenPositions[0].rx()]->setPixmap(*cellOneAntDisplayed);
        }

        if (cellOneDead)
        {
            //do nothing
        }
        else
        {
            int x1 = CellPositions[0].rx();
            int y1 = CellPositions[0].ry();

            labels[y1*boardSize + x1]->setPixmap(*oneCellImage);
        }

    }
    else if (numberCells == 2)
    {
        if (antigenPositions[0].rx() >= 0 && antigenPositions[0].rx() < boardSize)
        {
            if (x != antigenPositions[0].rx() && y != antigenPositions[0].ry())
                labels[antigenPositions[0].ry()*boardSize+antigenPositions[0].rx()]->setPixmap(*cellOneAntDisplayed);
        }
        if (antigenPositions[1].rx() >= 0 && antigenPositions[1].rx() < boardSize)
        {
            if (x != antigenPositions[1].rx() && y != antigenPositions[1].ry())
                labels[antigenPositions[1].ry()*boardSize+antigenPositions[1].rx()]->setPixmap(*cellTwoAntDisplayed);
        }

        if (cellOneDead)
        {
            //do nothing
        }
        else
        {
            int x1 = CellPositions[0].rx();
            int y1 = CellPositions[0].ry();

            labels[y1*boardSize + x1]->setPixmap(*oneCellImage);
        }

        if (cellTwoDead)
        {
            //do nothing
        }
        else
        {
            int x1 = CellPositions[1].rx();
            int y1 = CellPositions[1].ry();

            labels[y1*boardSize + x1]->setPixmap(*twoCellImage);
        }

    }
    else if (numberCells == 3)
    {

        if (antigenPositions[0].rx() >= 0 && antigenPositions[0].rx() < boardSize)
        {
            if (x != antigenPositions[0].rx() && y != antigenPositions[0].ry())
                labels[antigenPositions[0].ry()*boardSize+antigenPositions[0].rx()]->setPixmap(*cellOneAntDisplayed);
        }
        if (antigenPositions[1].rx() >= 0 && antigenPositions[1].rx() < boardSize)
        {
            if (x != antigenPositions[1].rx() && y != antigenPositions[1].ry())
                labels[antigenPositions[1].ry()*boardSize+antigenPositions[1].rx()]->setPixmap(*cellTwoAntDisplayed);
        }
        if (antigenPositions[2].rx() >= 0 && antigenPositions[2].rx() < boardSize)
        {
            if (x != antigenPositions[2].rx() && y != antigenPositions[2].ry())
                labels[antigenPositions[2].ry()*boardSize+antigenPositions[2].rx()]->setPixmap(*cellThreeAntDisplayed);
        }
        if (cellOneDead)
        {
            //do nothing
        }
        else
        {
            int x1 = CellPositions[0].rx();
            int y1 = CellPositions[0].ry();

            labels[y1*boardSize + x1]->setPixmap(*oneCellImage);
        }

        if (cellTwoDead)
        {
            //do nothing
        }
        else
        {
            int x1 = CellPositions[1].rx();
            int y1 = CellPositions[1].ry();

            labels[y1*boardSize + x1]->setPixmap(*twoCellImage);
        }

        if (cellThreeDead)
        {
            //do nothing
        }
        else
        {
            int x1 = CellPositions[2].rx();
            int y1 = CellPositions[2].ry();

            labels[y1*boardSize + x1]->setPixmap(*threeCellImage);
        }

    }


    //put after b/c want to show user over cell if on same space
    labels[y*boardSize+x]->setPixmap(*killerImage);
    labels[y*boardSize+x]->setScaledContents(true);




}

/**
This MainWindow member function updates the positions of the user and is called during keyPressEvent

@param px is the previous x-coordinate of the user
@param py is the previous y-coordinate of the user
@param nx is the new x-coordinate of the user
@param ny is the new y-coordinate of the user
*/
void MainWindow::updateKiller(int px, int py, int nx, int ny)
{
    labels[py*boardSize+px]->clear();

    //the paint event is later in code that called updateKiller
    killerPosition->setX(nx);
    killerPosition->setY(ny);
}


/**
This MainWindow SLOT updates the position of all live cells on the board each time the timer defined in the constructor
gets called.
*/
void MainWindow::updateCells()
{

    int lastRow = boardSize - 1;
    int lastColumn = lastRow; //since square

    int x1 = -1, y1 = -1;
    int x2 = -1, y2 = -1;
    int x3 = -1, y3 = -1;


    //killer position
    int kx = killerPosition->rx();
    int ky = killerPosition->ry();


    if (numberCells == 1)
    {
        //old position
        x1 = CellPositions[0].rx();
        y1 = CellPositions[0].ry();
    }
    else if (numberCells == 2)
    {
        //old positions
        x1 = CellPositions[0].rx();
        y1 = CellPositions[0].ry();
        x2 = CellPositions[1].rx();
        y2 = CellPositions[1].ry();
    }
    else if (numberCells == 3)
    {
        //old positions
        x1 = CellPositions[0].rx();
        y1 = CellPositions[0].ry();
        x2 = CellPositions[1].rx();
        y2 = CellPositions[1].ry();
        x3 = CellPositions[2].rx();
        y3 = CellPositions[2].ry();
    }

    //new positions
    int nx1 = x1;
    int ny1 = y1;
    int nx2 = x2;
    int ny2 = y2;
    int nx3 = x3;
    int ny3 = y3;

    if (livesLeft > 0)
    {

        //with oneCell (can be single ant or double ant)
        if (numberCells == 1)
        {
            if (!cellOneDead) //only move if alive
            {

                //if single antigen cell
                if (cellOneAnt2 == -1 && cellOneAnt1 != -1)
                {

                    //want to go away if have right ant(s)
                    if (cellOneAnt1 == antigen1 || cellOneAnt1 == antigen2)
                    {
                        //cell can be above, al, ar, r, l, b, bl, br

                        //cell above
                        if (y1 == ky && kx > x1)
                        {
                            if (x1 != 0)//move up if not in first row
                                nx1 = x1 - 1;
                            else //if in first row
                            {
                                if (y1 == 0) //if in first row and first column
                                    ny1 = y1 + 1;
                                else if (y1 == lastColumn)
                                    ny1 = y1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        ny1 = y1 + 1;
                                    else
                                        ny1 = y1 - 1;
                                }

                            }
                        }

                        //cell above-left
                        if (y1 < ky && kx > x1)
                        {

                            if (x1 != 0 && y1 != 0) //if not in first row and not in first colum
                            {
                                //randomly move up or left
                                int randNum = rand()%2;

                                if (randNum == 0)//move up
                                    nx1 = x1 - 1;
                                else //move left
                                    ny1 = y1 - 1;

                            }
                            else if (x1 == 0 && y1 != 0) //if in first row but not in first column
                                ny1 = y1 - 1;
                            else if (x1 != 0 && y1 == 0) //if in first colum  but not in first row
                                nx1 = x1 - 1;
                            else //in top left corner///move right or down
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny1 = y1 + 1;
                                else
                                    nx1 = x1 + 1;

                            }

                        }

                        //cell above-right
                        if (y1 > ky && kx > x1)
                        {
                            if (x1 != 0 && y1 != lastColumn) //if not in first row and not in last column
                            {
                                //randomly move up or right
                                int randNum = rand()%2;

                                if (randNum == 0)//move up
                                    nx1 = x1 - 1;
                                else //move right
                                    ny1 = y1 + 1;

                            }
                            else if (x1 == 0 && y1 != lastColumn) //if in first row but not in last column
                                ny1 = y1 + 1;
                            else if (x1 != 0 && y1 == lastColumn) //if in last column  but not in first row
                                nx1 = x1 - 1;
                            else //in top right corner///move right or down
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny1 = y1 - 1;
                                else
                                    nx1 = x1 + 1;

                            }


                        }

                        //cell right
                        if (y1 > ky && kx == x1)
                        {
                            if (y1 != lastColumn)
                                ny1 = y1 + 1;
                            else
                            {
                                if (x1 == 0)
                                    nx1 = x1 + 1;
                                else if (x1 == lastRow)
                                    nx1 = x1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        nx1 = x1 - 1;
                                    else
                                        nx1 = x1 + 1;
                                }
                            }
                        }

                        //cell below
                        if (y1 == ky && kx < x1)
                        {
                            if (x1 != lastRow)//move down if not in last row
                                nx1 = x1 + 1;
                            else //if in last row
                            {
                                if (y1 == 0) //if in last row and first column
                                    ny1 = y1 + 1;
                                else if (y1 == lastColumn)
                                    ny1 = y1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        ny1 = y1 + 1;
                                    else
                                        ny1 = y1 - 1;
                                }

                            }
                        }

                        //cell below-left
                        if (y1 < ky && kx < x1)
                        {
                            if (x1 != lastRow && y1 != 0) //if not in last row and not in first colum
                            {
                                //randomly move down or left
                                int randNum = rand()%2;

                                if (randNum == 0)//move down
                                    nx1 = x1 + 1;
                                else //move left
                                    ny1 = y1 - 1;

                            }
                            else if (x1 == lastRow && y1 != 0) //if in last row but not in first column
                                ny1 = y1 - 1;
                            else if (x1 != lastRow && y1 == 0) //if in first colum  but not in last row
                                nx1 = x1 + 1;
                            else //in bottom left//move right or up
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny1 = y1 + 1;
                                else
                                    nx1 = x1 - 1;

                            }


                        }

                        //cell below-right
                        if (y1 > ky && kx < x1)
                        {
                            if (x1 != lastColumn && y1 != lastColumn) //if not in last row and not in last column
                            {
                                //randomly move down or right
                                int randNum = rand()%2;

                                if (randNum == 0)//move down
                                    nx1 = x1 + 1;
                                else //move right
                                    ny1 = y1 + 1;

                            }
                            else if (x1 == lastColumn && y1 != lastColumn) //if in first row but not in last column
                                ny1 = y1 + 1;
                            else if (x1 != lastColumn && y1 == lastColumn) //if in last column  but not in first row
                                nx1 = x1 + 1;
                            else //in bottom right corner///move left or up
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny1 = y1 - 1;
                                else
                                    nx1 = x1 - 1;

                            }


                        }

                        //cell left
                        if (y1 < ky && kx == x1)
                        {
                            if (y1 != 0)
                                ny1 = y1 - 1;
                            else
                            {
                                if (x1 == 0)
                                    nx1 = x1 + 1;
                                else if (x1 == lastRow)
                                    nx1 = x1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        nx1 = x1 - 1;
                                    else
                                        nx1 = x1 + 1;
                                }
                            }
                        }

                    }
                    else
                    {
                        //want to move towards killer
                        //cell above
                        if (y1 == ky && kx > x1)
                            nx1 = x1 + 1; //move down toward killer

                        //cell above-left
                        if (y1 < ky && kx > x1)
                        {

                            //randomly move right or down
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 + 1;

                        }

                        //cell above-right
                        if (y1 > ky && kx > x1)
                        {
                            //randomly move left or down
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 - 1;


                        }

                        //cell right
                        if (y1 > ky && kx == x1)
                            ny1 = y1 - 1;

                        //cell below
                        if (y1 == ky && kx < x1)
                            nx1 = x1 - 1;


                        //cell below-left
                        if (y1 < ky && kx < x1)
                        {
                            //randomly move right or up
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 + 1;

                        }

                        //cell below-right
                        if (y1 > ky && kx < x1)
                        {
                            //randomly move left or up
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 - 1;
                        }

                        //cell left
                        if (y1 < ky && kx == x1)
                            ny1 = y1 + 1;


                    }
                }
                else //double antigen cell
                {

                    //want to go away if have right ant(s)
                    if ((cellOneAnt1 == antigen1 && cellOneAnt2 == antigen2)
                            ||(cellOneAnt1 == antigen2 && cellOneAnt2 == antigen1))
                    {
                        //cell can be above, al, ar, r, l, b, bl, br

                        //cell above
                        if (y1 == ky && kx > x1)
                        {
                            if (x1 != 0)//move up if not in first row
                                nx1 = x1 - 1;
                            else //if in first row
                            {
                                if (y1 == 0) //if in first row and first column
                                    ny1 = y1 + 1;
                                else if (y1 == lastColumn)
                                    ny1 = y1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        ny1 = y1 + 1;
                                    else
                                        ny1 = y1 - 1;
                                }

                            }
                        }

                        //cell above-left
                        if (y1 < ky && kx > x1)
                        {
                            if (x1 != 0 && y1 != 0) //if not in first row and not in first colum
                            {
                                //randomly move up or left
                                int randNum = rand()%2;

                                if (randNum == 0)//move up
                                    nx1 = x1 - 1;
                                else //move left
                                    ny1 = y1 - 1;

                            }
                            else if (x1 == 0 && y1 != 0) //if in first row but not in first column
                                ny1 = y1 - 1;
                            else if (x1 != 0 && y1 == 0) //if in first colum  but not in first row
                                nx1 = x1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 + 1;
                                else
                                    ny1 = y1 + 1;
                            }


                        }

                        //cell above-right
                        if (y1 > ky && kx > x1)
                        {
                            if (x1 != 0 && y1 != lastColumn) //if not in first row and not in last column
                            {
                                //randomly move up or right
                                int randNum = rand()%2;

                                if (randNum == 0)//move up
                                    nx1 = x1 - 1;
                                else //move right
                                    ny1 = y1 + 1;

                            }
                            else if (x1 == 0 && y1 != lastColumn) //if in first row but not in last column
                                ny1 = y1 + 1;
                            else if (x1 != 0 && y1 == lastColumn) //if in last column  but not in first row
                                nx1 = x1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 + 1;
                                else
                                    ny1 = y1 - 1;
                            }


                        }

                        //cell right
                        if (y1 > ky && kx == x1)
                        {
                            if (y1 != lastColumn)
                                ny1 = y1 + 1;
                            else
                            {
                                if (x1 == 0)
                                    nx1 = x1 + 1;
                                else if (x1 == lastRow)
                                    nx1 = x1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        nx1 = x1 - 1;
                                    else
                                        nx1 = x1 + 1;
                                }
                            }
                        }

                        //cell below
                        if (y1 == ky && kx < x1)
                        {
                            if (x1 != lastRow)//move down if not in last row
                                nx1 = x1 + 1;
                            else //if in last row
                            {
                                if (y1 == 0) //if in last row and first column
                                    ny1 = y1 + 1;
                                else if (y1 == lastColumn)
                                    ny1 = y1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        ny1 = y1 + 1;
                                    else
                                        ny1 = y1 - 1;
                                }

                            }
                        }

                        //cell below-left
                        if (y1 < ky && kx < x1)
                        {
                            if (x1 != lastRow && y1 != 0) //if not in last row and not in first colum
                            {
                                //randomly move down or left
                                int randNum = rand()%2;

                                if (randNum == 0)//move down
                                    nx1 = x1 + 1;
                                else //move left
                                    ny1 = y1 - 1;

                            }
                            else if (x1 == lastRow && y1 != 0) //if in last row but not in first column
                                ny1 = y1 - 1;
                            else if (x1 != lastRow && y1 == 0) //if in first colum  but not in last row
                                nx1 = x1 + 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 - 1;
                                else
                                    ny1 = y1 + 1;
                            }


                        }

                        //cell below-right
                        if (y1 > ky && kx < x1)
                        {
                            if (x1 != lastColumn && y1 != lastColumn) //if not in last row and not in last column
                            {
                                //randomly move down or right
                                int randNum = rand()%2;

                                if (randNum == 0)//move down
                                    nx1 = x1 + 1;
                                else //move right
                                    ny1 = y1 + 1;

                            }
                            else if (x1 == lastColumn && y1 != lastColumn) //if in first row but not in last column
                                ny1 = y1 + 1;
                            else if (x1 != lastColumn && y1 == lastColumn) //if in last column  but not in first row
                                nx1 = x1 + 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 - 1;
                                else
                                    ny1 = y1 - 1;
                            }


                        }

                        //cell left
                        if (y1 < ky && kx == x1)
                        {
                            if (y1 != 0)
                                ny1 = y1 - 1;
                            else
                            {
                                if (x1 == 0)
                                    nx1 = x1 + 1;
                                else if (x1 == lastRow)
                                    nx1 = x1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        nx1 = x1 - 1;
                                    else
                                        nx1 = x1 + 1;
                                }
                            }
                        }

                    }
                    else
                    {
                        //want to move towards killer
                        //cell above
                        if (y1 == ky && kx > x1)
                            nx1 = x1 + 1; //move down toward killer

                        //cell above-left
                        if (y1 < ky && kx > x1)
                        {

                            //randomly move right or down
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 + 1;

                        }

                        //cell above-right
                        if (y1 > ky && kx > x1)
                        {
                            //randomly move left or down
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 - 1;


                        }

                        //cell right
                        if (y1 > ky && kx == x1)
                            ny1 = y1 - 1;

                        //cell below
                        if (y1 == ky && kx < x1)
                            nx1 = x1 - 1;


                        //cell below-left
                        if (y1 < ky && kx < x1)
                        {
                            //randomly move right or up
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 + 1;

                        }

                        //cell below-right
                        if (y1 > ky && kx < x1)
                        {
                            //randomly move left or up
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 - 1;
                        }

                        //cell left
                        if (y1 < ky && kx == x1)
                            ny1 = y1 + 1;


                    }
                }

            }



            //show cell and set new position only if alive
            if (!cellOneDead)
            {
                labels[ny1*boardSize + nx1]->setPixmap(*oneCellImage);

                if (nx1 == killerPosition->rx() && ny1 == killerPosition->ry())
                {
                    if (livesLeft > 0)
                    {
                        lives[livesLeft-1]->clear();
                        livesLeft--;
                    }
                }

                CellPositions[0].setX(nx1);
                CellPositions[0].setY(ny1);
            }

            if (!cellOneDead)
                labels[y1*boardSize + x1]->clear();

        }
        else if (numberCells == 2)
        {
            //with oneCell (can be single ant or double ant)
            if (!cellOneDead) //only move if alive
            {

                //if single antigen cell
                if (cellOneAnt2 == -1 && cellOneAnt1 != -1)
                {

                    //want to go away if have right ant(s)
                    if (cellOneAnt1 == antigen1 || cellOneAnt1 == antigen2)
                    {
                        //cell can be above, al, ar, r, l, b, bl, br

                        //cell above
                        if (y1 == ky && kx > x1)
                        {
                            if (x1 != 0)//move up if not in first row
                                nx1 = x1 - 1;
                            else //if in first row
                            {
                                if (y1 == 0) //if in first row and first column
                                    ny1 = y1 + 1;
                                else if (y1 == lastColumn)
                                    ny1 = y1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        ny1 = y1 + 1;
                                    else
                                        ny1 = y1 - 1;
                                }

                            }
                        }

                        //cell above-left
                        if (y1 < ky && kx > x1)
                        {
                            if (x1 != 0 && y1 != 0) //if not in first row and not in first colum
                            {
                                //randomly move up or left
                                int randNum = rand()%2;

                                if (randNum == 0)//move up
                                    nx1 = x1 - 1;
                                else //move left
                                    ny1 = y1 - 1;

                            }
                            else if (x1 == 0 && y1 != 0) //if in first row but not in first column
                                ny1 = y1 - 1;
                            else if (x1 != 0 && y1 == 0) //if in first colum  but not in first row
                                nx1 = x1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 + 1;
                                else
                                    ny1 = y1 + 1;
                            }


                        }

                        //cell above-right
                        if (y1 > ky && kx > x1)
                        {
                            if (x1 != 0 && y1 != lastColumn) //if not in first row and not in last column
                            {
                                //randomly move up or right
                                int randNum = rand()%2;

                                if (randNum == 0)//move up
                                    nx1 = x1 - 1;
                                else //move right
                                    ny1 = y1 + 1;

                            }
                            else if (x1 == 0 && y1 != lastColumn) //if in first row but not in last column
                                ny1 = y1 + 1;
                            else if (x1 != 0 && y1 == lastColumn) //if in last column  but not in first row
                                nx1 = x1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 + 1;
                                else
                                    ny1 = y1 - 1;
                            }


                        }

                        //cell right
                        if (y1 > ky && kx == x1)
                        {
                            if (y1 != lastColumn)
                                ny1 = y1 + 1;
                            else
                            {
                                if (x1 == 0)
                                    nx1 = x1 + 1;
                                else if (x1 == lastRow)
                                    nx1 = x1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        nx1 = x1 - 1;
                                    else
                                        nx1 = x1 + 1;
                                }
                            }
                        }

                        //cell below
                        if (y1 == ky && kx < x1)
                        {
                            if (x1 != lastRow)//move down if not in last row
                                nx1 = x1 + 1;
                            else //if in last row
                            {
                                if (y1 == 0) //if in last row and first column
                                    ny1 = y1 + 1;
                                else if (y1 == lastColumn)
                                    ny1 = y1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        ny1 = y1 + 1;
                                    else
                                        ny1 = y1 - 1;
                                }

                            }
                        }

                        //cell below-left
                        if (y1 < ky && kx < x1)
                        {
                            if (x1 != lastRow && y1 != 0) //if not in last row and not in first colum
                            {
                                //randomly move down or left
                                int randNum = rand()%2;

                                if (randNum == 0)//move down
                                    nx1 = x1 + 1;
                                else //move left
                                    ny1 = y1 - 1;

                            }
                            else if (x1 == lastRow && y1 != 0) //if in last row but not in first column
                                ny1 = y1 - 1;
                            else if (x1 != lastRow && y1 == 0) //if in first colum  but not in last row
                                nx1 = x1 + 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 - 1;
                                else
                                    ny1 = y1 + 1;
                            }

                        }

                        //cell below-right
                        if (y1 > ky && kx < x1)
                        {
                            if (x1 != lastColumn && y1 != lastColumn) //if not in last row and not in last column
                            {
                                //randomly move down or right
                                int randNum = rand()%2;

                                if (randNum == 0)//move down
                                    nx1 = x1 + 1;
                                else //move right
                                    ny1 = y1 + 1;

                            }
                            else if (x1 == lastColumn && y1 != lastColumn) //if in first row but not in last column
                                ny1 = y1 + 1;
                            else if (x1 != lastColumn && y1 == lastColumn) //if in last column  but not in first row
                                nx1 = x1 + 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 - 1;
                                else
                                    ny1 = y1 - 1;
                            }


                        }

                        //cell left
                        if (y1 < ky && kx == x1)
                        {
                            if (y1 != 0)
                                ny1 = y1 - 1;
                            else
                            {
                                if (x1 == 0)
                                    nx1 = x1 + 1;
                                else if (x1 == lastRow)
                                    nx1 = x1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        nx1 = x1 - 1;
                                    else
                                        nx1 = x1 + 1;
                                }
                            }
                        }

                    }
                    else
                    {
                        //want to move towards killer
                        //cell above
                        if (y1 == ky && kx > x1)
                            nx1 = x1 + 1; //move down toward killer

                        //cell above-left
                        if (y1 < ky && kx > x1)
                        {

                            //randomly move right or down
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 + 1;

                        }

                        //cell above-right
                        if (y1 > ky && kx > x1)
                        {
                            //randomly move left or down
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 - 1;


                        }

                        //cell right
                        if (y1 > ky && kx == x1)
                            ny1 = y1 - 1;

                        //cell below
                        if (y1 == ky && kx < x1)
                            nx1 = x1 - 1;


                        //cell below-left
                        if (y1 < ky && kx < x1)
                        {
                            //randomly move right or up
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 + 1;

                        }

                        //cell below-right
                        if (y1 > ky && kx < x1)
                        {
                            //randomly move left or up
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 - 1;
                        }

                        //cell left
                        if (y1 < ky && kx == x1)
                            ny1 = y1 + 1;


                    }
                }
                else //double antigen cell
                {

                    //want to go away if have right ant(s)
                    if ((cellOneAnt1 == antigen1 && cellOneAnt2 == antigen2)
                            ||(cellOneAnt1 == antigen2 && cellOneAnt2 == antigen1))
                    {
                        //cell can be above, al, ar, r, l, b, bl, br

                        //cell above
                        if (y1 == ky && kx > x1)
                        {
                            if (x1 != 0)//move up if not in first row
                                nx1 = x1 - 1;
                            else //if in first row
                            {
                                if (y1 == 0) //if in first row and first column
                                    ny1 = y1 + 1;
                                else if (y1 == lastColumn)
                                    ny1 = y1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        ny1 = y1 + 1;
                                    else
                                        ny1 = y1 - 1;
                                }

                            }
                        }

                        //cell above-left
                        if (y1 < ky && kx > x1)
                        {
                            if (x1 != 0 && y1 != 0) //if not in first row and not in first colum
                            {
                                //randomly move up or left
                                int randNum = rand()%2;

                                if (randNum == 0)//move up
                                    nx1 = x1 - 1;
                                else //move left
                                    ny1 = y1 - 1;

                            }
                            else if (x1 == 0 && y1 != 0) //if in first row but not in first column
                                ny1 = y1 - 1;
                            else if (x1 != 0 && y1 == 0) //if in first colum  but not in first row
                                nx1 = x1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 + 1;
                                else
                                    ny1 = y1 + 1;
                            }


                        }

                        //cell above-right
                        if (y1 > ky && kx > x1)
                        {
                            if (x1 != 0 && y1 != lastColumn) //if not in first row and not in last column
                            {
                                //randomly move up or right
                                int randNum = rand()%2;

                                if (randNum == 0)//move up
                                    nx1 = x1 - 1;
                                else //move right
                                    ny1 = y1 + 1;

                            }
                            else if (x1 == 0 && y1 != lastColumn) //if in first row but not in last column
                                ny1 = y1 + 1;
                            else if (x1 != 0 && y1 == lastColumn) //if in last column  but not in first row
                                nx1 = x1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 + 1;
                                else
                                    ny1 = y1 - 1;
                            }


                        }

                        //cell right
                        if (y1 > ky && kx == x1)
                        {
                            if (y1 != lastColumn)
                                ny1 = y1 + 1;
                            else
                            {
                                if (x1 == 0)
                                    nx1 = x1 + 1;
                                else if (x1 == lastRow)
                                    nx1 = x1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        nx1 = x1 - 1;
                                    else
                                        nx1 = x1 + 1;
                                }
                            }
                        }

                        //cell below
                        if (y1 == ky && kx < x1)
                        {
                            if (x1 != lastRow)//move down if not in last row
                                nx1 = x1 + 1;
                            else //if in last row
                            {
                                if (y1 == 0) //if in last row and first column
                                    ny1 = y1 + 1;
                                else if (y1 == lastColumn)
                                    ny1 = y1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        ny1 = y1 + 1;
                                    else
                                        ny1 = y1 - 1;
                                }

                            }
                        }

                        //cell below-left
                        if (y1 < ky && kx < x1)
                        {
                            if (x1 != lastRow && y1 != 0) //if not in last row and not in first colum
                            {
                                //randomly move down or left
                                int randNum = rand()%2;

                                if (randNum == 0)//move down
                                    nx1 = x1 + 1;
                                else //move left
                                    ny1 = y1 - 1;

                            }
                            else if (x1 == lastRow && y1 != 0) //if in last row but not in first column
                                ny1 = y1 - 1;
                            else if (x1 != lastRow && y1 == 0) //if in first colum  but not in last row
                                nx1 = x1 + 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 - 1;
                                else
                                    ny1 = y1 + 1;
                            }


                        }

                        //cell below-right
                        if (y1 > ky && kx < x1)
                        {
                            if (x1 != lastColumn && y1 != lastColumn) //if not in last row and not in last column
                            {
                                //randomly move down or right
                                int randNum = rand()%2;

                                if (randNum == 0)//move down
                                    nx1 = x1 + 1;
                                else //move right
                                    ny1 = y1 + 1;

                            }
                            else if (x1 == lastColumn && y1 != lastColumn) //if in first row but not in last column
                                ny1 = y1 + 1;
                            else if (x1 != lastColumn && y1 == lastColumn) //if in last column  but not in first row
                                nx1 = x1 + 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 - 1;
                                else
                                    ny1 = y1 - 1;
                            }


                        }

                        //cell left
                        if (y1 < ky && kx == x1)
                        {
                            if (y1 != 0)
                                ny1 = y1 - 1;
                            else
                            {
                                if (x1 == 0)
                                    nx1 = x1 + 1;
                                else if (x1 == lastRow)
                                    nx1 = x1 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        nx1 = x1 - 1;
                                    else
                                        nx1 = x1 + 1;
                                }
                            }
                        }

                    }
                    else
                    {
                        //want to move towards killer
                        //cell above
                        if (y1 == ky && kx > x1)
                            nx1 = x1 + 1; //move down toward killer

                        //cell above-left
                        if (y1 < ky && kx > x1)
                        {

                            //randomly move right or down
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 + 1;

                        }

                        //cell above-right
                        if (y1 > ky && kx > x1)
                        {
                            //randomly move left or down
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 - 1;


                        }

                        //cell right
                        if (y1 > ky && kx == x1)
                            ny1 = y1 - 1;

                        //cell below
                        if (y1 == ky && kx < x1)
                            nx1 = x1 - 1;


                        //cell below-left
                        if (y1 < ky && kx < x1)
                        {
                            //randomly move right or up
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 + 1;

                        }

                        //cell below-right
                        if (y1 > ky && kx < x1)
                        {
                            //randomly move left or up
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 - 1;
                        }

                        //cell left
                        if (y1 < ky && kx == x1)
                            ny1 = y1 + 1;


                    }
                }

            }


            //show cell and set new position only if alive
            if (!cellOneDead)
            {
                if (nx1 == killerPosition->rx() && ny1 == killerPosition->ry())
                {
                    if (livesLeft > 0)
                    {
                        lives[livesLeft-1]->clear();
                        livesLeft--;
                    }
                }
                labels[ny1*boardSize + nx1]->setPixmap(*oneCellImage);
                CellPositions[0].setX(nx1);
                CellPositions[0].setY(ny1);
            }

            //with twoCell (can be single ant or double ant)
            if (!cellTwoDead) //only move if alive
            {

                //if single antigen cell
                if (cellTwoAnt2 == -1 && cellOneAnt1 != -1)
                {

                    //want to go away if have right ant(s)
                    if (cellTwoAnt1 == antigen1 || cellTwoAnt1 == antigen2)
                    {
                        //cell can be above, al, ar, r, l, b, bl, br

                        //cell above
                        if (y2 == ky && kx > x2)
                        {
                            if (x2 != 0)//move up if not in first row
                                nx2 = x2 - 1;
                            else //if in first row
                            {
                                if (y2 == 0) //if in first row and first column
                                    ny2 = y2 + 1;
                                else if (y2 == lastColumn)
                                    ny2 = y2 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        ny2 = y2 + 1;
                                    else
                                        ny2 = y2 - 1;
                                }

                            }
                        }

                        //cell above-left
                        if (y2 < ky && kx > x2)
                        {
                            if (x2 != 0 && y2 != 0) //if not in first row and not in first colum
                            {
                                //randomly move up or left
                                int randNum = rand()%2;

                                if (randNum == 0)//move up
                                    nx2 = x2 - 1;
                                else //move left
                                    ny2 = y2 - 1;

                            }
                            else if (x2 == 0 && y2 != 0) //if in first row but not in first column
                                ny2 = y2 - 1;
                            else if (x2 != 0 && y2 == 0) //if in first colum  but not in first row
                                nx2 = x2 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx2 = x2 + 1;
                                else
                                    ny2 = y2 + 1;
                            }


                        }

                        //cell above-right
                        if (y2 > ky && kx > x2)
                        {
                            if (x2 != 0 && y2 != lastColumn) //if not in first row and not in last column
                            {
                                //randomly move up or right
                                int randNum = rand()%2;

                                if (randNum == 0)//move up
                                    nx2 = x2 - 1;
                                else //move right
                                    ny2 = y2 + 1;

                            }
                            else if (x2 == 0 && y2 != lastColumn) //if in first row but not in last column
                                ny2 = y2 + 1;
                            else if (x2 != 0 && y2 == lastColumn) //if in last column  but not in first row
                                nx2 = x2 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx2 = x2 + 1;
                                else
                                    ny2 = y2 - 1;
                            }


                        }

                        //cell right
                        if (y2 > ky && kx == x2)
                        {
                            if (y2 != lastColumn)
                                ny2 = y2 + 1;
                            else
                            {
                                if (x2 == 0)
                                    nx2 = x2 + 1;
                                else if (x2 == lastRow)
                                    nx2 = x2 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        nx2 = x2 - 1;
                                    else
                                        nx2 = x2 + 1;
                                }
                            }
                        }

                        //cell below
                        if (y2 == ky && kx < x2)
                        {
                            if (x2 != lastRow)//move down if not in last row
                                nx2 = x2 + 1;
                            else //if in last row
                            {
                                if (y2 == 0) //if in last row and first column
                                    ny2 = y2 + 1;
                                else if (y2 == lastColumn)
                                    ny2 = y2 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        ny2 = y2 + 1;
                                    else
                                        ny2 = y2 - 1;
                                }

                            }
                        }

                        //cell below-left
                        if (y2 < ky && kx < x2)
                        {
                            if (x2 != lastRow && y2 != 0) //if not in last row and not in first colum
                            {
                                //randomly move down or left
                                int randNum = rand()%2;

                                if (randNum == 0)//move down
                                    nx2 = x2 + 1;
                                else //move left
                                    ny2 = y2 - 1;

                            }
                            else if (x2 == lastRow && y2 != 0) //if in last row but not in first column
                                ny2 = y2 - 1;
                            else if (x2 != lastRow && y2 == 0) //if in first colum  but not in last row
                                nx2 = x2 + 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx2 = x2 - 1;
                                else
                                    ny2 = y2 + 1;
                            }


                        }

                        //cell below-right
                        if (y2 > ky && kx < x2)
                        {
                            if (x2 != lastColumn && y2 != lastColumn) //if not in last row and not in last column
                            {
                                //randomly move down or right
                                int randNum = rand()%2;

                                if (randNum == 0)//move down
                                    nx2 = x2 + 1;
                                else //move right
                                    ny2 = y2 + 1;

                            }
                            else if (x2 == lastColumn && y2 != lastColumn) //if in first row but not in last column
                                ny2 = y2 + 1;
                            else if (x2 != lastColumn && y2 == lastColumn) //if in last column  but not in first row
                                nx2 = x2 + 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx2 = x2 - 1;
                                else
                                    ny2 = y2 - 1;
                            }


                        }

                        //cell left
                        if (y2 < ky && kx == x2)
                        {
                            if (y2 != 0)
                                ny2 = y2 - 1;
                            else
                            {
                                if (x2 == 0)
                                    nx2 = x2 + 1;
                                else if (x2 == lastRow)
                                    nx2 = x2 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        nx2 = x2 - 1;
                                    else
                                        nx2 = x2 + 1;
                                }
                            }
                        }

                    }
                    else
                    {
                        //want to move towards killer
                        //cell above
                        if (y2 == ky && kx > x2)
                            nx2 = x2 + 1; //move down toward killer

                        //cell above-left
                        if (y2 < ky && kx > x2)
                        {

                            //randomly move right or down
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx2 = x2 + 1;
                            else
                                ny2 = y2 + 1;

                        }

                        //cell above-right
                        if (y2 > ky && kx > x2)
                        {
                            //randomly move left or down
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx2 = x2 + 1;
                            else
                                ny2 = y2 - 1;


                        }

                        //cell right
                        if (y2 > ky && kx == x2)
                            ny2 = y2 - 1;

                        //cell below
                        if (y2 == ky && kx < x2)
                            nx2 = x2 - 1;


                        //cell below-left
                        if (y2 < ky && kx < x2)
                        {
                            //randomly move right or up
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx2 = x2 - 1;
                            else
                                ny2 = y2 + 1;

                        }

                        //cell below-right
                        if (y2 > ky && kx < x2)
                        {
                            //randomly move left or up
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx2 = x2 - 1;
                            else
                                ny2= y2 - 1;
                        }

                        //cell left
                        if (y2 < ky && kx == x2)
                            ny2 = y2 + 1;


                    }
                }
                else //double antigen cell
                {

                    //want to go away if have right ant(s)
                    if ((cellTwoAnt1 == antigen1 && cellTwoAnt2 == antigen2)
                            ||(cellTwoAnt1 == antigen2 && cellTwoAnt2 == antigen1))
                    {
                        //cell can be above, al, ar, r, l, b, bl, br

                        //cell above
                        if (y2 == ky && kx > x2)
                        {
                            if (x2 != 0)//move up if not in first row
                                nx2 = x2 - 1;
                            else //if in first row
                            {
                                if (y2 == 0) //if in first row and first column
                                    ny2 = y2 + 1;
                                else if (y2 == lastColumn)
                                    ny2 = y2 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        ny2 = y2 + 1;
                                    else
                                        ny2 = y2 - 1;
                                }

                            }
                        }

                        //cell above-left
                        if (y2 < ky && kx > x2)
                        {
                            if (x2 != 0 && y2 != 0) //if not in first row and not in first colum
                            {
                                //randomly move up or left
                                int randNum = rand()%2;

                                if (randNum == 0)//move up
                                    nx2 = x2 - 1;
                                else //move left
                                    ny2 = y2 - 1;

                            }
                            else if (x2 == 0 && y2 != 0) //if in first row but not in first column
                                ny2 = y2 - 1;
                            else if (x2 != 0 && y2 == 0) //if in first colum  but not in first row
                                nx2 = x2 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx2 = x2 + 1;
                                else
                                    ny2 = y2 + 1;
                            }


                        }

                        //cell above-right
                        if (y2 > ky && kx > x2)
                        {
                            if (x2 != 0 && y2 != lastColumn) //if not in first row and not in last column
                            {
                                //randomly move up or right
                                int randNum = rand()%2;

                                if (randNum == 0)//move up
                                    nx2 = x2 - 1;
                                else //move right
                                    ny2 = y2 + 1;

                            }
                            else if (x2 == 0 && y2 != lastColumn) //if in first row but not in last column
                                ny2 = y2 + 1;
                            else if (x2 != 0 && y2 == lastColumn) //if in last column  but not in first row
                                nx2 = x2 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 + 1;
                                else
                                    ny1 = y1 - 1;
                            }


                        }

                        //cell right
                        if (y2 > ky && kx == x2)
                        {
                            if (y2 != lastColumn)
                                ny2 = y2 + 1;
                            else
                            {
                                if (x2 == 0)
                                    nx2 = x2 + 1;
                                else if (x2 == lastRow)
                                    nx2 = x2 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        nx2 = x2 - 1;
                                    else
                                        nx2 = x2 + 1;
                                }
                            }
                        }

                        //cell below
                        if (y2 == ky && kx < x2)
                        {
                            if (x2 != lastRow)//move down if not in last row
                                nx2 = x2 + 1;
                            else //if in last row
                            {
                                if (y2 == 0) //if in last row and first column
                                    ny2 = y2 + 1;
                                else if (y2 == lastColumn)
                                    ny2 = y2 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        ny2 = y2 + 1;
                                    else
                                        ny2 = y2 - 1;
                                }

                            }
                        }

                        //cell below-left
                        if (y2 < ky && kx < x2)
                        {
                            if (x2 != lastRow && y2 != 0) //if not in last row and not in first colum
                            {
                                //randomly move down or left
                                int randNum = rand()%2;

                                if (randNum == 0)//move down
                                    nx2 = x2 + 1;
                                else //move left
                                    ny2 = y2 - 1;

                            }
                            else if (x2 == lastRow && y2 != 0) //if in last row but not in first column
                                ny2 = y2 - 1;
                            else if (x2 != lastRow && y2 == 0) //if in first colum  but not in last row
                                nx2 = x2 + 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 - 1;
                                else
                                    ny1 = y1 + 1;
                            }


                        }

                        //cell below-right
                        if (y2 > ky && kx < x2)
                        {
                            if (x2 != lastColumn && y2 != lastColumn) //if not in last row and not in last column
                            {
                                //randomly move down or right
                                int randNum = rand()%2;

                                if (randNum == 0)//move down
                                    nx2 = x2 + 1;
                                else //move right
                                    ny2 = y2 + 1;

                            }
                            else if (x2 == lastColumn && y2 != lastColumn) //if in first row but not in last column
                                ny2 = y2 + 1;
                            else if (x2 != lastColumn && y2 == lastColumn) //if in last column  but not in first row
                                nx2 = x2 + 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 - 1;
                                else
                                    ny1 = y1 - 1;
                            }


                        }

                        //cell left
                        if (y2 < ky && kx == x2)
                        {
                            if (y2 != 0)
                                ny2 = y2 - 1;
                            else
                            {
                                if (x2 == 0)
                                    nx2 = x2 + 1;
                                else if (x2 == lastRow)
                                    nx2 = x2 - 1;
                                else
                                {
                                    int randNum = rand()%2;

                                    if (randNum == 0)
                                        nx2 = x2 - 1;
                                    else
                                        nx2 = x2 + 1;
                                }
                            }
                        }

                    }
                    else
                    {
                        //want to move towards killer
                        //cell above
                        if (y2 == ky && kx > x2)
                            nx2 = x2 + 1; //move down toward killer

                        //cell above-left
                        if (y2 < ky && kx > x2)
                        {

                            //randomly move right or down
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx2 = x2 + 1;
                            else
                                ny2 = y2 + 1;

                        }

                        //cell above-right
                        if (y2 > ky && kx > x2)
                        {
                            //randomly move left or down
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx2 = x2 + 1;
                            else
                                ny2 = y2 - 1;


                        }

                        //cell right
                        if (y2 > ky && kx == x2)
                            ny2 = y2 - 1;

                        //cell below
                        if (y2 == ky && kx < x2)
                            nx2 = x2 - 1;


                        //cell below-left
                        if (y2 < ky && kx < x2)
                        {
                            //randomly move right or up
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx2 = x2 - 1;
                            else
                                ny2 = y2 + 1;

                        }

                        //cell below-right
                        if (y2 > ky && kx < x2)
                        {
                            //randomly move left or up
                            int randNum = rand()%2;
                            if (randNum == 0)
                                nx2 = x2 - 1;
                            else
                                ny2= y2 - 1;
                        }

                        //cell left
                        if (y2 < ky && kx == x2)
                            ny2 = y2 + 1;


                    }


                }
            }




            //show cell and set new position only if alive...
            //only set new position if space open
            if (!cellTwoDead)
            {
                if (nx1 == nx2 && ny1 == ny2) //if going to occupied space
                {
                    //set to old position (dont move)
                    labels[y2*boardSize + x2]->setPixmap(*twoCellImage);
                    CellPositions[1].setX(x2);
                    CellPositions[1].setY(x2);
                }
                else
                {
                    if (nx2 == killerPosition->rx() && ny2 == killerPosition->ry())
                    {
                        if (livesLeft > 0)
                        {
                            lives[livesLeft-1]->clear();
                            livesLeft--;
                        }
                    }
                    labels[ny2*boardSize + nx2]->setPixmap(*twoCellImage);
                    CellPositions[1].setX(nx2);
                    CellPositions[1].setY(ny2);
                }
            }

            if (!cellOneDead)
                labels[y1*boardSize + x1]->clear();

            if (!cellTwoDead)
                labels[y2*boardSize + x2]->clear();


        }
        else //if (numberCells == 3)
    {

        //with oneCell (can be single ant or double ant)
        if (!cellOneDead) //only move if alive
        {

            //if single antigen cell
            if (cellOneAnt2 == -1 && cellOneAnt1 != -1)
            {

                //want to go away if have right ant(s)
                if (cellOneAnt1 == antigen1 || cellOneAnt1 == antigen2)
                {
                    //cell can be above, al, ar, r, l, b, bl, br

                    //cell above
                    if (y1 == ky && kx > x1)
                    {
                        if (x1 != 0)//move up if not in first row
                            nx1 = x1 - 1;
                        else //if in first row
                        {
                            if (y1 == 0) //if in first row and first column
                                ny1 = y1 + 1;
                            else if (y1 == lastColumn)
                                ny1 = y1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny1 = y1 + 1;
                                else
                                    ny1 = y1 - 1;
                            }

                        }
                    }

                    //cell above-left
                    if (y1 < ky && kx > x1)
                    {
                        if (x1 != 0 && y1 != 0) //if not in first row and not in first colum
                        {
                            //randomly move up or left
                            int randNum = rand()%2;

                            if (randNum == 0)//move up
                                nx1 = x1 - 1;
                            else //move left
                                ny1 = y1 - 1;

                        }
                        else if (x1 == 0 && y1 != 0) //if in first row but not in first column
                            ny1 = y1 - 1;
                        else if (x1 != 0 && y1 == 0) //if in first colum  but not in first row
                            nx1 = x1 - 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 + 1;
                        }


                    }

                    //cell above-right
                    if (y1 > ky && kx > x1)
                    {
                        if (x1 != 0 && y1 != lastColumn) //if not in first row and not in last column
                        {
                            //randomly move up or right
                            int randNum = rand()%2;

                            if (randNum == 0)//move up
                                nx1 = x1 - 1;
                            else //move right
                                ny1 = y1 + 1;

                        }
                        else if (x1 == 0 && y1 != lastColumn) //if in first row but not in last column
                            ny1 = y1 + 1;
                        else if (x1 != 0 && y1 == lastColumn) //if in last column  but not in first row
                            nx1 = x1 - 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 - 1;
                        }


                    }

                    //cell right
                    if (y1 > ky && kx == x1)
                    {
                        if (y1 != lastColumn)
                            ny1 = y1 + 1;
                        else
                        {
                            if (x1 == 0)
                                nx1 = x1 + 1;
                            else if (x1 == lastRow)
                                nx1 = x1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 - 1;
                                else
                                    nx1 = x1 + 1;
                            }
                        }
                    }

                    //cell below
                    if (y1 == ky && kx < x1)
                    {
                        if (x1 != lastRow)//move down if not in last row
                            nx1 = x1 + 1;
                        else //if in last row
                        {
                            if (y1 == 0) //if in last row and first column
                                ny1 = y1 + 1;
                            else if (y1 == lastColumn)
                                ny1 = y1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny1 = y1 + 1;
                                else
                                    ny1 = y1 - 1;
                            }

                        }
                    }

                    //cell below-left
                    if (y1 < ky && kx < x1)
                    {
                        if (x1 != lastRow && y1 != 0) //if not in last row and not in first colum
                        {
                            //randomly move down or left
                            int randNum = rand()%2;

                            if (randNum == 0)//move down
                                nx1 = x1 + 1;
                            else //move left
                                ny1 = y1 - 1;

                        }
                        else if (x1 == lastRow && y1 != 0) //if in last row but not in first column
                            ny1 = y1 - 1;
                        else if (x1 != lastRow && y1 == 0) //if in first colum  but not in last row
                            nx1 = x1 + 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 + 1;
                        }

                    }

                    //cell below-right
                    if (y1 > ky && kx < x1)
                    {
                        if (x1 != lastColumn && y1 != lastColumn) //if not in last row and not in last column
                        {
                            //randomly move down or right
                            int randNum = rand()%2;

                            if (randNum == 0)//move down
                                nx1 = x1 + 1;
                            else //move right
                                ny1 = y1 + 1;

                        }
                        else if (x1 == lastColumn && y1 != lastColumn) //if in first row but not in last column
                            ny1 = y1 + 1;
                        else if (x1 != lastColumn && y1 == lastColumn) //if in last column  but not in first row
                            nx1 = x1 + 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 - 1;
                        }


                    }

                    //cell left
                    if (y1 < ky && kx == x1)
                    {
                        if (y1 != 0)
                            ny1 = y1 - 1;
                        else
                        {
                            if (x1 == 0)
                                nx1 = x1 + 1;
                            else if (x1 == lastRow)
                                nx1 = x1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 - 1;
                                else
                                    nx1 = x1 + 1;
                            }
                        }
                    }

                }
                else
                {
                    //want to move towards killer
                    //cell above
                    if (y1 == ky && kx > x1)
                        nx1 = x1 + 1; //move down toward killer

                    //cell above-left
                    if (y1 < ky && kx > x1)
                    {

                        //randomly move right or down
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx1 = x1 + 1;
                        else
                            ny1 = y1 + 1;

                    }

                    //cell above-right
                    if (y1 > ky && kx > x1)
                    {
                        //randomly move left or down
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx1 = x1 + 1;
                        else
                            ny1 = y1 - 1;


                    }

                    //cell right
                    if (y1 > ky && kx == x1)
                        ny1 = y1 - 1;

                    //cell below
                    if (y1 == ky && kx < x1)
                        nx1 = x1 - 1;


                    //cell below-left
                    if (y1 < ky && kx < x1)
                    {
                        //randomly move right or up
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx1 = x1 - 1;
                        else
                            ny1 = y1 + 1;

                    }

                    //cell below-right
                    if (y1 > ky && kx < x1)
                    {
                        //randomly move left or up
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx1 = x1 - 1;
                        else
                            ny1 = y1 - 1;
                    }

                    //cell left
                    if (y1 < ky && kx == x1)
                        ny1 = y1 + 1;


                }
            }
            else //double antigen cell
            {

                //want to go away if have right ant(s)
                if ((cellOneAnt1 == antigen1 && cellOneAnt2 == antigen2)
                        ||(cellOneAnt1 == antigen2 && cellOneAnt2 == antigen1))
                {
                    //cell can be above, al, ar, r, l, b, bl, br

                    //cell above
                    if (y1 == ky && kx > x1)
                    {
                        if (x1 != 0)//move up if not in first row
                            nx1 = x1 - 1;
                        else //if in first row
                        {
                            if (y1 == 0) //if in first row and first column
                                ny1 = y1 + 1;
                            else if (y1 == lastColumn)
                                ny1 = y1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny1 = y1 + 1;
                                else
                                    ny1 = y1 - 1;
                            }

                        }
                    }

                    //cell above-left
                    if (y1 < ky && kx > x1)
                    {
                        if (x1 != 0 && y1 != 0) //if not in first row and not in first colum
                        {
                            //randomly move up or left
                            int randNum = rand()%2;

                            if (randNum == 0)//move up
                                nx1 = x1 - 1;
                            else //move left
                                ny1 = y1 - 1;

                        }
                        else if (x1 == 0 && y1 != 0) //if in first row but not in first column
                            ny1 = y1 - 1;
                        else if (x1 != 0 && y1 == 0) //if in first colum  but not in first row
                            nx1 = x1 - 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 + 1;
                        }


                    }

                    //cell above-right
                    if (y1 > ky && kx > x1)
                    {
                        if (x1 != 0 && y1 != lastColumn) //if not in first row and not in last column
                        {
                            //randomly move up or right
                            int randNum = rand()%2;

                            if (randNum == 0)//move up
                                nx1 = x1 - 1;
                            else //move right
                                ny1 = y1 + 1;

                        }
                        else if (x1 == 0 && y1 != lastColumn) //if in first row but not in last column
                            ny1 = y1 + 1;
                        else if (x1 != 0 && y1 == lastColumn) //if in last column  but not in first row
                            nx1 = x1 - 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 - 1;
                        }


                    }

                    //cell right
                    if (y1 > ky && kx == x1)
                    {
                        if (y1 != lastColumn)
                            ny1 = y1 + 1;
                        else
                        {
                            if (x1 == 0)
                                nx1 = x1 + 1;
                            else if (x1 == lastRow)
                                nx1 = x1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 - 1;
                                else
                                    nx1 = x1 + 1;
                            }
                        }
                    }

                    //cell below
                    if (y1 == ky && kx < x1)
                    {
                        if (x1 != lastRow)//move down if not in last row
                            nx1 = x1 + 1;
                        else //if in last row
                        {
                            if (y1 == 0) //if in last row and first column
                                ny1 = y1 + 1;
                            else if (y1 == lastColumn)
                                ny1 = y1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny1 = y1 + 1;
                                else
                                    ny1 = y1 - 1;
                            }

                        }
                    }

                    //cell below-left
                    if (y1 < ky && kx < x1)
                    {
                        if (x1 != lastRow && y1 != 0) //if not in last row and not in first colum
                        {
                            //randomly move down or left
                            int randNum = rand()%2;

                            if (randNum == 0)//move down
                                nx1 = x1 + 1;
                            else //move left
                                ny1 = y1 - 1;

                        }
                        else if (x1 == lastRow && y1 != 0) //if in last row but not in first column
                            ny1 = y1 - 1;
                        else if (x1 != lastRow && y1 == 0) //if in first colum  but not in last row
                            nx1 = x1 + 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 + 1;
                        }


                    }

                    //cell below-right
                    if (y1 > ky && kx < x1)
                    {
                        if (x1 != lastColumn && y1 != lastColumn) //if not in last row and not in last column
                        {
                            //randomly move down or right
                            int randNum = rand()%2;

                            if (randNum == 0)//move down
                                nx1 = x1 + 1;
                            else //move right
                                ny1 = y1 + 1;

                        }
                        else if (x1 == lastColumn && y1 != lastColumn) //if in first row but not in last column
                            ny1 = y1 + 1;
                        else if (x1 != lastColumn && y1 == lastColumn) //if in last column  but not in first row
                            nx1 = x1 + 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 - 1;
                        }


                    }

                    //cell left
                    if (y1 < ky && kx == x1)
                    {
                        if (y1 != 0)
                            ny1 = y1 - 1;
                        else
                        {
                            if (x1 == 0)
                                nx1 = x1 + 1;
                            else if (x1 == lastRow)
                                nx1 = x1 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx1 = x1 - 1;
                                else
                                    nx1 = x1 + 1;
                            }
                        }
                    }

                }
                else
                {
                    //want to move towards killer
                    //cell above
                    if (y1 == ky && kx > x1)
                        nx1 = x1 + 1; //move down toward killer

                    //cell above-left
                    if (y1 < ky && kx > x1)
                    {

                        //randomly move right or down
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx1 = x1 + 1;
                        else
                            ny1 = y1 + 1;

                    }

                    //cell above-right
                    if (y1 > ky && kx > x1)
                    {
                        //randomly move left or down
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx1 = x1 + 1;
                        else
                            ny1 = y1 - 1;


                    }

                    //cell right
                    if (y1 > ky && kx == x1)
                        ny1 = y1 - 1;

                    //cell below
                    if (y1 == ky && kx < x1)
                        nx1 = x1 - 1;


                    //cell below-left
                    if (y1 < ky && kx < x1)
                    {
                        //randomly move right or up
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx1 = x1 - 1;
                        else
                            ny1 = y1 + 1;

                    }

                    //cell below-right
                    if (y1 > ky && kx < x1)
                    {
                        //randomly move left or up
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx1 = x1 - 1;
                        else
                            ny1 = y1 - 1;
                    }

                    //cell left
                    if (y1 < ky && kx == x1)
                        ny1 = y1 + 1;


                }
            }

        }


        //show cell and set new position only if alive
        if (!cellOneDead)
        {
            if (nx1 == killerPosition->rx() && ny1 == killerPosition->ry())
            {
                if (livesLeft > 0)
                {
                    lives[livesLeft-1]->clear();
                    livesLeft--;
                }
            }
            labels[ny1*boardSize + nx1]->setPixmap(*oneCellImage);
            CellPositions[0].setX(nx1);
            CellPositions[0].setY(ny1);
        }

        //with twoCell (can be single ant or double ant)
        if (!cellTwoDead) //only move if alive
        {

            //if single antigen cell
            if (cellTwoAnt2 == -1 && cellOneAnt1 != -1)
            {

                //want to go away if have right ant(s)
                if (cellTwoAnt1 == antigen1 || cellTwoAnt1 == antigen2)
                {
                    //cell can be above, al, ar, r, l, b, bl, br

                    //cell above
                    if (y2 == ky && kx > x2)
                    {
                        if (x2 != 0)//move up if not in first row
                            nx2 = x2 - 1;
                        else //if in first row
                        {
                            if (y2 == 0) //if in first row and first column
                                ny2 = y2 + 1;
                            else if (y2 == lastColumn)
                                ny2 = y2 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny2 = y2 + 1;
                                else
                                    ny2 = y2 - 1;
                            }

                        }
                    }

                    //cell above-left
                    if (y2 < ky && kx > x2)
                    {
                        if (x2 != 0 && y2 != 0) //if not in first row and not in first colum
                        {
                            //randomly move up or left
                            int randNum = rand()%2;

                            if (randNum == 0)//move up
                                nx2 = x2 - 1;
                            else //move left
                                ny2 = y2 - 1;

                        }
                        else if (x2 == 0 && y2 != 0) //if in first row but not in first column
                            ny2 = y2 - 1;
                        else if (x2 != 0 && y2 == 0) //if in first colum  but not in first row
                            nx2 = x2 - 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx2 = x2 + 1;
                            else
                                ny2 = y2 + 1;
                        }


                    }

                    //cell above-right
                    if (y2 > ky && kx > x2)
                    {
                        if (x2 != 0 && y2 != lastColumn) //if not in first row and not in last column
                        {
                            //randomly move up or right
                            int randNum = rand()%2;

                            if (randNum == 0)//move up
                                nx2 = x2 - 1;
                            else //move right
                                ny2 = y2 + 1;

                        }
                        else if (x2 == 0 && y2 != lastColumn) //if in first row but not in last column
                            ny2 = y2 + 1;
                        else if (x2 != 0 && y2 == lastColumn) //if in last column  but not in first row
                            nx2 = x2 - 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx2 = x2 + 1;
                            else
                                ny2 = y2 - 1;
                        }


                    }

                    //cell right
                    if (y2 > ky && kx == x2)
                    {
                        if (y2 != lastColumn)
                            ny2 = y2 + 1;
                        else
                        {
                            if (x2 == 0)
                                nx2 = x2 + 1;
                            else if (x2 == lastRow)
                                nx2 = x2 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx2 = x2 - 1;
                                else
                                    nx2 = x2 + 1;
                            }
                        }
                    }

                    //cell below
                    if (y2 == ky && kx < x2)
                    {
                        if (x2 != lastRow)//move down if not in last row
                            nx2 = x2 + 1;
                        else //if in last row
                        {
                            if (y2 == 0) //if in last row and first column
                                ny2 = y2 + 1;
                            else if (y2 == lastColumn)
                                ny2 = y2 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny2 = y2 + 1;
                                else
                                    ny2 = y2 - 1;
                            }

                        }
                    }

                    //cell below-left
                    if (y2 < ky && kx < x2)
                    {
                        if (x2 != lastRow && y2 != 0) //if not in last row and not in first colum
                        {
                            //randomly move down or left
                            int randNum = rand()%2;

                            if (randNum == 0)//move down
                                nx2 = x2 + 1;
                            else //move left
                                ny2 = y2 - 1;

                        }
                        else if (x2 == lastRow && y2 != 0) //if in last row but not in first column
                            ny2 = y2 - 1;
                        else if (x2 != lastRow && y2 == 0) //if in first colum  but not in last row
                            nx2 = x2 + 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx2 = x2 - 1;
                            else
                                ny2 = y2 + 1;
                        }


                    }

                    //cell below-right
                    if (y2 > ky && kx < x2)
                    {
                        if (x2 != lastColumn && y2 != lastColumn) //if not in last row and not in last column
                        {
                            //randomly move down or right
                            int randNum = rand()%2;

                            if (randNum == 0)//move down
                                nx2 = x2 + 1;
                            else //move right
                                ny2 = y2 + 1;

                        }
                        else if (x2 == lastColumn && y2 != lastColumn) //if in first row but not in last column
                            ny2 = y2 + 1;
                        else if (x2 != lastColumn && y2 == lastColumn) //if in last column  but not in first row
                            nx2 = x2 + 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx2 = x2 - 1;
                            else
                                ny2 = y2 - 1;
                        }


                    }

                    //cell left
                    if (y2 < ky && kx == x2)
                    {
                        if (y2 != 0)
                            ny2 = y2 - 1;
                        else
                        {
                            if (x2 == 0)
                                nx2 = x2 + 1;
                            else if (x2 == lastRow)
                                nx2 = x2 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx2 = x2 - 1;
                                else
                                    nx2 = x2 + 1;
                            }
                        }
                    }

                }
                else
                {
                    //want to move towards killer
                    //cell above
                    if (y2 == ky && kx > x2)
                        nx2 = x2 + 1; //move down toward killer

                    //cell above-left
                    if (y2 < ky && kx > x2)
                    {

                        //randomly move right or down
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx2 = x2 + 1;
                        else
                            ny2 = y2 + 1;

                    }

                    //cell above-right
                    if (y2 > ky && kx > x2)
                    {
                        //randomly move left or down
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx2 = x2 + 1;
                        else
                            ny2 = y2 - 1;


                    }

                    //cell right
                    if (y2 > ky && kx == x2)
                        ny2 = y2 - 1;

                    //cell below
                    if (y2 == ky && kx < x2)
                        nx2 = x2 - 1;


                    //cell below-left
                    if (y2 < ky && kx < x2)
                    {
                        //randomly move right or up
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx2 = x2 - 1;
                        else
                            ny2 = y2 + 1;

                    }

                    //cell below-right
                    if (y2 > ky && kx < x2)
                    {
                        //randomly move left or up
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx2 = x2 - 1;
                        else
                            ny2= y2 - 1;
                    }

                    //cell left
                    if (y2 < ky && kx == x2)
                        ny2 = y2 + 1;


                }
            }
            else //double antigen cell
            {

                //want to go away if have right ant(s)
                if ((cellTwoAnt1 == antigen1 && cellTwoAnt2 == antigen2)
                        ||(cellTwoAnt1 == antigen2 && cellTwoAnt2 == antigen1))
                {
                    //cell can be above, al, ar, r, l, b, bl, br

                    //cell above
                    if (y2 == ky && kx > x2)
                    {
                        if (x2 != 0)//move up if not in first row
                            nx2 = x2 - 1;
                        else //if in first row
                        {
                            if (y2 == 0) //if in first row and first column
                                ny2 = y2 + 1;
                            else if (y2 == lastColumn)
                                ny2 = y2 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny2 = y2 + 1;
                                else
                                    ny2 = y2 - 1;
                            }

                        }
                    }

                    //cell above-left
                    if (y2 < ky && kx > x2)
                    {
                        if (x2 != 0 && y2 != 0) //if not in first row and not in first colum
                        {
                            //randomly move up or left
                            int randNum = rand()%2;

                            if (randNum == 0)//move up
                                nx2 = x2 - 1;
                            else //move left
                                ny2 = y2 - 1;

                        }
                        else if (x2 == 0 && y2 != 0) //if in first row but not in first column
                            ny2 = y2 - 1;
                        else if (x2 != 0 && y2 == 0) //if in first colum  but not in first row
                            nx2 = x2 - 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx2 = x2 + 1;
                            else
                                ny2 = y2 + 1;
                        }


                    }

                    //cell above-right
                    if (y2 > ky && kx > x2)
                    {
                        if (x2 != 0 && y2 != lastColumn) //if not in first row and not in last column
                        {
                            //randomly move up or right
                            int randNum = rand()%2;

                            if (randNum == 0)//move up
                                nx2 = x2 - 1;
                            else //move right
                                ny2 = y2 + 1;

                        }
                        else if (x2 == 0 && y2 != lastColumn) //if in first row but not in last column
                            ny2 = y2 + 1;
                        else if (x2 != 0 && y2 == lastColumn) //if in last column  but not in first row
                            nx2 = x2 - 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx1 = x1 + 1;
                            else
                                ny1 = y1 - 1;
                        }


                    }

                    //cell right
                    if (y2 > ky && kx == x2)
                    {
                        if (y2 != lastColumn)
                            ny2 = y2 + 1;
                        else
                        {
                            if (x2 == 0)
                                nx2 = x2 + 1;
                            else if (x2 == lastRow)
                                nx2 = x2 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx2 = x2 - 1;
                                else
                                    nx2 = x2 + 1;
                            }
                        }
                    }

                    //cell below
                    if (y2 == ky && kx < x2)
                    {
                        if (x2 != lastRow)//move down if not in last row
                            nx2 = x2 + 1;
                        else //if in last row
                        {
                            if (y2 == 0) //if in last row and first column
                                ny2 = y2 + 1;
                            else if (y2 == lastColumn)
                                ny2 = y2 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny2 = y2 + 1;
                                else
                                    ny2 = y2 - 1;
                            }

                        }
                    }

                    //cell below-left
                    if (y2 < ky && kx < x2)
                    {
                        if (x2 != lastRow && y2 != 0) //if not in last row and not in first colum
                        {
                            //randomly move down or left
                            int randNum = rand()%2;

                            if (randNum == 0)//move down
                                nx2 = x2 + 1;
                            else //move left
                                ny2 = y2 - 1;

                        }
                        else if (x2 == lastRow && y2 != 0) //if in last row but not in first column
                            ny2 = y2 - 1;
                        else if (x2 != lastRow && y2 == 0) //if in first colum  but not in last row
                            nx2 = x2 + 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 + 1;
                        }


                    }

                    //cell below-right
                    if (y2 > ky && kx < x2)
                    {
                        if (x2 != lastColumn && y2 != lastColumn) //if not in last row and not in last column
                        {
                            //randomly move down or right
                            int randNum = rand()%2;

                            if (randNum == 0)//move down
                                nx2 = x2 + 1;
                            else //move right
                                ny2 = y2 + 1;

                        }
                        else if (x2 == lastColumn && y2 != lastColumn) //if in first row but not in last column
                            ny2 = y2 + 1;
                        else if (x2 != lastColumn && y2 == lastColumn) //if in last column  but not in first row
                            nx2 = x2 + 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx1 = x1 - 1;
                            else
                                ny1 = y1 - 1;
                        }


                    }

                    //cell left
                    if (y2 < ky && kx == x2)
                    {
                        if (y2 != 0)
                            ny2 = y2 - 1;
                        else
                        {
                            if (x2 == 0)
                                nx2 = x2 + 1;
                            else if (x2 == lastRow)
                                nx2 = x2 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx2 = x2 - 1;
                                else
                                    nx2 = x2 + 1;
                            }
                        }
                    }

                }
                else
                {
                    //want to move towards killer
                    //cell above
                    if (y2 == ky && kx > x2)
                        nx2 = x2 + 1; //move down toward killer

                    //cell above-left
                    if (y2 < ky && kx > x2)
                    {

                        //randomly move right or down
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx2 = x2 + 1;
                        else
                            ny2 = y2 + 1;

                    }

                    //cell above-right
                    if (y2 > ky && kx > x2)
                    {
                        //randomly move left or down
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx2 = x2 + 1;
                        else
                            ny2 = y2 - 1;


                    }

                    //cell right
                    if (y2 > ky && kx == x2)
                        ny2 = y2 - 1;

                    //cell below
                    if (y2 == ky && kx < x2)
                        nx2 = x2 - 1;


                    //cell below-left
                    if (y2 < ky && kx < x2)
                    {
                        //randomly move right or up
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx2 = x2 - 1;
                        else
                            ny2 = y2 + 1;

                    }

                    //cell below-right
                    if (y2 > ky && kx < x2)
                    {
                        //randomly move left or up
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx2 = x2 - 1;
                        else
                            ny2= y2 - 1;
                    }

                    //cell left
                    if (y2 < ky && kx == x2)
                        ny2 = y2 + 1;


                }


            }
        }



        //show cell and set new position only if alive...
        //only set new position if space open

        if (!cellTwoDead)
        {
            if (nx1 == nx2 && ny1 == ny2) //if going to occupied space
            {
                //set to old position (dont move)
                labels[y2*boardSize + x2]->setPixmap(*twoCellImage);
                CellPositions[1].setX(x2);
                CellPositions[1].setY(x2);

                nx2 = x2;
                ny2 = y2;
            }
            else
            {
                if (nx2 == killerPosition->rx() && ny2 == killerPosition->ry())
                {
                    if (livesLeft > 0)
                    {
                        lives[livesLeft-1]->clear();
                        livesLeft--;
                    }
                }
                labels[ny2*boardSize + nx2]->setPixmap(*twoCellImage);
                CellPositions[1].setX(nx2);
                CellPositions[1].setY(ny2);
            }
        }

        //with threeCell (can be single ant or double ant)
        if (!cellThreeDead) //only move if alive
        {

            //if single antigen cell
            if (cellThreeAnt2 == -1 && cellThreeAnt1 != -1)
            {

                //want to go away if have right ant(s)
                if (cellThreeAnt1 == antigen1 || cellThreeAnt1 == antigen2)
                {
                    //cell can be above, al, ar, r, l, b, bl, br

                    //cell above
                    if (y3 == ky && kx > x3)
                    {
                        if (x3 != 0)//move up if not in first row
                            nx3 = x3 - 1;
                        else //if in first row
                        {
                            if (y3 == 0) //if in first row and first column
                                ny3 = y3 + 1;
                            else if (y3 == lastColumn)
                                ny3 = y3 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny3 = y3 + 1;
                                else
                                    ny3 = y3 - 1;
                            }

                        }
                    }

                    //cell above-left
                    if (y3 < ky && kx > x3)
                    {
                        if (x3 != 0 && y3 != 0) //if not in first row and not in first colum
                        {
                            //randomly move up or left
                            int randNum = rand()%2;

                            if (randNum == 0)//move up
                                nx3 = x3 - 1;
                            else //move left
                                ny3 = y3 - 1;

                        }
                        else if (x3 == 0 && y3 != 0) //if in first row but not in first column
                            ny3 = y3 - 1;
                        else if (x3 != 0 && y3 == 0) //if in first colum  but not in first row
                            nx3 = x3 - 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx3 = x3 + 1;
                            else
                                ny3 = y3 + 1;
                        }


                    }

                    //cell above-right
                    if (y3 > ky && kx > x3)
                    {
                        if (x3 != 0 && y3!= lastColumn) //if not in first row and not in last column
                        {
                            //randomly move up or right
                            int randNum = rand()%2;

                            if (randNum == 0)//move up
                                nx3 = x3- 1;
                            else //move right
                                ny3 = y3 + 1;

                        }
                        else if (x3 == 0 && y3 != lastColumn) //if in first row but not in last column
                            ny3 = y3 + 1;
                        else if (x3 != 0 && y3 == lastColumn) //if in last column  but not in first row
                            nx3 = x3 - 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx3 = x3 + 1;
                            else
                                ny3 = y3 - 1;
                        }


                    }

                    //cell right
                    if (y3 > ky && kx == x3)
                    {
                        if (y3 != lastColumn)
                            ny3 = y3 + 1;
                        else
                        {
                            if (x3 == 0)
                                nx3 = x3 + 1;
                            else if (x3 == lastRow)
                                nx3 = x3 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx3 = x3 - 1;
                                else
                                    nx3 = x3 + 1;
                            }
                        }
                    }

                    //cell below
                    if (y3 == ky && kx < x3)
                    {
                        if (x3 != lastRow)//move down if not in last row
                            nx3 = x3 + 1;
                        else //if in last row
                        {
                            if (y3 == 0) //if in last row and first column
                                ny3 = y3 + 1;
                            else if (y3 == lastColumn)
                                ny3 = y3 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny3 = y3 + 1;
                                else
                                    ny3 = y3 - 1;
                            }

                        }
                    }

                    //cell below-left
                    if (y3 < ky && kx < x3)
                    {
                        if (x3 != lastRow && y3 != 0) //if not in last row and not in first colum
                        {
                            //randomly move down or left
                            int randNum = rand()%2;

                            if (randNum == 0)//move down
                                nx3 = x3 + 1;
                            else //move left
                                ny3 = y3 - 1;

                        }
                        else if (x3 == lastRow && y3 != 0) //if in last row but not in first column
                            ny3 = y3 - 1;
                        else if (x3 != lastRow && y3 == 0) //if in first colum  but not in last row
                            nx3 = x3 + 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx3 = x3 - 1;
                            else
                                ny3 = y3 + 1;
                        }

                    }

                    //cell below-right
                    if (y3 > ky && kx < x3)
                    {
                        if (x3 != lastColumn && y3 != lastColumn) //if not in last row and not in last column
                        {
                            //randomly move down or right
                            int randNum = rand()%2;

                            if (randNum == 0)//move down
                                nx3 = x3 + 1;
                            else //move right
                                ny3 = y3 + 1;

                        }
                        else if (x3 == lastColumn && y3 != lastColumn) //if in first row but not in last column
                            ny3 = y3 + 1;
                        else if (x3 != lastColumn && y3 == lastColumn) //if in last column  but not in first row
                            nx3 = x3 + 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx3 = x3 - 1;
                            else
                                ny3 = y3 - 1;
                        }


                    }

                    //cell left
                    if (y3 < ky && kx == x3)
                    {
                        if (y3 != 0)
                            ny3 = y3 - 1;
                        else
                        {
                            if (x3 == 0)
                                nx3 = x3 + 1;
                            else if (x3 == lastRow)
                                nx3 = x3 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx3 = x3 - 1;
                                else
                                    nx3 = x3 + 1;
                            }
                        }
                    }

                }
                else
                {
                    //want to move towards killer
                    //cell above
                    if (y3 == ky && kx > x3)
                        nx3 = x3 + 1; //move down toward killer

                    //cell above-left
                    if (y3 < ky && kx > x3)
                    {

                        //randomly move right or down
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx3 = x3 + 1;
                        else
                            ny3 = y3 + 1;

                    }

                    //cell above-right
                    if (y3 > ky && kx > x3)
                    {
                        //randomly move left or down
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx3 = x3 + 1;
                        else
                            ny3 = y3 - 1;


                    }

                    //cell right
                    if (y3 > ky && kx == x3)
                        ny3 = y3 - 1;

                    //cell below
                    if (y3 == ky && kx < x3)
                        nx3 = x3 - 1;


                    //cell below-left
                    if (y3 < ky && kx < x3)
                    {
                        //randomly move right or up
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx3 = x3 - 1;
                        else
                            ny3 = y3 + 1;

                    }

                    //cell below-right
                    if (y3 > ky && kx < x3)
                    {
                        //randomly move left or up
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx3 = x3 - 1;
                        else
                            ny3 = y3 - 1;
                    }

                    //cell left
                    if (y3 < ky && kx == x3)
                        ny3 = y3 + 1;


                }
            }
            else //double antigen cell
            {

                //want to go away if have right ant(s)
                if ((cellThreeAnt1 == antigen1 && cellThreeAnt2 == antigen2)
                        ||(cellThreeAnt1 == antigen2 && cellThreeAnt2 == antigen1))
                {
                    //cell can be above, al, ar, r, l, b, bl, br

                    //cell above
                    if (y3 == ky && kx > x3)
                    {
                        if (x3 != 0)//move up if not in first row
                            nx3 = x3 - 1;
                        else //if in first row
                        {
                            if (y3 == 0) //if in first row and first column
                                ny3 = y3 + 1;
                            else if (y3 == lastColumn)
                                ny3 = y3 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny3 = y3 + 1;
                                else
                                    ny3 = y3 - 1;
                            }

                        }
                    }

                    //cell above-left
                    if (y3 < ky && kx > x3)
                    {
                        if (x3 != 0 && y3 != 0) //if not in first row and not in first colum
                        {
                            //randomly move up or left
                            int randNum = rand()%2;

                            if (randNum == 0)//move up
                                nx3 = x3 - 1;
                            else //move left
                                ny3 = y3 - 1;

                        }
                        else if (x3 == 0 && y3 != 0) //if in first row but not in first column
                            ny3 = y3 - 1;
                        else if (x3 != 0 && y3 == 0) //if in first colum  but not in first row
                            nx3 = x3 - 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx3 = x3 + 1;
                            else
                                ny3 = y3 + 1;
                        }


                    }

                    //cell above-right
                    if (y3 > ky && kx > x3)
                    {
                        if (x3 != 0 && y3 != lastColumn) //if not in first row and not in last column
                        {
                            //randomly move up or right
                            int randNum = rand()%2;

                            if (randNum == 0)//move up
                                nx3 = x3 - 1;
                            else //move right
                                ny3 = y3 + 1;

                        }
                        else if (x3 == 0 && y3 != lastColumn) //if in first row but not in last column
                            ny3 = y3 + 1;
                        else if (x3 != 0 && y3 == lastColumn) //if in last column  but not in first row
                            nx3 = x3 - 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx3 = x3 + 1;
                            else
                                ny3 = y3 - 1;
                        }


                    }

                    //cell right
                    if (y3 > ky && kx == x3)
                    {
                        if (y3 != lastColumn)
                            ny3 = y3 + 1;
                        else
                        {
                            if (x3 == 0)
                                nx3 = x3 + 1;
                            else if (x3 == lastRow)
                                nx3 = x3 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx3 = x3 - 1;
                                else
                                    nx3= x3 + 1;
                            }
                        }
                    }

                    //cell below
                    if (y3 == ky && kx < x3)
                    {
                        if (x3 != lastRow)//move down if not in last row
                            nx3 = x3 + 1;
                        else //if in last row
                        {
                            if (y3 == 0) //if in last row and first column
                                ny3 = y3+ 1;
                            else if (y3 == lastColumn)
                                ny3 = y3- 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    ny3 = y3 + 1;
                                else
                                    ny3 = y3 - 1;
                            }

                        }
                    }

                    //cell below-left
                    if (y3 < ky && kx < x3)
                    {
                        if (x3 != lastRow && y3 != 0) //if not in last row and not in first colum
                        {
                            //randomly move down or left
                            int randNum = rand()%2;

                            if (randNum == 0)//move down
                                nx3 = x3 + 1;
                            else //move left
                                ny3 = y3 - 1;

                        }
                        else if (x3 == lastRow && y3 != 0) //if in last row but not in first column
                            ny3 = y3 - 1;
                        else if (x3 != lastRow && y3 == 0) //if in first colum  but not in last row
                            nx3 = x3 + 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx3 = x3 - 1;
                            else
                                ny3 = y3 + 1;
                        }


                    }

                    //cell below-right
                    if (y3 > ky && kx < x3)
                    {
                        if (x3 != lastColumn && y3 != lastColumn) //if not in last row and not in last column
                        {
                            //randomly move down or right
                            int randNum = rand()%2;

                            if (randNum == 0)//move down
                                nx3 = x3 + 1;
                            else //move right
                                ny3 = y3 + 1;

                        }
                        else if (x3 == lastColumn && y3 != lastColumn) //if in first row but not in last column
                            ny3 = y3 + 1;
                        else if (x3 != lastColumn && y3 == lastColumn) //if in last column  but not in first row
                            nx3= x3 + 1;
                        else
                        {
                            int randNum = rand()%2;

                            if (randNum == 0)
                                nx3 = x3 - 1;
                            else
                                ny3 = y3 - 1;
                        }


                    }

                    //cell left
                    if (y3 < ky && kx == x3)
                    {
                        if (y3 != 0)
                            ny3 = y3 - 1;
                        else
                        {
                            if (x3 == 0)
                                nx3 = x3 + 1;
                            else if (x3 == lastRow)
                                nx3 = x3 - 1;
                            else
                            {
                                int randNum = rand()%2;

                                if (randNum == 0)
                                    nx3 = x3 - 1;
                                else
                                    nx3 = x3 + 1;
                            }
                        }
                    }

                }
                else
                {
                    //want to move towards killer
                    //cell above
                    if (y3 == ky && kx > x3)
                        nx3 = x3 + 1; //move down toward killer

                    //cell above-left
                    if (y3 < ky && kx > x3)
                    {

                        //randomly move right or down
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx3 = x3 + 1;
                        else
                            ny3 = y3 + 1;

                    }

                    //cell above-right
                    if (y3 > ky && kx > x3)
                    {
                        //randomly move left or down
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx3 = x3 + 1;
                        else
                            ny3 = y3 - 1;


                    }

                    //cell right
                    if (y3 > ky && kx == x3)
                        ny3 = y3 - 1;

                    //cell below
                    if (y3 == ky && kx < x3)
                        nx3 = x3 - 1;


                    //cell below-left
                    if (y3 < ky && kx < x3)
                    {
                        //randomly move right or up
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx3 = x3 - 1;
                        else
                            ny3 = y3 + 1;

                    }

                    //cell below-right
                    if (y3 > ky && kx < x3)
                    {
                        //randomly move left or up
                        int randNum = rand()%2;
                        if (randNum == 0)
                            nx3 = x3 - 1;
                        else
                            ny3 = y3 - 1;
                    }

                    //cell left
                    if (y3 < ky && kx == x3)
                        ny3 = y3 + 1;


                }
            }

        }



        //show cell and set new position only if alive and space available
        if (!cellThreeDead)
        {

            if ((nx3 == nx1 && ny3 == ny1)||(nx3 == nx2 && ny3 == ny2))
            {
                labels[y3*boardSize + x3]->setPixmap(*threeCellImage);
                CellPositions[2].setX(x3);
                CellPositions[2].setY(y3);
            }
            else
            {
                if (nx3 == killerPosition->rx() && ny3 == killerPosition->ry())
                {
                    if (livesLeft > 0)
                    {
                        lives[livesLeft-1]->clear();
                        livesLeft--;
                    }
                }
                labels[ny3*boardSize + nx3]->setPixmap(*threeCellImage);
                CellPositions[2].setX(nx3);
                CellPositions[2].setY(ny3);
            }
        }

        if (!cellOneDead)
            labels[y1*boardSize + x1]->clear();

        if (!cellTwoDead)
            labels[y2*boardSize + x2]->clear();

        if (!cellThreeDead)
            labels[y3*boardSize + x3]->clear();

    }
    }

    QCoreApplication::processEvents();
    repaint();
}

/**
 This member function creates a window that displays the game win contents
*/
void MainWindow::gameWin()
{
    if (difficulty == 5)
    {
        this->close();
        counter++;
        if (counter == 1)
        {
            QWidget* beatBeginner = new QWidget;
            beatBeginner->setWindowTitle("You win!");
            QLabel* winTxt = new QLabel("You completed the Beginner difficulty!");
            QLabel* nextTxt = new QLabel("Are you ready for the next level?");
            QPushButton* ready = new QPushButton("Ready!");


            QVBoxLayout* layout = new QVBoxLayout;
            QHBoxLayout* hlayout = new QHBoxLayout;

            hlayout->addWidget(ready);

            layout->addWidget(winTxt);
            layout->addSpacerItem(new QSpacerItem(10,20));
            layout->addWidget(nextTxt);
            layout->addLayout(hlayout);

            beatBeginner->setLayout(layout);

            beatBeginner->show();

            connect(ready,SIGNAL(clicked()),this,SLOT(startEasy()));
            connect(ready,SIGNAL(clicked()),beatBeginner,SLOT(close()));
            connect(ready,SIGNAL(clicked()),this,SLOT(close()));

        }
        else if (counter == 2)
        {
            QWidget* beatEasy = new QWidget;
            beatEasy->setWindowTitle("You win!");
            QLabel* winTxt = new QLabel("You completed the Easy difficulty!");
            QLabel* nextTxt = new QLabel("Are you ready for the next level?");
            QPushButton* ready = new QPushButton("Ready!");


            QVBoxLayout* layout = new QVBoxLayout;
            QHBoxLayout* hlayout = new QHBoxLayout;

            hlayout->addWidget(ready);

            layout->addWidget(winTxt);
            layout->addSpacerItem(new QSpacerItem(10,20));
            layout->addWidget(nextTxt);
            layout->addLayout(hlayout);

            beatEasy->setLayout(layout);

            beatEasy->show();

            connect(ready,SIGNAL(clicked()),this,SLOT(startMedium()));
            connect(ready,SIGNAL(clicked()),beatEasy,SLOT(close()));
            connect(ready,SIGNAL(clicked()),this,SLOT(close()));
        }
        else if (counter == 3)
        {
            QWidget* beatMedium = new QWidget;
            beatMedium->setWindowTitle("You win!");
            QLabel* winTxt = new QLabel("You completed the Medium difficulty!");
            QLabel* nextTxt = new QLabel("Are you ready for the next level?");
            QPushButton* ready = new QPushButton("Ready!");


            QVBoxLayout* layout = new QVBoxLayout;
            QHBoxLayout* hlayout = new QHBoxLayout;

            hlayout->addWidget(ready);

            layout->addWidget(winTxt);
            layout->addSpacerItem(new QSpacerItem(10,20));
            layout->addWidget(nextTxt);
            layout->addLayout(hlayout);

            beatMedium->setLayout(layout);

            beatMedium->show();

            connect(ready,SIGNAL(clicked()),this,SLOT(startHard()));
            connect(ready,SIGNAL(clicked()),beatMedium,SLOT(close()));
            connect(ready,SIGNAL(clicked()),this,SLOT(close()));
        }
        else if (counter == 4)
        {
            QWidget* beatHard = new QWidget;
            beatHard->setWindowTitle("You win!");
            QLabel* winTxt = new QLabel("You completed the Hard difficulty!");
            QLabel* nextTxt = new QLabel("Are you ready for the next level?");
            QPushButton* ready = new QPushButton("Ready!");


            QVBoxLayout* layout = new QVBoxLayout;
            QHBoxLayout* hlayout = new QHBoxLayout;

            hlayout->addWidget(ready);

            layout->addWidget(winTxt);
            layout->addSpacerItem(new QSpacerItem(10,20));
            layout->addWidget(nextTxt);
            layout->addLayout(hlayout);

            beatHard->setLayout(layout);

            beatHard->show();

            connect(ready,SIGNAL(clicked()),this,SLOT(startExpert()));
            connect(ready,SIGNAL(clicked()),beatHard,SLOT(close()));
            connect(ready,SIGNAL(clicked()),this,SLOT(close()));
        }
        else if (counter == 5)
        {
            QWidget* win = new QWidget;
            win->setWindowTitle("You win!");
            QLabel* winTxt = new QLabel("Congratulations, you won STORY MODE!!! You are a master.");
            QLabel* quitTxt = new QLabel("Would you like to play again?");
            QPushButton* yes = new QPushButton("Yes");
            QPushButton* no = new QPushButton("No");


            QVBoxLayout* layout = new QVBoxLayout;
            QHBoxLayout* hlayout = new QHBoxLayout;

            hlayout->addWidget(yes);
            hlayout->addWidget(no);

            layout->addWidget(winTxt);
            layout->addSpacerItem(new QSpacerItem(10,20));
            layout->addWidget(quitTxt);
            layout->addLayout(hlayout);

            win->setLayout(layout);

            win->show();

            connect(yes,SIGNAL(clicked()),this,SLOT(startNewGame()));
            connect(yes,SIGNAL(clicked()),win,SLOT(close()));
            connect(yes,SIGNAL(clicked()),this,SLOT(close()));
            connect(no,SIGNAL(clicked()),this,SLOT(close()));
            connect(no,SIGNAL(clicked()),win,SLOT(close()));
        }

    }
    else
    {
        QWidget* win = new QWidget;
        win->setWindowTitle("You win!");
        QLabel* winTxt = new QLabel("Congratulations, you win!");
        QLabel* quitTxt = new QLabel("Would you like to play again?");
        QPushButton* yes = new QPushButton("Yes");
        QPushButton* no = new QPushButton("No");


        QVBoxLayout* layout = new QVBoxLayout;
        QHBoxLayout* hlayout = new QHBoxLayout;

        hlayout->addWidget(yes);
        hlayout->addWidget(no);

        layout->addWidget(winTxt);
        layout->addSpacerItem(new QSpacerItem(10,20));
        layout->addWidget(quitTxt);
        layout->addLayout(hlayout);

        win->setLayout(layout);

        win->show();

        connect(yes,SIGNAL(clicked()),this,SLOT(startNewGame()));
        connect(yes,SIGNAL(clicked()),win,SLOT(close()));
        connect(yes,SIGNAL(clicked()),this,SLOT(close()));
        connect(no,SIGNAL(clicked()),this,SLOT(close()));
        connect(no,SIGNAL(clicked()),win,SLOT(close()));
    }
}

/**
 This member function creates a window that displays the game over (losing) contents
*/
void MainWindow::gameOver()
{
    QWidget* lose = new QWidget;
    lose->setWindowTitle("You lose");
    QLabel* loseTxt = new QLabel("You lost.");
    QLabel* quitTxt = new QLabel("Would you like to play again?");
    QPushButton* yes = new QPushButton("Yes");
    QPushButton* no = new QPushButton("No");


    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* hlayout = new QHBoxLayout;

    hlayout->addWidget(yes);
    hlayout->addWidget(no);

    layout->addWidget(loseTxt);
    layout->addSpacerItem(new QSpacerItem(10,20));
    layout->addWidget(quitTxt);
    layout->addLayout(hlayout);

    lose->setLayout(layout);

    lose->show();

    connect(yes,SIGNAL(clicked()),this,SLOT(startNewGame()));
    connect(yes,SIGNAL(clicked()),lose,SLOT(close()));
    connect(yes,SIGNAL(clicked()),this,SLOT(close()));
    connect(no,SIGNAL(clicked()),this,SLOT(close()));
    connect(no,SIGNAL(clicked()),lose,SLOT(close()));

}

/**
This MainWindow SLOT randomly places an antigen in an open space around each cell that is still alive
*/
void MainWindow::randPlaceAntigens()
{
    //x is column and y is row...
    //place antigens on random unoccupied spaces and show
    if (livesLeft > 0)
    {
        //place antigen in space 1 square around cell
        if (!cellOneDead) //only place antigens if alive
        {
            placeAntigens(0,cellOneAnt2);
        }

        if (!cellTwoDead) //only place antigens if alive
        {
            placeAntigens(1,cellTwoAnt2);
        }

        if (!cellThreeDead) //only place antigens if alive
        {
            placeAntigens(2,cellThreeAnt2);
        }
    }

    //QCoreApplication::processEvents();
    //repaint();
}

/**
This MainWindow member function returns whether or not the win condition (all cells are dead) has been reached

@return is true if all once alive cells are dead
*/
bool MainWindow::win()
{
    if (numberCells == 1)
        if (cellOneDead)
            return true;
        else
            return false;
    else if (numberCells == 2)
        if (cellOneDead && cellTwoDead)
            return true;
        else
            return false;
    else
        if (cellOneDead && cellTwoDead && cellThreeDead)
            return true;
        else
            return false;


}

/**
This MainWindow member function creates a new start screen leading to the creation of a new game
*/
void MainWindow::startNewGame()
{
    StartScreen* s = new StartScreen();
}

/**
This MainWindow SLOT member function creates a new game for the easy story mode
**/
void MainWindow::startEasy()
{
    this->close();
    MainWindow* e = new MainWindow(5,1,livesLeft);
    e->show();
}

/**
This MainWindow SLOT member function creates a new game for the medium story mode
**/
void MainWindow::startMedium()
{
    this->close();
    MainWindow* m = new MainWindow(5,2,livesLeft);
    m->show();
}

/**
This MainWindow SLOT member function creates a new game for the hard story mode
**/
void MainWindow::startHard()
{
    this->close();
    MainWindow* h = new MainWindow(5,3,livesLeft);
    h->show();
}

/**
This MainWindow SLOT member function creates a new game for the expert story mode
**/
void MainWindow::startExpert()
{
    this->close();
    QCoreApplication::processEvents();
    MainWindow* ex = new MainWindow(5,4,livesLeft);
    ex->show();
}

/**
This MainWIndow member function places the antigens on the board given which cell and cell type

@param cellNumber is the number of the cell; ie. cellOne (0), cellTwo(1), or cellThree(2)
@param cellAnt2 is the second antigen, and exists only to identify whether the cell is single antigen (==-1) or double antigen (!= -1)
**/
void MainWindow::placeAntigens(int cellNumber, int cellAnt2)
{
    int lastColumn = boardSize - 1;
    int lastRow = lastColumn;
    int x1 = CellPositions[cellNumber].rx();
    int y1 = CellPositions[cellNumber].ry();


    int proposedX = killerPosition->rx();
    int proposedY = killerPosition->ry();

    //if single antigen cell
    if (cellAnt2 == -1)
    {

        //dont want to spawn on killer position
        while (proposedX == killerPosition->rx() && proposedY == killerPosition->ry())
        {
            //determine valid antigen placement locations

            //cell can be in corners, side, or middle

            //top left corner...right, below right, below
            if (x1 == 0 && y1 == 0)
            {
                int randNum = rand()%3;

                if (randNum == 0) //right
                {
                    proposedX = x1 + 1;
                    proposedY = y1;
                }
                else if (randNum == 1) //below
                {
                    proposedX = x1;
                    proposedY = y1 + 1;
                }
                else //below-right
                {
                    proposedX = x1 + 1;
                    proposedY = y1 + 1;
                }
            }

            //bottom left corner...top, above right, right
            else if (x1 == 0 && y1 == lastColumn)
            {
                int randNum = rand()%3;

                if (randNum == 0) //above
                {
                    proposedX = x1;
                    proposedY = y1 - 1;
                }
                else if (randNum == 1) //right
                {
                    proposedX = x1 + 1;
                    proposedY = y1;
                }
                else //above right
                {
                    proposedX = x1 + 1;
                    proposedY = y1 - 1;
                }
            }

            //bottom right corner...left, above left, above
            else if (x1 == lastRow && y1 == lastColumn)
            {
                int randNum = rand()%3;

                if (randNum == 0) //left
                {
                    proposedX = x1 - 1;
                    proposedY = y1;
                }
                else if (randNum == 1) //above
                {
                    proposedX = x1;
                    proposedY = y1 - 1;
                }
                else //above left
                {
                    proposedX = x1 - 1;
                    proposedY = y1 - 1;
                }
            }

            //top right corner...left, below left, below
            else if (x1 == lastRow && y1 == 0)
            {
                int randNum = rand()%3;

                if (randNum == 0) //below
                {
                    proposedX = x1;
                    proposedY = y1 + 1;
                }
                else if (randNum == 1) //left
                {
                    proposedX = x1 - 1;
                    proposedY = y1;
                }
                else //below left
                {
                    proposedX = x1 - 1;
                    proposedY = y1 + 1;
                }
            }

            //on left but not in corner...right, above, ar, br, below
            else if (x1 == 0 && (y1 != lastColumn || y1 != 0))
            {
                int randNum = rand()%5;

                if (randNum == 0) //right
                {
                    proposedX = x1 + 1;
                    proposedY = y1;
                }
                else if (randNum == 1) //above
                {
                    proposedX = x1;
                    proposedY = y1 - 1;
                }
                else if (randNum == 2) //below
                {
                    proposedX = x1;
                    proposedY = y1 + 1;
                }
                else if (randNum == 3) //below right
                {
                    proposedX = x1 + 1;
                    proposedY = y1 + 1;
                }
                else //above right
                {
                    proposedX = x1 + 1;
                    proposedY = y1 - 1;
                }
            }

            //on right but not in corner...left, above, al, bl, below
            else if (x1 == lastRow && (y1 != lastColumn && y1 != 0))
            {
                int randNum = rand()%5;

                if (randNum == 0) //left
                {
                    proposedX = x1 - 1;
                    proposedY = y1;
                }
                else if (randNum == 1) //above
                {
                    proposedX = x1;
                    proposedY = y1 - 1;
                }
                else if (randNum == 2) //above left
                {
                    proposedX = x1 - 1;
                    proposedY = y1 - 1;
                }
                else if (randNum == 3) //below left
                {
                    proposedX = x1 - 1;
                    proposedY = y1 + 1;
                }
                else //below
                {
                    proposedX = x1;
                    proposedY = y1 + 1;
                }
            }

            //on top but not in corner...below, br, r, bl, left
            else if (y1 == 0 && (x1 != lastRow && x1 != 0))
            {
                int randNum = rand()%5;

                if (randNum == 0) //left
                {
                    proposedX = x1 - 1;
                    proposedY = y1;
                }
                else if (randNum == 1) //below left
                {
                    proposedX = x1 - 1;
                    proposedY = y1 + 1;
                }
                else if (randNum == 2) //below
                {
                    proposedX = x1;
                    proposedY = y1 + 1;
                }
                else if (randNum == 3) //below right
                {
                    proposedX = x1 + 1;
                    proposedY = y1 + 1;
                }
                else //right
                {
                    proposedX = x1 + 1;
                    proposedY = y1;
                }
            }

            //on bottom but not in corner...above, al, l, right, ar
            else if (y1 == lastColumn && (x1 != lastRow && x1 != 0))
            {
                int randNum = rand()%5;

                if (randNum == 0) //left
                {
                    proposedX = x1 - 1;
                    proposedY = y1;
                }
                else if (randNum == 1) //above left
                {
                    proposedX = x1 - 1;
                    proposedY = y1 - 1;
                }
                else if (randNum == 2) //above
                {
                    proposedX = x1;
                    proposedY = y1 - 1;
                }
                else if (randNum == 3) //above right
                {
                    proposedX = x1 + 1;
                    proposedY = y1 - 1;
                }
                else //right
                {
                    proposedX = x1 + 1;
                    proposedY = y1;
                }
            }

            //in middle...a,al,ar,r,l,bl,br,b
            else
            {
                int randNum = rand()%8;

                //left
                if (randNum == 0)
                {
                    proposedX = x1 - 1;
                    proposedY = y1;
                }
                //above left
                else if (randNum == 1)
                {
                    proposedX = x1 - 1;
                    proposedY = y1 - 1;
                }
                //below left
                else if (randNum == 2)
                {
                    proposedX = x1 - 1;
                    proposedY = y1 + 1;
                }
                //below
                else if (randNum == 3)
                {
                    proposedX = x1;
                    proposedY = y1 + 1;
                }
                //above
                else if (randNum == 4)
                {
                    proposedX = x1;
                    proposedY = y1 - 1;
                }
                //above right
                else if (randNum == 5)
                {
                    proposedX = x1 + 1;
                    proposedY = y1 - 1;
                }
                //below right
                else if (randNum == 6)
                {
                    proposedX = x1 + 1;
                    proposedY = y1 + 1;
                }
                //right
                else
                {
                    proposedX = x1 + 1;
                    proposedY = y1;
                }
            }

        }

        //clear previous antigen location if on board
        if (antigenPositions[cellNumber].ry() == -1 || antigenPositions[cellNumber].rx() == -1)
        {
            //do nothing
        }
        else
        {
            labels[antigenPositions[cellNumber].ry()*boardSize + antigenPositions[cellNumber].rx()]->clear();
        }
        antigenPositions[cellNumber].setX(proposedX);
        antigenPositions[cellNumber].setY(proposedY);

        if (cellNumber == 0)
        {
            labels[proposedY*boardSize + proposedX]->setPixmap(*cellOneAnt1Image);
            cellOneAntDisplayed = cellOneAnt1Image;
            cellOneAntDis = cellOneAnt1;
        }
        else if (cellNumber == 1)
        {
            labels[proposedY*boardSize + proposedX]->setPixmap(*cellTwoAnt1Image);
            cellTwoAntDisplayed = cellTwoAnt1Image;
            cellTwoAntDis = cellTwoAnt1;
        }
        else if (cellNumber == 2)
        {
            labels[proposedY*boardSize + proposedX]->setPixmap(*cellThreeAnt1Image);
            cellThreeAntDisplayed = cellThreeAnt1Image;
            cellThreeAntDis = cellThreeAnt1;
        }

    }
    else //if double antigen cell
    {


        //dont want to spawn on killer position
        while (proposedX == killerPosition->rx() && proposedY == killerPosition->ry())
        {
            //determine valid antigen placement locations

            //cell can be in corners, side, or middle

            //top left corner...right, below right, below
            if (x1 == 0 && y1 == 0)
            {
                int randNum = rand()%3;

                if (randNum == 0) //right
                {
                    proposedX = x1 + 1;
                    proposedY = y1;
                }
                else if (randNum == 1) //below
                {
                    proposedX = x1;
                    proposedY = y1 + 1;
                }
                else //below-right
                {
                    proposedX = x1 + 1;
                    proposedY = y1 + 1;
                }
            }

            //bottom left corner...top, above right, right
            else if (x1 == 0 && y1 == lastColumn)
            {
                int randNum = rand()%3;

                if (randNum == 0) //above
                {
                    proposedX = x1;
                    proposedY = y1 - 1;
                }
                else if (randNum == 1) //right
                {
                    proposedX = x1 + 1;
                    proposedY = y1;
                }
                else //above right
                {
                    proposedX = x1 + 1;
                    proposedY = y1 - 1;
                }
            }

            //bottom right corner...left, above left, above
            else if (x1 == lastRow && y1 == lastColumn)
            {
                int randNum = rand()%3;

                if (randNum == 0) //left
                {
                    proposedX = x1 - 1;
                    proposedY = y1;
                }
                else if (randNum == 1) //above
                {
                    proposedX = x1;
                    proposedY = y1 - 1;
                }
                else //above left
                {
                    proposedX = x1 - 1;
                    proposedY = y1 - 1;
                }
            }

            //top right corner...left, below left, below
            else if (x1 == lastRow && y1 == 0)
            {
                int randNum = rand()%3;

                if (randNum == 0) //below
                {
                    proposedX = x1;
                    proposedY = y1 + 1;
                }
                else if (randNum == 1) //left
                {
                    proposedX = x1 - 1;
                    proposedY = y1;
                }
                else //below left
                {
                    proposedX = x1 - 1;
                    proposedY = y1 + 1;
                }
            }

            //on left but not in corner...right, above, ar, br, below
            else if (x1 == 0 && (y1 != lastColumn || y1 != 0))
            {
                int randNum = rand()%5;

                if (randNum == 0) //right
                {
                    proposedX = x1 + 1;
                    proposedY = y1;
                }
                else if (randNum == 1) //above
                {
                    proposedX = x1;
                    proposedY = y1 - 1;
                }
                else if (randNum == 2) //below
                {
                    proposedX = x1;
                    proposedY = y1 + 1;
                }
                else if (randNum == 3) //below right
                {
                    proposedX = x1 + 1;
                    proposedY = y1 + 1;
                }
                else //above right
                {
                    proposedX = x1 + 1;
                    proposedY = y1 - 1;
                }
            }

            //on right but not in corner...left, above, al, bl, below
            else if (x1 == lastRow && (y1 != lastColumn && y1 != 0))
            {
                int randNum = rand()%5;

                if (randNum == 0) //left
                {
                    proposedX = x1 - 1;
                    proposedY = y1;
                }
                else if (randNum == 1) //above
                {
                    proposedX = x1;
                    proposedY = y1 - 1;
                }
                else if (randNum == 2) //above left
                {
                    proposedX = x1 - 1;
                    proposedY = y1 - 1;
                }
                else if (randNum == 3) //below left
                {
                    proposedX = x1 - 1;
                    proposedY = y1 + 1;
                }
                else //below
                {
                    proposedX = x1;
                    proposedY = y1 + 1;
                }
            }

            //on top but not in corner...below, br, r, bl, left
            else if (y1 == 0 && (x1 != lastRow && x1 != 0))
            {
                int randNum = rand()%5;

                if (randNum == 0) //left
                {
                    proposedX = x1 - 1;
                    proposedY = y1;
                }
                else if (randNum == 1) //below left
                {
                    proposedX = x1 - 1;
                    proposedY = y1 + 1;
                }
                else if (randNum == 2) //below
                {
                    proposedX = x1;
                    proposedY = y1 + 1;
                }
                else if (randNum == 3) //below right
                {
                    proposedX = x1 + 1;
                    proposedY = y1 + 1;
                }
                else //right
                {
                    proposedX = x1 + 1;
                    proposedY = y1;
                }
            }

            //on bottom but not in corner...above, al, l, right, ar
            else if (y1 == lastColumn && (x1 != lastRow && x1 != 0))
            {
                int randNum = rand()%5;

                if (randNum == 0) //left
                {
                    proposedX = x1 - 1;
                    proposedY = y1;
                }
                else if (randNum == 1) //above left
                {
                    proposedX = x1 - 1;
                    proposedY = y1 - 1;
                }
                else if (randNum == 2) //above
                {
                    proposedX = x1;
                    proposedY = y1 - 1;
                }
                else if (randNum == 3) //above right
                {
                    proposedX = x1 + 1;
                    proposedY = y1 - 1;
                }
                else //right
                {
                    proposedX = x1 + 1;
                    proposedY = y1;
                }
            }

            //in middle...a,al,ar,r,l,bl,br,b
            else
            {
                int randNum = rand()%8;

                //left
                if (randNum == 0)
                {
                    proposedX = x1 - 1;
                    proposedY = y1;
                }
                //above left
                else if (randNum == 1)
                {
                    proposedX = x1 - 1;
                    proposedY = y1 - 1;
                }
                //below left
                else if (randNum == 2)
                {
                    proposedX = x1 - 1;
                    proposedY = y1 + 1;
                }
                //below
                else if (randNum == 3)
                {
                    proposedX = x1;
                    proposedY = y1 + 1;
                }
                //above
                else if (randNum == 4)
                {
                    proposedX = x1;
                    proposedY = y1 - 1;
                }
                //above right
                else if (randNum == 5)
                {
                    proposedX = x1 + 1;
                    proposedY = y1 - 1;
                }
                //below right
                else if (randNum == 6)
                {
                    proposedX = x1 + 1;
                    proposedY = y1 + 1;
                }
                //right
                else
                {
                    proposedX = x1 + 1;
                    proposedY = y1;
                }
            }

        }

        //clear previous antigen location if on board
        if (antigenPositions[cellNumber].ry() == -1 || antigenPositions[cellNumber].rx() == -1)
        {
            //do nothing
        }
        else
        {
            labels[antigenPositions[cellNumber].ry()*boardSize + antigenPositions[cellNumber].rx()]->clear();
        }
        antigenPositions[cellNumber].setX(proposedX);
        antigenPositions[cellNumber].setY(proposedY);

        int randNum = rand()%2;
        if (randNum == 0)
        {
            if (cellNumber == 0)
            {
                labels[proposedY*boardSize + proposedX]->setPixmap(*cellOneAnt1Image);
                cellOneAntDisplayed = cellOneAnt1Image;
                cellOneAntDis = cellOneAnt1;
            }
            else if (cellNumber == 1)
            {
                labels[proposedY*boardSize + proposedX]->setPixmap(*cellTwoAnt1Image);
                cellTwoAntDisplayed = cellTwoAnt1Image;
                cellTwoAntDis = cellTwoAnt1;
            }
            else if (cellNumber == 2)
            {
                labels[proposedY*boardSize + proposedX]->setPixmap(*cellThreeAnt1Image);
                cellThreeAntDisplayed = cellThreeAnt1Image;
                cellThreeAntDis = cellThreeAnt1;
            }
        }
        else
        {
            if (cellNumber == 0)
            {
                labels[proposedY*boardSize + proposedX]->setPixmap(*cellOneAnt2Image);
                cellOneAntDisplayed = cellOneAnt2Image;
                cellOneAntDis = cellOneAnt2;
            }
            else if (cellNumber == 1)
            {
                labels[proposedY*boardSize + proposedX]->setPixmap(*cellTwoAnt2Image);
                cellTwoAntDisplayed = cellTwoAnt2Image;
                cellTwoAntDis = cellTwoAnt2;
            }
            else if (cellNumber == 2)
            {
                labels[proposedY*boardSize + proposedX]->setPixmap(*cellThreeAnt2Image);
                cellThreeAntDisplayed = cellThreeAnt2Image;
                cellThreeAntDis = cellThreeAnt2;
            }
        }
    }
}
