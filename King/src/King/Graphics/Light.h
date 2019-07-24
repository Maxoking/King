#pragma once
#include "Model.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace King {
  namespace graphics {
    enum LightType{ None, Directional, Point, Spot};

    class Light {
    public:
      Light() {};
      void setPos(glm::vec3 pos) { m_pos = pos; };
      inline const glm::vec3& getPos() const { return m_pos; };
      void setColor(glm::vec3 color) { m_color = color; };
      inline const glm::vec3& getColor() const { return m_color; };
      void setIntensity(float intensity) { m_intensity = intensity; };
      inline const float& getIntensity() const { return m_intensity; };
      inline const LightType getType() const { return m_type; };
    protected:
      LightType m_type = LightType::None;
      glm::vec3 m_pos;
      glm::vec3 m_color = glm::vec3(1.f);
      float m_intensity = 0.5f;
    };

    class DirectionalLight : public Light {
    public:
      DirectionalLight() { m_type = LightType::Directional; };
    };

    class PointLight : public Light {
    public:
      PointLight(){ m_type = LightType::Point; };
      inline const float& getConstant() const { return m_constant; };
      void setConstant(float constant) { m_constant = constant; };
      inline const float& getLinear() const { return m_linear; };
      void setLinear(float linear) { m_linear = linear; };
      inline const float& getQuadratic() const { return m_quadratic; };
      void setQuadratic(float quadratic) { m_quadratic = quadratic; };
    protected:
      float m_constant = 1.f;
      float m_linear = 0.09f;
      float m_quadratic = 0.032f;

    };


  }
}
