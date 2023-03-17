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
      inline const glm::mat4& getViewMatrix() const { return m_viewMatrix; };
      inline const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; };
      void setProjectionMatrix(glm::mat4 proj) { m_projectionMatrix = proj; };
      void setViewMatrix(glm::mat4 view) { m_viewMatrix = view; };

      inline const glm::mat4& getViewProjectionMatrix() const { return m_projectionMatrix * m_viewMatrix; };

      void updateCameraMatrices();

      void setPos(glm::vec3 position) { m_position = position; };
      inline const glm::vec3& getPos() const { return m_position; };

      void setUp(glm::vec3 up) { m_upVector = up; };
      inline const glm::vec3& getUp() const { return m_upVector; };

      void setDir(glm::vec3 direction) { m_direction = direction; };
      inline const glm::vec3& getDir() const { return m_direction; };

      void setYaw(float yaw) { m_yaw = yaw; };
      inline const float& getYaw() const { return m_yaw; };


      void setPitch(float pitch) { m_pitch = pitch; };
      inline const float& getPitch() const { return m_pitch; };

      void setFov(float fov) { m_fov = fov; };
      inline const float& getFov() const { return m_fov; };

      void setZNear(float zNear) { m_zNear = zNear; };
      inline const float& getZNear() const { return m_zNear; };

      void setZFar(float zFar) { m_zFar = zFar; };
      inline const float& getZFar() const { return m_zFar; };


    private:
      glm::vec3 m_worldUp;
      glm::vec3 m_position, m_upVector, m_direction;
      float m_pitch, m_yaw;
      float m_fov, m_zNear, m_zFar;
      glm::mat4 m_projectionMatrix;
      glm::mat4 m_viewMatrix;
    };
  }
}
