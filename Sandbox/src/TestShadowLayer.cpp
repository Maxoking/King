
#include "TestShadowLayer.h"
#include "King/utils/ImageLoader.h"
#include <filesystem>


#define BIND_FN(x) std::bind(&TestShadowLayer::x, this, std::placeholders::_1)

TestShadowLayer::TestShadowLayer() {

  m_renderer = new graphics::SimpleRenderer3D();
  m_camera = new graphics::Camera(glm::vec3(0.f, 1.5f, 5.f),
    70.f,
    King::Application::get().getApectRatio(),
    0.01f,
    1000.f);

  
  m_shader = new graphics::Shader("D:/dev/King/King/src/King/Graphics/Shaders/TestShader2.vert",
    "D:/dev/King/King/src/King/Graphics/Shaders/TestShader2.frag");

  m_lightShader = new graphics::Shader("D:/dev/King/King/src/King/Graphics/Shaders/lightShader.vert",
    "D:/dev/King/King/src/King/Graphics/Shaders/lightShader.frag");

  m_shadowShader = new graphics::Shader("D:/dev/King/King/src/King/Graphics/Shaders/simpleShadowShader.vert",
    "D:/dev/King/King/src/King/Graphics/Shaders/simpleShadowShader.frag");


  m_camVelocity = glm::vec3(0.f);
  m_camSpeedForward = 0.f;
  m_camSpeedRight = 0.f;
  m_sensitivity = 30.f;
  m_windowCenter.first = (float)(Application::get().getWindow().getWidth()) / 2.f;
  m_windowCenter.second = (float)(Application::get().getWindow().getHeight()) / 2.f;


  m_light = new graphics::DirectionalLight();
  m_light->setPos(glm::vec3(3.f, 6.5f, 0.f));
  m_light->setIntensity(0.5f);
  m_lights.push_back(m_light);

  graphics::PointLight* pl = new graphics::PointLight();
  pl->setPos(glm::vec3(0.f, 5.f, 0.f));
  pl->setIntensity(0.5f);
  m_lights.push_back(pl);


  m_renderable = new graphics::Renderable(glm::vec3(0.f, 2.f, -2.f));
  m_renderable->loadModel("res/models/Monkey.obj");
  m_renderable->getMaterial().diffuse = glm::vec3(0.7f, 0.1f, 0.3f);
  m_renderable->getMaterial().specular = glm::vec3(0.7f, 0.1f, 0.3f);
  m_renderable->getMaterial().shininess = 32.f;
  m_renderables.push_back(m_renderable);

  m_lamp = new graphics::Renderable(pl->getPos());
  m_lamp->loadModel("res/models/smoothsphere.obj");
  m_lamp->setColor(glm::vec3(0.7f, 0.4f, 0.3f));
  m_lamp->getMaterial().diffuse = glm::vec3(0.7f, 0.1f, 0.3f);
  m_lamp->getMaterial().specular = glm::vec3(0.7f, 0.1f, 0.3f);
  m_lamp->getMaterial().shininess = 32.f;
  m_renderables.push_back(m_lamp);


  m_floor = new graphics::Renderable(glm::vec3(0.f));
  m_floor->loadModel("res/models/PlaneWithUV.obj");
  m_floor->getMaterial().diffuse = glm::vec3(0.45f, 0.4f, 0.7f);
  m_floor->getMaterial().specular = glm::vec3(0.45f, 0.4f, 0.7f);
  m_floor->getMaterial().shininess = 16.f;
  m_renderables.push_back(m_floor);


  m_lastTime = Application::getTime();
  camMode = false;

	m_tex2D = new graphics::Texture2D("res/textures/container.jpg");

  m_depthBuffer = new graphics::FrameBuffer();

  //The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
  m_depthBuffer->bind();

	m_texDepth = new graphics::TextureDepth(1024, 1024);
	m_depthBuffer->attachDepthAttachment(m_texDepth->getID());

  glDrawBuffer(GL_NONE); // No color buffer is drawn to.

  // Always check that our framebuffer is ok
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    KING_ERROR("FRAMEBUFFER NOT COMPLETE");

  m_depthBuffer->unbind();

  float near_plane = 1.0f, far_plane = 20.f;
  m_lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane,
    far_plane);

 
  //m_camera->setProjectionMatrix(m_lightProjection);
  
}

void TestShadowLayer::onAttach() {

}


void TestShadowLayer::onUpdate() {

  double currentTime = Application::getTime();
  float deltaTime = float(currentTime - m_lastTime);
  m_lastTime = currentTime;



  if (camMode) {
    Application::get().getWindow().setMousePos(m_windowCenter.first, m_windowCenter.second);
		m_mousespeed = m_sensitivity * deltaTime;
  }
  


  glm::vec3 forwardVec = glm::normalize(m_camera->getDir());
  glm::vec3 rightVec = glm::normalize(glm::cross(m_camera->getDir(), m_camera->getUp()));
  m_camera->setPos(m_camera->getPos() + rightVec * m_camVelocity.x * deltaTime);
  m_camera->setPos(m_camera->getPos() + forwardVec * m_camVelocity.z * deltaTime);
  m_camera->setPos(m_camera->getPos() + m_camera->getUp() * m_camVelocity.y * deltaTime);
  m_camera->updateCameraMatrices();

 


  glm::vec3 lightpos = m_light->getPos();
  glm::vec3 rot =  glm::rotateZ(lightpos, 0.25f * deltaTime);
  m_light->setPos(rot);

  //m_light->setIntensity(rot.y / 40.f);

  //if (m_light->getPos().y < 0) m_light->setIntensity(0.f);

  //m_lightView = glm::lookAt(m_light->getPos(),
  //  glm::vec3(0.0f, 0.0f, 0.0f),
  //  glm::vec3(0.0f, 1.0f, 0.0f));


  //m_lightSpaceMatrix = m_lightProjection * m_lightView;

}

void TestShadowLayer::onRender()
{

  m_lightView = glm::lookAt(m_light->getPos(),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f));


  m_lightSpaceMatrix = m_lightProjection * m_lightView;

  //1st renderpass for shadow map
  m_depthBuffer->bind();
  glViewport(0, 0, 1024, 1024);

	m_depthBuffer->clearDepth();
  ((graphics::SimpleRenderer3D*)m_renderer)->beginShadowPass(m_shadowShader, m_lightSpaceMatrix, m_renderables);

  for (int i = 0; i < m_renderables.size(); i++) {
    m_renderer->submit(m_renderables[i]);
  }

  m_renderer->flush();
  m_depthBuffer->unbind();

  m_renderer->end();


  //2nd renderpass
  glViewport(0, 0, Application::get().getWindow().getWidth(), Application::get().getWindow().getHeight());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glClear(GL_COLOR_BUFFER_BIT);
  
	m_tex2D->bind(0);
	m_texDepth->bind(1);

  m_renderer->begin(m_shader, m_camera, m_lights, m_lightSpaceMatrix);

 
  for (int i = 0; i < m_renderables.size(); i++) {
    m_renderer->submit(m_renderables[i]);
  }

  m_renderer->flush();
  m_renderer->end();

}

void TestShadowLayer::onEvent(Event& e) {
  King::EventDispatcher dispatcher(e);
  dispatcher.dispatch<King::MouseMoved>(BIND_FN(onMouseMoved));
  dispatcher.dispatch<King::KeyPressedEvent>(BIND_FN(onKeyPressed));
  dispatcher.dispatch<King::KeyReleasedEvent>(BIND_FN(onKeyReleased));
  dispatcher.dispatch<King::MouseButtonPressed>(BIND_FN(onMousePressed));
  dispatcher.dispatch<King::MouseButtonReleased>(BIND_FN(onMouseReleased));
}

bool TestShadowLayer::onMousePressed(King::MouseButtonPressed e) {
  if (e.getKeyCode() == GLFW_MOUSE_BUTTON_2) {
    Application::get().getWindow().disableCursor();
    camMode = true;
  }
  return true;
}

bool TestShadowLayer::onMouseReleased(King::MouseButtonReleased e) {
  if (e.getKeyCode() == GLFW_MOUSE_BUTTON_2) {
    Application::get().getWindow().enableCursor();
    camMode = false;
  }
  return true;
}

bool TestShadowLayer::onMouseMoved(King::MouseMoved e) {
   if (camMode) {
     float xOffset = m_windowCenter.first - Input::getMouseX();
     float yOffset = m_windowCenter.second - Input::getMouseY();
     m_camera->setYaw(m_camera->getYaw() - xOffset * m_mousespeed);
     m_camera->setPitch(m_camera->getPitch() + yOffset * m_mousespeed);
   }
  return true;
}

bool TestShadowLayer::onKeyPressed(King::KeyPressedEvent e)
{
  if (e.getRepeatCount() == 0) {
    if (e.getKeyCode() == GLFW_KEY_D) {
      m_camVelocity.x += camspeed;
    }

    if (e.getKeyCode() == GLFW_KEY_A) {
      m_camVelocity.x -= camspeed;
    }

    if (e.getKeyCode() == GLFW_KEY_W) {
      m_camVelocity.z += camspeed;
    }

    if (e.getKeyCode() == GLFW_KEY_S) {
      m_camVelocity.z -= camspeed;
    }

    if (e.getKeyCode() == GLFW_KEY_SPACE) {
      m_camVelocity.y += camspeed;
    }

    if (e.getKeyCode() == GLFW_KEY_C) {
      m_camVelocity.y -= camspeed;
    }
  }
 
  return true;
}

bool TestShadowLayer::onKeyReleased(King::KeyReleasedEvent e) {

  switch (e.getKeyCode()) {
  case GLFW_KEY_W:
    m_camVelocity.z -= camspeed;
    return false;
  case GLFW_KEY_S:
    m_camVelocity.z += camspeed;
    return false;
  case GLFW_KEY_A:
    m_camVelocity.x += camspeed;
    return false;
  case GLFW_KEY_D:
    m_camVelocity.x -= camspeed;
    return false;
  case GLFW_KEY_C:
    m_camVelocity.y += camspeed;
    return false;
  case GLFW_KEY_SPACE:
    m_camVelocity.y -= camspeed;
    return false;
  }
  return true;
}

void TestShadowLayer::onImGuiRender()
{
  ImGui::Begin("Light");
  ImGui::Text("Direction: %.1f x %.1f y %1.f z", m_light->getPos().x, m_light->getPos().y, m_light->getPos().z);
  ImGui::End();

  ImGui::Begin("Test");
  //ImGui::Text("FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  //ImGui::Text("Light Position: %.1f x %.1f y %1.f z", m_lightSphere->getPos().x, m_lightSphere->getPos().y, m_lightSphere->getPos().z);
  ImGui::ColorEdit3("light color", (float*)&m_light->getColor());
  ImGui::SliderFloat("light intensity", (float*)&m_light->getIntensity(), 0.f, 1.f, "%.3f");
  ImGui::ColorEdit3("object diffuse", (float*)&m_renderable->getMaterial().diffuse);
  ImGui::ColorEdit3("object specular", (float*)&m_renderable->getMaterial().specular);
  ImGui::InputFloat("object shininess", (float*)&m_renderable->getMaterial().shininess);


  for (auto& integrator : std::filesystem::directory_iterator("D:/dev/King/Sandbox/res/models")) {
    std::string string = integrator.path().filename().string();
    if (ImGui::Button(string.c_str())) {
      m_renderable->loadModel("res/models/" + string);
    };

  }

  ImGui::End();

  

  ImGui::Begin("FPS");
  ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("%.3f mousespeed", m_mousespeed);
  ImGui::End();

}
