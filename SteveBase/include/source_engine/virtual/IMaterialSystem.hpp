#pragma once

#include <misc/ProxiedClass.hpp>
#include <misc/Macro.hpp>

#include <source_engine/def/_EngineTypes.hpp>

#include <experimental/generator>

namespace SteveBase::SourceEngine::Structure {
    struct KeyValues;
}

namespace SteveBase::SourceEngine::Virtual {
    using namespace std::experimental;

    using namespace Define;
    using namespace Structure;

    class IMaterial;

    interface IMaterialSystem extends Misc::ProxiedClass {
        DefineVFunc(CreateMaterial, (const char *materialName, KeyValues *keyValue)->IMaterial *)(83)(materialName, keyValue);
        DefineVFunc(FirstMaterial, ()->MaterialHandle_t)(86)();
        DefineVFunc(NextMaterial, (MaterialHandle_t handle)->MaterialHandle_t)(87)(handle);
        DefineVFunc(InvalidMaterial, ()->MaterialHandle_t)(88)();
        DefineVFunc(GetMaterial, (MaterialHandle_t handle)->IMaterial*)(89)(handle);
        DefineVFunc(GetNumMaterials, ()->int)(90)();

        IMaterial *FindMaterial(const char *materialName, const char *textureGroupName, bool complain = true, const char *complainPrefix = nullptr) {
            return CallVirt<IMaterial *(const char *, const char *, bool, const char *)>(84)(materialName, textureGroupName, complain, complainPrefix);
        }

        IMaterial *CreateCustomMaterial(bool flat, bool wireframed, bool ignorez) const;

        generator<IMaterial *> GetAllMaterials();
    };
}