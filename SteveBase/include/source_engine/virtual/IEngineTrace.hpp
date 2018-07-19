#pragma once

#include <misc/ProxiedClass.hpp>

namespace SteveBase::SourceEngine::Structure {
    struct Ray;

}

namespace SteveBase::SourceEngine::Virtual {
    interface ITraceFilter;
    interface IEngineTrace extends Misc::ProxiedClass {
        DefineVFunc(TraceRay, 
            (const Ray &ray, unsigned int mask, ITraceFilter* traceFilter, CGameTrace* trace) -> void
        )(5)(ray, mask, traceFilter, trace);
    };
}