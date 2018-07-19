#pragma once

#include <utility>
#include <memory>

#include <vendor/miniz/miniz.h>

namespace SteveBase::Misc {

    class ZLib {
    public:
        static std::pair<std::shared_ptr<std::byte>, size_t> Compress(std::byte *mem, const size_t len) {
            size_t n = compressBound(len);
            std::shared_ptr<std::byte> alloc{ new std::byte[n], [](std::byte *p) { delete[] p; } };
            auto ret = compress((uint8_t *) alloc.get(), (uLong *) &n, (uint8_t *) mem, len);
            if (ret != Z_OK) {
                return { nullptr, 0 };
            }
            return { alloc, n };
        }

        template<class T>
        constexpr static auto Compress(const T *mem, const size_t len) {
            return Compress((std::byte *) mem, len);
        }

        template<class T>
        constexpr static auto Compress(std::shared_ptr<T> &mem, const size_t len) {
            return Compress((const T *) mem.get(), len * sizeof T);
        }

        template<class T, size_t len>
        constexpr static auto Compress(std::array<T, len> &&mem) {
            return Compress((const T *) mem.data(), len * sizeof T);
        }

        template<class T, size_t len>
        constexpr static auto Compress(const T (&mem)[len]) {
            return Compress((const T *) mem, len * sizeof T);
        }

        template<class T>
        static std::pair<std::shared_ptr<T>, size_t> Decompress(std::byte *mem, const size_t len) {
            size_t finalLen = len;

        try_uncompress:
            auto buf = std::make_unique<std::byte[]>(finalLen);
            const auto ret = uncompress((uint8_t *)buf.get(), (uLong *) &finalLen, (uint8_t *)mem, len);
            if (ret != Z_OK) {
                if (ret == Z_BUF_ERROR) {
                    // buffer too small, end the old one, expand it, try again
                    finalLen *= 2;
                    goto try_uncompress;
                }
                return { nullptr, 0 };
            }
            if (finalLen % sizeof T != 0) {
                return { nullptr, 0 };
            }

            std::shared_ptr<T> bufFinal { new T[finalLen / sizeof T], [](T *p) { delete[] p; } };
            memcpy(bufFinal.get(), buf.get(), finalLen);

            return { bufFinal, finalLen / sizeof T };
        }

        template<class T>
        constexpr static auto Decompress(const T *mem, const size_t len) {
            return Decompress<T>((std::byte *) mem, len);
        }

        template<class T>
        constexpr static auto Decompress(std::shared_ptr<std::byte> &mem, const size_t len) {
            return Decompress<T>((std::byte *) mem.get(), len);
        }

        template<class T, size_t len>
        constexpr static auto Decompress(std::array<T, len> &&mem) {
            return Decompress<T>((const T *)mem.data(), len * sizeof T);
        }

        template<class T, size_t len>
        constexpr static auto Decompress(const T(&mem)[len]) {
            return Decompress<T>((const T *)mem, len * sizeof T);
        }
    };
}
