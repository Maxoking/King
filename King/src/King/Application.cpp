//Always include precompiled header first
#include "kngpch.h"

#include "Application.h"
#include "utils/glmutils.h"
#include "utils/fileutils.h"
#include "Graphics/Shader.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/Buffer.h"
#include "glad/glad.h"

namespace King {

#define BIND_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

  //s_instance muss deklariert werden
  Application* Application::s_instance = nullptr;

  Application::Application()
  {
    s_instance = this;
    m_window = std::unique_ptr<Window>(Window::createWindow());
    m_window->setEventCallBack(BIND_FN(onEvent));
  }

  void Application::pushLayer(Layer * layer)
  {
    m_stack.pushLayer(layer);
    layer->onAttach();
  }

  void Application::pushOverlay(Layer * layer)
  {
    m_stack.pushOverlay(layer);
    layer->onAttach();
  }

  void Application::onEvent(Event & e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(BIND_FN(onWindowClose));
    dispatcher.dispatch<MouseMoved>(BIND_FN(onMouseMoved));
    //KING_CORE_TRACE(e);

    for (auto it = m_stack.end(); it != m_stack.begin();) {
      (*--it)->onEvent(e);
      if (e.m_handled)
        break;
    } 
  }
  
  bool Application::onMouseMoved(MouseMoved& e)
  {
    m_mouseX = e.getMouseX() / 100.f;
    m_mouseY = e.getMouseY() / 100.f;
    KING_CORE_TRACE(e);
    return true;
  }

  bool Application::onWindowClose(WindowCloseEvent& e)
  {
    m_running = false;
    return true;
  }

  bool Application::onWindowRezise(WindowResizeEvent & e)
  {
    KING_CORE_TRACE(e);
    return true;
  }


  Application::~Application()
  {
    //delete m_window;
  }

  void Application::run() {


    GLfloat vertices[] =
    {
        4.f,  2.25f,   0,
       12.f,  2.25f,   0,
       12.f,  6.25f,   0,
        4.f,  6.25f,   0,
        4.f,  2.25f,   0,
       12.f,  6.25f,   0
    };

   /* graphics::Buffer* vbo = new graphics::Buffer(vertices, 6 * 3, 3);
    graphics::VertexArray vao;
    vao.addBuffer(vbo, 0);*/

    GLuint vao;
    GLuint vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    graphics::Shader shader("C:/dev/King/King/src/King/Graphics/Shaders/BasicShader.vert",
      "C:/dev/King/King/src/King/Graphics/Shaders/BasicShader.frag");

    glm::mat4 viewMatrix(1.f);
    glm::mat4 projectionMatrix = glm::ortho(0.f, 16.f, 0.f, 9.f, 0.f, 1.f);
    //glm::mat4 projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f);
   
    shader.bind();

    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "view_mat"), 1, GL_FALSE, &viewMatrix[0][0]);
    
    while (m_running) {

      GLuint lightpos = glGetUniformLocation(shader.getID(), "light_pos");
      glUniform2f(lightpos, m_mouseX, m_mouseY);
      glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "proj_mat"), 1, GL_FALSE, &projectionMatrix[0][0]);

      glClearColor(0, 1, 0.4f, 1);
      
      glClear(GL_COLOR_BUFFER_BIT);
       //1st attribute buffer : vertices
      glEnableVertexAttribArray(0);
       //Draw the triangle !
      glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 3 vertices total -> 1 triangle
      glDisableVertexAttribArray(0);

      /*vao.bind();
      vbo->bind();
      */
      for (Layer* layer : m_stack) {
        layer->onUpdate();
      }

      m_window->onUpdate();
    };
  }
}
