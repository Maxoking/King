#pragma once
#include "King/Layer.h"
#include "King/Graphics/SimpleRenderer.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"


class ExampleLayer : public King::Layer {
public:
	ExampleLayer();
	void onRender() override;
	void onUpdate() override;
	void onAttach() override;
  //void onEvent(King::Event& e) override { KING_TRACE(e); };
};
