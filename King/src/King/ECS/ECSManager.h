#pragma once
#include "kngpch.h"

#include "Component.h"
#include "System.h"

namespace King {
	namespace ECS {

		//Entities sind ein pair aus einer ID für die entity, 
		//einem Vector für die enthaltenen Components, welche aus Type_id und id(index in m_components) bestehen
		typedef std::pair<uint32_t, std::vector< std::pair<uint32_t, uint32_t> >> EntityRawType;

		class ECSManager {
		private:
			std::vector<BaseECSSystem*> m_systems;
			std::map< uint32_t, std::vector<uint8_t> >  m_components;
			std::vector <EntityRawType*> m_entities;

		public:
			ECSManager() {};
			~ECSManager();

			EntityHandle makeEntity(BaseECSComponent* components, uint32_t* typeIDs, size_t numComponents);


			inline EntityRawType* handleToRawType(EntityHandle handle) {
				return (EntityRawType*)handle;
			}

			inline uint32_t handleToEntityIndex(EntityHandle handle) { //gibt entity index zurück
				return handleToRawType(handle)->first;
			}

			inline std::vector< std::pair<uint32_t, uint32_t> > handleToEntity(EntityHandle handle) { //gibt entity als liste aus den components zurück
				return handleToRawType(handle)->second;
			}



		};
	}
}