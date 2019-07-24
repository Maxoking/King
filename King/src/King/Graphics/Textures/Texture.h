#pragma once

#include "King/Core.h"
#include "glad/glad.h"


namespace King {
  namespace graphics {
		enum class TextureWrap {
			NONE = 0,
			REPEAT,
			CLAMP,
			MIRRORED_REPEAT,
			CLAMP_TO_EDGE,
			CLAMP_TO_BORDER
		};

		enum class TextureFilter {
			NONE = 0,
			LINEAR,
			NEAREST
		};

		enum class TextureFormat {
			NONE = 0,
			RGB,
			RGBA,
			LUMINANCE,
			LUMINANCE_ALPHA
		};


    class Texture {
    protected:
      GLuint m_ID;
      int m_width, m_height, m_numChannels;
    public:
      virtual void const bind(unsigned int slot = 0) = 0;
			virtual void const unbind(unsigned int slot = 0) = 0;

      inline GLuint getID() { return m_ID; };
      inline unsigned int getWidth() { return m_width; };
      inline unsigned int getHeight() { return m_height; };

    };
  }
}