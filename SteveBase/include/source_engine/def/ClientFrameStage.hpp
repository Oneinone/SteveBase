#pragma once

namespace SteveBase::SourceEngine::Define {
    enum class ClientFrameStage {
        Undefined = -1,
        Start,
        NetUpdateStart,
        NetUpdatePostDataUpdateStart,
        NetUpdatePostDataUpdateEnd,
        NetUpdateEnd,
        RenderStart,
        RenderEnd,
    };
}