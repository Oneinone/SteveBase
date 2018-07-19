#pragma once

#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Virtual {
    interface IConVar;

    interface ICVar extends Misc::ProxiedClass {
        DefineVFunc(RegisterConCommand, (IConVar *commandBase) -> void)(11)(commandBase);
        DefineVFunc(UnregisterConCommand, (IConVar *commandBase) -> void)(12)(commandBase);
        DefineVFunc(FindVar, (const char *varName)->IConVar *)(14)(varName);
    };
}
