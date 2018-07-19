#pragma once

#include <maths/Vector3.hpp>

namespace SteveBase::Maths {
    // Transformation matrix
    // this is kind of...mindfucking
    // i would like to have matrix 4x3 rather than 3x4...
    // or even 4x4 with the last dimension untouched (so determinant and linear system is still the same)
    // because you know, matricies in C is row based...
    // but here we're column based...so fucked up...
    // forward.x left.x up.x origin.x
    // forward.y left.y up.y origin.y
    // forward.z left.z up.z origin.z
    // indeed, we could just transpose the matrix to get it row based...
    // remember, quake derived games are right-handed 3d system
    class ViewMatrix {
        float m_base[3][4] = { 0 };

    public:
        ViewMatrix(float input[3][4]);
        ViewMatrix(Vector3 forward = { }, Vector3 left = { }, Vector3 up = { }, Vector3 origin = { });

        Vector3 GetForwardVector();
        Vector3 GetLeftVector();
        Vector3 GetUpVector();
        Vector3 GetOrigin();

        void SetForwardVector(Vector3 vec);
        void SetLeftVector(Vector3 vec);
        void SetUpVector(Vector3 vec);
        void SetOrigin(Vector3 vec);

        float *operator [](int index);

        ViewMatrix GetTransposedMatrix();
    };
}