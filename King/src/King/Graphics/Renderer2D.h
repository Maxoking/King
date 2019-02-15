#pragma once

#include "glad/glad.h"
#include "glm/vec3.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "Renderable2D.h"

namespace King {
	namespace graphics {
		class KING_API Renderer2D {
		public:
			virtual void submit(Renderable2D* renderable) = 0;
			virtual void flush() = 0;

		};
	}
}