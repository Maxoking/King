#include "kngpch.h"
#include "Window.h"

#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

#include <glad/glad.h>



namespace King {

  Window * Window::createWindow(const WindowData & props)
  {
    return new Window(props);
  }

  Window::Window(WindowData data)
  {
    init(data);
  }

  void Window::init(WindowData data)
  {
    m_data.title = data.title;
    m_data.height = data.height;
    m_data.width = data.width;

    if (!s_glfwInitialized) {
      int success = glfwInit();
      if (success) {
        KING_CORE_INFO("GLFW initialized");
      }
      else {
        KING_CORE_WARN("GLFW not initialized");
      }
      s_glfwInitialized = true;
    }

    KING_CORE_INFO("Creating Window {0}({1},{2})", data.title, data.width, data.height);

    m_glfwWindow = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_glfwWindow);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (status) {
      KING_CORE_INFO("Glad initialized");
    }
    else {
      KING_CORE_WARN("Glad not initialized");
    }
    glfwSetWindowUserPointer(m_glfwWindow, &m_data);

    //GLFW CALLBACKS
    glfwSetWindowCloseCallback(m_glfwWindow, [](GLFWwindow* window) {
      WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent e;
        data.EventCallBack(e);
    }); //Lambda

    glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow* window, int width, int height) {
      WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
      WindowResizeEvent e(width, height);
      data.EventCallBack(e);
    }); //Lambda


    glfwSetKeyCallback(m_glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);

      switch (action) {
        case GLFW_PRESS:
        {
          KeyPressedEvent e(key, 0);
          data.EventCallBack(e);
          break;
        }
        case GLFW_REPEAT:
        {
          KeyPressedEvent e(key, 1);
          data.EventCallBack(e);
          break;
        }         
        case GLFW_RELEASE:
        {
          KeyReleasedEvent e(key);
          data.EventCallBack(e);
          break;
        }
      }
      
    }); //Lambda

    glfwSetMouseButtonCallback(m_glfwWindow, [](GLFWwindow* window, int button, int action, int mods)
    {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

      switch (action)
      {
      case GLFW_PRESS:
      {
        MouseButtonPressed event(button);
        data.EventCallBack(event);
        break;
      }
      case GLFW_RELEASE:
      {
        MouseButtonReleased event(button);
        data.EventCallBack(event);
        break;
      }
      }
    });

    //glfwSetScrollCallback(m_glfwWindow, [](GLFWwindow* window, double xOffset, double yOffset)
    //{
    //  WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    //  MouseScrolled event((float)xOffset, (float)yOffset);
    //  data.EventCallBack(event);
    //}); //LAMBDA

    glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow* window, double xPos, double yPos)
    {
      WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

      MouseMoved event((float)xPos, (float)yPos);
      data.EventCallBack(event);
    }); //LAMBDA
  }

  void Window::onUpdate()
  {
    glfwPollEvents();
    glfwSwapBuffers(m_glfwWindow);
  }

  void Window::onEvent(Event & e)
  {
  }


  void Window::shutdown()
  {
    glfwDestroyWindow(m_glfwWindow);
  }

  Window::~Window()
  {
    shutdown();
  }

}
