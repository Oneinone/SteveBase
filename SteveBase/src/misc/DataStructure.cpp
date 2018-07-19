#include <GlobalDefines.hpp>
#include <misc/DataStructure.hpp>

#include <windows.h>

namespace SteveBase::Misc {
    // copypasted: https://stackoverflow.com/a/39018368/3289081
    std::wstring ConvertStringOfBytesToWides(std::string str) {
        auto convert = [&](wchar_t *wstr, int len) {
            return MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), wstr, len);
        };
        auto sizeRequired = [&]() {
            return convert(nullptr, 0);
        };

        if (auto len = sizeRequired(); len != 0) {
            auto ptr = std::unique_ptr<wchar_t[]>(new wchar_t[len + 1]);
            convert(ptr.get(), len);
            ptr[len] = '\0';
            return std::wstring(ptr.get(), len);
        }
        return L"";
    }

    std::string ConvertStringOfWidesToBytes(std::wstring wstr) {
        auto convert = [&](char *str, int len) {
            return WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.length(), str, len, nullptr, nullptr);
        };
        auto sizeRequired = [&]() {
            return convert(nullptr, 0);
        };

        if (auto len = sizeRequired(); len != 0) {
            auto ptr = std::unique_ptr<char[]>(new char[len + 1]);
            convert(ptr.get(), len);
            ptr[len] = '\0';
            return std::string(ptr.get(), len);
        }
        return "";
    }
}