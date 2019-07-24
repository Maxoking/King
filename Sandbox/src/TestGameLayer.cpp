
#include "TestGameLayer.h"
#include <filesystem>


#define BIND_FN(x) std::bind(&TestGameLayer::x, this, std::placeholders::_1)

TestGameLayer::TestGameLayer() {

  m_renderer = new graphics::SimpleRenderer3D();
  m_camera = new graphics::Camera(glm::vec3(0.f, 0.75f, 5.f),
    70.f,
    King::Application::get().getApectRatio(),
    0.01f,
    1000.f);

  
  m_shader = new graphics::Shader("C:/dev/King/King/src/King/Graphics/Shaders/testShader.vert",
    "C:/dev/King/King/src/King/Graphics/Shaders/testShader.frag");

  m_lightShader = new graphics::Shader("C:/dev/King/King/src/King/Graphics/Shaders/lightShader.vert",
    "C:/dev/King/King/src/King/Graphics/Shaders/lightShader.frag");

  m_shadowShader = new graphics::Shader("C:/dev/King/King/src/King/Graphics/Shaders/simpleShadowShader.vert",
    "C:/dev/King/King/src/King/Graphics/Shaders/simpleShadowShader.frag");


  m_camVelocity = glm::vec3(0.f);
  m_camSpeedForward = 0.f;
  m_camSpeedRight = 0.f;
  m_sensitivity = 0.25f;
  m_windowCenter.first = (float)(Application::get().getWindow().getWidth()) / 2.f;
  m_windowCenter.second = (float)(Application::get().getWindow().getHeight()) / 2.f;


  m_light = new graphics::DirectionalLight();
  m_light->setPos(glm::vec3(0.f, 1.f, 0.f));
  m_light->setIntensity(0.3f);

  m_lights.push_back(m_light);

  graphics::PointLight* pl = new graphics::PointLight();
  pl->setPos(glm::vec3(-5.f, 2.5f, 0.5f));
  m_lights.push_back(pl);



  graphics::Renderable* testLight = new graphics::Renderable(pl->getPos());
  testLight->loadModel("res/models/Cube.obj");
  testLight->setColor(glm::vec3(0.7f, 0.4f, 0.3f));
  testLight->getMaterial().diffuse = glm::vec3(0.7f, 0.2f, 0.5f);
  testLight->getMaterial().specular = glm::vec3(0.7f, 0.4f, 0.3f);
  testLight->getMaterial().shininess = 32.f;
  m_renderables.push_back(testLight);

  m_renderable = new graphics::Renderable(pl->getPos() + glm::vec3(0.f, 5.f, 0.f));
  m_renderable->loadModel("res/models/tesst.obj");
  m_renderable->setColor(glm::vec3(0.7f, 0.4f, 0.3f));
  m_renderable->getMaterial().diffuse = glm::vec3(0.7f, 0.4f, 0.3f);
  m_renderable->getMaterial().specular = glm::vec3(0.7f, 0.4f, 0.3f);
  m_renderable->getMaterial().shininess = 32.f;
  m_renderables.push_back(m_renderable);

  m_lightSphere = new graphics::Renderable(glm::vec3(m_light->getPos()));
  m_lightSphere->loadModel("res/models/Sphere.obj");
  m_lightSphere->setColor(glm::vec3(0.2f, 0.7f, 0.3f));

  m_floor = new graphics::Renderable(glm::vec3(0.f));
  m_floor->loadModel("res/models/plane.obj");
  //m_floor->setColor(glm::vec3(0.45f, 0.4f, 0.7f)); 
  m_floor->getMaterial().diffuse = glm::vec3(0.45f, 0.4f, 0.7f);
  m_floor->getMaterial().specular = glm::vec3(0.45f, 0.4f, 0.7f);
  m_floor->getMaterial().shininess = 16.f;
  m_renderables.push_back(m_floor);


  m_lastTime = Application::getTime();
  camMode = false;

  //std::filesystem::directory_entry dir = std::filesystem::directory_entry();
  //dir.path = "C:\dev\King\Sandbox\res\models";

  glGenTextures(1, &m_shadowMap);
  glBindTexture(GL_TEXTURE_2D, m_shadowMap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
    1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  m_depthBuffer = new graphics::FrameBuffer();
  m_depthBuffer->bind();
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap, 0);
  glDrawBuffer(GL_NONE);
  glDrawBuffer(GL_NONE);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    KING_TRACE("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

  m_depthBuffer->unbind();


  float near_plane = 1.0f, far_plane = 7.5f;
  m_lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane,
    far_plane);
 
  
}

void TestGameLayer::onAttach() {
  //m_vaos.push_back(m_VertexArray);
  std::vector<graphics::Mesh> vec = m_renderable->getModel()->getMeshes();
  m_vaos.push_back(vec[0].getVao());

}


void TestGameLayer::onUpdate() {

  double currentTime = Application::getTime();
  float deltaTime = float(currentTime - m_lastTime);
  m_lastTime = currentTime;

  if (Input::isKeyPressed(GLFW_KEY_I)) {
    m_lightSphere->setPos(m_lightSphere->getPos() - glm::vec3(0, 0.f, 2.f) * deltaTime);
  }

  if (Input::isKeyPressed(GLFW_KEY_K)) {
    m_lightSphere->setPos(m_lightSphere->getPos() + glm::vec3(0, 0.f, 2.f) * deltaTime);
  }
  if (Input::isKeyPressed(GLFW_KEY_J)) {
    m_lightSphere->setPos(m_lightSphere->getPos() - glm::vec3(2.f, 0.f, 0) * deltaTime);
  }
  if (Input::isKeyPressed(GLFW_KEY_L)) {
    m_lightSphere->setPos(m_lightSphere->getPos() + glm::vec3(2.f, 0.f, 0) * deltaTime);
  }
  if (Input::isKeyPressed(GLFW_KEY_U)) {
    m_lightSphere->setPos(m_lightSphere->getPos() + glm::vec3(0.f, 2.f, 0.f) * deltaTime);
  }
  if (Input::isKeyPressed(GLFW_KEY_H)) {
    m_lightSphere->setPos(m_lightSphere->getPos() - glm::vec3(0.f, 2.f, 0.f) * deltaTime);
  }

  m_light->setPos(m_lightSphere->getPos());

  if (camMode) {
    Application::get().getWindow().setMousePos(m_windowCenter.first, m_windowCenter.second);
  }
  


  glm::vec3 forwardVec = glm::normalize(m_camera->getDir());
  glm::vec3 rightVec = glm::normalize(glm::cross(m_camera->getDir(), m_camera->getUp()));
  m_camera->setPos(m_camera->getPos() + rightVec * m_camVelocity.x);
  m_camera->setPos(m_camera->getPos() + forwardVec * m_camVelocity.z);
  m_camera->setPos(m_camera->getPos() + m_camera->getUp() * m_camVelocity.y);

  m_camera->updateCameraMatrices();
}

void TestGameLayer::onRender()
{
  //1st renderpass for shadow map
  m_lightView = glm::lookAt(m_light->getPos(),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f));

  m_lightSpaceMatrix = m_lightProjection * m_lightView;

  //m_shadowShader->bind();
  //m_shadowShader->setUniformMat4("light_space_mat", m_lightSpaceMatrix);


 
  glViewport(0, 0, 1024, 1024);
  m_depthBuffer->bind();
  glClear(GL_DEPTH_BUFFER_BIT);


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
  m_shader->setUniformMat4("light_space_mat", m_lightSpaceMatrix);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_shadowMap);
  m_shader->setUniform1i("shadow_map", 0);
  m_renderer->begin(m_shader, m_camera, m_lights, m_lightSpaceMatrix);

    
    


  for (int i = 0; i < m_renderables.size(); i++) {
    m_renderer->submit(m_renderables[i]);
  }

 
  m_renderer->flush();
  m_renderer->end();

}

void TestGameLayer::onEvent(Event& e) {
  King::EventDispatcher dispatcher(e);
  dispatcher.dispatch<King::MouseMoved>(BIND_FN(onMouseMoved));
  dispatcher.dispatch<King::KeyPressedEvent>(BIND_FN(onKeyPressed));
  dispatcher.dispatch<King::KeyReleasedEvent>(BIND_FN(onKeyReleased));
  dispatcher.dispatch<King::MouseButtonPressed>(BIND_FN(onMousePressed));
  dispatcher.dispatch<King::MouseButtonReleased>(BIND_FN(onMouseReleased));
}

bool TestGameLayer::onMousePressed(King::MouseButtonPressed e) {
  if (e.getKeyCode() == GLFW_MOUSE_BUTTON_2) {
    Application::get().getWindow().disableCursor();
    camMode = true;
  }
  return true;
}

bool TestGameLayer::onMouseReleased(King::MouseButtonReleased e) {
  if (e.getKeyCode() == GLFW_MOUSE_BUTTON_2) {
    Application::get().getWindow().enableCursor();
    camMode = false;
  }
  return true;
}

bool TestGameLayer::onMouseMoved(King::MouseMoved e) {
   if (camMode) {
     float xOffset = m_windowCenter.first - Input::getMouseX();
     float yOffset = m_windowCenter.second - Input::getMouseY();
     m_camera->setYaw(m_camera->getYaw() - xOffset * m_sensitivity);
     m_camera->setPitch(m_camera->getPitch() + yOffset * m_sensitivity);
   }
  return true;
}

bool TestGameLayer::onKeyPressed(King::KeyPressedEvent e)
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

bool TestGameLayer::onKeyReleased(King::KeyReleasedEvent e) {

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

void TestGameLayer::onImGuiRender()
{
  ImGui::Begin("Test");
  ImGui::Text("FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("Light Position: %.1f x %.1f y %1.f z", m_lightSphere->getPos().x, m_lightSphere->getPos().y, m_lightSphere->getPos().z);
  ImGui::ColorEdit3("light color", (float*)&m_light->getColor());
  ImGui::SliderFloat("light intensity", (float*)&m_light->getIntensity(), 0.f, 1.f, "%.3f");
  ImGui::ColorEdit3("object diffuse", (float*)&m_renderable->getMaterial().diffuse);
  ImGui::ColorEdit3("object specular", (float*)&m_renderable->getMaterial().specular);
  ImGui::InputFloat("object shininess", (float*)&m_renderable->getMaterial().shininess);


  for (auto& integrator : std::filesystem::directory_iterator("C:/dev/King/Sandbox/res/models")) {
    std::string string = integrator.path().filename().string();
    if (ImGui::Button(string.c_str())) {
      m_renderable->loadModel("res/models/" + string);
    };
  
  }

  ImGui::End();
}
