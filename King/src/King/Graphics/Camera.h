#pragma once
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/rotate_vector.hpp"

namespace King {
  namespace graphics {
    class KING_API Camera {
    public:
      Camera(const glm::vec3& pos, float fov, float aspectRatio, float zNear, float zFar);
      inline const glm::mat4& const getViewMatrix() { return m_viewMatrix; };
      inline const glm::mat4& const getProjectionMatrix() { return m_projectionMatrix; };
      void updateCameraMatrices();

      void setPos(glm::vec3 position) { m_position = position; };
      inline const glm::vec3& const getPos() { return m_position; };

      void setUp(glm::vec3 up) { m_upVector = up; };
      inline const glm::vec3& const getUp() { return m_upVector; };

      void setDir(glm::vec3 direction) { m_direction = direction; };
      inline const glm::vec3& const getDir() { return m_direction; };

      void setYaw(float yaw) { m_yaw = yaw; };
      inline const float& const getYaw() { return m_yaw; };
      void setPitch(float pitch) { m_pitch = pitch; };
      inline const float& const getPitch() { return m_pitch; };
    private:
      glm::vec3 m_worldUp;
      glm::vec3 m_position, m_upVector, m_direction;
      float m_pitch, m_yaw;
      glm::mat4 m_projectionMatrix;
      glm::mat4 m_viewMatrix;
    };
  }
}
