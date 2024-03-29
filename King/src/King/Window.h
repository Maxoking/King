#pragma once
#include "kngpch.h"

#include "King/Core.h"
#include "Events/Event.h"

#include "GLFW/glfw3.h"


namespace King {
	using EventCallbackFn = std::function<void(Event&)>;

	static bool s_glfwInitialized = false;


	struct WindowData {

		unsigned int width;
		unsigned int height;
		std::string title;

		EventCallbackFn EventCallBack;

		WindowData(const std::string& title = "King Engine", unsigned int width = 1280, unsigned int height = 720) : title(title), width(width), height(height) {}
	};

	class KING_API Window
	{
	public:
		static Window* createWindow(const WindowData& props = WindowData());

		Window(WindowData data);
		~Window();


		void onUpdate();
		void onEvent(Event& e);

		GLFWwindow* getNativeWindow() { return m_glfwWindow; };
		unsigned int getWidth() { return m_data.width; };
		unsigned int getHeight() { return m_data.height; };
		void setEventCallBack(const EventCallbackFn& callback) { m_data.EventCallBack = callback; };
		std::string getTitle() { return m_data.title; };
		void setMousePos(double xPos, double yPos) { glfwSetCursorPos(m_glfwWindow, xPos, yPos); };
		void disableCursor() { glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); };
		void enableCursor() { glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL); };
	private:
		void init(WindowData data);
		void shutdown();

		GLFWwindow* m_glfwWindow;
		WindowData m_data;
	};
}
