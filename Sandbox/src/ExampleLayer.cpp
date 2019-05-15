#include "ExampleLayer.h"

#define BIND_FN(x) std::bind(&ExampleLayer::x, this, std::placeholders::_1)

ExampleLayer::ExampleLayer()
	: Layer("Example")
{
	m_shader = new King::graphics::Shader("C:/dev/King/King/src/King/Graphics/Shaders/BasicShader.vert",
		"C:/dev/King/King/src/King/Graphics/Shaders/BasicShader.frag");

	m_projectionMatrix = glm::ortho(0.f, (float)King::Application::get().getWindow().getWidth(), 0.f, (float) King::Application::get().getWindow().getHeight(), 0.f, 1.f);
	m_viewMatrix = glm::mat4(1.f);
	m_shader->bind();
	m_shader->setUniformMat4("proj_mat", m_projectionMatrix);
	m_shader->setUniformMat4("view_mat", m_viewMatrix);
	m_shader->unbind();
	m_renderer = new King::graphics::SimpleRenderer();
}

void ExampleLayer::onRender()
{
	m_shader->bind(); 

	
	m_shader->setUniform2f("light_pos", glm::vec2(m_mouseX, m_mouseY));

	for(int i = 0; i < m_renderables.size(); i++) {
		m_renderer->submit(m_renderables[i]);
	}

	m_renderer->flush();

	m_shader->unbind();
}

void ExampleLayer::onUpdate()
{
	auto[x, y] = King::Input::getMousePos(); //std::pair
	m_mouseX = x;
	m_mouseY = King::Application::get().getWindow().getHeight() - y;


}

void ExampleLayer::onAttach()
{	
}

void ExampleLayer::addSprite(glm::vec3 pos, glm::vec2 size)
{
	King::graphics::Renderable2D* sprite = new King::graphics::Renderable2D(pos, size, m_shader);
	add(sprite);
}

void ExampleLayer::addSpriteAtCursor(glm::vec2 size)
{
	addSprite({ m_mouseX - size.x * 0.5f, m_mouseY - size.y * 0.5f, 0.f }, size);
}

void ExampleLayer::onEvent(King::Event & e)
{
	King::EventDispatcher dispatcher(e);
	dispatcher.dispatch<King::MouseButtonPressed>(BIND_FN(onMouseButtonPressed));
}

bool ExampleLayer::onMouseButtonPressed(King::MouseButtonPressed e)
{
	addSpriteAtCursor(glm::vec2( 100.f ));
	return false;
}


