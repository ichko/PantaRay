#pragma once

namespace PantaRay {

    template <typename T, typename O> T Cast(O something) {
        return static_cast<T>(something);
    }

}