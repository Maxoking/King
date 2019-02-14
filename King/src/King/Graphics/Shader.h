#pragma once
#include "glad/glad.h"
#include "King/utils/fileutils.h"

namespace King {
  namespace graphics {
    class KING_API Shader {
    private:
      GLuint m_ID;
      std::string m_vertPath, m_fragPath;
    public:
      Shader(const char* vertPath, const char* fragPath);
      ~Shader();
      GLuint load();
      void bind();
      void unbind();
      GLuint getID() { return m_ID; };
    };
  }
}

