#pragma once

#include <misc/ProxiedClass.hpp>

#include <string>

namespace SteveBase::SourceEngine::Structure {
    struct model_t;
    struct StudioModel;
}

namespace SteveBase::SourceEngine::Virtual {
    using namespace SourceEngine::Structure;

    interface IVModelInfo extends Misc::ProxiedClass {
        std::string GetModelName(const model_t *model) const;

        DefineVFunc(GetModelMaterials, (const model_t *model, int count, IMaterial** materials)->void)(19)(model, count, materials);
        DefineVFunc(GetStudioModel, (const model_t *model)->StudioModel *)(32)(model);

        template <size_t N>
        constexpr void GetModelMaterials(const model_t *model, const IMaterial *(materials)[N]) {
            return GetModelMaterials(model, N, materials);
        }
    };
}