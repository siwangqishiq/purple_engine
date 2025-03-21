#pragma once

#include <string>
#include "glm/vec2.hpp"
#include <vector>
#include "render/shader.h"

namespace purple{
    struct Particle{
        glm::vec2 pos;
        glm::vec2 velocity;
    };

    class ParticleGroup{
    public:
        ParticleGroup(std::string id_, int particleCount_);
        ~ParticleGroup();
        
        void init();
        void updateAndRender();
    protected:
        int particleCount;
    private:
        std::string id;
        GLuint ssbo = 0;
        GLuint vao;

        Shader computeShader;
        Shader renderShader;

        std::vector<Particle> prepareData();
    };
}

