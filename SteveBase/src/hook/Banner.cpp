#include <GlobalDefines.hpp>
#include <hook/Banner.hpp>

#include <assets/Fonts.hpp>
#include <manager/DrawManager.hpp>
#include <manager/VariableManager.hpp>

#include <source_engine/index.hpp>

#include <vendor/hash/hash.h>
#include <vendor/XorStr/XorStr.h>

namespace SteveBase::Hook {
    using namespace SourceEngine::Define;
    using namespace SourceEngine::Structure;
    using namespace SourceEngine::Virtual;

    void Banner::OnPaintTraverse() {
        if (DynamicVariable(misc.drawbanner).Get<bool>()) {
            if (Get<CGlobalVarsBase>()->HasRealTimePassed(time)) {
                position += 1;
                time = Get<CGlobalVarsBase>()->GetRelativeTimeToReal(1 / (float) 120);
            }

            if (position % DrawManager::GetScreenSize().Width() == 0 && position != 0) {
                position = -240;
            }

            Get<ISurface>()
                ->SetTextFont<Assets::Fonts::ESP::ExtraLarge>()
                ->SetTextPos(position, 60)
                ->PrintText(text("~ Welcome To SteveBase ~"));
        }
        else {
            position = -240;
        }
    }
}
