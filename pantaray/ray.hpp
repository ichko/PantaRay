#pragma once

#include "vector.hpp"

namespace PantaRay {

    struct Ray {

        Vector start;
        Vector direction;

        Ray(Vector& _start, Vector& _direction) : start(_start), direction(_direction) {}

        Vector ScaleTo(double factor) const {
            return start.Copy().Add(direction.Copy().Scale(factor));
        }

    };

}