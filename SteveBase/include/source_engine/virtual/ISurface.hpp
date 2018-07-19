#pragma once

#include <manager/FontManager.hpp>

#include <misc/Color.hpp>
#include <misc/DataStructure.hpp>
#include <misc/Macro.hpp>
#include <misc/ProxiedClass.hpp>
#include <utility/Tuple.hpp>

#include <source_engine/def/_EngineTypes.hpp>
#include <source_engine/def/EFontFlags.hpp>
#include <source_engine/def/FontDrawType.hpp>

namespace SteveBase::SourceEngine::Virtual {
    using namespace Define;
    using namespace Manager;
    using namespace Misc;
    using namespace Utility;

    interface ISurface extends ProxiedClass {
    private:
        DefineVFunc(DrawSetColor_Raw, (int r, int g, int b, int a) -> void)(15)(r, g, b, a);
        DefineVFunc(DrawFilledRect_Raw, (int x0, int y0, int x1, int y1) -> void)(16)(x0, y0, x1, y1);
        DefineVFunc(DrawOutlinedRect_Raw, (int x0, int y0, int x1, int y1) -> void)(18)(x0, y0, x1, y1);
        DefineVFunc(DrawLine_Raw, (int x0, int y0, int x1, int y1) -> void)(19)(x0, y0, x1, y1);
        DefineVFunc(DrawPolyLine_Raw, (int *x, int *y, int count) -> void)(20)(x, y, count);
        DefineVFunc(DrawSetTextFont_Raw, (HFont font) -> void)(23)(font);
        DefineVFunc(DrawSetTextColor_Raw, (int r, int g, int b, int a) -> void)(25)(r, g, b, a);
        DefineVFunc(DrawSetTextPos_Raw, (int x, int y) -> void)(26)(x, y);
        DefineVFunc(DrawPrintText_Raw, (const wchar_t *textPtr, int textLen, FontDrawType drawType) -> void)(28)(textPtr, textLen, drawType);

        DefineVFunc(SetFontGlyphSet_Raw,
            (HFont font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin, int nRangeMax) -> void
        )(72)(font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
    public:
        DefineVFunc(GetScreenSize, (int &wide, int &tall) -> void)(44)(wide, tall);
        DefineVFunc(SetCursor, (bool visible) -> void)(57)(visible);
        DefineVFunc(IsCursorVisible, () -> bool)(58)();
        DefineVFunc(CreateFont, () -> HFont)(71)();

        DefineVFunc(AddCustomFontFile, (const char *fontName, const char *fontFileName) -> bool)(73)(fontName, fontFileName);
        DefineVFunc(PlaySound, (const char *fileName) -> void)(82)(fileName);
    public:
        ISurface *SetColor(int r, int g, int b, int a) {
            DrawSetColor_Raw(r, g, b, a);
            return this;
        }

        ISurface *SetColor(Color c) {
            DrawSetColor_Raw(c.R(), c.G(), c.B(), c.A());
            return this;
        }

        ISurface *DrawFilledRect(int x0, int y0, int x1, int y1) {
            DrawFilledRect_Raw(x0, y0, x1, y1);
            return this;
        }

        ISurface *DrawFilledRect(Tuple<int, int> pt0, Tuple<int, int> pt1) {
            return DrawFilledRect(pt0.Item<0>(), pt0.Item<1>(), pt1.Item<0>(), pt1.Item<1>());
        }

        ISurface *DrawOutlinedRect(int x0, int y0, int x1, int y1) {
            DrawOutlinedRect_Raw(x0, y0, x1, y1);
            return this;
        }

        ISurface *DrawOutlinedRect(Tuple<int, int> pt0, Tuple<int, int> pt1) {
            return DrawOutlinedRect(pt0.Item<0>(), pt0.Item<1>(), pt1.Item<0>(), pt1.Item<1>());
        }

        ISurface *DrawLine(int x0, int y0, int x1, int y1) {
            DrawLine_Raw(x0, y0, x1, y1);
            return this;
        }

        ISurface *DrawLine(Tuple<int, int> from, Tuple<int, int> to) {
            return DrawLine(from.Item<0>(), from.Item<1>(), to.Item<0>(), to.Item<1>());
        }

        ISurface *DrawPolyLine(int *x, int *y, int count) {
            DrawPolyLine_Raw(x, y, count);
            return this;
        }

        /*
            vector<Tuple<int, int>> pts = {
                { 0, 1 }, // pt0
                { 1, 2 }, // pt1
                { 3, 4 }, // pt2
                { 13, 37 }, // pt3
                // as such
            }
        */
        ISurface *DrawPolyLine(List<Tuple<int, int>> pts) {
            // We already have the array size = size of vector of points
            int count = pts.size();

            /*  DrawPolyLine accepts an integer pointers of x and y
                that uses the array index as point inex
                so:
                    pt0 = { x[0], y[0] }
                    pt1 = { x[1], y[1] }
                    pt2 = { x[2], y[2] }
                    ptN = { x[N], y[N] }
                    ...
                We can have:
                    x[0] = pt[0].x, y[0] = pt[0].y;
                    x[1] = pt[1].x, y[1] = pt[1].y;
                    x[2] = pt[2].x, y[2] = pt[2].y;
                    x[N] = pt[N].x, y[N] = pt[N].y;
                    ...
                We use a loop to unpack the point vector and remarshal the points into their own specific coordinate union

            */
            auto x = std::make_unique<int[]>(count);
            auto y = std::make_unique<int[]>(count);

            // I could have had independent copy function here but I decided not to use it
            // Never should I have made two loops

            for (auto i = 0; i < count; i++) {
                pts[i].Deconstruct(x[i], y[i]); // can't use structured binding here
            }

            return DrawPolyLine(x.get(), y.get(), count);
        }

        ISurface *SetTextFont(HFont font) {
            DrawSetTextFont_Raw(font);
            return this;
        }

        ISurface *SetTextColor(int r, int g, int b, int a) {
            DrawSetTextColor_Raw(r, g, b, a);
            return this;
        }

        ISurface *SetTextColor(Color c) {
            DrawSetTextColor_Raw(c.R(), c.G(), c.B(), c.A());
            return this;
        }

        ISurface *SetTextPos(int x, int y) {
            DrawSetTextPos_Raw(x, y);
            return this;
        }

        ISurface *SetTextPos(Tuple<int, int> pt) {
            return SetTextPos(pt.Item<0>(), pt.Item<1>());
        }

        ISurface *PrintText(std::wstring text, FontDrawType drawType = FontDrawType::Default) {
            DrawPrintText_Raw(text.c_str(), text.length(), drawType);
            return this;
        }

        ISurface *PrintText(std::string text, FontDrawType drawType = FontDrawType::Default) {
            return PrintText(ConvertStringOfBytesToWides(text), drawType);
        }

        ISurface *SetFontGlyphSet(HFont &font, const char *fontName, int tall, int weight, int blur, int scanlines, EFontFlags flags, int nRangeMin = 0, int nRangeMax = 0) {
            SetFontGlyphSet_Raw(font, fontName, tall, weight, blur, scanlines, (int) flags, nRangeMin, nRangeMax);
            return this;
        }

        HFont CreateFontAndSetGlyph(const char *fontName, int tall, int weight, int blur, int scanlines, EFontFlags flags, int nRangeMin = 0, int nRangeMax = 0) {
            auto font = CreateFont();
            SetFontGlyphSet(font, fontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
            return font;
        }

        template <class T>
        constexpr ISurface *SetTextFont() {
            SetTextFont(FontManager::GetFont<T>());
            return this;
        }

        constexpr ISurface *BeginDraw() {
            return this;
        }

        constexpr ISurface *EndDraw() {
            return this;
        }
    };

}
