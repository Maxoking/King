#pragma once
#include "King/Core.h"
#include "Buffers/Buffer.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexArray.h"
#include "Shader.h"
#include "glm/vec2.hpp"

namespace King {
	namespace graphics {
		class KING_API Renderable2D {
		private:
			glm::vec3 m_position;
			glm::vec2 m_size;
			
			VertexArray* m_vao;
			IndexBuffer* m_ibo;
			Shader* m_shader;
			
		public:
			Renderable2D(glm::vec3 position, glm::vec2 size, Shader* shader);

			inline VertexArray* getVAO() { return m_vao; };
			inline IndexBuffer* getIBO() { return m_ibo; };
			inline Shader* const getShader() { return m_shader; };

			inline glm::vec3& const getPosition() { return m_position ; };
			inline glm::vec2& const getSize() { return m_size; };
		};
	}
}
