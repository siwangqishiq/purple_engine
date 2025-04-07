#pragma once

#include <string>
#include <vector>
#include "render/shader.h"
#include "particle/particle.h"

namespace purple{
    class ParticleGroup{
    public:
        ParticleGroup(std::string id_, int particleCount_);
        ~ParticleGroup();
        
        void init();

        void updateAndRender(float deltaTime, float depth);
        void update(float deltaTime);
        void render(float depth);
        void dispose();
    protected:
        int particleCount;
    private:
        std::string id;
        GLuint ssbo = 0;
        GLuint vao = 0;

        Shader computeShader;
        Shader renderShader;
        
        std::vector<Particle> prepareData();
    };
}

