#pragma once
#include "King/Core.h"
#include "glad/glad.h"

namespace King {
  namespace graphics {
    class KING_API Buffer {
    private:
      GLuint m_ID;
      GLuint m_componentCount;
    public:
      Buffer(GLfloat* data, GLsizei size, GLuint components);
      //~Buffer();
      void bind();
      void unbind();

      inline GLuint getComponentCount() { return m_componentCount; };
      inline GLuint getID() { return m_ID; };
    };
  }
}
