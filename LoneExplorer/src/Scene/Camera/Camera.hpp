#ifndef CAMERA_HPP
#define CAMERA_HPP
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Les diff�rents types de d�placements possibles
// ----------------------------------------------
enum CameraDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    BOTTOM
};

// Valeurs par d�faut
// ------------------
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 0.75f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
    private:
        // Attributs de base pour la cam�ra
        // --------------------------------
         glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
         glm::vec3 m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
         glm::vec3 m_Up = glm::vec3(0.0f, 0.0f, 0.0f);
         glm::vec3 m_Right = glm::vec3(0.0f, 0.0f, 0.0f);
         glm::vec3 m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

        // Angles d'Euler
        // --------------
         float m_Yaw = YAW;
         float m_Pitch = PITCH;

        // Options
        // -------
         float m_MovementSpeed = SPEED;
         float m_MouseSensitivity = SENSITIVITY;
         float m_Zoom = ZOOM;

        // Modifier la cam�ra
        // ------------------
         void updateCameraVectors();

    public:
        // Initialisation
        // --------------
         Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

        // Gestion des d�placements
        // ------------------------
         void Move(CameraDirection direction, float deltaTime);
         void Look(float xoffset, float yoffset);
         void Zoom(float yoffset);

        // Getter - Setter
        // ---------------
         const glm::mat4 getCameraMatrix(const unsigned int& width, const unsigned int& height);
         const glm::mat4 getViewMatrix() { return glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);  }
         const glm::mat4 getProjMatrix(const unsigned int& width, const unsigned int& height) { return glm::perspective(glm::radians(m_Zoom), static_cast<float>(width) / height, 0.01f, 500.0f * 2); }
         inline const float getMovementSpeed() { return Camera::m_MovementSpeed; };
         inline void setMovementSpeed(float newMovementSpeed) { Camera::m_MovementSpeed = newMovementSpeed; };
         inline void setPosition(glm::vec3 newPos) { Camera::m_Position = newPos; };
         inline const float getZoom() { return Camera::m_Zoom; };
         inline const glm::vec3 getPosition() { return Camera::m_Position; };
};

#endif