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
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);

        std::vector<Particle> particleData = prepareData();

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

#ifndef __ANDROID__
        glEnable(GL_PROGRAM_POINT_SIZE);
#endif

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
        // float depth = purple::Engine::getRenderEngine()->getAndChangeDepthValue();
        // std::cout << "depth = " << depth << std::endl;
        for(int i = 0 ; i < particleCount ; i++){
            particles[i].pos = glm::vec3(RndFloat(-1.0f , 1.0f), RndFloat(-1.0f , 1.0f), purple::Engine::getRenderEngine()->getAndChangeDepthValue());
            // particles[i].velocity = glm::vec3(0.0f, 0.0f ,0.0f);
            particles[i].color = glm::vec4(RndFloat(0.0f , 1.0f),
                RndFloat(0.0f , 1.0f),RndFloat(0.0f , 1.0f),RndFloat(0.0f , 1.0f));
            // std::cout << "particle pos: " << particles[i].pos[0] << " " << particles[i].pos[1]
            //     << " " << particles[i].pos[2] << std::endl;
            // std::cout << "particle color: " << particles[i].color[0] 
            //     << " " << particles[i].color[1]
            //     << " " << particles[i].color[2]
            //     << " " << particles[i].color[3] << std::endl;
             particles[i].velocity = 0.01f * glm::vec3(RndFloat(-1.0f , 1.0f), RndFloat(-1.0f , 1.0f) , 0.0f);
        }//end for i
        return particles;
    }

    void ParticleGroup::updateAndRender(){
        computeShader.useShader();
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
        computeShader.dispathComputeShader(particleCount,1,1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

        renderShader.useShader();
        glBindVertexArray(vao);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
        glDrawArrays(GL_POINTS, 0, this->particleCount);
        glBindVertexArray(0);
    }

    ParticleGroup::~ParticleGroup(){
        Log::i("particle_group" , "~ParticleGroup");
        computeShader.deleteSelf();
        renderShader.deleteSelf();
    }
}