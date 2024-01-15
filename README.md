# Electric Tower Generator Application

## Overview
The Electric Tower Generator application is designed to create and visualize electric tower structures in a three-dimensional space. It consists of three dynamic-link libraries (DLLs): Geometry, Reader, and TowerCreator. The application also includes a visualization component for interactive viewing and manipulation of the generated towers.

## File Structure
The application is structured into three main components:

### 1. Geometry DLL
#### Files:
- **Point3D.h/cpp**: Defines a 3D point class with x, y, and z coordinates.
    - `Point3D(double inX, double inY, double inZ = 0)`: Constructor for Point3D.
    - `~Point3D()`: Destructor for Point3D.
    - `double x() const`: Returns the x-coordinate of the point.
    - `double y() const`: Returns the y-coordinate of the point.
    - `double z() const`: Returns the z-coordinate of the point.
    - `void setX(double inX)`: Sets the x-coordinate of the point.
    - `void setY(double inY)`: Sets the y-coordinate of the point.
    - `void setZ(double inZ)`: Sets the z-coordinate of the point.

- **Triangle.h/cpp**: Represents a 3D triangle using three Point3D vertices.
    - `Triangle(Point3D p1, Point3D p2, Point3D p3)`: Constructor for Triangle.
    - `~Triangle()`: Destructor for Triangle.
    - `Point3D p1() const`: Returns the first vertex of the triangle.
    - `Point3D p2() const`: Returns the second vertex of the triangle.
    - `Point3D p3() const`: Returns the third vertex of the triangle.

- **Triangulation.h/cpp**: Manages a collection of triangles forming a 3D mesh.
    - `Triangulation(const std::vector<Triangle>& inTriangles)`: Constructor for Triangulation.
    - `~Triangulation()`: Destructor for Triangulation.
    - `std::vector<Triangle> getTriangles() const`: Returns the collection of triangles.

### 2. Reader DLL
#### Files:
- **Reader.h/cpp**: Implements a class for reading various types of data files, including vertices, colors, and STL files.
    - `Reader()`: Constructor for Reader class.
    - `vector<float> readSTL(const string& filePath)`: Reads STL file data from the specified file path.

- **TriangleInfo**: Structure defining information about a triangle, including normals, vertices, and attribute byte count.

### 3. TowerCreator DLL
#### Files:
- **TowerCreator.h/cpp**: Provides a class for creating tower structures based on specified positions and heights.
    - `TowerCreator()`: Constructor for TowerCreator class.
    - `std::vector<float> addTower(const Point3D& position, const float& mTowerHeight)`: Adds a tower at the specified position with the given height.

### 4. BoundingBox DLL
#### Files:
- **BoundingBox.h/cpp**: Implements a class for calculating the bounding box of terrain.
    - `BoundingBox()`: Constructor for BoundingBox class.
    - `std::vector<double> boundingBoxOfTerrain(const std::vector<float>& mVerticesOfOriginalLine)`: Calculates and returns the bounding box of terrain based on the provided vertices.


### 5. Application Visualizer
#### Files:
- **Visualizer.h/cpp**: Main application class utilizing Qt for the user interface.
    - `Visualizer(QWindow* parent = nullptr)`: Constructor for the Visualizer class.
    - `~Visualizer()`: Destructor for the Visualizer class.
    - `void setupUi()`: Sets up the user interface.
    - `void zoomSlider(int& value)`: Handles zoom slider changes.
    - `void browseSTL()`: Handles the STL file browsing.
    - `void readSTL()`: Reads STL file data.
    - `void setHeight()`: Sets the tower height.

- **OpenGLWindow.h/cpp**: Handles rendering and OpenGL integration.

- **Reader.h**: Includes functions for reading vertices, colors, and STL files.

- **TowerCreator.h**: Includes functions for creating tower structures.


### 6. Software Tools
 
1. `C++`: The primary programming language for the application.
 
2. `QT`: The Qt framework is utilized for the development of the graphical user interface (GUI) components.
 
3. `OpenGL`: OpenGL is employed for rendering 3D graphics, enhancing the visualization capabilities of the application.
 
4. `Visual Studio`: The project is developed and built using the Visual Studio integrated development environment.
 
5. `Git`: Git is used for version control and collaborative development, allowing for easy tracking of changes and contributions.
 
