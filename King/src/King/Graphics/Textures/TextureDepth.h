#pragma once
#include "Texture.h"

namespace King {
	namespace graphics {
		class TextureDepth : public Texture {
		public:
			TextureDepth(int width, int height);
			void const bind(unsigned int slot = 0);
			void const unbind(unsigned int slot = 0);
		};

	}
}