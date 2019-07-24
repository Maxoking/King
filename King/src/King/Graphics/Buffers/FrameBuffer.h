#pragma once
#include "King/Core.h"
#include "glad/glad.h"

#include "BufferLayout.h"

namespace King {
  namespace graphics {
    class  FrameBuffer {
    private:
      GLuint m_ID;
    public:
      FrameBuffer();
      void bind();
      void unbind();
			void clearDepth();
			void clearColor();
			void clearStencil();
      void attachColorAttachment(GLuint textureID);
      void attachDepthAttachment(GLuint textureID);
      void attachStencilAttachment(GLuint textureID);

      void setDrawBuffer(GLuint drawBuffer);
      void setReadBuffer(GLuint readBuffer);

      bool checkStatus();

      inline GLuint getID() { return m_ID; };
    };
  }
}
