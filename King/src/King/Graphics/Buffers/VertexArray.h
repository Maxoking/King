#pragma once
#include "kngpch.h"
#include "King/Core.h"
#include "Buffer.h"
#include "glad/glad.h"
#include "IndexBuffer.h"

namespace King {
  namespace graphics {
    class KING_API VertexArray {
    private:
      GLuint m_ID;
      std::vector<std::shared_ptr<Buffer>> m_buffers;
      std::shared_ptr<IndexBuffer> m_ibo;

    public:
      VertexArray();
      ~VertexArray();
      void addBuffer(Buffer* buffer, GLuint index);
      void addBufferWithLayout(const std::shared_ptr<Buffer>& vertexBuffer);
      void setIBO(const std::shared_ptr<IndexBuffer>& ibo) { m_ibo = ibo; };
      virtual const std::shared_ptr<IndexBuffer>& getIBO() const { return m_ibo; };
      void bind();
      void unbind();

   
    };
  }
}

