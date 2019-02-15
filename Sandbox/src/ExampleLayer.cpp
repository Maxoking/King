#include "ExampleLayer.h"

ExampleLayer::ExampleLayer()
	: Layer("Example")
{
	m_shader = new King::graphics::Shader("C:/dev/King/King/src/King/Graphics/Shaders/BasicShader.vert",
		"C:/dev/King/King/src/King/Graphics/Shaders/BasicShader.frag");
	m_projectionMatrix = glm::ortho(0.f, 16.f, 0.f, 9.f, 0.f, 1.f);
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
	for(int i = 0; i < m_renderables.size(); i++) {
		m_renderer->submit(m_renderables[i]);
	}

	m_renderer->flush();

	m_shader->unbind();
}

void ExampleLayer::onUpdate()
{

}

void ExampleLayer::onAttach()
{	
	King::graphics::Renderable2D* sprite = new King::graphics::Renderable2D(glm::vec3(5, 5, 0), glm::vec2(3.f), m_shader);
	add(sprite);
}
