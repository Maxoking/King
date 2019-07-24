#pragma once

#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
//#include "../../utils/glmutils.h"
#include "../Renderable.h"
#include "../Camera.h"
#include "../Shader.h"
#include "../Light.h"

namespace King {
	namespace graphics {
		class KING_API Renderer {
		public:
			virtual void submit(Renderable* renderable) = 0;
      virtual void begin(Shader* shader, Camera* camera) = 0;
      virtual void begin(Shader* shader, Camera* camera, std::vector<Light*> lights, glm::mat4 lightSpaceMatrix) = 0;
      virtual void end() = 0;
      virtual void submit(std::shared_ptr<VertexArray> vao) = 0;
			virtual void flush() = 0;
    protected:
      Shader* active_shader;

		};
	}
}