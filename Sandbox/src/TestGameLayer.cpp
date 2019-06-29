
#include "TestGameLayer.h"

#define BIND_FN(x) std::bind(&TestGameLayer::x, this, std::placeholders::_1)

TestGameLayer::TestGameLayer() {

  m_renderer = new graphics::SimpleRenderer3D();
  m_camera.reset(new graphics::Camera(glm::vec3(0.f, 0.f, -5.f),
    70.f,
    King::Application::get().getApectRatio(),
    0.01f,
    1000.f));
 

  m_VertexArray.reset(new King::graphics::VertexArray());


  GLfloat vertices[] =
  {
      -0.5, -0.5,  0.5, 0.8f, 0.2f, 0.f, 1.f,
     0.5, -0.5,  0.5, 0.8f, 0.2f, 0.f, 1.f,
     0.5,  0.5,  0.5, 0.8f, 0.2f, 0.f, 1.f,
    -0.5,  0.5,  0.5, 0.8f, 0.2f, 0.f, 1.f,
    // back
    -0.5, -0.5, -0.5, 0.8f, 0.2f, 0.f, 1.f,
     0.5, -0.5, -0.5, 0.8f, 0.2f, 0.f, 1.f,
     0.5,  0.5, -0.5, 0.8f, 0.2f, 0.f, 1.f,
    -0.5,  0.5, -0.5, 0.8f, 0.2f, 0.f, 1.f,

  };

  GLuint indices[] =
  {
    // front
     0, 1, 2,
     2, 3, 0,
     // right
     1, 5, 6,
     6, 2, 1,
     // back
     7, 6, 5,
     5, 4, 7,
     // left
     4, 0, 3,
     3, 7, 4,
     // bottom
     4, 5, 1,
     1, 0, 4,
     // top
     3, 2, 6,
     6, 7, 3

  };


  graphics::BufferLayout layout = {
    {graphics::ShaderDataType::Vec3, "a_position"},
    {graphics::ShaderDataType::Vec4, "a_color"}
  };
  //graphics::Buffer vbo = graphics::Buffer(vertices, sizeof(vertices));
  //vbo.setLayout(layout);
  std::shared_ptr<graphics::Buffer> vbo(new graphics::Buffer(vertices, sizeof(vertices)));
  vbo->setLayout(layout);

  /* graphics::VertexArray vao = graphics::VertexArray();
   vao.addBufferWithLayout(vbo);*/
  m_VertexArray->addBufferWithLayout(vbo);

  //raphics::IndexBuffer ibo = graphics::IndexBuffer(indices, 36);
  std::shared_ptr<graphics::IndexBuffer> ibo(new graphics::IndexBuffer(indices, sizeof(indices) / sizeof(GLuint)));
  //vao.setIBO(ibo);
  m_VertexArray->setIBO(ibo);

  //m_model.reset(new graphics::Model());
  
  m_shader = new graphics::Shader("C:/dev/King/King/src/King/Graphics/Shaders/testShader.vert",
    "C:/dev/King/King/src/King/Graphics/Shaders/testShader.frag");
  m_shader->bind();
  m_shader->setUniformMat4("view_mat", m_camera->getViewMatrix());
  m_shader->setUniformMat4("proj_mat", m_camera->getProjectionMatrix());
  m_shader->unbind();

  m_camVelocity = glm::vec3(0.f);
  m_camSpeedForward = 0.f;
  m_camSpeedRight = 0.f;
  m_sensitivity = 0.5f;
  m_windowCenter.first = (float)(Application::get().getWindow().getWidth()) / 2.f;
  m_windowCenter.second = (float)(Application::get().getWindow().getHeight()) / 2.f;

  m_lastTime = Application::getTime();
  camMode = false;
  //Application::get().getWindow().disableCursor();
  
}

void TestGameLayer::onAttach() {
  m_vaos.push_back(m_VertexArray);
}


void TestGameLayer::onUpdate() {

  double currentTime = Application::getTime();
  float deltaTime = float(currentTime - m_lastTime);

  if (camMode) {
    Application::get().getWindow().setMousePos(m_windowCenter.first, m_windowCenter.second);
  }
  


  glm::vec3 forwardVec = glm::normalize(m_camera->getDir());
  glm::vec3 rightVec = glm::normalize(glm::cross(m_camera->getDir(), m_camera->getUp()));
  m_camera->setPos(m_camera->getPos() + rightVec * m_camVelocity.x);
  m_camera->setPos(m_camera->getPos() + forwardVec * m_camVelocity.z);

  m_camera->updateCameraMatrices();
}

void TestGameLayer::onRender()
{
  m_shader->bind();
  
  m_shader->setUniformMat4("view_mat", m_camera->getViewMatrix());

  for (int i = 0; i < m_vaos.size(); i++) {
    m_renderer->submit(m_vaos[i]);
  }

 
  m_renderer->flush();

  m_shader->unbind();
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
  return false;
}

bool TestGameLayer::onMouseReleased(King::MouseButtonReleased e) {
  if (e.getKeyCode() == GLFW_MOUSE_BUTTON_2) {
    Application::get().getWindow().enableCursor();
    camMode = false;
  }
  return false;
}

bool TestGameLayer::onMouseMoved(King::MouseMoved e) {

   if (camMode) {
     float xOffset = m_windowCenter.first - Input::getMouseX();
     float yOffset = m_windowCenter.second - Input::getMouseY();
     m_camera->setYaw(m_camera->getYaw() - xOffset * m_sensitivity);
     m_camera->setPitch(m_camera->getPitch() - yOffset * m_sensitivity);
   }
  return false;
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
  }
 
  

  return false;
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
  }
  return false;
}
