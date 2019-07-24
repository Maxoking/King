#pragma once

#include "King/Core.h"
#include "glad/glad.h"


namespace King {
  namespace graphics {
    class Texture {
    private:
      unsigned int m_width, m_height;
      GLuint m_ID;
    public:
      Texture();
      void bind();
      void unbind();

      inline GLuint getID() { return m_ID; };
      inline unsigned int getWidth() { return m_width; };
      inline unsigned int getHeight() { return m_height; };

    };
  }
}