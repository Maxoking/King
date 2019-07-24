#pragma once
#include "Model.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace King {
  namespace graphics {

    struct Material {
      glm::vec3 diffuse;
      glm::vec3 specular;
      float shininess;
    };

    class KING_API Renderable {
    public:
      Renderable(glm::vec3 pos);
      void loadModel(std::string path);
      void setPos(glm::vec3 pos) { m_pos = pos; };
      inline const glm::vec3& getPos() const { return m_pos; };
      void setColor(glm::vec3 color) { m_color = color; };
      inline const glm::vec3& getColor() const { return m_color; };
      void move(glm::vec3 vec) { m_pos += vec; };
      glm::mat4 comtputeModelMatrix();
      Model* getModel() { return m_model; };
      inline Material& getMaterial() { return m_material; };
    private:
      Model* m_model;
      Material m_material;
      glm::vec3 m_pos;
      glm::vec3 m_color;
    };
  }
}
