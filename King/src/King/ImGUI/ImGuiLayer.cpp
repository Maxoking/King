#include "kngpch.h"
#include "ImGuiLayer.h"

#include "King/Application.h"

#include "ImGuiExamples/ImguiRenderer.h"
#include "GLFW/glfw3.h"


namespace King {

  ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
  {
  }

  ImGuiLayer::~ImGuiLayer()
  {
  }

  void ImGuiLayer::onAttach()
  {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    ImGui_ImplOpenGL3_Init("#version 410");
  }

  void ImGuiLayer::onDetach()
  {
  }


  void ImGuiLayer::onEvent(Event & e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<MouseButtonPressed>(KING_BIND_FN(ImGuiLayer::onMousePressed));
    dispatcher.dispatch<MouseButtonReleased>(KING_BIND_FN(ImGuiLayer::onMouseReleased));
    dispatcher.dispatch<MouseMoved>(KING_BIND_FN(ImGuiLayer::onMouseMoved));
    dispatcher.dispatch<KeyPressedEvent>(KING_BIND_FN(ImGuiLayer::onKeyPressed));
    dispatcher.dispatch<KeyReleasedEvent>(KING_BIND_FN(ImGuiLayer::onKeyReleased));
  }

  void ImGuiLayer::onUpdate()
  {
    Application& app = Application::get();
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    float time = (float)glfwGetTime();
    io.DeltaTime = m_time > 0.0 ? (time - m_time) : (1.0f / 60.0f);
    m_time = time;

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  bool ImGuiLayer::onMousePressed(MouseButtonPressed & e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.getKeyCode()] = true;
    return false;
  }

  bool ImGuiLayer::onMouseReleased(MouseButtonReleased & e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.getKeyCode()] = false;
    return false;
  }

  bool ImGuiLayer::onMouseMoved(MouseMoved & e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(e.getMouseX(), e.getMouseY());
    return false;
  }

  bool ImGuiLayer::onKeyPressed(KeyPressedEvent & e)
  {
    return false;
  }

  bool ImGuiLayer::onKeyReleased(KeyReleasedEvent & e)
  {
    return false;
  }
}
