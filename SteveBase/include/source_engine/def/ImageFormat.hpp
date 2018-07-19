#pragma once

namespace SteveBase::SourceEngine::Define {
    enum class ImageFormat {
        Unknown = -1,
        RGBA8888 = 0,
        ABGR8888,
        RGB888,
        BGR888,
        RGB565,
        I8,
        IA88,
        P8,
        A8,
        RGB888_BlueScreen,
        BGR888_BlueScreen,
        ARGB8888,
        BGRA8888,
        DXT1,
        DXT3,
        DXT5,
        BGRX8888,
        BGR565,
        BGRX5551,
        BGRA4444,
        DXT1_OneBitAlpha,
        BGRA5551,
        UV88,
        UVWQ8888,
        RGBA16161616F,
        RGBA16161616,
        UVLX8888,
        R32F,			// Single-channel 32-bit floating point
        RGB323232F,	// NOTE: D3D9 does not have this format
        RGBA32323232F,
        RG1616F,
        RG3232F,
        RGBX8888,

        Null,			// Dummy format which takes no video memory

        // Compressed normal map formats
        ATI2N,			// One-surface ATI2N / DXN format
        ATI1N,			// Two-surface ATI1N format

        RGBA1010102,	// 10 bit-per component render targets
        BGRA1010102,
        R16F,			// 16 bit FP format

        // Depth-stencil texture formats
        D16,
        D15S1,
        D32,
        D24S8,
        Linear_D24S8,
        D24X8,
        D24X4S4,
        D24FS8,
        D16_Shadow,	// Specific formats for shadow mapping
        D24X8_Shadow,	// Specific formats for shadow mapping

        // supporting these specific formats as non-tiled for procedural cpu access (360-specific)
        Linear_BGRX8888,
        Linear_RGBA8888,
        Linear_ABGR8888,
        Linear_ARGB8888,
        Linear_BGRA8888,
        Linear_RGB888,
        Linear_BGR888,
        Linear_BGRX5551,
        Linear_I8,
        Linear_RGBA16161616,

        LE_BGRX8888,
        LE_BGRA8888,

        TotalAmountOfImageFormats,
    };
}
