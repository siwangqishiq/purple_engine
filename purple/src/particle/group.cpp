#include "particle/group.h"
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

        float viewWidth = purple::Engine::ScreenWidth;
        float viewHeight = purple::Engine::ScreenHeight;
        glm::vec2 p(0.0f, 0.0f);
        float k = viewHeight / viewWidth;
        float step = viewWidth / particleCount;

        for(int i = 0 ; i < particleCount ; i++){
            // particles[i].pos = glm::vec4(RndFloat(-1.0f , 1.0f), RndFloat(-1.0f , 1.0f), 
            //     purple::Engine::getRenderEngine()->getAndChangeDepthValue() , 1.0f);
            particles[i].pos = glm::vec4(step * i, step * i * k , 0.0f , 1.0f);
            particles[i].color = glm::vec4(
                RndFloat(0.0f , 1.0f),
                RndFloat(0.0f , 1.0f),
                RndFloat(0.0f , 1.0f),
                RndFloat(0.0f , 1.0f)
            );
            particles[i].velocity = 100.0f * glm::vec4(RndFloat(-1.0f , 1.0f), 
                RndFloat(-1.0f , 1.0f) , 0.0f , 0.0f);

            particles[i].size = 100.0f;
            particles[i].type = 1;
        }//end for i
        return particles;
    }

    void ParticleGroup::updateAndRender(float deltaTime, float depth){
        update(deltaTime);
        depth = purple::Engine::getRenderEngine()->getAndChangeDepthValue();
        render(depth);
    }

    void ParticleGroup::update(float deltaTime){
        computeShader.useShader();
        computeShader.setUniformFloat("dt" , deltaTime);
        computeShader.setUniformVec2("viewSize", 
            glm::vec2(Engine::ScreenWidth , Engine::ScreenHeight));
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
        computeShader.dispathComputeShader(particleCount,1,1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    }

    void ParticleGroup::render(float depth){
        glDepthMask(GL_FALSE); // 禁止写入深度缓冲区
        glBindVertexArray(vao);
        renderShader.useShader();
        renderShader.setUniformFloat("depth",depth);
        renderShader.setUniformMat3("transMat" , 
            Engine::getRenderEngine()->normalMatrix_);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
        glDrawArrays(GL_POINTS, 0, this->particleCount);
        glBindVertexArray(0);
        glDepthMask(GL_TRUE);  // 恢复深度写入
    }

    void ParticleGroup::dispose(){
        Log::i("particle_group" , "dispose()");
        if(vao != 0){
            GLuint ids[1];
            ids[0] = vao;
            glDeleteVertexArrays(1, ids);
        }
        if(ssbo != 0){
            GLuint ids[1];
            ids[0] = ssbo;
            glDeleteBuffers(1 , ids);
        }
        computeShader.deleteSelf();
        renderShader.deleteSelf();
    }

    ParticleGroup::~ParticleGroup(){
        Log::i("particle_group" , "~ParticleGroup");
    }
}