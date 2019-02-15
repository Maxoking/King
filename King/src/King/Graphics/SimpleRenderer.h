#pragma once
#include "Renderer2D.h"


namespace King {
	namespace graphics {
		class KING_API SimpleRenderer : public Renderer2D {
		private:
			std::deque<Renderable2D*> m_renderQueue;
		public:
			virtual void submit(Renderable2D* renderable) override;
			virtual void flush() override;

		};
	
	
	}
}
