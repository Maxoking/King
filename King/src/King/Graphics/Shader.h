#pragma once
#include "glad/glad.h"
#include "glm/mat4x4.hpp"
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

	  void setUniform1f(const GLchar* name, float value);
	  void setUniform1i(const GLchar* name, int value);
	  void setUniform2f(const GLchar* name, glm::vec2 value);
	  void setUniform3f(const GLchar* name, glm::vec3 value);
	  void setUniform4f(const GLchar* name, glm::vec4 value);
	  void setUniformMat4(const GLchar* name, glm::mat4 value);
    };
  }
}

