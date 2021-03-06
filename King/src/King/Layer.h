#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Renderable2D.h"
#include "glm/mat4x4.hpp"


namespace King {

	class KING_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onRender() {}
    virtual void onImGuiRender() {}


    virtual void onEvent(Event& e) {};

    inline const std::string getName() { return m_debugName; }
  protected:
    std::string m_debugName;
	  glm::mat4 m_projectionMatrix;
	  glm::mat4 m_viewMatrix;
	  graphics::Renderer* m_renderer;
	  graphics::Shader* m_shader;
    std::vector<std::shared_ptr<graphics::VertexArray>> m_vaos;
  };

}