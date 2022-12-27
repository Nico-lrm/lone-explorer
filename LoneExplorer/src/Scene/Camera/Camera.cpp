#include "Camera.hpp"

// Définition des fonctions
// ------------------------
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
    // Si l'utilisateur saisies de nouvelles valeurs pour la caméra
    m_Position = position;
    m_WorldUp = up;
    m_Yaw = yaw;
    m_Pitch = pitch;

    // On met à jour les vecteurs de notre caméra
    updateCameraVectors();
}

const glm::mat4 Camera::getCameraMatrix(const unsigned int& width, const unsigned int& height)
{
    // Initialisation
    glm::mat4 view{ glm::mat4(1.0f) };
    glm::mat4 projection{ glm::mat4(1.0f) };

    // Calcul
    view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);    
    projection = glm::perspective(glm::radians(m_Zoom), static_cast<float>(width) / height, 0.01f, 500.f);

    // Retour
    return projection * view;
}

void Camera::Move(CameraDirection direction, float deltaTime)
{
    float velocity{ m_MovementSpeed * deltaTime };
    switch (direction)
    {
        case FORWARD:
            m_Position += m_Orientation * velocity;
        break;
        case BACKWARD:
            m_Position -= m_Orientation * velocity;
        break;
        case LEFT:
            m_Position -= m_Right * velocity;
        break;
        case RIGHT:
            m_Position += m_Right * velocity;
        break;
        case UP:
            m_Position += m_Up * velocity;
        break;
        case BOTTOM:
            m_Position -= m_Up * velocity;
        break;
    }
}

void Camera::Look(float xoffset, float yoffset)
{
    xoffset *= m_MouseSensitivity;
    yoffset *= m_MouseSensitivity;

    m_Yaw += xoffset;
    m_Pitch += yoffset;

    // Pour éviter que l'écran s'inverse, on ajoute une contrainte sur le Pitch
    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;

    // On met à jour les vectors grâce à notre fonction
    updateCameraVectors();
}

void Camera::Zoom(float yoffset)
{
    m_Zoom -= static_cast<float>(yoffset);
    if (m_Zoom < 1.0f)
        m_Zoom = 1.0f;
    if (m_Zoom > ZOOM)
        m_Zoom = ZOOM;
}

void Camera::updateCameraVectors()
{
    // On modifie l'orientation de la caméra
    glm::vec3 newOrientation;
    newOrientation.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    newOrientation.y = sin(glm::radians(m_Pitch));
    newOrientation.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Orientation = glm::normalize(newOrientation);
    
    // On calcul les vecteurs Up et Right de la caméra en fonction de la nouvelle orientation et de WorldUp
    m_Right = glm::normalize(glm::cross(m_Orientation, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Orientation));
}