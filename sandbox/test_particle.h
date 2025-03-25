#pragma once

#include <memory>
#include "purple.h"
#include "particle/group.h"

class TestParticle : public purple::IApp{
public:
    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;

private:
    long mTime = 0;

    std::shared_ptr<purple::ParticleGroup> particles;
    
    void testSsbo();

    void testParticleUpdate();
};
