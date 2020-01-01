#pragma once

#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement {
    FORWARD, 
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -45.0f;
const float PITCH = -20.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
private:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    glm::vec3 position;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    float yaw, pitch;

    void updateCameraVectors();
public:
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
         float yaw = YAW,
         float pitch = PITCH);

  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw = YAW, float pitch = PITCH);

  glm::mat4 GetViewMatrix();
  glm::vec3 GetPosition();
  float GetZoom();

  void ProcessKeyboard(CameraMovement direction, float deltaTime);
  void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
  void ProcessMouseScroll(float yOffset);
};
