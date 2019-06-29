#pragma once

#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
//#include "../../utils/glmutils.h"
#include "../Renderable2D.h"

namespace King {
	namespace graphics {
		class KING_API Renderer {
		public:
			virtual void submit(Renderable2D* renderable) = 0;
      virtual void submit(std::shared_ptr<VertexArray> vao) = 0;
			virtual void flush() = 0;

		};
	}
}