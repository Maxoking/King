#include "kngpch.h"
#include "Input.h"
#include "King/Application.h"

#include <GLFW/glfw3.h>

namespace King {

	Input* Input::s_instance = new Input();

	bool Input::isKeyPressed(int keycode) {
		auto window = Application::get().getWindow().getNativeWindow();

		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::isMouseButtonPressed(int keycode) {
		auto window = Application::get().getWindow().getNativeWindow();

		auto state = glfwGetMouseButton(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> Input::getMousePos() {
		auto window = Application::get().getWindow().getNativeWindow();
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return { (float)x, (float)y };
	}

	float Input::getMouseX() {
		auto window = Application::get().getWindow().getNativeWindow();
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return (float)x;
	}

	float Input::getMouseY() {
		auto window = Application::get().getWindow().getNativeWindow();
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return (float)y;
	}
}