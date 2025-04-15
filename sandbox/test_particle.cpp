#include "test_particle.h"
#include "utils.h"

void TestParticle::onInit(){
    // std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    mTime = purple::currentTimeMillis();

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
    
    particles = std::make_shared<purple::ParticleGroup>("test", 64);

    threadPool = std::make_unique<purple::ThreadPool>(3);

    isEnd.store(false);

    threadPool->enqueue([this]{
        while(!this->isEnd){
            purple::Log::i("test" , "run in thread %d" , std::this_thread::get_id());
        }//end while
    });

    threadPool->enqueue([this]{
        while(!this->isEnd){
            purple::Log::i("test" , "run in thread %d" , std::this_thread::get_id());
        }//end while
    });
}

void TestParticle::onTick(){
    // testSsbo();
    testParticleUpdate();
}

void TestParticle::onDispose(){
    particles->dispose();

    this->isEnd = true;
    threadPool->shutdown();
}

void TestParticle::testSsbo(){
    // purple::Log::i("test","TestParticle::testSsbo");
}

void TestParticle::testParticleUpdate(){
    long t = purple::currentTimeMillis();
    long dtMls = t - mTime;
    mTime = t;
    float dt = dtMls / 1000.0f;
    // std::cout << "dela Time = " << dt << std::endl;
    particles->updateAndRender(dt, -1.0f);
}

