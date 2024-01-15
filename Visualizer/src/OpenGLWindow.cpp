#pragma once
#include "stdafx.h"
#include "BoundingBox.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <tuple>
#include <GL/glu.h>
#include <cmath>
#include <algorithm>

// OpenGLWindow constructor initializes member variables with default values
OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
    mBackground(background), mZoomFactor(1.0f), mTowerHeight(0.0f) {
    setParent(parent);
    setMinimumSize(1500, 800);
    QStringList file_lists = { "Vertex.glsl" ,"Fragment.glsl" };
    mShaderWatcher = new QFileSystemWatcher(file_lists, this);
    connect(mShaderWatcher, &QFileSystemWatcher::fileChanged, this, &OpenGLWindow::shaderWatcher);
}


// OpenGLWindow destructor, releases allocated resources
OpenGLWindow::~OpenGLWindow() {
    reset();
}


// Reset function to release OpenGL resources and disconnect signals
void OpenGLWindow::reset() {
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}


// Set the zoom factor for the scene and trigger an update
void OpenGLWindow::setZoomFactor(float& inZoom) {
    mZoomFactor = inZoom;
    update();
}


// Set the tower height and trigger an update
void OpenGLWindow::setTowerHeight(float& height) {
    mTowerHeight = height;
    update();
}


// Handle mouse press event, create tower at the clicked position
void OpenGLWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        mMousePos = event->pos();
        if (mCount == 0)
        {
            mVerticesOfWire.clear();
            mColorOfWire.clear();
        }
        if (mboundingBox.size() != 0)
        {
            double xDiv = 1500 / (mboundingBox[3] - mboundingBox[0]);
            double yDiv = 800 / (mboundingBox[4] - mboundingBox[1]);
            double zDiv = (mboundingBox[5] - mboundingBox[2]);
            double yInverted = mboundingBox[4] - (mMousePos.y() / yDiv);
            Point3D mMouseClick(mMousePos.x() / xDiv, yInverted, 0);
            double positionX = mMousePos.x() / xDiv;

            // Store the vertices and colors of the tower
            QVector<GLfloat> towerVertices;
            mTowerCreator  = new TowerCreator();
            mTempVerticesOfTower = mTowerCreator->addTower(mMouseClick, mTowerHeight);
            if (mCount == 0)
            {
                mVerticesOfWire << mTempVerticesOfTower[0] << mTempVerticesOfTower[1] << mTempVerticesOfTower[2] + mTowerHeight;
                mColorOfWire << 1 << 1 << 0;
            }
            else
            {
                mVerticesOfWire << mTempVerticesOfTower[0] << mTempVerticesOfTower[1] << mTempVerticesOfTower[2] + mTowerHeight;
                mVerticesOfWire << mTempVerticesOfTower[0] << mTempVerticesOfTower[1] << mTempVerticesOfTower[2] + mTowerHeight;
                mColorOfWire << 1 << 1 << 0;
                mColorOfWire << 1 << 1 << 0;
            }
            for (int i = 0; i < mTempVerticesOfTower.size(); i += 3)
            {
                towerVertices << mTempVerticesOfTower[i];
                towerVertices << mTempVerticesOfTower[i + 1];
                towerVertices << mTempVerticesOfTower[i + 2];
            }

            // Set tower colors
            QVector<GLfloat> towerColors =
            {
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
            };

            // Update count and store data for rendering
            mCount += 1;
            if (mFlag == 1)
            {
                mVerticesOfTower += towerVertices;
                mColorsOfTower += towerColors;
                update();
            }
        }

    }
}


// Paint the OpenGL scene, drawing tower and wireframe
void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    mProgram->bind();
    QMatrix4x4 matrix_proj;
    QMatrix4x4 matrix_view;
    QMatrix4x4 matrix_model;

    matrix_model.setToIdentity();
    matrix_model.rotate(mRotationAngle);

    //matrix_model.setToIdentity();
    matrix_proj.ortho(-40.0f, 40.0f, -40.0f, 40.0f, -100.0f, 100.0f);
    //matrix_proj.ortho(0.0f, 20.0f, 0.0f , 20.0f , -100.0f, 100.0f);


  //  matrix_view.setToIdentity();
    matrix_model.translate(0, 0, -2);
    matrix_model.scale(mZoomFactor);
    matrix_proj.translate(0, 0, -2);
    matrix_proj.scale(mZoomFactor);

    mProgram->setUniformValue(mMatrixUniformProj, matrix_proj);
    mProgram->setUniformValue(mMatrixUniformView, matrix_view);
    mProgram->setUniformValue(mMatrixUniformModel, matrix_model);
    mProgram->setUniformValue(mLightPosLoc, QVector3D(0, 90, 0));

    QMatrix3x3 normalMatrix = matrix_model.normalMatrix();
    mProgram->setUniformValue(mNormalMatrixLoc, normalMatrix);

    GLfloat* verticesData = mVerticesOfOrignalLine.data();
    GLfloat* normalData = mNormalsOfTriangle.data();
    GLfloat* colorsData = mColorOfOrignalLine.data();

    glVertexAttribPointer(mPosAttr, 3, GL_FLOAT, GL_FALSE, 0, verticesData);
    glVertexAttribPointer(mNormalsOpenGL, 3, GL_FLOAT, GL_FALSE, 0, normalData);
    glVertexAttribPointer(mColAttr, 3, GL_FLOAT, GL_FALSE, 0, colorsData);

    glEnableVertexAttribArray(mColAttr);
    glEnableVertexAttribArray(mPosAttr);
    glEnableVertexAttribArray(mNormalsOpenGL);

    // Draw the lines
    glDrawArrays(GL_TRIANGLES, 0, mVerticesOfOrignalLine.size() / 3);

    // Set up data for the wireframe
    GLfloat* TowerVertexData = mVerticesOfTower.data();
    GLfloat* TowercolorsData = mColorsOfTower.data();

    // Configure vertex attribute pointers and enable them
    glVertexAttribPointer(mPosAttr, 3, GL_FLOAT, GL_FALSE, 0, TowerVertexData);
    glVertexAttribPointer(mColAttr, 3, GL_FLOAT, GL_FALSE, 0, TowercolorsData);
    glEnableVertexAttribArray(mPosAttr);
    glEnableVertexAttribArray(mColAttr);

    // Draw the wireframe as lines
    glDrawArrays(GL_LINE_LOOP, 0, mVerticesOfTower.size() / 3);

    // Set up data for the wireframe
    GLfloat* wireVertexData = mVerticesOfWire.data();
    GLfloat* wireColorcolorsData = mColorOfWire.data();

    // Configure vertex attribute pointers and enable them
    glVertexAttribPointer(mPosAttr, 3, GL_FLOAT, GL_FALSE, 0, wireVertexData);
    glVertexAttribPointer(mColAttr, 3, GL_FLOAT, GL_FALSE, 0, wireColorcolorsData);
    glEnableVertexAttribArray(mPosAttr);
    glEnableVertexAttribArray(mColAttr);

    // Draw the wireframe as lines
    glDrawArrays(GL_LINES, 0, mVerticesOfWire.size() / 3);
}


// Initialize OpenGL, shaders, and program
void OpenGLWindow::initializeGL()
{
    QString qvertexShaderSource = readShader("Vertex.glsl");
    QString qfragmentShaderSource = readShader("Fragment.glsl");

    mRotationAngle = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, 0.0f);

    initializeOpenGLFunctions();
    setMouseTracking(true);

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, qvertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, qfragmentShaderSource);
    mProgram->bindAttributeLocation("vertex", 0);
    mProgram->bindAttributeLocation("normal", 1);

    mProgram->link();

    mPosAttr = mProgram->attributeLocation("posAttr");
    mNormalsOpenGL = mProgram->attributeLocation("normalAttr");
    mMatrixUniformProj = mProgram->uniformLocation("u_ProjMatrix");
    mMatrixUniformView = mProgram->uniformLocation("u_viewMatrix");
    mMatrixUniformModel = mProgram->uniformLocation("u_modelMatrix");
    mNormalMatrixLoc = mProgram->uniformLocation("normalMatrix");
    mLightPosLoc = mProgram->uniformLocation("lightPos");
}

// Slot for Shader
void OpenGLWindow::shaderWatcher()
{
    QString vertexShaderSource = readShader("Vertex.glsl");
    QString fragmentShaderSource = readShader("Fragment.glsl");

    mProgram->release();
    mProgram->removeAllShaders();
    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
}

// To clear the window
void OpenGLWindow::updateAll()
{
    mTowerHeight = 15.0f;
    mZoomFactor = 1.0f;
    mFlag = 0;
    mCount = 0;
    mVerticesOfOrignalLine.clear();
    mColorOfOrignalLine.clear();
    mVerticesOfTower.clear();
    mColorsOfTower.clear();
    mVerticesOfWire.clear();
    mColorOfWire.clear();
    mboundingBox.clear();
    update();
}

// Read shader File
QString OpenGLWindow::readShader(QString filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "Invalid file";

    QTextStream stream(&file);
    QString line = stream.readLine();

    while (!stream.atEnd()) {
        line.append(stream.readLine());
    }
    file.close();
    return line;
}


// Handle mouse wheel events to zoom in/out
void OpenGLWindow::wheelEvent(QWheelEvent* event)
{
    int delta = event->angleDelta().y();
    if (delta > 0)
    {
        // Zoom in
        mZoomFactor *= 1.1f;
    }
    else {
        // Zoom out
        mZoomFactor /= 1.1f;
    }
    update();
}


// To get no of Triangles
int OpenGLWindow::getNoOfTowers()
{
    return mCount;
}


// To get Tower Height
float OpenGLWindow::getTowerHeight()
{
    return mTowerHeight;
}


// To get Bounding Box of Terrain
std::vector<double> OpenGLWindow::getBoundingBox()
{
    return mboundingBox;
}


// Update data for the original line (tower) 
void OpenGLWindow::updateData(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors) {
    mVerticesOfOrignalLine = vertices;
    mColorOfOrignalLine = colors;
    mFlag = 1;
    mTempVerticesofTriangles.clear();
    for (int i = 0; i < mVerticesOfOrignalLine.size(); i++)
    {
        mTempVerticesofTriangles.push_back(mVerticesOfOrignalLine[i]);
    }
    mBbox = new BoundingBox();
    mboundingBox = mBbox->boundingBoxOfTerrain(mTempVerticesofTriangles);
    update();
}

//Code for update Normals
void OpenGLWindow::updateNormals(const QVector<GLfloat>& normals) {
    mNormalsOfTriangle = normals;
    update();
}


// Handle mouse move events to rotate the scene
void OpenGLWindow::mouseMoveEvent(QMouseEvent* event) {
    int dx = event->x() - mLastPos.x();
    int dy = event->y() - mLastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        // Create rotation quaternions based on mouse movement
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

        // Combine rotations and update rotation angle
        mRotationAngle = rotX * rotY * mRotationAngle;
        update();
    }

    // Update last mouse position
    mLastPos = event->pos();
}


// Delete last tower
void OpenGLWindow::removeLastTower()
{
    mTempVerticesOfTower.clear();
    if (mVerticesOfTower.size() != 0)
    {
        TowerCreator tower;
        for (int i = 0; i < mVerticesOfTower.size(); i++)
        {
            mTempVerticesOfTower.push_back(mVerticesOfTower[i]);
        }

        tower.deleteTower(mTempVerticesOfTower);
        mVerticesOfTower.clear();

        for (int i = 0; i < mTempVerticesOfTower.size(); i++)
        {
            mVerticesOfTower << mTempVerticesOfTower[i];
        }
        for (int i = 0; i < 54; i++)
        {
            mColorsOfTower.removeLast();
        }
        mCount -= 1;
        if (mCount >= 1)
        {
            for (int i = 0; i < 6; i++)
            {
                mVerticesOfWire.removeLast();
                mColorOfWire.removeLast();
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                mVerticesOfWire.removeLast();
                mColorOfWire.removeLast();
            }
            mFlagDeleteTower = 1;
        }
        update();
    }
}


void OpenGLWindow::resetTerrainPosition()
{
    mRotationAngle.setX(0);
    mRotationAngle.setY(0);
    mRotationAngle.setZ(0);
    update();
}
