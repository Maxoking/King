#pragma once
//#include "entt.hpp"


namespace King {
	class Scene {
	public:
		Scene();
		~Scene();

		void onUpdate(double timeStep);
	private:
		//one entity registry per scene
		//entt::registry m_registry;
	};
}
