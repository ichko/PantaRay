#pragma once

#include <math.h>
#include "constants.hpp"

namespace PantaRay {

    struct Vector {

        float x, y, z;

        Vector(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}

        void MakeZero() {
            x = y = z = 0;
        }

        bool IsZero(float eps = Constants::eps) {
            return Length() < eps;
        }

        float LengthSqr() {
            return x * x + y * y + z * z;
        }

        float Length() {
            return sqrt(LengthSqr());
        }

        Vector& Scale(float factor) {
            x *= factor;
            y *= factor;
            z *= factor;

            return *this;
        }

        Vector& Add(const Vector& vector) {
            x += vector.x;
            y += vector.y;
            z += vector.z;

            return *this;
        }

        Vector& Subtract(const Vector& vector) {
            Add(vector.Copy().Reflect());

            return *this;
        }

        Vector& Reflect() {
            x = -x;
            y = -y;
            z = -z;

            return *this;
        }

        float Dot(const Vector& vector) {
            return x * vector.x + y * vector.y + z * vector.z;
        }

        Vector& Normalize() {
            float length = Length();
            x /= length;
            y /= length;
            z /= length;

            return *this;
        }

        Vector Copy() const {
            return Vector(x, y, z);
        }

    };

}