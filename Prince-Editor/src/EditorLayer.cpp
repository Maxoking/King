#include "EditorLayer.h"
#include "King/utils/ImageLoader.h"
#include <filesystem>


#define BIND_FN(x) std::bind(&EditorLayer::x, this, std::placeholders::_1)

EditorLayer::EditorLayer() {

	m_renderer = new graphics::SimpleRenderer3D();
	m_camera = new graphics::Camera(glm::vec3(0.f, 1.5f, 5.f),
		70.f,
		King::Application::get().getApectRatio(),
		0.01f,
		1000.f);


	m_shader = new graphics::Shader("D:/dev/King/King/src/King/Graphics/Shaders/TestShader2.vert",
		"D:/dev/King/King/src/King/Graphics/Shaders/TestShader2.frag");

	m_lightShader = new graphics::Shader("C:/dev/King/King/src/King/Graphics/Shaders/lightShader.vert",
		"D:/dev/King/King/src/King/Graphics/Shaders/lightShader.frag");

	m_shadowShader = new graphics::Shader("C:/dev/King/King/src/King/Graphics/Shaders/simpleShadowShader.vert",
		"D:/dev/King/King/src/King/Graphics/Shaders/simpleShadowShader.frag");


	m_tex2D = new graphics::Texture2D("res/textures/container.jpg");


	m_camVelocity = glm::vec3(0.f);
	m_camSpeedForward = 0.f;
	m_camSpeedRight = 0.f;
	m_sensitivity = 100.f;
	m_windowCenter.first = (float)(Application::get().getWindow().getWidth()) / 2.f;
	m_windowCenter.second = (float)(Application::get().getWindow().getHeight()) / 2.f;


	m_light = new graphics::DirectionalLight();
	m_light->setPos(glm::vec3(3.f, 6.5f, 0.f));
	m_light->setIntensity(0.7f);
	m_lights.push_back(m_light);

	//graphics::PointLight* pl = new graphics::PointLight();
	//pl->setPos(glm::vec3(0.f, 5.f, 0.f));
	//pl->setIntensity(0.5f);
	//m_lights.push_back(pl);


	m_renderable = new graphics::Renderable(glm::vec3(0.f, 2.f, -2.f));
	m_renderable->loadModel("res/models/smoothsphere.obj");
	m_renderable->getMaterial().diffuse = glm::vec3(0.f, 0.7f, 0.1f);
	m_renderable->getMaterial().specular = glm::vec3(1.f);
	m_renderable->getMaterial().shininess = 32.f;
	m_renderables.push_back(m_renderable);


	m_floor = new graphics::Renderable(glm::vec3(0.f));
	m_floor->loadModel("res/models/PlaneWithUV.obj");
	m_floor->getMaterial().diffuse = glm::vec3(0.3f, 0.3f, .3f);
	m_floor->getMaterial().specular = glm::vec3(1.f);
	m_floor->getMaterial().shininess = 16.f;
	m_floor->getMaterial().texture = graphics::Texture2D("res/textures/checkerboard.jpg");
	m_renderables.push_back(m_floor);

	m_lastTime = Application::getTime();
	camMode = false;


	graphics::AttachmentSpecification aSpecColor(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	graphics::AttachmentSpecification aSpecDepth(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8);
	graphics::FramebufferSpecification fSpec({ aSpecColor }, aSpecDepth, 1280, 720);
	m_frameBuffer = new graphics::FrameBuffer(fSpec);


	graphics::AttachmentSpecification shadowMapSpec(GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_FLOAT);
	graphics::FramebufferSpecification fSpecShadowBuffer({}, shadowMapSpec, 4096, 4096);
	m_shadowMapBuffer = new graphics::FrameBuffer(fSpecShadowBuffer);
	m_shadowMapBuffer->bind();
	glDrawBuffer(GL_NONE); // No color buffer is drawn to.

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		KING_ERROR("FRAMEBUFFER NOT COMPLETE");

	m_shadowMapBuffer->unbind();

	float near_plane = 1.0f, far_plane = 100.f;
	m_lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane,
		far_plane);
}

void EditorLayer::onAttach() {

}


void EditorLayer::onUpdate() {

	double currentTime = Application::getTime();
	float deltaTime = float(currentTime - m_lastTime);
	m_lastTime = currentTime;



	if (camMode) {
		Application::get().getWindow().setMousePos(m_windowCenter.first, m_windowCenter.second);
		m_mousespeed = m_sensitivity * deltaTime;
	}



	glm::vec3 forwardVec = glm::normalize(m_camera->getDir());
	glm::vec3 rightVec = glm::normalize(glm::cross(m_camera->getDir(), m_camera->getUp()));
	m_camera->setPos(m_camera->getPos() + rightVec * m_camVelocity.x * deltaTime);
	m_camera->setPos(m_camera->getPos() + forwardVec * m_camVelocity.z * deltaTime);
	m_camera->setPos(m_camera->getPos() + m_camera->getUp() * m_camVelocity.y * deltaTime);
	m_camera->updateCameraMatrices();

}

void EditorLayer::onRender()
{

	m_lightView = glm::lookAt(m_light->getPos(),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));


	m_lightSpaceMatrix = m_lightProjection * m_lightView;

	//1st renderpass for shadow map
	m_shadowMapBuffer->bind();
	glViewport(0, 0, 4096, 4096);
	m_shadowMapBuffer->clearDepth();
	((graphics::SimpleRenderer3D*)m_renderer)->beginShadowPass(m_shadowShader, m_lightSpaceMatrix, m_renderables);

	for (int i = 0; i < m_renderables.size(); i++) {
		m_renderer->submit(m_renderables[i]);
	}

	m_renderer->flush();
	m_shadowMapBuffer->unbind();
	m_renderer->end();


	//2nd renderpass
	m_frameBuffer->bind();
	glViewport(0, 0, m_viewPortSize[0], m_viewPortSize[1]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shadowMapBuffer->bindDepthAttachment(1);
	m_renderer->begin(m_shader, m_camera, m_lights, m_lightSpaceMatrix);


	for (int i = 0; i < m_renderables.size(); i++) {
		m_renderer->submit(m_renderables[i]);
	}


	m_renderer->flush();
	m_frameBuffer->unbind();
	m_renderer->end();
}

void EditorLayer::onEvent(Event& e) {
	King::EventDispatcher dispatcher(e);
	dispatcher.dispatch<King::MouseMoved>(BIND_FN(onMouseMoved));
	dispatcher.dispatch<King::KeyPressedEvent>(BIND_FN(onKeyPressed));
	dispatcher.dispatch<King::KeyReleasedEvent>(BIND_FN(onKeyReleased));
	dispatcher.dispatch<King::MouseButtonPressed>(BIND_FN(onMousePressed));
	dispatcher.dispatch<King::MouseButtonReleased>(BIND_FN(onMouseReleased));
}

bool EditorLayer::onMousePressed(King::MouseButtonPressed e) {
	if (e.getKeyCode() == GLFW_MOUSE_BUTTON_2) {
		Application::get().getWindow().disableCursor();
		camMode = true;
	}
	return true;
}

bool EditorLayer::onMouseReleased(King::MouseButtonReleased e) {
	if (e.getKeyCode() == GLFW_MOUSE_BUTTON_2) {
		Application::get().getWindow().enableCursor();
		camMode = false;
	}
	return true;
}

bool EditorLayer::onMouseMoved(King::MouseMoved e) {
	if (camMode) {
		float xOffset = m_windowCenter.first - Input::getMouseX();
		float yOffset = m_windowCenter.second - Input::getMouseY();
		m_camera->setYaw(m_camera->getYaw() - xOffset * m_mousespeed);
		m_camera->setPitch(m_camera->getPitch() + yOffset * m_mousespeed);
	}
	return true;
}

bool EditorLayer::onKeyPressed(King::KeyPressedEvent e)
{
	if (e.getRepeatCount() == 0) {
		if (e.getKeyCode() == GLFW_KEY_D) {
			m_camVelocity.x += camspeed;
		}

		if (e.getKeyCode() == GLFW_KEY_A) {
			m_camVelocity.x -= camspeed;
		}

		if (e.getKeyCode() == GLFW_KEY_W) {
			m_camVelocity.z += camspeed;
		}

		if (e.getKeyCode() == GLFW_KEY_S) {
			m_camVelocity.z -= camspeed;
		}

		if (e.getKeyCode() == GLFW_KEY_SPACE) {
			m_camVelocity.y += camspeed;
		}

		if (e.getKeyCode() == GLFW_KEY_C) {
			m_camVelocity.y -= camspeed;
		}
	}

	return true;
}

bool EditorLayer::onKeyReleased(King::KeyReleasedEvent e) {

	switch (e.getKeyCode()) {
	case GLFW_KEY_W:
		m_camVelocity.z -= camspeed;
		return false;
	case GLFW_KEY_S:
		m_camVelocity.z += camspeed;
		return false;
	case GLFW_KEY_A:
		m_camVelocity.x += camspeed;
		return false;
	case GLFW_KEY_D:
		m_camVelocity.x -= camspeed;
		return false;
	case GLFW_KEY_C:
		m_camVelocity.y += camspeed;
		return false;
	case GLFW_KEY_SPACE:
		m_camVelocity.y -= camspeed;
		return false;
	}
	return true;
}

void EditorLayer::onImGuiRender()
{
	static bool p_open = true;
	static bool opt_fullscreen_persistant = true;
	static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
	bool opt_fullscreen = opt_fullscreen_persistant;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &p_open, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Dockspace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows, 
			// which we can't undo at the moment without finer window depth/z control.
			//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

			if (ImGui::MenuItem("Exit")) KING_CORE_INFO("Files Menu");
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}


	ImGui::Begin("Settings");
	ImGui::Text("FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::SliderFloat("light intensity", (float*)&m_light->getIntensity(), 0.f, 1.f, "%.3f");
	ImGui::SliderFloat3("light dir", (float*)&m_light->getPos(), -10.f, 10.f);
	ImGui::Separator();
	ImGui::SliderFloat3("object pos", (float*)&m_renderable->getPos(), -10.f, 10.f);
	ImGui::ColorEdit3("object diffuse", (float*)&m_renderable->getMaterial().diffuse);
	ImGui::ColorEdit3("object specular", (float*)&m_renderable->getMaterial().specular);
	ImGui::SliderFloat("object shininess", (float*)&m_renderable->getMaterial().shininess, 1.f, 512.f, "%.3f", 2.f);

	ImGui::Spacing();
	if (ImGui::CollapsingHeader("Meshes"))
	{
		for (auto& integrator : std::filesystem::directory_iterator("D:/dev/King/Prince-Editor/res/models")) {
			std::string string = integrator.path().filename().string();
			if (ImGui::Button(string.c_str())) {
				m_renderable->loadModel("res/models/" + string);
			};
		}
	}
	
	ImGui::End();

	ImGui::Begin("Viewport");
	ImVec2 viewPortSize = ImGui::GetContentRegionAvail();
	if (m_viewPortSize.x != viewPortSize.x || m_viewPortSize.y != viewPortSize.y) {
		m_frameBuffer->getSpecification().m_width = viewPortSize[0];
		m_frameBuffer->getSpecification().m_height = viewPortSize[1];
		m_frameBuffer->invalidate();
		glm::mat4 perspective = glm::perspective(m_camera->getFov(), viewPortSize[0] / viewPortSize[1], m_camera->getZNear(), m_camera->getZFar());
		m_camera->setProjectionMatrix(perspective);
		m_viewPortSize = viewPortSize;
	}
	ImGui::Image((void*)m_frameBuffer->getColorAttachment(), viewPortSize, {0, 1}, {1, 0});
	ImGui::End();

	ImGui::End();

}
