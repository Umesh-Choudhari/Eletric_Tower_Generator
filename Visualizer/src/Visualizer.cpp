#include "stdafx.h"
#include "Visualizer.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <QTimer>


using namespace std;


//Constructor 
Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
    //connect statements for signal and slots.
    connect(mInfoButton, &QPushButton::clicked, this, &Visualizer::terrainInformation);
    connect(mTerrainLengthButton, &QPushButton::clicked, this, &Visualizer::terrainLength);
    connect(mTerrainWidthButton, &QPushButton::clicked, this, &Visualizer::terrainHeight);
    connect(mTerrainHeightButton, &QPushButton::clicked, this, &Visualizer::terrainWidth);
    connect(mpushButtonRead, &QPushButton::clicked, this, &Visualizer::render);
    connect(mBrowseButton, &QPushButton::clicked, this, &Visualizer::browseSTL);
    connect(mSetHeightMin, &QPushButton::clicked, this, &Visualizer::setHeight);
    connect(mResetButton, &QPushButton::clicked, this, &Visualizer::reset);
    connect(mDeleteTowerButton, &QPushButton::clicked, this, &Visualizer::deleteLastTower);
    connect(mTerrainResetButton, &QPushButton::clicked, this, &Visualizer::resetPositionOfTerrain);
}

Visualizer::~Visualizer()
{

}

void Visualizer::terrainInformation()
{
    terrainLength();
    terrainWidth();
    terrainHeight();
}
void Visualizer::resetPositionOfTerrain()
{
    mRenderer->resetTerrainPosition();
}

void Visualizer::terrainLength()
{

    mBoundingBox = mRenderer->getBoundingBox();
    if (mBoundingBox.size() == 0)
    {
        mStatusLabel->setText("Please Load The File.");
        return;
    }
    mLength = to_string(mBoundingBox[3] - mBoundingBox[0]);
    QString qstr = QString::fromStdString("Length of Terrain is " + mLength);
    mLineEdit1->setText(qstr);
}

void Visualizer::terrainWidth()
{
    mBoundingBox = mRenderer->getBoundingBox();
    if (mBoundingBox.size() == 0)
    {
        mStatusLabel->setText("Please Load The File.");
        return;
    }
    mWidth = to_string(mBoundingBox[4] - mBoundingBox[1]);
    QString qstr = QString::fromStdString("Width of Terrain is " + mWidth);
    mLineEdit2->setText(qstr);
}

void Visualizer::terrainHeight()
{
    mBoundingBox = mRenderer->getBoundingBox();
    if (mBoundingBox.size() == 0)
    {
        mStatusLabel->setText("Please Load The File.");
        return;
    }
    mHeight = to_string(mBoundingBox[5] - mBoundingBox[2]);
    QString qstr = QString::fromStdString("Height of Terrain is " + mHeight);
    mLineEdit3->setText(qstr);

}

void Visualizer::render()
{
    mStatusLabel->setText("File Is Loading Please Wait");
    // Create a QTimer instance
    QTimer* timer = new QTimer(this);

    // Connect the timeout signal to a lambda function that calls readSTL
    connect(timer, &QTimer::timeout, [this, timer]() {
        readSTL();
        timer->deleteLater();  // Optional: Cleanup the timer after it's done
        });

    // Set the interval to 10,000 milliseconds (10 seconds)
    timer->start(100);
}

void Visualizer::reset()
{
    mStatusLabel->setText("Window Cleared successfully");
    mLineEdit1->setText("");
    mLineEdit2->setText("");
    mLineEdit3->setText("");
    mLength = "";
    mHeight = "";
    mWidth = "";
    mRenderer->updateAll();
}

void Visualizer::deleteLastTower()
{
    mRenderer->removeLastTower();
}

void Visualizer::setupUi() {
    // Use the primary screen to set the main window size
    resize(800, 600);

    // Create a central widget to hold the layout
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Use a vertical layout for the main window
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Create a horizontal layout for the title
    QHBoxLayout* titleLayout = new QHBoxLayout;

    // Add the title label to the layout
    QLabel* titleLabel = new QLabel("Electricity Tower Generator", centralWidget);
    titleLabel->setObjectName("titleLabel");
    titleLabel->setStyleSheet("QLabel { font-size: 18px; font-weight: bold; }");

    // Add the title label to the layout at the center
    titleLayout->addWidget(titleLabel, 0, Qt::AlignCenter);

    // Set the spacing and add the title layout to the main layout
    titleLayout->setSpacing(10);
    mainLayout->addLayout(titleLayout);



    // Create a widget to hold the buttons and spin boxes
    QWidget* buttonWidget = new QWidget(centralWidget);
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);

    // Create buttons and spin boxes (unchanged from the previous code)
    mpushButtonRead = new QPushButton("Render STL", buttonWidget);
    mBrowseButton = new QPushButton("Browse STL", buttonWidget);
    mDoubleSpinBoxMin = new QDoubleSpinBox(buttonWidget);
    mSetHeightMin = new QPushButton("Height of Tower", buttonWidget);
    mResetButton = new QPushButton("Reset Window", buttonWidget);
    mDeleteTowerButton = new QPushButton("Delete Tower", buttonWidget);
    mInfoButton = new QPushButton("Terrain Information", buttonWidget);
    mTerrainLengthButton = new QPushButton("Terrain Length", buttonWidget);
    mTerrainHeightButton = new QPushButton("Terrain Width", buttonWidget);
    mTerrainWidthButton = new QPushButton("Terrain Height", buttonWidget);
    mTerrainResetButton = new QPushButton("Reset Terrain", buttonWidget);

    // Add buttons and spin boxes to the layout
    buttonLayout->addWidget(mpushButtonRead);
    buttonLayout->addWidget(mBrowseButton);
    buttonLayout->addWidget(mDoubleSpinBoxMin);
    buttonLayout->addWidget(mSetHeightMin);
    buttonLayout->addWidget(mResetButton);
    buttonLayout->addWidget(mDeleteTowerButton);
    buttonLayout->addWidget(mInfoButton);
    buttonLayout->addWidget(mTerrainLengthButton);
    buttonLayout->addWidget(mTerrainHeightButton);
    buttonLayout->addWidget(mTerrainWidthButton);
    buttonLayout->addWidget(mTerrainResetButton);

    // Add the button widget to the main layout
    mainLayout->addWidget(buttonWidget);

    // Create a QHBoxLayout for the line edits
    QHBoxLayout* lineEditLayout = new QHBoxLayout;

    // Add the line edits to the layout
    mLineEdit1 = new QLineEdit(centralWidget);
    mLineEdit2 = new QLineEdit(centralWidget);
    mLineEdit3 = new QLineEdit(centralWidget);

    lineEditLayout->addWidget(mLineEdit1);
    lineEditLayout->addWidget(mLineEdit2);
    lineEditLayout->addWidget(mLineEdit3);

    // Add the QHBoxLayout with the line edits to the main layout
    mainLayout->addLayout(lineEditLayout);

    // Create a QHBoxLayout for the OpenGL window
    QHBoxLayout* openGLLayout = new QHBoxLayout;

    // Create and set up the OpenGLWindow
    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
    mRenderer->setGeometry(QRect(100, 30, 1500, 800));
    mRenderer->setFixedSize(1500, 800);  // Set a fixed size for the OpenGL window

    // Add the OpenGL window to the layout
    openGLLayout->addWidget(mRenderer);

    // Add the QHBoxLayout with the OpenGL window to the main layout
    mainLayout->addLayout(openGLLayout);


    // Create and set up the QStatusBar
    mStatusBar = new QStatusBar(centralWidget);
    mStatusBar->setObjectName("statusBar");
    mStatusBar->setStyleSheet("QStatusBar { background-color: #4CAF50; color: white; }");


    // Create a label to display messages in the status bar
    mStatusLabel = new QLabel(centralWidget);
    mStatusLabel->setObjectName("statusLabel");
    mStatusLabel->setAlignment(Qt::AlignCenter);
    mStatusLabel->setStyleSheet("QLabel { color: white; font-weight: bold; }");

    mStatusBar->addWidget(mStatusLabel);
    mainLayout->addWidget(mStatusBar);

    // Set the main window title
    setWindowTitle(QCoreApplication::translate("Electricity Tower Generator", "Electricity Tower Generator", nullptr));
}



// slot to set height of tower
void Visualizer::setHeight()
{
    mTowerHeight = mDoubleSpinBoxMin->value();
    mBoundingBox = mRenderer->getBoundingBox();
    if (mBoundingBox.size() == 0)
    {
        mStatusLabel->setText("Please Load File");
        return;
    }
    double mHeight = abs(mBoundingBox[5] - mBoundingBox[2]);
    if (abs(mTowerHeight-15) > mHeight)
    {
        mStatusLabel->setText("Height provided is to less or greater then the terrain height so reset a height");
        mTowerHeight = 0;
        mRenderer->setTowerHeight(mTowerHeight);
    }
    else
    {
        mStatusLabel->setText("Tower height is well-seted");
        mRenderer->setTowerHeight(mTowerHeight);
    }

    
}

// slot to browse file
void Visualizer::browseSTL()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "", tr("STL Files(*.stl);; All Files(*)"));
    if (!fileName.isEmpty())
    {
        mFileName = fileName.toStdString();
        mStatusLabel->setText("File browsed successfully");

    }
}

// slot to zoom 
void Visualizer::zoomSlider(int value)
{
    GLfloat zoomFactor = 0.5 + (value / 100.0) * 1.0;
    mRenderer->setZoomFactor(zoomFactor);
}


// slot to read stl file
void Visualizer::readSTL()
{

    std::string filePath = mFileName;
    Reader read;
    std::vector<float> mTempNormals;
    mTempVertices = read.readSTL(mFileName, mTempNormals);
    for (int i = 0; i < mTempNormals.size(); i+=3)
    {
        mNormals << mTempNormals[i] << mTempNormals[i + 1] << mTempNormals[i + 2];
    }
    if (mTempVertices.size() != 0)
    {
        for (int i = 0; i < mTempVertices.size(); i += 12)
        {

            mVertices << mTempVertices[i] << mTempVertices[i + 1] << mTempVertices[i + 2];
            mVertices << mTempVertices[i + 3] << mTempVertices[i + 4] << mTempVertices[i + 5];
            mVertices << mTempVertices[i + 6] << mTempVertices[i + 7] << mTempVertices[i + 8];
            mVertices << mTempVertices[i + 9] << mTempVertices[i + 10] << mTempVertices[i + 11];

            mColors << 0.0f << 1.0f << 1.0f;
            mColors << 1.0f << 1.0f << 0.0f;
            mColors << 1.0f << 0.0f << 1.0f;
            mColors << 0.0f << 0.0f << 1.0f;
        }

        mRenderer->updateData(mVertices, mColors);
        mRenderer->updateNormals(mNormals);
        mStatusLabel->setText("File is Loaded successfully");
        mVertices.clear();
        mColors.clear();
    }
    else
    {
        mStatusLabel->setText("Unable To Load A File");
    }
}


