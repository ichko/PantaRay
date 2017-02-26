#pragma once

#include "vector.hpp"


namespace PantaRay {

    struct Intersection {

        Vector position;
        Vector normal;
        float distance;
        float u, v;

    };

}