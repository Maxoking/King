#pragma once
#include "kngpch.h"
#include "Texture2D.h"

namespace King {
	namespace graphics {
		
		Texture2D::Texture2D(char * filename, TextureFilter filter, 
			TextureWrap wrap , TextureFormat format )
		{
			glGenTextures(1, &m_ID);
			glBindTexture(GL_TEXTURE_2D, m_ID);
			unsigned char *data = loadImage(filename, &m_width, &m_height, &m_numChannels);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_width, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			stbi_image_free(data);
		}

		Texture2D::Texture2D(TextureFilter filter,
			TextureWrap wrap, TextureFormat format)
		{
			glGenTextures(1, &m_ID);
			glBindTexture(GL_TEXTURE_2D, m_ID); 
			uint32_t whiteColor = 0xffffff;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, &whiteColor);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		}

		void Texture2D::setData(void* data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_width, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}

		void const Texture2D::bind(unsigned int slot)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, m_ID);
		}

		void const Texture2D::unbind(unsigned int slot)
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, 0);
		}


	}
}