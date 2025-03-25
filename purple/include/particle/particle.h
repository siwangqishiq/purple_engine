#pragma once

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace purple{
    struct Particle{
        glm::vec4 pos;
        glm::vec4 velocity;
        glm::vec4 color;
        int type;
        float size;
        glm::vec2 padding;
    };
}