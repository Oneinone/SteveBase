#pragma once

#include <misc/ProxiedClass.hpp>
#include <source_engine/def/OverrideType.hpp>

namespace SteveBase::SourceEngine::Virtual {
    using namespace Define;

    class IMaterial;

    interface IVModelRender extends Misc::ProxiedClass {
    private:
        DefineVFunc(TrueForcedMaterialOverride, (IMaterial *newMaterial, OverrideType overrideType) -> void)(1)(newMaterial, overrideType);
    public:
        // I want to fucking kill myself
        void ForcedMaterialOverride(IMaterial *newMaterial, OverrideType overrideType = OverrideType::Normal) {
            return TrueForcedMaterialOverride(newMaterial, overrideType);
        }
    };
}
