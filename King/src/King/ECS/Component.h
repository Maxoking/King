#pragma once
#include "kngpch.h"
typedef void* EntityHandle;

namespace King {
	namespace ECS {

		struct BaseECSComponent {
			static uint32_t nextID();
			EntityHandle entityID;
		};

		template<typename T>
		struct ECSComponent : public BaseECSComponent {
			static const uint32_t ID;
			static const size_t SIZE;
		};

		template<typename T>
		const uint32_t ECSComponent<T>::ID(BaseECSComponent::nextID());

		template<typename T>
		const size_t ECSComponent<T>::SIZE(sizeof(T));


	}//namespace ECS end
}//namespace King end
