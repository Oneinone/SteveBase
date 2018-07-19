#pragma once

#include <source_engine/def/TraceType.hpp>

namespace SteveBase::SourceEngine::Virtual {
    using namespace Define;
    using namespace Structure;

    class CBaseEntity;

    interface ITraceFilter {
        virtual bool ShouldHitEntity(CBaseEntity *entity, int contentsMask) = 0;
        virtual TraceType GetTraceType() const = 0;
    };

    class LambdaTraceFilter implements ITraceFilter {
    public:
        std::function<bool(CBaseEntity*, int)> m_callSite;
        TraceType m_traceType;

        LambdaTraceFilter(std::function<bool(CBaseEntity*, int)> fn, TraceType type = TraceType::Everything) {
            m_callSite = fn;
            m_traceType = type;
        }
        bool ShouldHitEntity(CBaseEntity* pEnt, int contentsMask) override {
            return m_callSite(pEnt, contentsMask);
        }
        TraceType GetTraceType() const override {
            return m_traceType;
        }
    };

}