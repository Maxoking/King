#include "kngpch.h"
#include "SimpleRenderer3D.h"

namespace King {
	namespace graphics {

		SimpleRenderer3D::SimpleRenderer3D() {
		}


		void SimpleRenderer3D::begin(Shader* shader, Camera* camera, std::vector<Light*> lights, glm::mat4 lightSpaceMatrix) {
			active_shader = shader;
			shader->bind();
			shader->setUniformMat4("view_proj_mat", camera->getViewProjectionMatrix());
			shader->setUniform3f("view_pos", camera->getPos());
			shader->setUniform1i("lightCount", lights.size());
			shader->setUniform1i("shadow_map", 1);
			shader->setUniform1i("ourTexture", 0);
			shader->setUniformMat4("light_space_mat", lightSpaceMatrix);

			for (int i = 0; i < lights.size(); i++) {
				std::string integer = std::to_string(i);
				switch (lights[i]->getType()) {
				case LightType::Directional:
					shader->setUniform1i(("lights[" + integer + "].type").c_str(), LightType::Directional);
					shader->setUniform3f(("lights[" + integer + "].direction").c_str(), lights[i]->getPos());
					shader->setUniform3f(("lights[" + integer + "].color").c_str(), lights[i]->getColor());
					shader->setUniform1f(("lights[" + integer + "].intensity").c_str(), lights[i]->getIntensity());
					continue;
				case LightType::Point:
					shader->setUniform1i(("lights[" + integer + "].type").c_str(), LightType::Point);
					shader->setUniform3f(("lights[" + integer + "].position").c_str(), lights[i]->getPos());
					shader->setUniform3f(("lights[" + integer + "].color").c_str(), lights[i]->getColor());
					shader->setUniform1f(("lights[" + integer + "].intensity").c_str(), lights[i]->getIntensity());

					shader->setUniform1f(("lights[" + integer + "].constant").c_str(), ((PointLight*)lights[i])->getConstant());
					shader->setUniform1f(("lights[" + integer + "].linear").c_str(), ((PointLight*)lights[i])->getLinear());
					shader->setUniform1f(("lights[" + integer + "].quadratic").c_str(), ((PointLight*)lights[i])->getQuadratic());
					continue;

				}
			}
		}

		void SimpleRenderer3D::beginShadowPass(Shader* shader, glm::mat4 lightSpaceMatrix, std::vector<Renderable*> renderables)
		{
			active_shader = shader;
			shader->bind();
			shader->setUniformMat4("light_space_mat", lightSpaceMatrix);
		}

		void SimpleRenderer3D::end()
		{
			active_shader->unbind();
		}

		void SimpleRenderer3D::submit(Renderable* renderable) {
			m_renderQueue.push_back(renderable);
		}


		void SimpleRenderer3D::flush()
		{

			while (!m_renderQueue.empty()) {
				Renderable* renderable = m_renderQueue.front();
				renderable->getMaterial().texture.bind(0);
				active_shader->setUniformMat4("model_mat", renderable->comtputeModelMatrix());
				active_shader->setUniform3f("material.diffuse", renderable->getMaterial().diffuse);
				active_shader->setUniform3f("material.specular", renderable->getMaterial().specular);
				active_shader->setUniform1f("material.shininess", renderable->getMaterial().shininess);

				for (int i = 0; i < renderable->getModel()->getMeshes().size(); i++) {
					std::shared_ptr<VertexArray> vao = renderable->getModel()->getMeshes().at(i).getVao();
					vao->bind();
					vao->getIBO()->bind();

					glDrawElements(GL_TRIANGLES, vao->getIBO()->getCount(), GL_UNSIGNED_INT, 0);

					vao->getIBO()->unbind();
					vao->unbind();
				}


				renderable->getMaterial().texture.unbind();
				m_renderQueue.pop_front();

			}


		}

	}
}