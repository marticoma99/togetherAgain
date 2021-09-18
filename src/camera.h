#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include <iostream>

//Represents the camera position
class Camera {
	//in which cell is the top up corner of the camera
	double xCam;
	double yCam;
public:
	Camera(double x, double y);
	//update the camera cell
	void updateCamera(double x, double y);
	//update the camera cell Y
	void updateCameraY(double pos);
	//update the camera cell X
	void updateCameraX(double pos);
	//get the camera position X
	double getX();
	//get the camera position Y
	double getY();
};

#endif