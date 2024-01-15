#pragma once
#include <QtWidgets/QMainWindow>
#include "OpenGLWindow.h"
#include "Reader.h"
#include <Qvector>
#include <bitset>
#include <string>
#include <cstdint> // Include this header for uint16_t and uint32_t

class OpenGLWindow;

class Visualizer : public QMainWindow {
    Q_OBJECT

public:
    // Constructor for the Visualizer class
    Visualizer(QWindow* parent = nullptr);

    // Destructor for the Visualizer class
    ~Visualizer();

private:
    // Helper function to set up the user interface
    void setupUi();
    void readSTL();

private slots:
    // Slot function to handle changes in the zoom slider
    void zoomSlider(int value);

    // Slot function to browse and select an STL file
    void browseSTL();

    // Slot function to read and process the vertices from an STL file
    void render();


    // Slot function to set the tower height based on user input
    void setHeight();

    //Slot for reaset
    void reset();

    //Slot for delete Tower
    void deleteLastTower();

    //
    void resetPositionOfTerrain();

    //Slot for terrain information Display
    void terrainInformation();
    void terrainLength();
    void terrainWidth();
    void terrainHeight();

private:
    QStatusBar* mStatusBar;
    QWidget* mCentralWidget;
    OpenGLWindow* mRenderer;
    QLineEdit* mLineEdit;
    QLineEdit* mLineEdit1;
    QLineEdit* mLineEdit2;
    QLineEdit* mLineEdit3;

    QPushButton* mInfoButton;
    QPushButton* mpushButton;
    QPushButton* mResetButton;
    QPushButton* mDeleteTowerButton;
    QPushButton* mpushButtonRead;
    QPushButton* mBrowseButton;
    QPushButton* mSeeDimentionButton;
    QPushButton* mTerrainLengthButton;
    QPushButton* mTerrainHeightButton;
    QPushButton* mTerrainWidthButton;
    QPushButton* mTerrainInformation;
    QPushButton* mTerrainResetButton;

    QPushButton* mSetHeightMin;
    QPushButton* mSetHeightMax;
    QDoubleSpinBox* mDoubleSpinBoxMin;
    QDoubleSpinBox* mDoubleSpinBoxMax;

    QLabel* mStatusLabel;

    QVector<GLfloat>mVertices;
    QVector<GLfloat>mColors;
    QVector<GLfloat>mNormals;
    QString mText;

    vector<GLfloat>mTempVertices;
    vector<GLfloat>mTempColors;
    vector<double> mBoundingBox;

    std::string mFileName;
    float mTowerHeight;

    std::string mLength;
    std::string mWidth;
    std::string mHeight;
};

