#include "kngpch.h"
#include "Buffer.h"
#include "FrameBuffer.h"

namespace King {
	namespace graphics {

		FrameBuffer::FrameBuffer() {
			glGenFramebuffers(1, &m_ID);
		}


		FrameBuffer::FrameBuffer(const FramebufferSpecification& fSpec) : m_fSpec(fSpec)
		{
			invalidate();
		}


		void FrameBuffer::bind() {
			glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		}

		void FrameBuffer::unbind() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void FrameBuffer::clearDepth() {
			glClear(GL_DEPTH_BUFFER_BIT);
		}

		void FrameBuffer::clearColor() {
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void FrameBuffer::clearStencil() {
			glClear(GL_STENCIL_BUFFER_BIT);
		}

		void FrameBuffer::attachColorAttachment(GLuint textureID) {
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
		}

		void FrameBuffer::createColorAttachment(int index, const AttachmentSpecification& aSpec) {
			glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

			GLuint colorAttachment;
			glCreateTextures(GL_TEXTURE_2D, 1, &colorAttachment);
			m_colorAttachments.emplace_back(colorAttachment);
			glBindTexture(GL_TEXTURE_2D, colorAttachment);

			glTexImage2D(GL_TEXTURE_2D, 0, aSpec.m_internalFormat, m_fSpec.m_width, m_fSpec.m_height, 0, aSpec.m_format, aSpec.m_type, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, colorAttachment, 0);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

		}

		void FrameBuffer::createDepthAttachment(const AttachmentSpecification& aSpec)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

			glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment);
			glBindTexture(GL_TEXTURE_2D, m_depthAttachment);

			glTexImage2D(GL_TEXTURE_2D, 0, aSpec.m_internalFormat, m_fSpec.m_width, m_fSpec.m_height, 0, aSpec.m_format, aSpec.m_type, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, aSpec.m_minfilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, aSpec.m_magfilter);

			GLenum target = GL_DEPTH_ATTACHMENT;

			switch (aSpec.m_internalFormat) {
			case GL_DEPTH24_STENCIL8:
				target = GL_DEPTH_STENCIL_ATTACHMENT;
				break;

			default:
				break;
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, target, GL_TEXTURE_2D, m_depthAttachment, 0);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}



		void FrameBuffer::attachDepthAttachment(GLuint textureID) {
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureID, 0);
		}



		void FrameBuffer::attachStencilAttachment(GLuint textureID) {
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, textureID, 0);
		}

		void FrameBuffer::invalidate() {
			if (m_ID) {
				glDeleteFramebuffers(1, &m_ID);
				glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data());
				glDeleteTextures(1, &m_depthAttachment);

				m_colorAttachments.clear();
				m_depthAttachment = 0;
			}

			glGenFramebuffers(1, &m_ID);
			for (size_t i = 0; i < m_fSpec.m_colorSpecifications.size(); i++) {
				createColorAttachment(i, m_fSpec.m_colorSpecifications[i]);
			}

			if (m_fSpec.usesDepthBuffer) createDepthAttachment(m_fSpec.m_depthSpecification);
			if (!checkStatus()) KING_ERROR("FRAMEBUFFER NOT COMPLETE!");
		}

		void FrameBuffer::setDrawBuffer(GLuint drawBuffer)
		{

		}

		void FrameBuffer::setReadBuffer(GLuint readBuffer)
		{
		}

		void FrameBuffer::bindColorAttachment(int index, unsigned int slot) {
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, m_colorAttachments[index]);
		}

		void FrameBuffer::bindDepthAttachment(unsigned int slot) {
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
		}

		bool FrameBuffer::checkStatus() {
			return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
		}



	}
}
