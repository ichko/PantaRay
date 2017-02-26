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

        PinholeCamera& Set(Vector _position, Vector _target, Vector _up = Vector(0, 0, 1)) {
            position = _position;
            target = _target;
            up = _up.Normalize();

            return *this;

        }

        void Begin() {
            auto forward = target.Copy().Subtract(position).Normalize();
            auto left = up.Copy().Cross(forward).Normalize();

            auto left_factor = tanf(fov / 2);
            auto up_factor = left_factor / aspect_ratio;

            auto middle_left = left.Copy().Scale(left_factor);
            auto middle_up = up.Copy().Scale(up_factor);

            top_left = middle_left.Copy().Add(middle_up).Add(forward);
            top_right = left.Copy().Scale(-left_factor).Add(middle_up).Add(forward);
            bottom_left = middle_left.Copy().Add(up.Copy().Scale(-up_factor)).Add(forward);
        }

        Ray GetRay(float x_interpolation, float y_interpolation) {
            return Ray(
                position.Copy(),
                top_left.Copy()
                    .Add(top_right.Copy().Subtract(top_left).Scale(x_interpolation))
                    .Add(bottom_left.Copy().Subtract(top_left).Scale(y_interpolation))
                    .Normalize()
            );
        }

    };

}