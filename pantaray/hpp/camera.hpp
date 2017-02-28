#pragma once

#include "ray.hpp"

namespace PantaRay {

    struct ICamera {

        virtual void Begin() = 0;

        virtual Ray GetRay(float x_interpolation, float y_interpolation) = 0;

        virtual ~ICamera() {}

    };


    class PinholeCamera : public ICamera {

        Vector top_left;
        Vector top_right;
        Vector bottom_left;

        Vector position;
        Vector target;
        Vector up;

        float fov;
        float aspect_ratio;

    public:
        PinholeCamera(float _fov, float _aspect_ratio) : fov(_fov), aspect_ratio(_aspect_ratio) {}

        PinholeCamera& Set(Vector _position, Vector _target, Vector _up = Vector(0, 0, 1));

        void Begin();

        Ray GetRay(float x_interpolation, float y_interpolation);

    };

}
