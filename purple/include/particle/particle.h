#pragma once

#include <string>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include <vector>
#include "render/shader.h"

namespace purple{

    struct Particle{
        glm::vec3 pos;
        float _padding0;
        glm::vec3 velocity;
        float _padding1;
        glm::vec4 color;
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

