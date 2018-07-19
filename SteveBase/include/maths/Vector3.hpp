#pragma once

#include <string>
#include <vendor/XorStr/XorStr.h>
#include <vendor/ggformat/ggformat.h>

namespace SteveBase::Maths {
    /// <Vector3>
    /// Replacement for Valve's Vector bullshit
    class Vector3 {
        float x, y, z;
    public:
        Vector3(float X = 0, float Y = 0, float Z = 0) {
            Init(X, Y, Z);
        }

        void Init(float X = 0, float Y = 0, float Z = 0) {
            x = X;
            y = Y;
            z = Z;
        }

        bool IsValid() {
            return x > 0.0f && y > 0.0f && z > 0.0f;
        }

        void Clear() {
            x = y = z = 0.0f;
        }

        bool operator ==(Vector3 v);
        bool operator !=(Vector3 v);
        Vector3& operator +=(Vector3 v);
        Vector3& operator -=(Vector3 v);
        Vector3& operator *=(Vector3 v);
        Vector3& operator /=(Vector3 v);
        Vector3 operator +(Vector3 v);
        Vector3 operator -(Vector3 v);
        Vector3 operator *(Vector3 v);
        Vector3 operator /(Vector3 v);
        Vector3& operator +=(float fl);
        Vector3& operator -=(float fl);
        Vector3& operator *=(float fl);
        Vector3& operator /=(float fl);
        Vector3 operator +(float fl);
        Vector3 operator -(float fl);
        Vector3 operator *(float fl);
        Vector3 operator /(float fl);
        Vector3& operator =(Vector3 vOther);

        Vector3 CrossProduct(Vector3 vOther);

        float DotProduct(Vector3 vOther);

        Vector3 Cross(Vector3 vOther) {
            return CrossProduct(vOther);
        }

        float Dot(Vector3 vOther) {
            return DotProduct(vOther);
        }

        float &X() {
            return x;
        }

        float &Y() {
            return y;
        }

        float &Z() {
            return z;
        }

        float Area();

        float Magnitude();

        float DistanceTo(Vector3 vOther);

        float AngleTo(Vector3 vOther);

        Vector3 Normalize();

        std::string ToString() {
            return ggformat_to_string(text("Vector3 = [{0}, {1}, {2}]"), X(), Y(), Z());
        }
    };
}
