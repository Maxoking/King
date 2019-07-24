#include "kngpch.h"
#include "Renderable.h"

King::graphics::Renderable::Renderable(glm::vec3 pos) : m_pos(pos)
{
}

void King::graphics::Renderable::loadModel(std::string path)
{
  m_model = new Model(path);
  //m_model->loadModel(path);
}

glm::mat4 King::graphics::Renderable::comtputeModelMatrix()
{
  glm::mat4 modelMatrix = glm::translate(glm::mat4(1.f), m_pos);
  return modelMatrix;
}
