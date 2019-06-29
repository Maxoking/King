#pragma once
#include "King/Core.h"
#include "King/Layer.h"
#include "King/Application.h"
#include "King/Graphics/Renderer/SimpleRenderer3D.h"
#include "King/Graphics/Buffers/VertexArray.h"
#include "King/Graphics/Buffers/IndexBuffer.h"
#include "King/Graphics/Buffers/Buffer.h"
#include "Model.h"
#include "King/Graphics/Camera.h"
#include "King/Events/KeyEvent.h"

#include "King/Input.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"



using namespace King;

class TestGameLayer : public King::Layer {

public:
  TestGameLayer();
  void onUpdate() override;
  void onAttach() override;
  void onRender() override;
  void onEvent(Event & e) override;
  bool onMousePressed(King::MouseButtonPressed e);
  bool onMouseReleased(King::MouseButtonReleased e);
  bool onKeyPressed(King::KeyPressedEvent e);
  bool onKeyReleased(King::KeyReleasedEvent e);
  bool onMouseMoved(King::MouseMoved e);



private:
  float m_camSpeedForward;
  float m_camSpeedRight;
  float camspeed = 0.0025f;
  glm::vec3 m_camVelocity;
  float m_sensitivity;
  float m_lastTime;
  bool camMode;
  std::pair<float, float> m_windowCenter;
  std::shared_ptr<graphics::VertexArray> m_VertexArray;
//  std::shared_ptr<graphics::Model> m_model;
  std::shared_ptr<graphics::Camera> m_camera;
  

};
