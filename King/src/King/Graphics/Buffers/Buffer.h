#pragma once
#include "King/Core.h"
#include "glad/glad.h"

#include "BufferLayout.h"

namespace King {
  namespace graphics {
    class KING_API Buffer {
    private:
      GLuint m_ID;
      GLuint m_componentCount;
      BufferLayout m_layout;
    public:
      Buffer(GLfloat* data, GLsizei size, GLuint components);
      Buffer(GLfloat * data, uint32_t size);
      void bind();
      void unbind();

      const BufferLayout& getLayout() const { return m_layout; }
      void setLayout(const BufferLayout& layout) { m_layout = layout; }

      inline GLuint getComponentCount() { return m_componentCount; };
      inline GLuint getID() { return m_ID; };
    };
  }
}
