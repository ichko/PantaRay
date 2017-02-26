#pragma once

#include "vector.hpp"

namespace PantaRay {

    struct Matrix {

        float data[3][3];

        Vector& Multiply(Vector& vector) {
            auto _x = vector.x * data[0][0] + vector.y * data[1][0] + vector.z * data[2][0];
            auto _y = vector.x * data[0][1] + vector.y * data[1][1] + vector.z * data[2][1];
            auto _z = vector.x * data[0][2] + vector.y * data[1][2] + vector.z * data[2][2];

            vector.x = _x;
            vector.y = _y;
            vector.z = _z;

            return vector;
        }

        Matrix& Rotational(Vector& axis, float angle) {
            float angle_sin = sin(angle);
            float angle_cos = cos(angle);

            data[0][0] = angle_cos + axis.x * axis.x * (1 - angle_cos);
            data[1][0] = axis.x * axis.y * (1 - angle_cos) - axis.z * angle_sin;
            data[2][0] = axis.x * axis.z * (1 - angle_cos) + axis.y * angle_sin;

            data[0][1] = axis.y * axis.x * (1 - angle_cos) + axis.z * angle_sin;
            data[1][1] = angle_cos + axis.y * axis.y * (1 - angle_cos);
            data[2][1] = axis.y * axis.z * (1 - angle_cos) - axis.x * angle_sin;

            data[0][2] = axis.z * axis.x * (1 - angle_cos) - axis.y * angle_sin;
            data[1][2] = axis.z * axis.y * (1 - angle_cos) + axis.x * angle_sin;
            data[1][2] = angle_cos + axis.z * axis.z * (1 - angle_cos);

            return *this;
        }

    };

}