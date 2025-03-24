#include "test_particle.h"

void TestParticle::onInit(){
    // std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    purple::Log::i("test","TestParticle::onInit");
    unsigned int computeShaderProgram = 
        purple::CreateComputeProgremAsset("shader/compute/compute.glsl");
    purple::Log::i("test","computeShaderProgram : %d", computeShaderProgram);

    int maxWorkGroupInvocations = 0;
    int size_x = 0;
    int size_y = 0;
    int size_z = 0;
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0 , &size_x);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1 , &size_y);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2 , &size_z);
    purple::Log::i("test","GL_MAX_COMPUTE_WORK_GROUP_SIZE(%d, %d, %d)", size_x , size_y, size_z);
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &maxWorkGroupInvocations);
    purple::Log::i("test","GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS = %d" , maxWorkGroupInvocations);
    
    particles = std::make_shared<purple::ParticleGroup>("test", 1024 * 64);
}

void TestParticle::onTick(){
    // testSsbo();
    testParticleUpdate();
}

void TestParticle::onDispose(){
}

void TestParticle::testSsbo(){
    // purple::Log::i("test","TestParticle::testSsbo");
}

void TestParticle::testParticleUpdate(){
    particles->updateAndRender();
}

