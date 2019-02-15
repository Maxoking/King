//Always include precompiled header first
#include "kngpch.h"

#include "Application.h"
#include "utils/glmutils.h"
#include "utils/fileutils.h"
#include "Graphics/Shader.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/Buffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Renderable2D.h"
#include "Graphics/SimpleRenderer.h"
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



    /*graphics::Shader shader("C:/dev/King/King/src/King/Graphics/Shaders/BasicShader.vert",
      "C:/dev/King/King/src/King/Graphics/Shaders/BasicShader.frag");*/

	//graphics::Renderable2D sprite1(glm::vec3(5, 5, 0), glm::vec2(3.f), shader);

 //   glm::mat4 viewMatrix(1.f);
 //   glm::mat4 projectionMatrix = glm::ortho(0.f, 16.f, 0.f, 9.f, 0.f, 1.f);
	//glm::mat4 modelMatrix1(glm::translate(glm::mat4(1.f), glm::vec3(0,0,0)));

	//glm::mat4 modelMatrix2(glm::translate(glm::mat4(1.f), glm::vec3(-2, -4, 0)));
 //   //glm::mat4 projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f);
 //  
 //   shader.bind();

	//graphics::SimpleRenderer renderer;

 //   glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "view_mat"), 1, GL_FALSE, &viewMatrix[0][0]);
    
    while (m_running) {

	  //shader.setUniform2f("light_pos", { m_mouseX, m_mouseY });

	  /*shader.setUniformMat4("proj_mat", projectionMatrix);*/
      glClearColor(0, 1, 0.4f, 1);
      
      glClear(GL_COLOR_BUFFER_BIT);

	 /* renderer.submit(&sprite1);
	  renderer.flush();*/


      for (Layer* layer : m_stack) {
        layer->onUpdate();
      }

	  for (Layer* layer : m_stack) {
		  layer->onRender();
	  }


      m_window->onUpdate();
    };
  }
}
