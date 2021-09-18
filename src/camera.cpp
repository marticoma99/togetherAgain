#include "camera.h"

//initial cell pos
Camera::Camera(double x, double y) {
	xCam = x;
	yCam = y;
}
//update camera cell
void Camera::updateCamera(double x, double y) {
	xCam = x;
	yCam = y;
}
//update camera cell Y
void Camera::updateCameraY(double pos) {
	yCam = pos;
}
//update camera cell X
void Camera::updateCameraX(double pos) {
	xCam = pos;
}
//get Camera cell X
double Camera::getX() {
	return xCam;
}
//get camera cell Y
double Camera::getY() {
	return yCam;
}

