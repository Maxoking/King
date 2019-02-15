#pragma once
#include "King/Core.h"
#include "glad/glad.h"

namespace King {
	namespace graphics {

		class KING_API IndexBuffer {
		private:
			GLuint m_ID;
			GLuint m_count;
		public:
			IndexBuffer(GLuint * data, GLsizei count);
			void bind();
			void unbind();

			inline GLuint getCount() { return m_count; };
			inline GLuint getID() { return m_ID; };
		};

	}
}

