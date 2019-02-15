#include "kngpch.h"
#include "SimpleRenderer.h"
namespace King {
	namespace graphics {

		void SimpleRenderer::submit(Renderable2D * renderable)
		{
			m_renderQueue.push_back(renderable);
		}

		void SimpleRenderer::flush()
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
