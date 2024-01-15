#pragma once
#include "TowerCreator.h"
#include "BoundingBox.h"
#include "OpenGLWindow.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMainWindow>
#include <QQuaternion>
#include <QWheelEvent>

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    // Constructor for the OpenGLWindow class
    OpenGLWindow(const QColor& background, QMainWindow* parent);

    // Destructor for the OpenGLWindow class
    ~OpenGLWindow();

    // Update the data for rendering
    void updateData(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors);
    void updateNormals(const QVector<GLfloat>& normals);

    // Handle mouse move events
    void mouseMoveEvent(QMouseEvent* event) override;

    // Handle mouse press events
    void mousePressEvent(QMouseEvent* event) override;

    // Handle wheel events (mouse wheel)
    void wheelEvent(QWheelEvent* event) override;

    // Set the zoom factor for rendering
    void setZoomFactor(float& inZoom);

    // Set the tower height for rendering
    void setTowerHeight(float& height);

    //Clear all the vertices of vector 
    void updateAll();

    //Clear all the Last added tower
    void removeLastTower();

    //To get no of towers
    int getNoOfTowers();

    //To get Height of Tower
    float getTowerHeight();

    void resetTerrainPosition();

    //Get Bounding Box
    std::vector<double>  getBoundingBox();

protected:
    // Paint the OpenGL 
    void paintGL() override;

    // Initialize the OpenGL 
    void initializeGL() override;

private:
    // Reset the OpenGL context and cleanup resources
    void reset();

private slots:
    QString readShader(QString filePath);

    //Slot for shaderWatcher
    void shaderWatcher();

private:
    QOpenGLContext* mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;

    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;

    QList<QVector3D> mVertices;
    QList<QVector3D> mNormals;


    GLint mPosAttr = 0;
    GLint mColAttr = 0;
    GLint mMatrixUniform = 0;
    QOpenGLBuffer mVbo;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;

    QQuaternion mRotationAngle;
    QPoint mLastPos;
    QPoint mMousePos;
    QPoint mTranslatedMousePos;
    GLfloat mZoomFactor = 1.0f;

    QVector<GLfloat> mVerticesOfOrignalLine;
    QVector<GLfloat> mColorOfOrignalLine;
    QVector<GLfloat> mNormalsOfTriangle;

    QVector<GLfloat> mVerticesOfTower;
    QVector<GLfloat> mColorsOfTower;

    QVector<GLfloat> mVerticesOfWire;
    QVector<GLfloat> mColorOfWire;

    int mTranslate = 0;
    int mCount = 0;
    int mFlag = 0;
    int mFlagDeleteTower = 0;
    int mTowerDeleteCount = 0;
    float mTowerHeight = 0.0f;
    bool mAnimating = false;

    std::vector<float> mTempVerticesofTriangles;
    std::vector<float> mTempVerticesOfTower;
    std::vector<double> mboundingBox;
    QFileSystemWatcher* mShaderWatcher;

    GLint mNormalsOpenGL = 0;
    GLint mMatrixUniformProj = 0;
    GLint mMatrixUniformView = 0;
    GLint mMatrixUniformModel = 0;

    int mLightPosLoc = 0;
    int mNormalMatrixLoc = 0;

    TowerCreator* mTowerCreator;
    BoundingBox* mBbox;
};

