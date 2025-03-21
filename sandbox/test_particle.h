#pragma once

#include <memory>
#include "purple.h"
#include "particle/particle.h"

class TestParticle : public purple::IApp{
public:
    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;

private:
    float mTime = 0.0f;

    std::shared_ptr<purple::ParticleGroup> particles;
    
    void testSsbo();

    void testParticleUpdate();
};
