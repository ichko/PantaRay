#pragma once

#include "vector.hpp"

namespace PantaRay {

    struct Ray {

        Vector start;
        Vector direction;
        unsigned recursion_depth;


        Ray(Vector& _start, Vector& _direction, unsigned _recursion_depth = 0) :
            start(_start), direction(_direction), recursion_depth(_recursion_depth) {
        }

        Vector ScaleTo(float factor) const {
            return start.Copy().Add(direction.Copy().Scale(factor));
        }

        Ray Copy() const {
            return Ray(start.Copy(), direction.Copy(), recursion_depth);
        }

        Ray& Translate(float& factor) {
            start.Add(direction.Copy().Scale(factor));
            return *this;
        }

    };

}
