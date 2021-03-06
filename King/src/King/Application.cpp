//Always include precompiled header first
#include "kngpch.h"

#include "Application.h"
#include "utils/fileutils.h"
#include "Graphics/Shader.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/Buffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Renderable2D.h"
#include "Graphics/Buffers/BufferLayout.h"
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

    m_imGuiLayer = new ImGuiLayer();
    pushOverlay(m_imGuiLayer);

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
    dispatcher.dispatch<KeyPressedEvent>(BIND_FN(onKeyPressed));

    for (auto it = m_stack.end(); it != m_stack.begin();) {
      (*--it)->onEvent(e);
      if (e.m_handled)
        break;
    } 
  }

  bool Application::onKeyPressed(KeyPressedEvent& e)
  {
    if(e.getKeyCode() == GLFW_KEY_ESCAPE)
      m_running = false;
    return false;
  }
  

  bool Application::onWindowClose(WindowCloseEvent& e)
  {
    m_running = false;
    return true;
  }

  bool Application::onWindowRezise(WindowResizeEvent & e)
  {
    return true;
  }


  Application::~Application()
  {
    //delete m_window;
  }

  void Application::run() {
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glfwSwapInterval(0);

    while (m_running) {


      

      glClearColor(0.7f, 0.3f, 0.4f, 1);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      for (Layer* layer : m_stack) {
        layer->onUpdate();
      }

	    for (Layer* layer : m_stack) {
		    layer->onRender();
	    }

      m_imGuiLayer->begin();
      for (Layer* layer : m_stack) {
        layer->onImGuiRender();
      }
      m_imGuiLayer->end();


      m_window->onUpdate();
    };
  }
}
