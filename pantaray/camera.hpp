#pragma once

#include "ray.hpp"

namespace PantaRay {

    struct ICamera {

        virtual void Begin() = 0;

        virtual Ray GetRay(double x_interpolation, double y_interpolation) = 0;

        virtual ~ICamera() {}

    };


    class PinholåCamera : public ICamera {

        Vector top_left;
        Vector top_right;
        Vector bottom_left;

        Vector position;
        Vector target;
        Vector up;

        double fov;
        double aspect_ratio;

    public:
        PinholåCamera(double _fov, double _aspect_ratio) : fov(_fov), aspect_ratio(_aspect_ratio) {}

        void Setup(Vector _position, Vector _target, Vector _up = Vector(0, 0, 1)) {
            position = _position;
            target = _target.Normalize();
            up = _up.Normalize();
        }

        void Begin() {
            auto forward = target.Copy().Subtract(position);
            auto left = forward.Copy().Cross(up).Normalize();

            auto left_factor = forward.Length() * tan(fov / 2);
            auto up_factor = left_factor / aspect_ratio;

            auto middle_left = left.Copy().Scale(left_factor);
            auto middle_up = up.Copy().Scale(up_factor);

            top_left = middle_left.Copy().Add(middle_up);
            top_right = left.Copy().Scale(-left_factor).Add(middle_up);
            bottom_left = middle_left.Copy().Add(up.Copy().Scale(-up_factor));
        }

        Ray GetRay(double x_interpolation, double y_interpolation) {
            auto _top_right = top_right.Copy();
            return Ray(
                position.Copy(),
                _top_right
                    .Copy()
                    .Subtract(top_left)
                    .ScaleTo(x_interpolation)
                    .Add(_top_right
                        .Copy()
                        .Subtract(bottom_left)
                        .ScaleTo(y_interpolation)
                    )
            );
        }

    };

}