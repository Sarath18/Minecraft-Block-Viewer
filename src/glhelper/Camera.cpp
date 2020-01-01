#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                                                           movementSpeed(SPEED),
                                                                           mouseSensitivity(SENSITIVITY),
                                                                           zoom(ZOOM) {
  this->position = position;
  this->worldUp = up;
  this->yaw = yaw;
  this->pitch = pitch;

  this->updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {

  this->position = glm::vec3(posX, posY, posZ);
  this->worldUp = glm::vec3(upX, upY, upZ);
  this->yaw = yaw;
  this->pitch = pitch;

  this->updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime) {
  float velocity = this->movementSpeed * deltaTime;

  if( FORWARD == direction ) {
    this->position += this->front * velocity;
  }

  if( BACKWARD == direction ) {
    this->position -= this->front * velocity;
  }

  if( RIGHT == direction ) {
    this->position += this->right * velocity;
  }

  if( LEFT == direction ) {
    this->position -= this->right * velocity;
  }
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
  xOffset *= this->mouseSensitivity;
  yOffset *= this->mouseSensitivity;

  this->yaw += xOffset;
  this->pitch += yOffset;

  if(constrainPitch) {
    if(this->pitch > 89.0f)
      this->pitch = 89.0f;

    if(this->pitch < -89.0f)
      this->pitch = -89.0f;
  }

  this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset) {
  if(this->zoom >= 1.0f && this->zoom <= 45.0f)
    this->zoom -= yOffset;

  if(this->zoom <= 1.0f)
    this->zoom = 1.0f;

  if(this->zoom >= 45.0f)
    this->zoom = 45.0f;
}

float Camera::GetZoom() {
  return this->zoom;
}

void Camera::updateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
  front.y = sin(glm::radians(this->pitch));
  front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

  this->front = glm::normalize(front);
  this->right = glm::normalize(glm::cross(this->front, this->worldUp));
  this->up = glm::normalize(glm::cross(this->right, this->front));
}

glm::vec3 Camera::GetPosition() {
  return this->position;
}