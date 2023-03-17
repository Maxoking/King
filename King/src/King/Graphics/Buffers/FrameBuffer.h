#pragma once
#include "King/Core.h"
#include "glad/glad.h"

#include "BufferLayout.h"

namespace King {
	namespace graphics {
		struct AttachmentSpecification {
			GLint m_internalFormat = 0;
			GLenum m_format;
			GLenum m_type;
			GLenum m_minfilter = GL_LINEAR;
			GLenum m_magfilter = GL_LINEAR;
			GLenum m_wrap_s = GL_CLAMP_TO_BORDER;
			GLenum m_wrap_t = GL_CLAMP_TO_BORDER;

			AttachmentSpecification() = default;

			AttachmentSpecification(GLint internalFormat, GLenum format, GLenum type) : 
				m_internalFormat(internalFormat), m_format(format), m_type(type) {}
		};


		struct FramebufferSpecification {
			uint32_t m_width = 0;
			uint32_t m_height = 0;


			std::vector<AttachmentSpecification> m_colorSpecifications;
			AttachmentSpecification m_depthSpecification;
			bool usesDepthBuffer = false;

			int samples = 1; //for multisampling

			FramebufferSpecification() = default;
			FramebufferSpecification(std::initializer_list<AttachmentSpecification> colorSpecs, uint32_t width, uint32_t height) :
				m_colorSpecifications(colorSpecs), m_width(width), m_height(height) {};


			FramebufferSpecification(std::initializer_list<AttachmentSpecification> colorSpecs, AttachmentSpecification depthSpec, uint32_t width, uint32_t height) :
				m_colorSpecifications(colorSpecs), m_depthSpecification(depthSpec), m_width(width), m_height(height) {
				usesDepthBuffer = true;
			};


		};

		class  FrameBuffer {
			
		private:
			GLuint m_ID = 0;

			std::vector<GLuint> m_colorAttachments;
			GLuint m_depthAttachment = 0;

			FramebufferSpecification m_fSpec;
		public:
			
			FrameBuffer();
			FrameBuffer(const FramebufferSpecification& fSpec);
			void bind();
			void unbind();
			void clearDepth();
			void clearColor();
			void clearStencil();
			void attachColorAttachment(GLuint textureID);
			void createColorAttachment(int index, const AttachmentSpecification& aSpec);
			void createDepthAttachment(const AttachmentSpecification& aSpec);
			void attachDepthAttachment(GLuint textureID);
			void attachStencilAttachment(GLuint textureID);

			void bindColorAttachment(int index, unsigned int slot);
			void bindDepthAttachment(unsigned int slot);


			void invalidate();

			void setDrawBuffer(GLuint drawBuffer);
			void setReadBuffer(GLuint readBuffer);

			bool checkStatus();

			

			inline GLuint getID() { return m_ID; };
			inline GLuint getColorAttachment(size_t index = 0) { return m_colorAttachments[index]; };
			inline GLuint getDepthAttachment() { return m_depthAttachment; };

			inline FramebufferSpecification& getSpecification() { return m_fSpec; };
		};
	}
}
