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

        float LengthSqr() const {
            return x * x + y * y + z * z;
        }

        float Length() const {
            return sqrtf(LengthSqr());
        }

        Vector& Scale(float factor) {
            x *= factor;
            y *= factor;
            z *= factor;

            return *this;
        }

        Vector& ScaleTo(float factor) {
            Normalize();
            return Scale(factor);
        }

        Vector& Add(const Vector& vector) {
            x += vector.x;
            y += vector.y;
            z += vector.z;

            return *this;
        }

        Vector& Subtract(const Vector& vector) {
            x -= vector.x;
            y -= vector.y;
            z -= vector.z;

            return *this;
        }

        Vector& Reflect() {
            x = -x;
            y = -y;
            z = -z;

            return *this;
        }

        Vector& Cross(const Vector& vector) {
            auto _x = y * vector.z - z * vector.y;
            auto _y = z * vector.x - x * vector.z;
            auto _z = x * vector.y - y * vector.x;

            x = _x;
            y = _y;
            z = _z;

            return *this;
        }

        Vector& Reflect(const Vector& normal) {
            Subtract(normal.Copy().Scale(normal.Dot(*this) * 2));
            return *this;
        }

        float Dot(const Vector& vector) const {
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