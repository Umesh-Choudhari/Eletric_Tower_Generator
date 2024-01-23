# ElectricTowerGenerator Testing Guide
 
## Overview
This guide is designed to assist in testing the `ElectricTowerGenerator` application using Google Test. It includes details about the purpose of the tests, where they should be located, and steps for integrating the Google Test tool into your development process.
 
## 1. What you are testing
The tests are centered around validating the functionality and behavior of the `Visualizer` application. The main goals encompass testing key methods such as `readSTL`, `AddTower`, `DeleteTower`, various functions within the `Geometry dll`, `Reader dll`, `TowerCreator dll`, and other pertinent functionalities.
 
## 2. Test location
The test cases are organized using Google Test framework. Test files are structured as follows:
- All the Test Cases are available at this location [Test Suite Location](https://github.com/Umesh-Choudhari/Eletric_Tower_Generator/tree/inProgress/SampleTest1/src)
 
## 3. Steps to Integrate Testing Tool (Google Test)
 
### Prerequisites
Make sure you have Google Test installed on your system. you can follow the [Google Test Installation Guide](https://github.com/google/googletest/blob/main/googletest/README.md).
or follow the steps mentioned below
- Right click on the project
- Click on add and select new project
- Select Google test as project type and provide appropriate location
- Create the test suite under this project
