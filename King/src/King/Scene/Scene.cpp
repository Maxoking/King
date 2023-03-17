#include "kngpch.h"

#include "Scene.h"
#include <glm/glm.hpp>

namespace King {

	struct TransformComponent {
		glm::mat4 transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent& transformComponent) = default;
		TransformComponent(const glm::mat4& transform) : transform(transform) {}
	};

	Scene::Scene() {
		
	}

	void Scene::onUpdate(double deltaTime) {

	}

	Scene::~Scene() {

	}

}
