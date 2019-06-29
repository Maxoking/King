#include "kngpch.h"
#include "SimpleRenderer3D.h"

namespace King {
  namespace graphics {

    SimpleRenderer3D::SimpleRenderer3D() {
    }

    void SimpleRenderer3D::submit(Renderable2D* renderable) {};

    void SimpleRenderer3D::submit(std::shared_ptr<VertexArray> vao)
    {
      m_renderQueue.push_back(vao);
    }

    void SimpleRenderer3D::flush()
    {
   /*   submit(m_VertexArray);
      m_Shader->bind();*/
      while (!m_renderQueue.empty()) {
        std::shared_ptr<VertexArray> vao = m_renderQueue.front();

        vao->bind();
        vao->getIBO()->bind();

        //renderable->getShader()->setUniformMat4("model_mat", glm::translate(glm::mat4(1.f), renderable->getPosition()));
        glDrawElements(GL_TRIANGLES, vao->getIBO()->getCount(), GL_UNSIGNED_INT, 0);

        vao->getIBO()->unbind();
        vao->unbind();

        m_renderQueue.pop_front();
  
      }

      //m_Shader->unbind();
    }

  }
}