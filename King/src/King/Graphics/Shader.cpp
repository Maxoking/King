#include "kngpch.h"
#include "Shader.h"

namespace King {
  namespace graphics {
    Shader::Shader(const char* vertPath, const char* fragPath)
      : m_vertPath(vertPath), m_fragPath(fragPath)
    {
      m_ID = load();
    }

    Shader::~Shader()
    {
      glDeleteShader(m_ID);
    }

    GLuint Shader::load()
    {

      GLint compileResult = GL_FALSE;
      int infoLogLength;

      std::string vertexCode = read_file(m_vertPath.c_str());
      const char* vertexSource = vertexCode.c_str();
      GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertexID, 1, &vertexSource, NULL);
      glCompileShader(vertexID);



      glGetShaderiv(vertexID, GL_COMPILE_STATUS, &compileResult);
      glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &infoLogLength);
      if (infoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(vertexID, infoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
      }

      std::string fragCode = read_file(m_fragPath.c_str());
      const char* fragSource = fragCode.c_str();
      GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragID, 1, &fragSource, NULL);
      glCompileShader(fragID);

      glGetShaderiv(fragID, GL_COMPILE_STATUS, &compileResult);
      glGetShaderiv(fragID, GL_INFO_LOG_LENGTH, &infoLogLength);
      if (infoLogLength > 0) {
        std::vector<char> fragShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragID, infoLogLength, NULL, &fragShaderErrorMessage[0]);
        printf("%s\n", &fragShaderErrorMessage[0]);
      }

      GLuint shaderProgram = glCreateProgram();
      glAttachShader(shaderProgram, vertexID);
      glAttachShader(shaderProgram, fragID);
      glLinkProgram(shaderProgram);
      return shaderProgram;
    }

    void Shader::bind()
    {
      glUseProgram(m_ID);
    }

    void Shader::unbind()
    {
      glUseProgram(0);
    }

	void Shader::setUniform1f(const GLchar * name, float value)
	{
		glUniform1f(glGetUniformLocation(m_ID, name), value);
	}

	void Shader::setUniform1i(const GLchar * name, int value)
	{
		glUniform1i(glGetUniformLocation(m_ID, name), value);
	}

	void Shader::setUniform2f(const GLchar * name, glm::vec2 value)
	{
		glUniform2f(glGetUniformLocation(m_ID, name), value.x, value.y);
	}

	void Shader::setUniform3f(const GLchar * name, glm::vec3 value)
	{
		glUniform3f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z);
	}

	void Shader::setUniform4f(const GLchar * name, glm::vec4 value)
	{
		glUniform4f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z, value.w);
	}

	void Shader::setUniformMat4(const GLchar * name, glm::mat4 value)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, &value[0][0]);
	}
  }
}
