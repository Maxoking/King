#include "kngpch.h"
#include "Camera.h"

namespace King {
  namespace graphics {

    Camera::Camera(const glm::vec3& pos, float fov, float aspectRatio, float zNear, float zFar)
    {
      m_yaw = -90.f;
      m_pitch = 0.f;
      m_position = pos;
      m_fov = fov;
      m_zNear = zNear;
      m_zFar = zFar;
      //m_direction = glm::vec3(0.f, 0.f, 0.1f);
      m_direction = glm::vec3(0.f, 0.f, -1.f);
      m_worldUp = glm::vec3(0.f, 1.f, 0.f);
      m_upVector = glm::cross(m_direction, glm::normalize(glm::cross(m_worldUp, m_direction)));

      m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, m_upVector);

      m_projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
    }
    void Camera::updateCameraMatrices()
    {
      glm::vec3 front;
      front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
      front.y = sin(glm::radians(m_pitch));
      front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
      m_direction = glm::normalize(front);
      m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, m_upVector);
    }
  }
}

