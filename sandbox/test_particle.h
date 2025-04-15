#pragma once

#include <memory>
#include "purple.h"
#include "particle/group.h"
#include "widget/thread_pool.h"

class TestParticle : public purple::IApp{
public:
    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;
    
private:
    long mTime = 0;

    std::unique_ptr<purple::ThreadPool> threadPool;

    std::shared_ptr<purple::ParticleGroup> particles;

    std::atomic<bool> isEnd = false;
    
    void testSsbo();

    void testParticleUpdate();
};
