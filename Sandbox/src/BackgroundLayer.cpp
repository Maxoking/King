#include "BackgoundLayer.h"

#define BIND_FN(x) std::bind(&BackgroundLayer::x, this, std::placeholders::_1)

BackgroundLayer::BackgroundLayer()
	: Layer("Example")
{
	m_shader = new King::graphics::Shader("C:/dev/King/King/src/King/Graphics/Shaders/BasicShader.vert",
		"C:/dev/King/King/src/King/Graphics/Shaders/BasicShader.frag");

	m_projectionMatrix = glm::ortho(0.f, (float)King::Application::get().getWindow().getWidth(), 0.f, (float)King::Application::get().getWindow().getHeight(), 0.f, 1.f);
	m_viewMatrix = glm::mat4(1.f);
	m_shader->bind();
	m_shader->setUniformMat4("proj_mat", m_projectionMatrix);
	m_shader->setUniformMat4("view_mat", m_viewMatrix);
	m_shader->unbind();
	m_renderer = new King::graphics::SimpleRenderer();
}

void BackgroundLayer::onRender()
{
	m_shader->bind();


	m_shader->setUniform2f("light_pos", glm::vec2(0, 0));

	for (int i = 0; i < m_renderables.size(); i++) {
		m_renderer->submit(m_renderables[i]);
	}

	m_renderer->flush();

	m_shader->unbind();
}

void BackgroundLayer::onUpdate()
{

}

void BackgroundLayer::onAttach()
{
	m_shader->bind();
	m_shader->setUniform4f("base_color", glm::vec4(1.f, 0.f, 0.f, 1.f));
	m_shader->unbind();
	add(new King::graphics::Renderable2D(glm::vec3(0.f), glm::vec2(100.f), m_shader));
}
