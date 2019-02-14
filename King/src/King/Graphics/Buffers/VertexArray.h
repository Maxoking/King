#pragma once
#include "kngpch.h"
#include "King/Core.h"
#include "Buffer.h"
#include "glad/glad.h"

namespace King {
  namespace graphics {
    class KING_API VertexArray {
    private:
      GLuint m_ID;
      std::vector<Buffer*> m_buffers;

    public:
      VertexArray();
      ~VertexArray();
      void addBuffer(Buffer* buffer, GLuint index);
      void bind();
      void unbind();

   
    };
  }
}

