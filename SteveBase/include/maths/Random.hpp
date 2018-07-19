#pragma once

#include <random>

#include <misc/TemplateMetaprogramming.hpp>

#include <vendor/XorStr/XorStr.h>

namespace SteveBase::Maths {
    using namespace Misc;

    class Random {
        template<typename T>
        static constexpr T MakePseudoNumberGenerator(T min, T max) {
            if (IsSixtyFourBit<T>()) {
                // random-number engine used (Mersenne-Twister in this case)
                std::mt19937_64 rng(std::random_device{}());
                return std::uniform_int_distribution<T>(min, max)(rng);
            }

            // random-number engine used (Mersenne-Twister in this case)
            std::mt19937 rng(std::random_device{}());
            return std::uniform_int_distribution<T>(min, max)(rng);
        }

        template<typename T>
        static constexpr T MakePseudoRealNumberGenerator(T min, T max) {
            static_assert(IsReal<T>(), "must be real");
            // random-number engine used (Mersenne-Twister in this case)
            std::mt19937 rng(std::random_device{}());
            return std::uniform_real_distribution<T>(min, max)(rng);
        }

    public:
        static constexpr uint64_t NextUnsignedInt64(uint64_t min, uint64_t max) {
            return MakePseudoNumberGenerator(min, max);
        }

        static constexpr uint64_t NextUnsignedInt64(uint64_t max) {
            return NextSignedInt64(std::numeric_limits<uint64_t>::min(), max);
        }

        static constexpr uint64_t NextUnsignedInt64() {
            return NextSignedInt64(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max());
        }

    public:
        static constexpr int64_t NextSignedInt64(int64_t min, int64_t max) {
            return MakePseudoNumberGenerator(min, max);
        }

        static constexpr int64_t NextSignedInt64(int64_t max) {
            return NextSignedInt64(std::numeric_limits<int64_t>::min(), max);
        }

        static constexpr int64_t NextSignedInt64() {
            return NextSignedInt64(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
        }

    public:
        static constexpr uint32_t NextUnsignedInt32(uint32_t min, uint32_t max) {
            return MakePseudoNumberGenerator(min, max);
        }

        static constexpr uint32_t NextUnsignedInt32(uint32_t max) {
            return NextUnsignedInt32(std::numeric_limits<uint32_t>::min(), max);
        }

        static constexpr uint32_t NextUnsignedInt32() {
            return NextUnsignedInt32(std::numeric_limits<uint32_t>::min(), std::numeric_limits<uint32_t>::max());
        }

    public:
        // Direct copypaste of https://stackoverflow.com/a/7560564
        static constexpr int32_t NextSignedInt32(int32_t min, int32_t max) {
            return MakePseudoNumberGenerator(min, max);
        }

        static constexpr int32_t NextSignedInt32(int32_t max) {
            return NextSignedInt32(std::numeric_limits<int32_t>::min(), max);
        }

        static constexpr int32_t NextSignedInt32() {
            return NextSignedInt32(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max());
        }

    public:
        static constexpr uint16_t NextUnsignedInt16(uint16_t min, uint16_t max) {
            return MakePseudoNumberGenerator(min, max);
        }

        static constexpr uint16_t NextUnsignedInt16(uint16_t max) {
            return NextUnsignedInt16(std::numeric_limits<uint16_t>::min(), max);
        }

        static constexpr uint16_t NextUnsignedInt16() {
            return NextUnsignedInt16(std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
        }

    public:
        static constexpr int16_t NextSignedInt16(int16_t min, int16_t max) {
            return MakePseudoNumberGenerator(min, max);
        }

        static constexpr int16_t NextSignedInt16(int16_t max) {
            return NextSignedInt16(std::numeric_limits<int16_t>::min(), max);
        }

        static constexpr int16_t NextSignedInt16() {
            return NextSignedInt16(std::numeric_limits<int16_t>::min(), std::numeric_limits<int16_t>::max());
        }

    public:
        static constexpr uint8_t NextUnsignedInt8(uint8_t min, uint8_t max) {
            return (uint8_t)MakePseudoNumberGenerator((uint16_t)min, (uint16_t)max);
        }

        static constexpr uint8_t NextUnsignedInt8(uint8_t max) {
            return NextUnsignedInt8(std::numeric_limits<uint8_t>::min(), max);
        }

        static constexpr uint8_t NextUnsignedInt8() {
            return NextUnsignedInt8(std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max());
        }

    public:
        static constexpr int8_t NextSignedInt8(int8_t min, int8_t max) {
            return (int8_t)MakePseudoNumberGenerator((int16_t)min, (int16_t)max);
        }

        static constexpr int8_t NextSignedInt8(int8_t max) {
            return NextSignedInt8(std::numeric_limits<int8_t>::min(), max);
        }

        static constexpr int8_t NextSignedInt8() {
            return NextSignedInt8(std::numeric_limits<int8_t>::min(), std::numeric_limits<int8_t>::max());
        }

    public:
        static constexpr double_t NextDouble(double_t min, double_t max) {
            return MakePseudoRealNumberGenerator(min, max);
        }

        static constexpr double_t NextDouble(double_t max) {
            return NextDouble(std::numeric_limits<double_t>::min(), max);
        }

        static constexpr double_t NextDouble() {
            return NextDouble(std::numeric_limits<double_t>::min(), std::numeric_limits<double_t>::max());
        }

    public:
        static constexpr float_t NextFloat(float_t min, float_t max) {
            return MakePseudoRealNumberGenerator(min, max);
        }

        static constexpr float_t NextFloat(float_t max) {
            return NextFloat(std::numeric_limits<float_t>::min(), max);
        }

        static constexpr float_t NextFloat() {
            return NextFloat(std::numeric_limits<float_t>::min(), std::numeric_limits<float_t>::max());
        }

    public:
        static constexpr bool NextBool() {
            return NextSignedInt8(0, 1); // 50/50 generator, if you want a probability bool see GetChanceBool
        }

        static bool GetChanceBool(double_t prob, double_t max = 1) {
            std::mt19937 rng(std::random_device{}());
            std::bernoulli_distribution dist(prob / max);

            return dist(rng);
        }

        static std::string GetRandomString(uint16_t size) {
            std::string alphanum = text(
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
            );

            std::string str;
            str.reserve(size);

            for (auto i = 0; i < size; i++) {
                str[i] = alphanum[NextSignedInt32() % alphanum.length()];
            }

            return str;
        }


    };
}
