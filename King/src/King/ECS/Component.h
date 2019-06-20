#pragma once
//#include "kngpch.h"

#define NULL_ENTITY_HANDLE nullptr

namespace King {
  namespace ECS {

    struct BaseECSComponent;

    typedef void* EntityHandle;
    typedef uint32_t(*ECSComponentCreateFunction) (std::vector<uint8_t>& memory, EntityHandle entity, BaseECSComponent* comp);
    typedef void(*ECSComponentFreeFunction)(BaseECSComponent* comp);

		struct BaseECSComponent {
    public:
			static uint32_t registerComponentType(ECSComponentCreateFunction createfn, ECSComponentFreeFunction freefn, size_t size);
			EntityHandle m_entity = NULL_ENTITY_HANDLE;

      inline static ECSComponentCreateFunction getTypeCreateFunction(uint32_t id) {
        return std::get<0>(s_componentTypes[id]);
      }

      inline static ECSComponentFreeFunction getTypeFreeFunction(uint32_t id) {
        return std::get<1>(s_componentTypes[id]);
      }

      inline static size_t getTypeSize(uint32_t id) {
        return std::get<2>(s_componentTypes[id]);
      }

    private:
      static std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>> s_componentTypes;
		};

		template<typename T>
		struct ECSComponent : public BaseECSComponent {
      static const ECSComponentCreateFunction CREATE_FUNCTION;
      static const ECSComponentFreeFunction FREE_FUNCTION;
			static const uint32_t TYPE_ID;
			static const size_t SIZE;
		};

    template<typename Component>
    uint32_t ECSComponentCreate(std::vector<uint8_t>& memory, EntityHandle entity, BaseECSComponent* comp) {
      uint32_t index = memory.size();
      memory.resize(index + Component::SIZE);
      Component* component = new(&memory[index]) Component(*(Component*)comp);
      component->m_entity = entity;
    }

    template<typename Component>
    void ECSComponentFree(BaseECSComponent* comp) {
      Component* component = (Component*)comp;
      component->~Component();
    }

		template<typename T>
		const uint32_t ECSComponent<T>::TYPE_ID(BaseECSComponent::registerComponentType(ECSComponentCreate<T>, 
      ECSComponentFree<T>, sizeof(T)));

		template<typename T>
		const size_t ECSComponent<T>::SIZE(sizeof(T));


	}//namespace ECS end
}//namespace King end
