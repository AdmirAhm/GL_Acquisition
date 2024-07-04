# GL_Acquisition
## Introduction
This project represents an easy to use graphical tool developed with C++ and OpenGL for debuging and supervising electro-mechanical systems based on the sensor outputs. The programm allows user to control translation, rotation and color of different cubes displayed on screen based on data sent via TCP network socket.

## Instructions
Running the programm opens a window seen below:

![Image Alt text](/images/Capture.PNG "Main Screen")

Here the user can see on which IP address and port the network socket is opened. Instances and measures fields are used to declare how many cubes should be displaied and how many measurements are sent to socket.
By selecting Edit option, user can set parameters for every cube which include:
* Initial position, rotation and color
* Measurement index (starting with 1) for position rotation and color. This declares which measurement changes which value
* Factor for position, rotation and color. This changes sensitivity cube movement

Run option starts the simulation.

![Image Alt text](/images/Capture1.PNG "Main Screen")

Here we can see 3 different cubes with different initial position rotation and color. To remove potential jitter in graphic representation, a simple averaging filter is used, which takes an average of last 10 measurements.

# Testing
Program was tested using an ESP8266 D1 mini microcontroller with MMA845X gyro sensor. Testing files are available in Test folder.
