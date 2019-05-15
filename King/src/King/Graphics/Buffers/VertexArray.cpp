#include "kngpch.h"
#include "VertexArray.h"

namespace King {
  namespace graphics {
     VertexArray::VertexArray()
     {
       glGenVertexArrays(1, &m_ID);
     }

     VertexArray::~VertexArray() 
     {
       for (int i = 0; i < m_buffers.size(); i++) {
         delete m_buffers[i];
       }
     }

     void VertexArray::addBuffer(Buffer* buffer, GLuint index)
     {
       bind();
       buffer->bind();

       glEnableVertexAttribArray(index);
       glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

       buffer->unbind();
       unbind();
     }

     void VertexArray::bind()
     {
       glBindVertexArray(m_ID);
     }

     void VertexArray::unbind()
     {
       glBindVertexArray(0);
     }

  }
}