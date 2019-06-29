#include "kngpch.h"
#include "SimpleRenderer2D.h"
namespace King {
	namespace graphics {


    void SimpleRenderer2D::submit(std::shared_ptr<VertexArray> vao) {};

		void SimpleRenderer2D::submit(Renderable2D * renderable)
		{
			m_renderQueue.push_back(renderable);
		}

		void SimpleRenderer2D::flush()
		{
			while (!m_renderQueue.empty()) {
				Renderable2D* renderable = m_renderQueue.front();

				renderable->getVAO()->bind();
				renderable->getIBO()->bind();

				renderable->getShader()->setUniformMat4("model_mat", glm::translate(glm::mat4(1.f), renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_INT, 0);

				renderable->getIBO()->unbind();
				renderable->getVAO()->unbind();

				m_renderQueue.pop_front();
				
			}
		}

	}
}
