#pragma once

#include <assets/IHitSound.hpp>

namespace SteveBase::Assets::Hitsound {
    class HitmarkerHitsound implements IHitSound {
    public:
        uint8_t *GetHitsound() override;
        uint8_t *GetKillsound() override;
    };
}