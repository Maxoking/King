#pragma once
#include "King/Layer.h"
#include "King/Graphics/Renderer/SimpleRenderer2D.h"
#include "King/Input.h"
#include "King/Application.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"


class ExampleLayer : public King::Layer {
private:
	float m_mouseX, m_mouseY;
public:
	ExampleLayer();
	void onRender() override;
	void onUpdate() override;
	void onAttach() override;
	void addSprite(glm::vec3 pos, glm::vec2 size);
	void addSpriteAtCursor(glm::vec2 size);
	void onEvent(King::Event& e) override;
	bool onMouseButtonPressed(King::MouseButtonPressed e);
  
};
