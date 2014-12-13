#include "startscreen.h"

/**
This StartScreen default constructor creates all the visuals of the class as wells as the connect statements.
*/
StartScreen::StartScreen()
{

    QWidget* window = new QWidget;

    welcome = new QLabel("Welcome to Killer T!!");
    QLabel* insTxt = new QLabel("New to KillerT? View the instructions:");

    instructions = new QPushButton("View Instructions");
    instructions->setFixedSize(100,20);

    diffSelect = new QLabel("Please select a difficulty:");
    beginner = new QRadioButton("Beginner (one single antigen cell)");
    easy = new QRadioButton("Easy (two single antigen cells)");;
    medium = new QRadioButton("Medium (one single antigen cell, one double antigen cell)");
    hard = new QRadioButton("Hard (two single antigen cell, one double antigen cell)");
    expert = new QRadioButton("Expert (one single antigen cell, two double antigen cell)");
    story = new QRadioButton("Story (5 lives, all modes back to back to back to back to back)");

    start = new QPushButton("START");
    start->setDisabled(true);

    QVBoxLayout* vlayout = new QVBoxLayout;

    vlayout->addWidget(welcome);
    vlayout->addSpacerItem(new QSpacerItem(2,30));
    vlayout->addWidget(insTxt);
    vlayout->addWidget(instructions);
    vlayout->addSpacerItem(new QSpacerItem(2,30));
    vlayout->addWidget(diffSelect);
    vlayout->addWidget(beginner);
    vlayout->addWidget(easy);
    vlayout->addWidget(medium);
    vlayout->addWidget(hard);
    vlayout->addWidget(expert);
    vlayout->addWidget(story);
    vlayout->addSpacerItem(new QSpacerItem(2,30));
    vlayout->addWidget(start);

    QObject::connect(beginner,SIGNAL(clicked(bool)),start,SLOT(setEnabled(bool)));
    QObject::connect(easy,SIGNAL(clicked(bool)),start,SLOT(setEnabled(bool)));
    QObject::connect(medium,SIGNAL(clicked(bool)),start,SLOT(setEnabled(bool)));
    QObject::connect(hard,SIGNAL(clicked(bool)),start,SLOT(setEnabled(bool)));
    QObject::connect(expert,SIGNAL(clicked(bool)),start,SLOT(setEnabled(bool)));
    QObject::connect(story,SIGNAL(clicked(bool)),start,SLOT(setEnabled(bool)));

    QObject::connect(start,SIGNAL(clicked()),this,SLOT(setDifficulty()));
    QObject::connect(start,SIGNAL(clicked()),window,SLOT(close()));
    QObject::connect(start,SIGNAL(clicked()),this,SLOT(createGame()));
    QObject::connect(instructions,SIGNAL(clicked()),this,SLOT(displayInstructions()));


    window->setLayout(vlayout);


    window->setFixedSize(350,350);

    window->show();

}

/**
This SLOT function sets the difficulty level value held by the StartScreen private variable.
*/
void StartScreen::setDifficulty()
{
    if (beginner->isChecked())
        difficulty = 0;
    else if (easy->isChecked())
        difficulty = 1;
    else if (medium->isChecked())
        difficulty = 2;
    else if (hard->isChecked())
        difficulty = 3;
    else if (expert->isChecked())
        difficulty = 4;
    else
        difficulty = 5;
}

/**
This SLOT function creates a game (MainWindow) with the difficulty held by the private difficulty variable
*/
void StartScreen::createGame()
{
    if (difficulty == 5)
    {
        MainWindow* w = new MainWindow(difficulty,0,5);

        w->show();
    }
    else
    {
        MainWindow* w = new MainWindow(difficulty,-1,3);

        w->show();

    }
}

/**
This SLOT function displays a window giving the instructions to the game
*/
void StartScreen::displayInstructions()
{

    QString killerTFile("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\T.jpg");
    killerImage = new QPixmap(killerTFile);


    QString redCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\red.png");
    singleAntExample = new QPixmap(redCell);

    QString purpleCell("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\purple.png");
    doubleAntExample = new QPixmap(purpleCell);

    QString redAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\redAnt.jpg");
    antExample = new QPixmap (redAnt);


    QString blueAnt("C:\\Users\\Daniel\\Documents\\UCLA\\PIC 10C\\blueAnt.jpg");
    antExample2 = new QPixmap (blueAnt);

    QWidget* window = new QWidget;
    window->setWindowTitle("Instructions");

    QVBoxLayout* mainLayout = new QVBoxLayout;

    QLabel* goal = new QLabel("Goal: The purpose of the game is to kill the opposing cell(s) before you die.\n");
    QLabel* controls = new QLabel("Controls: Use the arrow keys to move.");

    mainLayout->addWidget(goal);
    mainLayout->addWidget(controls);


    QHBoxLayout* htemp = new QHBoxLayout;
    QLabel* killer = new QLabel("This is YOU, the killer T cell:");
    QLabel* killerLabel = new QLabel;
    killerLabel->setPixmap(*killerImage);
    killerLabel->setMinimumSize(40,40);
    killerLabel->setMaximumSize(40,40);
    killerLabel->setScaledContents(true);
    htemp->addWidget(killer);
    htemp->addWidget(killerLabel);
    htemp->addSpacerItem(new QSpacerItem(550,40));

    mainLayout->addLayout(htemp);

    QLabel* cellExp = new QLabel("There are two types of opposing cells:");
    mainLayout->addWidget(cellExp);

    QHBoxLayout* singleLayout = new QHBoxLayout;
    QHBoxLayout* doubleLayout = new QHBoxLayout;

    QLabel* singleAntCell = new QLabel("\t1. Single Antigen Cell:");
    QLabel* doubleAntCell = new QLabel("\t2. Double Antigen Cell:");

    singleLayout->addWidget(singleAntCell);

    QLabel* singleLabel = new QLabel;
    singleLabel->setPixmap(*singleAntExample);
    singleLabel->setMinimumSize(40,40);
    singleLabel->setMaximumSize(40,40);
    singleLabel->setScaledContents(true);

    singleLayout->addWidget(singleLabel);
    singleLayout->addSpacerItem(new QSpacerItem(520,40));
    mainLayout->addLayout(singleLayout);

    doubleLayout->addWidget(doubleAntCell);

    QLabel* doubleLabel = new QLabel;
    doubleLabel->setPixmap(*doubleAntExample);
    doubleLabel->setMinimumSize(40,40);
    doubleLabel->setMaximumSize(40,40);
    doubleLabel->setScaledContents(true);

    doubleLayout->addWidget(doubleLabel);
    doubleLayout->addSpacerItem(new QSpacerItem(520,40));
    mainLayout->addLayout(doubleLayout);

    QLabel* doubleAntExplained = new QLabel("A single antigen cell contains a single red, blue, or yellow antigen, whereas\na double antigen cell contains two distinct single antigens (meaning it can be\nred + blue = purple, red + yellow = orange, or blue + yellow = green).");
    mainLayout->addWidget(doubleAntExplained);

    QHBoxLayout* antLayout = new QHBoxLayout;

    QLabel* antExplained = new QLabel("For example, the following is the antigen for the single antigen cell above:");
    antLayout->addWidget(antExplained);

    QLabel* antLabel = new QLabel;
    QPixmap* temp = new QPixmap(redAnt);
    antLabel->setPixmap(*temp);
    antLabel->setMinimumSize(40,40);
    antLabel->setMaximumSize(40,40);
    antLabel->setScaledContents(true);
    antLayout->addWidget(antLabel);

    antLayout->addSpacerItem(new QSpacerItem(70,40));

    mainLayout->addLayout(antLayout);

    QHBoxLayout* antLayout2 = new QHBoxLayout;

    QLabel* antExplained2 = new QLabel("And the following are the antigens for the double antigen cell above:");
    antLayout2->addWidget(antExplained2);


    QLabel* antLabelRed = new QLabel();
    antLabelRed->setPixmap(*antExample);
    antLabelRed->setMinimumSize(40,40);
    antLabelRed->setMaximumSize(40,40);
    antLabelRed->setScaledContents(true);
    antLayout2->addWidget(antLabelRed);


    QLabel* antLabel2 = new QLabel;
    antLabel2->setPixmap(*antExample2);
    antLabel2->setMinimumSize(40,40);
    antLabel2->setMaximumSize(40,40);
    antLabel2->setScaledContents(true);
    antLayout2->addWidget(antLabel2);

    antLayout2->addSpacerItem(new QSpacerItem(50,40));

    mainLayout->addLayout(antLayout2);

    mainLayout->addWidget(new QLabel("In order to kill an oppoisng cell, you must currently have the opposing cell's antigen(s).\nAntigens are picked up by moving into the ones dropped by the opposing cells.\nYou can only carry two antigens at a time, and it is not possible to pick up two of the same\nantigen.\n\nYou start each game with 3 lives (5 in story mode), and you lose a life each time a cell kills you\n(by moving into you).\n\nGood luck!!"));


    window->setLayout(mainLayout);
    window->setFixedSize(505,500);
    window->show();
}
