#pragma once
#include "Renderer.h"
#include "../Shader.h"


namespace King {
	namespace graphics {
		class KING_API SimpleRenderer3D : public Renderer {
		private:
			std::deque<Renderable*> m_renderQueue;

		public:
			SimpleRenderer3D();
			virtual void begin(Shader* shader, Camera* camera, std::vector<Light*> lights, glm::mat4 lightSpaceMatrix) override;
			void beginShadowPass(Shader* shader, glm::mat4 lightSpaceMatric, std::vector<Renderable*> renderables);
			virtual void end() override;
			virtual void submit(Renderable* renderable) override;
			virtual void flush() override;
		};


	}
}