#pragma once

#include "vector.hpp"


namespace PantaRay {

    struct Mesh;

    struct Intersection {

        Vector position;
        Vector normal;
        Mesh* mesh;
        float distance;
        float u, v;

    };

}
