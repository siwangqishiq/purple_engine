#include <gtest/gtest.h>
#include "purple.h"
#include "purple_ui.h"

class PurpleUiCustomWidgetTest : public ::testing::Test{
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

TEST_F(PurpleUiCustomWidgetTest,custom_widget_test1){
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

