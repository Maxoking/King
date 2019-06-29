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
       glDeleteVertexArrays(1, &m_ID);
     }

     void VertexArray::addBuffer(Buffer* buffer, GLuint index)
     {
       bind();
       buffer->bind();

       glEnableVertexAttribArray(index);
       glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);


       //m_buffers.push_back(buffer);

       buffer->unbind();
       unbind();
     }

     void VertexArray::addBufferWithLayout(const std::shared_ptr<Buffer>& buffer)
     {
       bind();
       buffer->bind();
       int index = 0;
       BufferLayout layout = buffer->getLayout();
       for (auto const& element : layout) {
         glEnableVertexAttribArray(index);

         glVertexAttribPointer(index, ////////////////
           element.getComponentCount(), 
           element.getComponentType(), 
           element.m_normalized ? GL_TRUE : GL_FALSE, 
           layout.getStride(), 
           (const void*)element.m_offset); /////////////

         index++;
       }
       m_buffers.push_back(buffer);
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