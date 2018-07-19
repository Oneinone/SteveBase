#include <GlobalDefines.hpp>
#include <maths/ViewMatrix.hpp>

#include <maths/Vector3.hpp>

#include <cstring>

#pragma message ("warning: unfinished")

namespace SteveBase::Maths {

    enum {
        FORWARD,
        LEFT,
        UP,
        ORIGIN
    };

    ViewMatrix::ViewMatrix(float input[3][4]) {
        // treating base and input as linear memory
        memcpy((float*)m_base, (float*)input, sizeof(float) * 3 * 4);
    }

    ViewMatrix::ViewMatrix(Vector3 forward, Vector3 left, Vector3 up, Vector3 origin) {
        SetForwardVector(forward);
        SetLeftVector(left);
        SetUpVector(up);
        SetOrigin(origin);
    }

    Vector3 ViewMatrix::GetForwardVector() {
        return Vector3(
            m_base[0][FORWARD], // x
            m_base[1][FORWARD], // y
            m_base[2][FORWARD]  // z
        );
    }
    Vector3 ViewMatrix::GetLeftVector() {
        return Vector3(
            m_base[0][LEFT], // x
            m_base[1][LEFT], // y
            m_base[2][LEFT]  // z
        );
    }
    Vector3 ViewMatrix::GetUpVector() {
        return Vector3(
            m_base[0][UP], // x
            m_base[1][UP], // y
            m_base[2][UP]  // z
        );
    }
    Vector3 ViewMatrix::GetOrigin() {
        return Vector3(
            m_base[0][ORIGIN], // x
            m_base[1][ORIGIN], // y
            m_base[2][ORIGIN]  // z
        );
    }
    void ViewMatrix::SetForwardVector(Vector3 vec) {
        m_base[0][FORWARD] = vec.X();
        m_base[1][FORWARD] = vec.Y();
        m_base[2][FORWARD] = vec.Z();
    }
    void ViewMatrix::SetLeftVector(Vector3 vec) {
        m_base[0][LEFT] = vec.X();
        m_base[1][LEFT] = vec.Y();
        m_base[2][LEFT] = vec.Z();
    }
    void ViewMatrix::SetUpVector(Vector3 vec) {
        m_base[0][UP] = vec.X();
        m_base[1][UP] = vec.Y();
        m_base[2][UP] = vec.Z();
    }
    void ViewMatrix::SetOrigin(Vector3 vec) {
        m_base[0][ORIGIN] = vec.X();
        m_base[1][ORIGIN] = vec.Y();
        m_base[2][ORIGIN] = vec.Z();
    }

    float *ViewMatrix::operator[](int index) {
        return m_base[index];
    }

    // Direct copypaste of https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/mathlib/mathlib_base.cpp#L1157
    ViewMatrix ViewMatrix::GetTransposedMatrix() {
        ViewMatrix copy = *this;

        // ignoring origin
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                copy[i][j] = (*this)[j][i];
            }
        }

        copy.SetOrigin({ 0, 0, 0 });

        return copy;
    }
}
