#include <GlobalDefines.hpp>
#include <maths/Vector3.hpp>

#include <maths/Math.hpp>

#include <cmath>
#include <cstring>

namespace SteveBase::Maths {
    bool Vector3::operator ==(Vector3 v) {
        return std::memcmp(this, &v, sizeof(Vector3)) == 0;
    }

    bool Vector3::operator !=(Vector3 v) {
        return !(*this == v);
    }

    Vector3& Vector3::operator +=(Vector3 v) {
        x += v.x;
        y += v.y;
        z += v.y;

        return *this;
    }

    Vector3& Vector3::operator -=(Vector3 v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return *this;
    }

    Vector3& Vector3::operator *=(Vector3 v) {
        x *= v.x;
        y *= v.y;
        z *= v.y;

        return *this;
    }

    Vector3& Vector3::operator /=(Vector3 v) {
        x /= v.x;
        y /= v.y;
        z /= v.y;

        return *this;
    }

    Vector3 Vector3::operator +(Vector3 v) {
        return { x + v.x, y + v.y, z + v.z };
    }

    Vector3 Vector3::operator -(Vector3 v) {
        return { x - v.x, y - v.y, z - v.z };
    }

    Vector3 Vector3::operator *(Vector3 v) {
        return { x * v.x, y * v.y, z * v.z };
    }

    Vector3 Vector3::operator /(Vector3 v) {
        return { x / v.x, y / v.y, z / v.z };
    }

    Vector3& Vector3::operator +=(float fl) {
        x += fl;
        y += fl;
        z += fl;

        return *this;
    }

    Vector3& Vector3::operator -=(float fl) {
        x -= fl;
        y -= fl;
        z -= fl;

        return *this;
    }

    Vector3& Vector3::operator *=(float fl) {
        x *= fl;
        y *= fl;
        z *= fl;

        return *this;
    }

    Vector3& Vector3::operator /=(float fl) {
        x /= fl;
        y /= fl;
        z /= fl;

        return *this;
    }

    Vector3 Vector3::operator +(float fl) {
        return { x + fl, y + fl, z + fl };
    }

    Vector3 Vector3::operator -(float fl) {
        return { x - fl, y - fl, z - fl };
    }

    Vector3 Vector3::operator *(float fl) {
        return { x * fl, y * fl, z * fl };
    }

    Vector3 Vector3::operator /(float fl) {
        return { x / fl, y / fl, z / fl };
    }

    Vector3 &Vector3::operator =(Vector3 vOther) {
        x = vOther.x;
        y = vOther.y;
        z = vOther.z;

        return *this;
    }

    // Eww, just think like sarrus rule
    Vector3 Vector3::CrossProduct(Vector3 vOther) {
        return {
             (Y() * vOther.Z() - Z() * vOther.Y()), //   i(a.y * b.z - a.z * b.y)
            -(X() * vOther.Z() - Z() * vOther.X()), // - j(a.x * b.z - a.z * b.x)
             (X() * vOther.Y() - Y() * vOther.X())  // + k(a.x * b.y - a.y * b.x) where i = j = k = 1
        };
    }

    float Vector3::DotProduct(Vector3 vOther) {
        auto cross = *this * vOther;
        return cross.x + cross.y + cross.z;
    }

    float Vector3::Area() {
        return Math::Square(x) + Math::Square(y) + Math::Square(z);
    }
    float Vector3::Magnitude() {
        return std::sqrt(Area());
    }
    float Vector3::DistanceTo(Vector3 vOther) {
        auto delta = *this - vOther;
        auto dist = std::sqrt(delta.Magnitude());

        return std::min(dist, 1.0f);
    }

    // a . b = a x b x cos theta
    // cos theta = a . b / a x b
    float Vector3::AngleTo(Vector3 vOther) {
        return std::acos(this->Dot(vOther) / this->Cross(vOther).Magnitude());
    }
    Vector3 Vector3::Normalize() {
        auto norm = Magnitude();
        return Vector3(x / norm, y / norm, z / norm);
    }
}