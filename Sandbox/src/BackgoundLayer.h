#pragma once
#include "King/Layer.h"
#include "King/Application.h"
#include "King/Graphics/SimpleRenderer.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

class BackgroundLayer : public King::Layer {
private:
	float m_mouseX, m_mouseY;
public:
	BackgroundLayer();
	void onRender() override;
	void onUpdate() override;
	void onAttach() override;/*
	void onEvent(King::Event& e) override;
	bool onMouseButtonPressed(King::MouseButtonPressed e);
*/
};