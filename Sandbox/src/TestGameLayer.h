#pragma once
#include "King/Core.h"
#include "King/Layer.h"
#include "King/Application.h"
#include "King/Graphics/Renderer/SimpleRenderer3D.h"
#include "King/Graphics/Buffers/VertexArray.h"
#include "King/Graphics/Buffers/IndexBuffer.h"
#include "King/Graphics/Buffers/Buffer.h"
#include "King/Graphics/Model.h"
#include "King/Graphics/Camera.h"
#include "King/Events/KeyEvent.h"
#include "King/Graphics/Renderable.h"
#include "King/Graphics/Buffers/FrameBuffer.h"
#include "King/Graphics/Textures/TextureDepth.h"

#include "imgui.h"
#include "King/Input.h"
#include "King/utils/SimpleOBJLoader.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/random.hpp"
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
  void onImGuiRender() override;



private:
  float m_camSpeedForward;
  float m_camSpeedRight;
  float camspeed = 0.015f;
  glm::vec3 m_camVelocity;
  float m_sensitivity;
  double m_lastTime;
  bool camMode;
  std::vector<graphics::Renderable*> m_renderables;
  std::pair<float, float> m_windowCenter;
  graphics::Camera* m_camera;
  graphics::Renderable* m_lightSphere;
  graphics::Renderable* m_renderable;
  graphics::Renderable* m_floor;
  graphics::Shader* m_lightShader;
  graphics::Shader* m_shadowShader;
  graphics::Light* m_light;
  graphics::FrameBuffer* m_depthBuffer;
  glm::mat4 m_lightView;
  glm::mat4 m_lightProjection;
  glm::mat4 m_lightSpaceMatrix;
 //graphics::Texture2D* m_tex2D;
  graphics::TextureDepth* m_texDepth;
  std::vector<graphics::Light*> m_lights;
};
