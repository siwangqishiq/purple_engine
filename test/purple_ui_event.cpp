#include <gtest/gtest.h>
#include "purple.h"
#include "purple_ui.h"

class PurpleUiEventTest : public ::testing::Test{
public:
    const int screenWidth = 1280;
    const int screenHeight = 800;
    std::shared_ptr<purple::UiRoot> uiRoot = nullptr;
    
protected:
    void SetUp() override {
        purple::UNITTEST = true;
        purple::Engine::init(screenWidth , screenHeight);   
    }

    void TearDown() override {
        uiRoot = nullptr;
        purple::Engine::dispose();
    }
};

TEST_F(PurpleUiEventTest,event_test_click1){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);
    uiRoot->startRenderUI();

    std::vector<purple::InputEvent> inputSeq = {
        {EVENT_ACTION_BEGIN, 100,100 ,0 , nullptr},
        {EVENT_ACTION_END, 101,101 ,0 , nullptr},
    };

    bool isClicked = false;
    container->setClick<StackContainer>([&isClicked](InputEvent &e){
        isClicked = true;
    });
    
    for(auto &event : inputSeq){
        uiRoot->dispatchInputEvent(event);
    }//end for each

    EXPECT_EQ(isClicked, true);
}

TEST_F(PurpleUiEventTest,event_test_click2){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);
    uiRoot->startRenderUI();

    std::vector<purple::InputEvent> inputSeq = {
        {EVENT_ACTION_BEGIN, 100,100 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,100 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,100 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,100 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,100 ,0 , nullptr},
        {EVENT_ACTION_CANCEL, 100,100 ,0 , nullptr},
    };

    bool isClicked = false;
    container->setClick<StackContainer>([&isClicked](InputEvent &e){
        isClicked = true;
    });
    
    for(auto &event : inputSeq){
        uiRoot->dispatchInputEvent(event);
    }//end for each

    EXPECT_EQ(isClicked, false);
    
    std::vector<purple::InputEvent> inputSeq2 = {
        {EVENT_ACTION_BEGIN, 100,100 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,100 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,100 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,100 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,100 ,0 , nullptr},
        {EVENT_ACTION_END, 100,100 ,0 , nullptr},
    };

    for(auto &event : inputSeq2){
        uiRoot->dispatchInputEvent(event);
    }//end for each
    EXPECT_EQ(isClicked, true);
}

TEST_F(PurpleUiEventTest,event_test_container_click){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    auto widget1 = std::make_shared<Widget>(LAYOUT_MATCH_PARENT,200);
    widget1->setId<Widget>("widget1");

    container->addChild(widget1);

    auto widget2 = std::make_shared<Widget>(100,100);
    widget2->setId<Widget>("widget2");
    container->addChild(widget2);

    bool isWidget1Clicked = false;
    widget1->setClick<Widget>([&isWidget1Clicked](InputEvent &event){
        isWidget1Clicked = true;
    });

    bool isWidget2Clicked = false;
    widget2->setClick<Widget>([&isWidget2Clicked](InputEvent &event){
        isWidget2Clicked = true;
    });

    uiRoot->startRenderUI();

    std::vector<purple::InputEvent> inputSeq = {
        {EVENT_ACTION_BEGIN, 100,700 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,700 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,700 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,700 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,700 ,0 , nullptr},
        {EVENT_ACTION_END, 100,700 ,0 , nullptr},
    };
    for(auto &event : inputSeq){
        uiRoot->dispatchInputEvent(event);
    }//end for each
    EXPECT_EQ(isWidget1Clicked, true);

    std::vector<purple::InputEvent> inputSeq2 = {
        {EVENT_ACTION_BEGIN, 100,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 100,550 ,0 , nullptr},
        {EVENT_ACTION_END, 100,550 ,0 , nullptr},
    };
    for(auto &event : inputSeq2){
        uiRoot->dispatchInputEvent(event);
    }//end for each
    EXPECT_EQ(isWidget2Clicked, true);
}

TEST_F(PurpleUiEventTest,event_test_container_click2){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    auto widget1 = std::make_shared<Widget>(LAYOUT_MATCH_PARENT,200);
    widget1->setId<Widget>("widget1");

    container->addChild(widget1);

    auto widget2 = std::make_shared<Widget>(100,100);
    widget2->setId<Widget>("widget2");
    container->addChild(widget2);

    bool isWidget1Clicked = false;
    widget1->setClick<Widget>([&isWidget1Clicked](InputEvent &event){
        isWidget1Clicked = true;
    });

    bool isWidget2Clicked = false;
    widget2->setClick<Widget>([&isWidget2Clicked](InputEvent &event){
        isWidget2Clicked = true;
    });

    bool containerClicked = false;
    container->setClick<ColumContainer>([&containerClicked](InputEvent &event){
        containerClicked = true;
    });

    uiRoot->startRenderUI();

    std::vector<purple::InputEvent> inputSeq = {
        {EVENT_ACTION_BEGIN, 150,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 150,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 150,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 150,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 150,550 ,0 , nullptr},
        {EVENT_ACTION_END, 150,550 ,0 , nullptr},
    };
    for(auto &event : inputSeq){
        uiRoot->dispatchInputEvent(event);
    }//end for each

    EXPECT_EQ(isWidget1Clicked, false);
    EXPECT_EQ(isWidget2Clicked, false);
    EXPECT_EQ(containerClicked, true);
}

TEST_F(PurpleUiEventTest,event_test_container_click3){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    auto widget1 = std::make_shared<Widget>(LAYOUT_MATCH_PARENT,200);
    widget1->setId<Widget>("widget1");

    container->addChild(widget1);

    auto widget2 = std::make_shared<Widget>(100,100);
    widget2->setId<Widget>("widget2");
    container->addChild(widget2);

    bool isWidget1Clicked = false;
    widget1->setClick<Widget>([&isWidget1Clicked](InputEvent &event){
        isWidget1Clicked = true;
    });

    bool isWidget2Clicked = false;
    widget2->setClick<Widget>([&isWidget2Clicked](InputEvent &event){
        isWidget2Clicked = true;
    });

    bool containerClicked = false;
    container->setClick<ColumContainer>([&containerClicked](InputEvent &event){
        containerClicked = true;
    });

    uiRoot->startRenderUI();

    std::vector<purple::InputEvent> inputSeq = {
        {EVENT_ACTION_BEGIN, 60,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 62,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 60,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 60,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 60,550 ,0 , nullptr},
        {EVENT_ACTION_END, 63,550 ,0 , nullptr},
    };
    for(auto &event : inputSeq){
        uiRoot->dispatchInputEvent(event);
    }//end for each

    EXPECT_EQ(isWidget1Clicked, false);
    EXPECT_EQ(isWidget2Clicked, true);
    EXPECT_EQ(containerClicked, false);
}

TEST_F(PurpleUiEventTest,event_test_container_moveout){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    auto widget1 = std::make_shared<Widget>(LAYOUT_MATCH_PARENT,200);
    widget1->setId<Widget>("widget1");

    container->addChild(widget1);

    auto widget2 = std::make_shared<Widget>(100,100);
    widget2->setId<Widget>("widget2");
    container->addChild(widget2);

    bool isWidget1Clicked = false;
    widget1->setClick<Widget>([&isWidget1Clicked](InputEvent &event){
        isWidget1Clicked = true;
    });

    bool isWidget2Clicked = false;
    widget2->setClick<Widget>([&isWidget2Clicked](InputEvent &event){
        isWidget2Clicked = true;
    });

    bool containerClicked = false;
    container->setClick<ColumContainer>([&containerClicked](InputEvent &event){
        containerClicked = true;
    });

    uiRoot->startRenderUI();

    std::vector<purple::InputEvent> inputSeq = {
        {EVENT_ACTION_BEGIN, 60,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 120,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 60,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 60,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 60,550 ,0 , nullptr},
        {EVENT_ACTION_END, 63,550 ,0 , nullptr},
    };
    for(auto &event : inputSeq){
        uiRoot->dispatchInputEvent(event);
    }//end for each

    EXPECT_EQ(isWidget1Clicked, false);
    EXPECT_EQ(isWidget2Clicked, false);
    EXPECT_EQ(containerClicked, false);
}


TEST_F(PurpleUiEventTest,event_test_container_moveout2){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    auto widget1 = std::make_shared<Widget>(LAYOUT_MATCH_PARENT,200);
    widget1->setId<Widget>("widget1");

    container->addChild(widget1);

    auto widget2 = std::make_shared<Widget>(100,100);
    widget2->setId<Widget>("widget2");
    container->addChild(widget2);

    bool isWidget1Clicked = false;
    widget1->setClick<Widget>([&isWidget1Clicked](InputEvent &event){
        isWidget1Clicked = true;
    });

    bool isWidget2Clicked = false;
    widget2->setClick<Widget>([&isWidget2Clicked](InputEvent &event){
        isWidget2Clicked = true;
    });

    bool containerClicked = false;
    container->setClick<ColumContainer>([&containerClicked](InputEvent &event){
        containerClicked = true;
    });

    uiRoot->startRenderUI();

    std::vector<purple::InputEvent> inputSeq = {
        {EVENT_ACTION_BEGIN, 60,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 60,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 60,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 60,550 ,0 , nullptr},
        {EVENT_ACTION_MOVE, 60,550 ,0 , nullptr},
        {EVENT_ACTION_END, 120,550 ,0 , nullptr},
    };
    for(auto &event : inputSeq){
        uiRoot->dispatchInputEvent(event);
    }//end for each

    EXPECT_EQ(isWidget1Clicked, false);
    EXPECT_EQ(isWidget2Clicked, false);
    EXPECT_EQ(containerClicked, false);
}
