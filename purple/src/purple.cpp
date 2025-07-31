
#include "purple.h"
#include "log.h"
#include "render/render.h"
#include "audio/audio.h"
#include <stdio.h>
#include "widget/timer.h"
#include <algorithm>
#include "utils.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

namespace purple{
    const char* purple::Engine::TAG = "purple";

    std::shared_ptr<RenderEngine> purple::Engine::renderEngine_ = nullptr;
    std::shared_ptr<Timer> purple::Engine::timer_ = nullptr;

    int purple::Engine::ScreenWidth = 0;
    int purple::Engine::ScreenHeight = 0;
    float purple::Engine::dpSize = 1.0f;

    bool UNITTEST = false;

    Platform platform = Unknow;

    Platform DetectPlatform() {
        if(platform != Unknow){
            return platform;
        }

        #ifdef __APPLE__
        #if TARGET_OS_IPHONE
            platform = iOS;
        #elif TARGET_OS_MAC
            platform = Mac_x86;
            #if defined(__arm64__) || defined(__aarch64__)
                platform = Mac_arm64;
            #elif defined(__x86_64__) || defined(__i386__)
                platform = Mac_x86;
            #else
                platform = Unknow;
            #endif
        #else
            platform = Unknow;
        #endif
        #elif defined(_WIN32)
            platform = Windows;
        #elif defined(__ANDROID__)
            platform = Android;
        #elif defined(__linux__)
        // 默认认为是 Linux 环境
        bool is_raspberry_pi = false;

        // 检测是否为 Raspberry Pi
        std::ifstream cpuinfo("/proc/cpuinfo");
        if (cpuinfo.is_open()) {
            std::string line;
            while (std::getline(cpuinfo, line)) {
                if (line.find("Raspberry Pi") != std::string::npos) {
                    is_raspberry_pi = true;
                    break;
                }
            }
            cpuinfo.close();
        }

        if (is_raspberry_pi) {
            platform = Raspi;
        } else {
            platform = Linux;
        }
        #else
            platform = Unknow;
        #endif
        return platform;
    }


    void Engine::init(int width , int height){
        InitParams params;
        init(width , height , params);
    }

    void Engine::init(int width , int height , InitParams& params){
        Log::w(TAG,"init engine");
        long startTime = currentTimeMillis();
        ScreenWidth = width;
        ScreenHeight = height;
        
        Log::w(TAG,"init screen size: %d  , %d" , ScreenWidth , ScreenHeight);

        if(UNITTEST){
            return;
        }
        
        renderEngine_ = std::make_shared<RenderEngine>();
        renderEngine_->init(params);
        renderEngine_->onScreenResize();

        // std::cout << " error init2 : " << glGetError() << std::endl;
        
        AudioManager::getInstance()->init();
        
        long endTime = currentTimeMillis();
        Log::w(TAG , "purple engine start time : %ld ms" , endTime - startTime);
    }
    
    void Engine::resize(int w , int h){
        if(ScreenWidth == w && ScreenHeight == h){
            return;
        }

        ScreenWidth = w;
        ScreenHeight = h;
        Log::w(TAG , "scren resize %d x %d" , w , h);
        calculateDpSize();

        if(renderEngine_ == nullptr){
            renderEngine_ = std::make_shared<RenderEngine>();
        }
        renderEngine_->onScreenResize();
    }

    int Engine::vpTopx(float vpSize){
        return vpSize * dpSize;
    }

    void Engine::tick(){
        renderEngine_->resetDepth();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(timer_ != nullptr){
            timer_->trick();
        }

        if(renderEngine_->vramManager_ != nullptr){ //显存缓存清空
            renderEngine_->vramManager_->onPostRender();
            renderEngine_->getShapeBatch()->getVRamManager()->onPostRender();
            renderEngine_->getSpriteBatch()->getVRamManager()->onPostRender();
        }
    }


    void Engine::dispose(){
        if(UNITTEST){
            return;
        }

        Log::w(TAG,"engine dispose");
        if(renderEngine_ != nullptr){
            renderEngine_->free();
        }
        if(timer_ != nullptr){
            timer_->clear();
        }
    }

    std::shared_ptr<RenderEngine> Engine::getRenderEngine(){
        return renderEngine_;
    }

    std::shared_ptr<Timer> Engine::getTimer(){
        if(timer_ == nullptr){
            timer_ = std::make_shared<Timer>();
        }

        return timer_;
    }

    //将引擎绘制内容 导出为图片
    int Engine::exportImageFile(std::string path ,int left , int bottom, int width , int height){
        Log::i("purple_engine" , "export image : %d, %d , %d , %d"
            , left , bottom , width , height);
        if(left < 0 || bottom < 0 || width <= 0 || height <= 0){
            Log::e("purple_engine" , "export image error invalied param : %d, %d , %d , %d"
                , left , bottom , width , height);
            return -1;
        }

        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadBuffer(GL_BACK);
        const int channel = 3;
        const int size = channel * width * height;
        std::vector<uint8_t> pixels(size);
        glReadPixels(left , bottom , width , height,
                    GL_RGB , GL_UNSIGNED_BYTE , pixels.data());
        for(int line = 0; line != height/2; ++line) {
            std::swap_ranges(pixels.begin() + 3 * width * line,
                             pixels.begin() + 3 * width * (line+1),
                             pixels.begin() + 3 * width * (height-line-1));
        }//end for line
        stbi_write_png(path.c_str() , width, height, channel , pixels.data() , channel * width);
        return 0;    
    }
}