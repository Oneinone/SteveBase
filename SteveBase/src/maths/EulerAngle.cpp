#include <GlobalDefines.hpp>
#include <maths/EulerAngle.hpp>

#include <maths/Vector3.hpp>

#include <cmath>
#include <algorithm>

namespace SteveBase::Maths {
    const auto RadianPerDegree = (float)M_PI / 180.f;
    const auto DegreePerRadian = 180.f / (float)M_PI;

    float EulerAngle::DegreeToRadian(float deg) {
        return deg * RadianPerDegree;
    }

    float EulerAngle::RadianToDegree(float rad) {
        return rad * DegreePerRadian;
    }

    EulerAngle EulerAngle::ToNormalizedAngle() {
        auto angle = *this;

        while (angle.X() > 89.0f) {
            angle.X() -= 180.f;
        }

        while (angle.X() < -89.0f) {
            angle.X() += 180.f;
        }

        while (angle.Y() > 180.f) {
            angle.Y() -= 360.f;
        }

        while (angle.Y() < -180.f) {
            angle.Y() += 360.f;
        }

        return angle;
    }

    // Clamped Angle: (-90, 90), [-180, 180], (0, 0)
    EulerAngle EulerAngle::ToClampedAngle() {
        auto angle = *this;

        angle.Y() = std::clamp(angle.Y(), -89.f, 89.f);
        angle.Y() = std::clamp(angle.Y(), -180.f, 180.f);
        angle.Z() = 0;

        return angle;
    }

    Vector3 EulerAngle::GetUnitForwardVector() {
        Vector3 out;

        const auto sinePitch = std::sinf(DegreeToRadian(Pitch()));
        const auto cosinePitch = std::cosf(DegreeToRadian(Pitch()));
        const auto sineYaw = std::sinf(DegreeToRadian(Yaw()));
        const auto cosineYaw = std::cosf(DegreeToRadian(Yaw()));

        out.X() = cosinePitch * cosineYaw;
        out.Y() = cosinePitch * sineYaw;
        out.Z() = -sinePitch;

        return out;
    }
    Vector3 EulerAngle::GetUnitRightVector() {
        Vector3 out;

        const auto sinePitch = std::sinf(DegreeToRadian(Pitch()));
        const auto sineYaw = std::sinf(DegreeToRadian(Yaw()));
        const auto sineRoll = std::sinf(DegreeToRadian(Roll()));

        const auto cosinePitch = std::cosf(DegreeToRadian(Pitch()));
        const auto cosineYaw = std::cosf(DegreeToRadian(Yaw()));
        const auto cosineRoll = std::cosf(DegreeToRadian(Roll()));

        out.X() = -1 * sineRoll * sinePitch * cosineYaw + -1 * cosineRoll * -sineYaw;
        out.Y() = -1 * sineRoll * sinePitch * sineYaw + -1 * cosineRoll * cosineYaw;
        out.Z() = -1 * sineRoll * cosinePitch;

        return out;
    }
    Vector3 EulerAngle::GetUnitUpVector() {
        Vector3 out;

        const auto sinePitch = std::sinf(DegreeToRadian(Pitch()));
        const auto sineYaw = std::sinf(DegreeToRadian(Yaw()));
        const auto sineRoll = std::sinf(DegreeToRadian(Roll()));

        const auto cosinePitch = std::cosf(DegreeToRadian(Pitch()));
        const auto cosineYaw = std::cosf(DegreeToRadian(Yaw()));
        const auto cosineRoll = std::cosf(DegreeToRadian(Roll()));

        out.X() = cosineRoll * sinePitch * cosineYaw + -sineRoll * -sineYaw;
        out.Y() = cosineRoll * sinePitch * sineYaw + -sineRoll * cosineYaw;
        out.Z() = cosineRoll * cosinePitch;

        return out;
    }
    void EulerAngle::SetForwardVector(Vector3 vec) {

    }
    void EulerAngle::SetRightVector(Vector3 vec) {

    }
    void EulerAngle::SetUpVector(Vector3 vec) {

    }
}
