#include "kngpch.h"
#include "IndexBuffer.h"


namespace King {
	namespace graphics {

		IndexBuffer::IndexBuffer(GLuint * data, GLsizei count) : m_count(count)
		{
			glGenBuffers(1, &m_ID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void IndexBuffer::bind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		}

		void IndexBuffer::unbind() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

	}
}