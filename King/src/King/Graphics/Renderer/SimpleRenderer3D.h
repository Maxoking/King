#pragma once
#include "Renderer.h"


namespace King {
  namespace graphics {
    class KING_API SimpleRenderer3D : public Renderer {
    private:
      //std::deque<Renderable2D*> m_renderQueue;
      std::deque<std::shared_ptr<VertexArray>> m_renderQueue;

    public:
      SimpleRenderer3D();
      virtual void submit(Renderable2D* renderable) override;
      virtual void submit(std::shared_ptr<VertexArray> vao) override;
      virtual void flush() override;

    };


  }
}