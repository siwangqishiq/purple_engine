#pragma once

#include <memory>
#include "purple.h"

class TestParticle : public purple::IApp{
public:
    virtual void onInit() override;
    virtual void onTick() override;
    virtual void onDispose() override;

private:
    float mTime = 0.0f;
    
    void testSsbo();
};
