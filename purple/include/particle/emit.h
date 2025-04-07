#pragma once

namespace purple{
    class ParticleEmit{
    public:
        ParticleEmit();

        ~ParticleEmit();

    private:
        int maxParticleCount;
        int minParticleCount;
    };
}
