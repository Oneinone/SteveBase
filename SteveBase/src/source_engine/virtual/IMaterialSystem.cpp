#include <GlobalDefines.hpp>
#include <source_engine/virtual/IMaterialSystem.hpp>

#include <maths/Random.hpp>

#include <vendor/XorStr/XorStr.h>
#include <vendor/ggformat/ggformat.h>

namespace SteveBase::SourceEngine::Virtual {
    using namespace Maths;

    // copypasted from gamerfood
    IMaterial *IMaterialSystem::CreateCustomMaterial(bool flat, bool wireframed, bool ignorez) const {
        auto material_format = text(R"(
		    "{0}"
		    {
			    "$basetexture" "vgui/white_additive"
			    "$envmap" "env_cubemap"
			    "$model" "1"
			    "$flat" "1"
			    "$nocull" "0"
			    "$selfillum" "1"
			    "$halflambert" "1"
			    "$nofog" "0"
			    "$znearer" "0"
			    "$wireframe" "{}"
			    "$ignorez" "{}"
		    }
	    )");

        auto chams_format = text(R"(
            "{0}"
            {
	            "$surfaceprop" Metal
	            "$envmap" "env_cubemap"
	            "$phong" "1"
	            "$phongfresnelranges" "[0.5 0.75 1]"
	            "$basetexture "{}"
	            "$ignorez" {}
	            "$nofog" {}
	            "$model" "1"
	            "$nocull" "1"
	            "$halflambert" "1"
	            "$phongexponent" "25"
	            "$rimlight" "1"
	            "$rimlightexponent" "1"
	            "$rimlightboost" "1"
	            "$selfillum" "1"
	            "$selfillum_envmapmask_alpha" "1"
	            "$selfillumtint" "[0.61 0.61 0.61]"
            }
        )");

        auto keyValue = ggformat_to_string(material_format,
            flat ? text("UnlitGeneric") : text("VertexLitGeneric"),
            wireframed,
            ignorez
        );
        auto materialName = ggformat_to_string(text("custom_{}"), Random::NextUnsignedInt16(0, 5000));

        return nullptr;
    }

    generator<IMaterial *> IMaterialSystem::GetAllMaterials() {
        auto invalid = InvalidMaterial();

        for (auto handle = FirstMaterial(); handle != invalid; handle = NextMaterial(handle)) {
            auto material = GetMaterial(handle);
            if (material != nullptr) {
                co_yield material;
            }
        }
    }
}
