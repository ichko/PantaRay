#include "../hpp/camera.hpp"

namespace PantaRay {

    PinholeCamera& PinholeCamera::Set(Vector _position, Vector _target, Vector _up) {
        position = _position;
        target = _target;
        up = _up.Normalize();

        return *this;
    }

    void PinholeCamera::Begin() {
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

    Ray PinholeCamera::GetRay(float x_interpolation, float y_interpolation) {
        return Ray(
            position.Copy(),
            top_left.Copy()
            .Add(top_right.Copy().Subtract(top_left).Scale(x_interpolation))
            .Add(bottom_left.Copy().Subtract(top_left).Scale(y_interpolation))
            .Normalize()
        );
    }

}
