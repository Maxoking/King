#include "kngpch.h"
#include "Buffer.h"

namespace King {
  namespace graphics {
    Buffer::Buffer(GLfloat * data, GLsizei count, GLuint components) : m_componentCount(components)
    {
      glGenBuffers(1, &m_ID);
	    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
      glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
	    glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Buffer::Buffer(GLfloat* data, uint32_t size) {
      glGenBuffers(1, &m_ID);
      glBindBuffer(GL_ARRAY_BUFFER, m_ID);
      glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Buffer::bind() {
      glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    }

    void Buffer::unbind() {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }



  }
}
