#pragma once

#include <maths/EulerAngle.hpp>
#include <maths/Vector3.hpp>
#include <maths/ViewMatrix.hpp>
#include <misc/Macro.hpp>

namespace SteveBase::SourceEngine::Structure {
    using namespace Maths;

    struct model_t;
    using ModelInstanceHandle_t = unsigned short;

    struct ModelRenderInfo {
        Vector3 origin;
        EulerAngle angles;
        Pad(sizeof(int32_t));
        void *pRenderable;
        const model_t *pModel;
        const ViewMatrix *pModelToWorld = nullptr;
        const ViewMatrix *pLightingOffset = nullptr;
        const Vector3 *pLightingOrigin = nullptr;
        int flags;
        int entity_index;
        int skin;
        int body;
        int hitboxset;
        ModelInstanceHandle_t instance;
    };
}