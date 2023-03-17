#pragma once
#include "King/Core.h"
#include "Texture.h"

#include "King/utils/ImageLoader.h"
#include "glad/glad.h"
namespace King {
	namespace graphics {
		class Texture2D : public Texture {

		public:
			Texture2D(char* filename, TextureFilter filter = TextureFilter::LINEAR, 
				TextureWrap wrap = TextureWrap::REPEAT, TextureFormat format = TextureFormat::RGB);

			Texture2D(TextureFilter filter = TextureFilter::LINEAR,
				TextureWrap wrap = TextureWrap::REPEAT, TextureFormat format = TextureFormat::RGB);

			void setData(void* data);
			void const bind(unsigned int slot = 0) override;
			void const unbind(unsigned int slot = 0) override;

		};
	}
}