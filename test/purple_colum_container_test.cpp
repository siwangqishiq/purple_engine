#include <gtest/gtest.h>
#include "purple.h"
#include "purple_ui.h"

std::shared_ptr<purple::UiRoot> uiRoot = nullptr;

class PurpleUiColumContainerTest : public ::testing::Test{
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

TEST_F(PurpleUiColumContainerTest,colum_container_test_width_set){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_MATCH_PARENT,LAYOUT_WRAP_CONTENT);
    uiRoot->setRootContainer(container);

    uiRoot->startRenderUI();

    EXPECT_EQ(purple::Engine::ScreenWidth , container->getWidth());
}

TEST_F(PurpleUiColumContainerTest,colum_container_test_width_warpcontent){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    uiRoot->setRootContainer(container);

    auto child1 = std::make_shared<Widget>(100 , 200);
    container->addChild(child1);

    auto child2 = std::make_shared<Widget>(200 , 200);
    container->addChild(child2);

    auto child3 = std::make_shared<Widget>(300 , 200);
    container->addChild(child3);

    uiRoot->startRenderUI();
    
    EXPECT_EQ(300 , container->getWidth());
}

TEST_F(PurpleUiColumContainerTest,colum_container_test_width_warpcontent_padding){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    container->setPadding<ColumContainer>(20,10,30,10);

    uiRoot->setRootContainer(container);

    auto child1 = std::make_shared<Widget>(100 , 200);
    container->addChild(child1);

    auto child2 = std::make_shared<Widget>(200 , 200);
    container->addChild(child2);

    auto child3 = std::make_shared<Widget>(300 , 200);
    container->addChild(child3);
    
    uiRoot->startRenderUI();
    
    EXPECT_EQ(300 + 20 + 30 , container->getWidth());
}


TEST_F(PurpleUiColumContainerTest,colum_container_test_width_warpcontent_instackcontainer){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    uiRoot->setRootContainer(container);

    auto subContainer = std::make_shared<StackContainer>(LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    container->addChild(subContainer);

    auto child1 = std::make_shared<Widget>(300 , 200);
    subContainer->addChild(child1);

    uiRoot->startRenderUI();
    
    EXPECT_EQ(300 , container->getWidth());
}

TEST_F(PurpleUiColumContainerTest,colum_container_test_width_matchparent_instackcontainer){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    uiRoot->setRootContainer(container);

    auto subContainer = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT , LAYOUT_WRAP_CONTENT);
    container->addChild(subContainer);

    auto child1 = std::make_shared<Widget>(300 , 200);
    subContainer->addChild(child1);
    
    uiRoot->startRenderUI();
    
    EXPECT_EQ(subContainer->getWidth() , container->getWidth());
}

TEST_F(PurpleUiColumContainerTest,colum_container_test_width_warpcontent_instackcontainer2){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    uiRoot->setRootContainer(container);

    auto subContainer = std::make_shared<StackContainer>(LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    container->addChild(subContainer);

    auto child1 = std::make_shared<Widget>(400 , 200);
    child1->setMargin<Widget>(10,0,20,0);

    subContainer->addChild(child1);

    uiRoot->startRenderUI();
    
    EXPECT_EQ(child1->getWidth() + child1->getMarginHorizontal(), container->getWidth());
}


TEST_F(PurpleUiColumContainerTest,colum_container_test_height_matchparent){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(container);

    auto child1 = std::make_shared<Widget>(300 , 200);
    container->addChild(child1);
    
    uiRoot->startRenderUI();
    
    EXPECT_EQ(purple::Engine::ScreenHeight , container->getHeight());
}

TEST_F(PurpleUiColumContainerTest,colum_container_test_height_warp){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_MATCH_PARENT,LAYOUT_WRAP_CONTENT);
    uiRoot->setRootContainer(container);

    auto child1 = std::make_shared<Widget>(300 , 200);
    container->addChild(child1);
    
    uiRoot->startRenderUI();
    
    EXPECT_EQ(200, container->getHeight());
}

TEST_F(PurpleUiColumContainerTest,colum_container_test_height_warp_margin){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto container = std::make_shared<ColumContainer>(LAYOUT_MATCH_PARENT,LAYOUT_WRAP_CONTENT);
    uiRoot->setRootContainer(container);

    auto child1 = std::make_shared<Widget>(300 , 200);
    container->addChild(child1);

    auto child2 = std::make_shared<Widget>(300 , 500);
    child2->setMargin<Widget>(0,7,0,7);
    container->addChild(child2);
    
    uiRoot->startRenderUI();
    
    EXPECT_EQ(200 + 500 + child2->getMarginVertical(), container->getHeight());
}

TEST_F(PurpleUiColumContainerTest,colum_container_test_child_position){
    uiRoot = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    using namespace purple;
    auto rootContainer = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    uiRoot->setRootContainer(rootContainer);

    auto container = std::make_shared<ColumContainer>(LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    container->setLayoutGravity<ColumContainer>(LayoutGravity::TopLeft);
    rootContainer->addChild(container);

    auto child1 = std::make_shared<Widget>(100 , 100);
    container->addChild(child1);

    auto child2 = std::make_shared<Widget>(400 , 100);
    container->addChild(child2);

    auto child3 = std::make_shared<Widget>(100 , 100);
    container->addChild(child3);
    
    uiRoot->startRenderUI();

    EXPECT_EQ(400, container->getWidth());
    EXPECT_EQ(300, container->getHeight());
    EXPECT_EQ(purple::Engine::ScreenHeight , child1->top);
    EXPECT_EQ(purple::Engine::ScreenHeight - 100 , child2->top);
    EXPECT_EQ(purple::Engine::ScreenHeight - 200 , child3->top);
}





