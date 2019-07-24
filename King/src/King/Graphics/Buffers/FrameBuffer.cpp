#include "kngpch.h"
#include "Buffer.h"
#include "FrameBuffer.h"

namespace King {
  namespace graphics {

    FrameBuffer::FrameBuffer()
    {
      glGenFramebuffers(1, &m_ID);
    }


    void FrameBuffer::bind() {
      glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
    }

    void FrameBuffer::unbind() {
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::attachColorAttachment(GLuint textureID) {
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
    }

    void FrameBuffer::attachDepthAttachment(GLuint textureID) {
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureID, 0);
    }

    void FrameBuffer::attachStencilAttachment(GLuint textureID) {
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, textureID, 0);
    }

    void FrameBuffer::setDrawBuffer(GLuint drawBuffer)
    {
      
    }

    void FrameBuffer::setReadBuffer(GLuint readBuffer)
    {
    }

    bool FrameBuffer::checkStatus() {
      return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    }


    
  }
}
