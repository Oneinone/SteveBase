#include <GlobalDefines.hpp>
#include <source_engine/virtual/IClientEntityList.hpp>

#include <GlobalDefines.hpp>
#include <Interface.hpp>

#include <source_engine/virtual/IEngineClient.hpp>

namespace SteveBase::SourceEngine::Virtual {
    generator<CBaseEntity *> IClientEntityList::GetAllEntities() {
        for (auto i = Get<IEngineClient>()->GetMaxClients(); i <= GetHighestEntityIndex(); i++) {
            auto entity = GetClientEntity(i);
            if (entity != nullptr) {
                co_yield entity;
            }
        }
    }

    generator<CCSPlayer *> IClientEntityList::GetAllPlayers() {
        for (auto i = 1; i <= Get<IEngineClient>()->GetMaxClients(); i++) {
            auto entity = GetClientEntity(i);
            if (entity != nullptr) {
                co_yield (CCSPlayer *) entity;
            }
        }
    }

    CCSPlayer *IClientEntityList::GetLocalPlayer() {
        return (CCSPlayer *)this->GetClientEntity(Get<IEngineClient>()->GetLocalPlayer());
    }
}
