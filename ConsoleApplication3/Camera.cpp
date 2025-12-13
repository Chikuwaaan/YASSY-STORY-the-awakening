#include "Camera.h"

Camera::Camera() {
    camera.x = 960.0;
    camera.y = 540.0;
    camera.offsetX = 0.0;
    camera.offsetY = 0.0;
    camera.targetX = 960.0;
    camera.targetY = 540.0;
    camera.zoom = 1.0;
}

CAMERA Camera::getCam() {
    return camera;
}

void Camera::setCam(CAMERA cam) {
    camera = cam;
}