#pragma once

#include "vector.hpp"

namespace PantaRay {

    struct Ray {

        Vector start;
        Vector direction;
        unsigned recursion_depth;


        Ray(Vector& _start, Vector& _direction) :
            start(_start), direction(_direction), recursion_depth(0) {
        }

        Vector ScaleTo(float factor) const {
            return start.Copy().Add(direction.Copy().Scale(factor));
        }

    };

}
