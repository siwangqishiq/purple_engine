
#pragma once

#include "log.h"
#include <memory>
#include "render/common.h"
#include "render/render.h"
#include "render/render_batch.h"
#include "widget/timer.h"
#include "render/texture.h"
#include "render/sprite.h"
#include "json.h"
#include "audio/audio.h"
#include "input/input_common.h"
#include <cmath>


namespace purple{
    
    const bool isDebug = true;

    enum Platform{
        Unknow = -1,
        Android,
        iOS,
        Windows,
        Mac_x86,
        Mac_arm64,
        Linux,
        Raspi
    };

    extern Platform platform;
    
    Platform DetectPlatform();

    extern bool UNITTEST;

    struct InitParams{
        glm::vec4 clearColor = glm::vec4(1.0f , 1.0f , 1.0f , 1.0f);
    };

    class IApp{
    public:
        virtual void onInit() = 0;
        virtual void onTick() = 0;
        virtual void onDispose() = 0;
        virtual void onResize(int w, int h){}
    };

    class RenderEngine;
    class Engine{
    public:
        static const char *TAG;
        static int ScreenWidth;
        static int ScreenHeight;
        
        static void init(int width , int height);

        static void init(int width , int height , InitParams& params);

        static void dispose();

        static void tick();

        static void resize(int w , int h);

        static std::shared_ptr<RenderEngine> getRenderEngine();

        static std::shared_ptr<Timer> getTimer();

        static int vpTopx(float vpSize);
        
        //导出图片
        static int exportImageFile(std::string path ,int left , int top , 
                int width , int height);
    private:
        static std::shared_ptr<RenderEngine> renderEngine_;
        static std::shared_ptr<Timer> timer_;

        static float dpSize;
            
        static void calculateDpSize(){
            double totalSize = sqrt(ScreenWidth * ScreenWidth + ScreenHeight * ScreenHeight);
            Engine::dpSize = totalSize / 1000.0f;
        }
    };
}

