#pragma once
#include "King/Core.h"
#include "glad/glad.h"

namespace King {
  namespace graphics {

    enum class KING_API ShaderDataType {
      None = 0, Float, Vec2, Vec3, Vec4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t shaderDataTypeSize(ShaderDataType type) {
      switch (type) {
      case ShaderDataType::Float:   return 4;
      case ShaderDataType::Vec2:    return 2 * 4;
      case ShaderDataType::Vec3:    return 3 * 4;
      case ShaderDataType::Vec4:    return 4 * 4;
      case ShaderDataType::Mat3:    return 3 * 3 * 4;
      case ShaderDataType::Mat4:    return 4 * 4 * 4;
      case ShaderDataType::Int:     return 4;
      case ShaderDataType::Int2:    return 4 * 2;
      case ShaderDataType::Int3:    return 4 * 3;
      case ShaderDataType::Int4:    return 4 * 4;
      case ShaderDataType::Bool:    return 1;
      }

      KING_CORE_FATAL("Unknown ShaderDataType");
      return 0;
    };

    struct KING_API BufferElement {
      std::string m_name;
      ShaderDataType m_type;
      uint32_t m_size;
      uint32_t m_offset;
      bool m_normalized;

      BufferElement(ShaderDataType type, std::string name)
        : m_name(name), m_type(type), m_size(shaderDataTypeSize(m_type)), m_offset(0) {};

      uint32_t getComponentCount() const
      {
        switch (m_type)
        {
        case ShaderDataType::Float:   return 1;
        case ShaderDataType::Vec2:    return 2;
        case ShaderDataType::Vec3:    return 3;
        case ShaderDataType::Vec4:    return 4;
        case ShaderDataType::Mat3:    return 3 * 3;
        case ShaderDataType::Mat4:    return 4 * 4;
        case ShaderDataType::Int:     return 1;
        case ShaderDataType::Int2:    return 2;
        case ShaderDataType::Int3:    return 3;
        case ShaderDataType::Int4:    return 4;
        case ShaderDataType::Bool:    return 1;
        }

        KING_CORE_FATAL(false, "Unknown ShaderDataType!");
        return 0;
      }

      GLenum getComponentType() const
      {
        switch (m_type)
        {
        case ShaderDataType::Float:   return GL_FLOAT;
        case ShaderDataType::Vec2:    return GL_FLOAT;
        case ShaderDataType::Vec3:    return GL_FLOAT;
        case ShaderDataType::Vec4:    return GL_FLOAT;
        case ShaderDataType::Mat3:    return GL_FLOAT;
        case ShaderDataType::Mat4:    return GL_FLOAT;
        case ShaderDataType::Int:     return GL_INT;
        case ShaderDataType::Int2:    return GL_INT;
        case ShaderDataType::Int3:    return GL_INT;
        case ShaderDataType::Int4:    return GL_INT;
        case ShaderDataType::Bool:    return GL_BOOL;
        }

        KING_CORE_FATAL(false, "Unknown ShaderDataType!");
        return 0;
      }
    };

    class KING_API BufferLayout {
    private:
      std::vector<BufferElement> m_elements;
      uint32_t m_stride;

    private:
      void calculateOffsetAndStride() {
        uint32_t offset = 0;
        m_stride = 0;
        for (int i = 0; i < m_elements.size(); i++) {
          m_elements[i].m_offset = offset;
          offset += m_elements[i].m_size;
          m_stride += m_elements[i].m_size;
        }
      };

    public:
      BufferLayout() {};
      BufferLayout(const std::initializer_list<BufferElement>& elements) : m_elements(elements) {
        calculateOffsetAndStride();
      };

      inline const std::vector<BufferElement>& getElements() const { return m_elements; };
      inline const uint32_t& getStride() const { return m_stride; };

      std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
      std::vector<BufferElement>::iterator end() { return m_elements.end(); }
      std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
      std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

    };
  }
}