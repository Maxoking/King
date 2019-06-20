#pragma once
#include "kngpch.h"

#include "Component.h"
namespace King {
  namespace ECS {
    class BaseECSSystem {
    public:
      BaseECSSystem(const std::vector<uint32_t> componentTypesIn) : m_componentTypes(componentTypesIn) {};
      virtual void updateComponents(float delta, BaseECSComponent** components) {};
      const std::vector<uint32_t>& getComponentTypes() { return m_componentTypes; };
    private:
      std::vector<uint32_t> m_componentTypes;
    };
  }
}
