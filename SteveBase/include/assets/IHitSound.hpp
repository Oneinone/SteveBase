#pragma once

#include <cstdint>

#include <misc/Macro.hpp>

namespace SteveBase::Assets {

    interface IHitSound {
        virtual ~IHitSound() = default;
        virtual uint8_t *GetHitsound() = 0;
        virtual uint8_t *GetKillsound() = 0;
    };
}