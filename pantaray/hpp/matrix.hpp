#pragma once

#include "vector.hpp"


namespace PantaRay {

    struct Matrix {

        float data[3][3];

        Vector& Multiply(Vector& vector);

        Matrix& Rotational(Vector& axis, float angle);

    };

}
