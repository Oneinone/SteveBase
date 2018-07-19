#pragma once

#include <string>
#include <vendor/XorStr/XorStr.h>
#include <vendor/ggformat/ggformat.h>

namespace SteveBase::Maths {

    class Vector3;

    /// <EulerAngles>
    /// Replacement for Valve's QAngle bullshit
    class EulerAngle {
        // this shit exists for referencing purposes
        enum {
            PITCH = 0,	// up / down
            YAW,		// left / right
            ROLL		// fall over
        };

        // All 360 degree
        float alpha;
        float beta;
        float gamma;

    public:
        EulerAngle(float a = 0, float b = 0, float g = 0) {
            Init(a, b, g);
        }

        void Init(float a = 0, float b = 0, float g = 0) {
            alpha = a;
            beta = b;
            gamma = g;
        }

        float &Alpha() {
            return alpha;
        }
        float &Beta() {
            return beta;
        }
        float &Gamma() {
            return gamma;
        }

        // aliases
        float &Phi() {
            return alpha;
        }
        float &Theta() {
            return beta;
        }
        float &Psi() {
            return gamma;
        }
        // If you insists
        float &X() {
            return alpha;
        }
        float &Y() {
            return beta;
        }
        float &Z() {
            return gamma;
        }
        // Or still
        float &Pitch() {
            return alpha;
        }
        float &Yaw() {
            return beta;
        }
        float &Roll() {
            return gamma;
        }

    private:
        static float DegreeToRadian(float deg);
        static float RadianToDegree(float rad);
    public:
        EulerAngle ToNormalizedAngle();
        EulerAngle ToClampedAngle(); // Clamped Angle: (-90, 90), [-180, 180], (0, 0)
        Vector3 GetUnitForwardVector();
        Vector3 GetUnitRightVector();
        Vector3 GetUnitUpVector();
        void SetForwardVector(Vector3 vec);
        void SetRightVector(Vector3 vec);
        void SetUpVector(Vector3 vec);

        std::string ToString() {
            return ggformat_to_string(text("EulerAngle = [{}, {}, {}]"), X(), Y(), Z());
        }
    };
}
