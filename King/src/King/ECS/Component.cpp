#include "kngpch.h"
#include "Component.h"

//static uint32_t s_componentID = 0;

namespace King {
	namespace ECS {

		std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>> BaseECSComponent::s_componentTypes;

		uint32_t BaseECSComponent::registerComponentType(ECSComponentCreateFunction createfn,
			ECSComponentFreeFunction freefn, size_t size) {

			uint32_t componentID = s_componentTypes.size();
			s_componentTypes.push_back(std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>(
				createfn, freefn, size));
			return componentID;
		}

	}//namespace ECS end
}//namespace King end