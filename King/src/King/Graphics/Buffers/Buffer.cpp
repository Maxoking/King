#include "kngpch.h"
#include "Buffer.h"

namespace King {
  namespace graphics {
    Buffer::Buffer(GLfloat * data, GLsizei count, GLuint components)
    {
      glGenBuffers(1, &m_ID);
      bind();
      glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
      unbind();
    }

    void Buffer::bind() {
      glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    }

    void Buffer::unbind() {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

  }
}
