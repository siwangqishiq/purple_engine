//
// Created by panyi on 2024/4/28.
//

#include "AndroidApplication.h"
#include "test1_app.h"
#include "test_render_text.h"
#include "test_ui.h"
#include "test_ui_img.h"
#include "test_ui_text.h"
#include "input/input_manager.h"
#include <thread>
#include <string>
#include <vector>

void AndroidApplication::init(){
    purple::Engine::init(width , height);

    // appInstanceList.push_back(std::make_shared<Test1App>());
    // appInstanceList.push_back(std::make_shared<TestTextRender>());
//     appInstanceList.push_back(std::make_shared<TestUi>());
     appInstanceList.push_back(std::make_shared<TestImgUi>());
//    appInstanceList.push_back(std::make_shared<TestTextUi>());
    
    for(std::shared_ptr<purple::IApp> &app : appInstanceList){
        app->onInit();
    }

    purple::Engine::getTimer()->scheduleAtFixedRate([this](void *app){
        std::string fpsStr = "fps : " + std::to_string(fps);
        purple::Log::w("fps" , fpsStr);
        fps = 0;
    } , 1000L);
}

void AndroidApplication::tick(){
    purple::Engine::tick();
    for(std::shared_ptr<purple::IApp> &app : appInstanceList){
        app->onTick();
    }
    fps++;
}

void AndroidApplication::dispose(){
    for(std::shared_ptr<purple::IApp> &app : appInstanceList){
        app->onDispose();
    }
    purple::Engine::dispose();
}

void AndroidApplication::resize(int w , int h) {
    this->width = w;
    this->height = h;
    purple::Engine::init(w , h);
}

void AndroidApplication::onTouchEvent(int action , float x , float y){
    int inputAction = 0;
    switch (action) {
        case 0://down
            inputAction = purple::EVENT_ACTION_BEGIN;
            break;
        case 1:
            inputAction = purple::EVENT_ACTION_END;
            break;
        case 2://move
            inputAction = purple::EVENT_ACTION_MOVE;
            break;
        case 3://cancel
            inputAction = purple::EVENT_ACTION_CANCEL;
            break;
        default:
            break;
    }

    purple::InputEvent event;
    event.action = inputAction;
    event.x = x;
    event.y = purple::Engine::ScreenHeight - y;

    purple::InputManager::getInstance()->onEvent(event);
}