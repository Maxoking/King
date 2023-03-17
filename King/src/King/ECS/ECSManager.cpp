#include "kngpch.h"
#include "ECSManager.h"

namespace King {
	namespace ECS {

		EntityHandle ECSManager::makeEntity(BaseECSComponent* entityComponents, uint32_t* componentTypeIDs, size_t numComponents)
		{
			EntityRawType* newEntity = new EntityRawType();
			EntityHandle handle = (EntityHandle)newEntity;

			for (uint32_t i; i < numComponents; i++) {

				//ToDO: if(falsche typeId) -> return NULL_HANDLE und gib fehler aus

				ECSComponentCreateFunction createfn = BaseECSComponent::getTypeCreateFunction(componentTypeIDs[i]);
				std::pair<uint32_t, uint32_t> newPair;
				newPair.first = componentTypeIDs[i];
				newPair.second = createfn(m_components[componentTypeIDs[i]], handle, &entityComponents[i]);
				newEntity->second.push_back(newPair);
			}

			return EntityHandle();
		}
	}
}