#pragma once

#include <maths/Vector3.hpp>

namespace SteveBase::Maths {
    /// <Vector4>
    /// Replacement for Valve's VectorAligned bullshit
    class Vector4 : public Vector3 {
    public:
        Vector4() {

        }

        Vector4(float X, float Y, float Z, float W) {
            Init(X, Y, Z);
            w = W;
        }

        Vector4(float X, float Y, float Z) {
            Init(X, Y, Z);
        }

        Vector4(Vector3 &vOther) {
            Init(vOther.X(), vOther.Y(), vOther.Z());
        }

        Vector4& operator =(Vector3 &vOther) {
            Init(vOther.X(), vOther.Y(), vOther.Z());
            return *this;
        }

        float &W() {
            return w;
        }

    private: float w;    // this space is used anyway
    };
}