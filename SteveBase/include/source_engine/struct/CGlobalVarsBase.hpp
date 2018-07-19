#pragma once

#include <utility/Tuple.hpp>

#undef GetTickCount // fuck you winapi
#undef GetCurrentTime // fuck you winapi

namespace SteveBase::SourceEngine::Structure {
    using namespace Utility;

    struct CGlobalVarsBase {
    private:
        float			realtime;
        int				framecount;
        float			absoluteframetime;
        float			absoluteframestarttime;
        float			curtime;
        float			frametime;
        int				maxClients;
        int				tickcount;
        float			interval_per_tick;
        float			interpolation_amount;
        int				simTicksThisFrame;
        int				network_protocol;
        void		    *pSaveData;
        bool			m_bClient;
        int				nTimestampNetworkingBase;
        int				nTimestampRandomizeWindow;
    public:
        float GetRealTime() const { return realtime;  }
        int GetFrameCount() const { return framecount; }

        float GetAbsoluteFrameTime() const { return absoluteframetime; }
        float GetAbsoluteFrameStartTime() const { return absoluteframestarttime; }

        float GetCurrentTime() const { return curtime; }
        float GetFrameTime() const { return frametime; }

        int GetMaxClients() const { return maxClients; }
        int GetTickCount() const { return tickcount; }

        float GetIntervalPerTick() const { return interval_per_tick; }
        float GetInterpolationAmount() const { return interpolation_amount; }

        int GetSimulatedTicksThisFrame() const { return simTicksThisFrame;  }

        int GetNetworkProtocol() const { return network_protocol; }

        Tuple<float, float> GetRelativeTimeToReal(float amount) const {
            return Tuple<>::Create(GetRealTime(), amount);
        }

        bool HasRealTimePassed(Tuple<float, float> relativeTime) const {
            return GetRealTime() > relativeTime.Item<0>() + relativeTime.Item<1>();
        }
    };
}
