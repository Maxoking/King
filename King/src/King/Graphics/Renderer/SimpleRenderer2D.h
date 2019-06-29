#pragma once
#include "Renderer.h"


namespace King {
	namespace graphics {
		class KING_API SimpleRenderer2D : public Renderer {
		private:
			std::deque<Renderable2D*> m_renderQueue;
		public:
			virtual void submit(Renderable2D* renderable) override;
      virtual void submit(std::shared_ptr<VertexArray> vao) override;
			virtual void flush() override;

		};
	
	
	}
}
