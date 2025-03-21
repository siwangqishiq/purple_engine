#include "particle/particle.h"
#include "purple.h"
#include "render/shader.h"
#include "utils.h"

namespace purple{
    ParticleGroup::ParticleGroup(std::string id_, int particleCount_){
        this->id = id_;
        this->particleCount = particleCount_;

        Log::i("particle_group" , "ParticleGroup");
        init();
    }

    void ParticleGroup::init(){
        std::vector<Particle> particleData = prepareData();

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnable(GL_PROGRAM_POINT_SIZE);

        glGenBuffers(1, &ssbo);
        if(ssbo == 0){
            Log::e("particle_group" , "create ssbo buffer failed");
        }
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBufferData(GL_SHADER_STORAGE_BUFFER, particleData.size() * sizeof(Particle),
            particleData.data(), GL_DYNAMIC_COPY);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);

        computeShader = Shader::buildGPUComptuteShaderAssetFile("shader/particle/circle_particles.glsl");
        if(computeShader.programId == 0){
            Log::e("particle_group" , "create compute shader error");
        }
        Log::i("particle_group" , "particle computeShader : %d" , computeShader.programId);

        renderShader = Shader::buildGPUProgramAssetFile("shader/particle/particles_vert.glsl",
            "shader/particle/particles_frag.glsl");
        if(renderShader.programId == 0){
            Log::e("particle_group" , "create renderShader error");
        }
        Log::i("particle_group" , "particle renderShader : %d" , renderShader.programId);
    }

    std::vector<Particle> ParticleGroup::prepareData(){
        std::vector<Particle> particles(particleCount);
        for(int i = 0 ; i < particleCount ; i++){
            particles[i].pos = glm::vec2(RndFloat(-1.0f , 1.0f), RndFloat(-1.0f , 1.0f));
            particles[i].velocity = glm::vec2(RndFloat(-1.0f , 1.0f), RndFloat(-1.0f , 1.0f));
        }//end for i
        return particles;
    }

    void ParticleGroup::updateAndRender(){
        computeShader.useShader();
        // glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
        computeShader.dispathComputeShader(particleCount / 32,1,1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

        renderShader.useShader();
        glBindVertexArray(vao);
        // glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
        glDrawArrays(GL_POINTS, 0, this->particleCount);
        glBindVertexArray(0);
    }

    ParticleGroup::~ParticleGroup(){
        Log::i("particle_group" , "~ParticleGroup");
    }
}