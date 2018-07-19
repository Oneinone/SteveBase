#include <GlobalDefines.hpp>
#include <manager/CVarManager.hpp>

#include <Interface.hpp>
#include <source_engine/index.hpp>
#include <vendor/XorStr/XorStr.h>

namespace SteveBase::Manager {
    using namespace SourceEngine::Virtual;

    List<const char *> spoofList{
        textdup("sv_cheats")
    };

    void CVarManager::Init() {
        for (auto it : spoofList) {
            auto var = Get<ICVar>()->FindVar(it);
            // var->m_nFlags = FCVAR_NONE;
        }
    }
}
