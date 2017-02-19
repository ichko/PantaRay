#pragma once

#include "vector.hpp"


namespace PantaRay {

    struct Intersection {

        Vector position;
        Vector normal;
        double distance;
        double u, v;

    };

}