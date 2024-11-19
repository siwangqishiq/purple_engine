#include "test_ui.h"
#include "ui/color.h"
#include "ui/text.h"
#include "ui/colum_container.h"
#include "ui/row_container.h"
#include "ui/stack_container.h"

void TestUi::testContainer(){
    using namespace purple;

    PWidget child1 = std::make_shared<Widget>();
    child1->left = 0;
    child1->top = purple::Engine::ScreenHeight;
    child1->setSize<Widget>(200,100)
        .setBackgroundColor<Widget>(purple::ConverColorValue(purple::Color::Red));

    PWidget child2 = std::make_shared<Widget>();
    child2->left = 0;
    child2->top = purple::Engine::ScreenHeight - 100;
    child2->setSize<Widget>(200,100)
        .setBackgroundColor<Widget>(purple::ConverColorValue(purple::Color::Green));

    PWidget child3 = std::make_shared<Widget>();
    child3->left = 0;
    child3->top = purple::Engine::ScreenHeight - 200;
    child3->setSize<Widget>(200,100)
        .setBackgroundColor<Widget>(purple::ConverColorValue(purple::Color::Blue));


    PContainer container = std::make_shared<Container>();
    container->setBackgroundColor<Widget>(purple::ConverColorValue(purple::Color::White));
    container->addChild(child1);
    container->addChild(child2);
    container->addChild(child3);

    std::shared_ptr<Text> textChild = std::make_shared<Text>(L"Hello World 你好世界!",
        LAYOUT_MATCH_PARENT,
        LAYOUT_WRAP_CONTENT);
    textChild->left = 0;
    textChild->top = purple::Engine::ScreenHeight - 300 - 20;
    
    textChild->setBackgroundColor<Text>(purple::ConverColorValue(purple::Color::Green))
        .setFontSize<Text>(50.0f)
        .setFontColor<Text>(purple::ConverColorValue(purple::Color::Black))
        .setBackgroundConnerRadius<Text>(16.0f)
        .setPadding<Text>(10,10,10,10)
        .setTextGravity<Text>(TextGravity::TopCenter);

    container->addChild(textChild);
    
    this->ui->rootContainer_ = container;
}

void TestUi::testColoumContainer(){
    using namespace purple;

    auto container = std::make_shared<ColumContainer>();
    
    container->setBackgroundColor<ColumContainer>(ConverColorValue(Color::White))
        .setBackgroundConnerRadius<ColumContainer>(10.0f);

    std::shared_ptr<Text> text1 = std::make_shared<Text>(L"Hello World 你好世界1234567890~你好世界1234567890~",
        LAYOUT_MATCH_PARENT,
        LAYOUT_WRAP_CONTENT);
    text1->setBackgroundColor<Text>(ConverColorValue(Color::Red))
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setBackgroundConnerRadius<Text>(10.0f)
        .setFontSize<Text>(80.0f)
        .setPadding<Text>(10,10,10,10)
        .setMargin<Text>(20,20,20,0);
    container->addChild(text1);

    std::shared_ptr<Text> text2 = std::make_shared<Text>(L"HelloWorld",
        LAYOUT_WRAP_CONTENT,
        LAYOUT_WRAP_CONTENT);
    text2->setBackgroundColor<Text>(ConverColorValue(Color::Purple))
        .setBackgroundConnerRadius<Text>(10.0f)
        .setPadding<Text>(10,10,10,10)
        .setMargin<Text>(10,10,0,0);
    container->addChild(text2);

    std::shared_ptr<Text> text3 = std::make_shared<Text>(L"你好世界\nHello",
        LAYOUT_WRAP_CONTENT,
        LAYOUT_WRAP_CONTENT);
    text3->setBackgroundColor<Text>(ConverColorValue(Color::Blue))
        .setFontColor<Text>(ConverColorValue(Color::Purple))
        .setBackgroundConnerRadius<Text>(10.0f)
        .setMargin<Text>(0,10,0,0)
        .setPadding<Text>(20,20,20,20);
    container->addChild(text3);

    this->ui->rootContainer_ = container;
}

void TestUi::testColumContainerGravity(){
    using namespace purple;

    auto container = std::make_shared<ColumContainer>();
    container->setBackgroundColor<ColumContainer>(ConverColorValue(Color::White))
        .setPadding<ColumContainer>(20,20,20,20)
        .setSize<ColumContainer>(400, LAYOUT_MATCH_PARENT)
        .setBackgroundConnerRadius<ColumContainer>(0.0f);

    auto cube1 = std::make_shared<Widget>(100,100);
    cube1->setBackgroundColor<Widget>(ConverColorValue(Color::Purple))
        .setMargin<Widget>(0,10,20,10)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube1);

    auto cube2 = std::make_shared<Widget>(100,100);
    cube2->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setMargin<Widget>(0,10,0,10)
        .setLayoutGravity<Widget>(LayoutGravity::TopCenter)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube2);

    auto cube3 = std::make_shared<Widget>(100,100);
    cube3->setBackgroundColor<Widget>(ConverColorValue(Color::SkyBlue))
        .setMargin<Widget>(20,10,0,10)
        .setLayoutGravity<Widget>(LayoutGravity::TopRight)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube3);

    auto text1 = std::make_shared<Text>(L"Hello World",LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    text1->setBackgroundColor<Text>(ConverColorValue(Color::Yellow))
        .setFontSize<Text>(64.0f)
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setLayoutGravity<Text>(LayoutGravity::TopCenter);
    container->addChild(text1);
    
    ui->rootContainer_ = container;
}

void TestUi::testColumContainerWeight(){
     using namespace purple;

    auto container = std::make_shared<ColumContainer>();
    container->setBackgroundColor<ColumContainer>(ConverColorValue(Color::White))
        .setSize<ColumContainer>(LAYOUT_MATCH_PARENT, 600)
        .setBackgroundConnerRadius<ColumContainer>(0.0f);

    auto cube1 = std::make_shared<Widget>(100,100);
    cube1->setBackgroundColor<Widget>(ConverColorValue(Color::Purple))
        .setMargin<Widget>(0,0,20,10)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube1);

    auto cube2 = std::make_shared<Widget>(100,100);
    cube2->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setMargin<Widget>(0,10,0,10)
        .setLayoutGravity<Widget>(LayoutGravity::TopCenter)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube2);

    auto cube3 = std::make_shared<Widget>(LAYOUT_MATCH_PARENT,0);
    cube3->setBackgroundColor<Widget>(ConverColorValue(Color::SkyBlue))
        .setMargin<Widget>(0,10,0,10)
        .setLayoutWeight<Widget>(1)
        .setLayoutGravity<Widget>(LayoutGravity::TopRight)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube3);

    auto text1 = std::make_shared<Text>(L"你好呀~",LAYOUT_MATCH_PARENT,LAYOUT_WRAP_CONTENT);
    text1->setBackgroundColor<Text>(ConverColorValue(Color::Yellow))
        .setFontSize<Text>(64.0f)
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setLayoutWeight<Text>(1)
        .setTextGravity<Text>(TextGravity::Center)
        .setLayoutGravity<Text>(LayoutGravity::TopCenter);
    container->addChild(text1);
    
    ui->rootContainer_ = container;
}

void TestUi::testColumContainerComplex(){
    using namespace purple;

    auto container = std::make_shared<ColumContainer>();
    container->setBackgroundColor<ColumContainer>(ConverColorValue(Color::White))
        .setSize<ColumContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT)
        .setBackgroundConnerRadius<ColumContainer>(0.0f);

    auto cube1 = std::make_shared<Widget>(100,100);
    cube1->setBackgroundColor<Widget>(ConverColorValue(Color::Purple))
        .setMargin<Widget>(0,0,20,10)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube1);

    auto childContainer = std::make_shared<ColumContainer>(500,200);
    childContainer->setBackgroundColor<ColumContainer>(ConverColorValue(Color::Blue));
    childContainer->setId<ColumContainer>("outter_view");
    auto text1 = std::make_shared<Text>(L"Hello",
        LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    text1->setFontSize<Text>(64.0f)
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setLayoutWeight<Text>(1)
        .setTextGravity<Text>(TextGravity::Center)
        .setId<Text>("inner_text");
    childContainer->addChild(text1);

    auto text2 = std::make_shared<Text>(L"Hello2",
        LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    text2->setFontSize<Text>(64.0f)
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setLayoutWeight<Text>(1)
        .setTextGravity<Text>(TextGravity::Center)
        .setId<Text>("inner_text");
    childContainer->addChild(text2);

    container->addChild(childContainer);

    auto cube2 = std::make_shared<Widget>(100,100);
    cube2->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setMargin<Widget>(0,10,0,10)
        .setLayoutGravity<Widget>(LayoutGravity::TopCenter)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube2);

    auto cube3 = std::make_shared<Widget>(LAYOUT_MATCH_PARENT,0);
    cube3->setBackgroundColor<Widget>(ConverColorValue(Color::SkyBlue))
        .setMargin<Widget>(0,10,0,10)
        .setLayoutWeight<Widget>(1)
        .setLayoutGravity<Widget>(LayoutGravity::TopRight)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube3);

    
    ui->rootContainer_ = container;
}

void TestUi::testRowContainer(){
    using namespace purple;

    auto container = std::make_shared<RowContainer>();
    container->setBackgroundColor<RowContainer>(ConverColorValue(Color::White))
        .setSize<RowContainer>(LAYOUT_MATCH_PARENT, LAYOUT_WRAP_CONTENT)
        .setBackgroundConnerRadius<RowContainer>(30.0f);

    auto cube1 = std::make_shared<Widget>(100,100);
    cube1->setBackgroundColor<Widget>(ConverColorValue(Color::Purple))
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube1);

    auto cube2 = std::make_shared<Widget>(100,100);
    cube2->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setMargin<Widget>(0,0,0,10)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube2);

    auto text1 = std::make_shared<Text>(L"Hello你好", LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    text1->setFontSize<Text>(64.0f)
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setLayoutWeight<Text>(1)
        .setBackgroundColor<Text>(glm::vec4(1.0f,0.0f,0.0f,0.4f))
        .setTextGravity<Text>(TextGravity::CenterLeft);
    container->addChild(text1);

    auto cube3 = std::make_shared<Widget>(200,300);
    cube3->setBackgroundColor<Widget>(ConverColorValue(Color::SkyBlue))
        .setMargin<Widget>(0,0,80,0)
        .setLayoutWeight<Widget>(1)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube3);

    ui->rootContainer_ = container;
}

void TestUi::testRowContainerGravity(){
    using namespace purple;

    auto container = std::make_shared<RowContainer>();
    container->setBackgroundColor<RowContainer>(ConverColorValue(Color::White))
        .setSize<RowContainer>(LAYOUT_MATCH_PARENT, LAYOUT_WRAP_CONTENT)
        .setBackgroundConnerRadius<RowContainer>(30.0f);

    auto cube1 = std::make_shared<Widget>(100,200);
    cube1->setBackgroundColor<Widget>(ConverColorValue(Color::Purple))
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube1);

    auto cube2 = std::make_shared<Widget>(100,100);
    cube2->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setMargin<Widget>(20,0,0,0)
        .setLayoutGravity<Widget>(LayoutGravity::CenterRight)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube2);

    auto text1 = std::make_shared<Text>(L"Hello你好",
        LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    text1->setFontSize<Text>(64.0f)
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setMargin<Text>(20,0,0,0)
        .setBackgroundColor<Text>(ConverColorValue(Color::SkyBlue))
        .setTextGravity<Text>(TextGravity::BottomRight)
        .setLayoutGravity<Text>(LayoutGravity::BottomRight);
    container->addChild(text1);

    auto cube3 = std::make_shared<Widget>(200,30);
    cube3->setBackgroundColor<Widget>(ConverColorValue(Color::SkyBlue))
        .setMargin<Widget>(80,10,0,10)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube3);

    ui->rootContainer_ = container;
}

void TestUi::testRowContainerWeight(){
    using namespace purple;

    auto container = std::make_shared<RowContainer>();
    container->setBackgroundColor<RowContainer>(ConverColorValue(Color::White))
        .setSize<RowContainer>(LAYOUT_MATCH_PARENT, LAYOUT_WRAP_CONTENT)
        .setBackgroundConnerRadius<RowContainer>(30.0f);

    auto cube1 = std::make_shared<Widget>(100,200);
    cube1->setBackgroundColor<Widget>(ConverColorValue(Color::Purple))
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube1);

    auto cube2 = std::make_shared<Widget>(100,100);
    cube2->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setMargin<Widget>(20,0,0,0)
        .setLayoutGravity<Widget>(LayoutGravity::CenterRight)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube2);

    auto text1 = std::make_shared<Text>(L"Hello你好",
        LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    text1->setFontSize<Text>(64.0f)
        .setFontColor<Text>(ConverColorValue(Color::Black))
        .setMargin<Text>(20,0,0,0)
        .setBackgroundColor<Text>(ConverColorValue(Color::SkyBlue))
        .setTextGravity<Text>(TextGravity::Center)
        .setLayoutWeight<Text>(1)
        .setLayoutGravity<Text>(LayoutGravity::BottomRight);
    container->addChild(text1);

    auto cube3 = std::make_shared<Widget>(200,30);
    cube3->setBackgroundColor<Widget>(ConverColorValue(Color::SkyBlue))
        .setMargin<Widget>(0,10,0,10)
        .setLayoutWeight<Widget>(3)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube3);

    ui->rootContainer_ = container;
}

void TestUi::testRowContainerCompose(){
    using namespace purple;

    auto container = std::make_shared<RowContainer>();
    container->setBackgroundColor<RowContainer>(ConverColorValue(Color::White))
        .setPadding<RowContainer>(20,20,20,20)
        .setSize<RowContainer>(LAYOUT_MATCH_PARENT, LAYOUT_WRAP_CONTENT);

    auto cube1 = std::make_shared<Widget>(0,200);
    cube1->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setLayoutWeight<Widget>(1)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube1);

    auto cube2 = std::make_shared<Widget>(0,200);
    cube2->setBackgroundColor<Widget>(ConverColorValue(Color::Green))
        .setLayoutWeight<Widget>(1)
        .setMargin<Widget>(100,0,0,0)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube2);

    auto cube3 = std::make_shared<Widget>(0,200);
    cube3->setBackgroundColor<Widget>(ConverColorValue(Color::SkyBlue))
        .setLayoutWeight<Widget>(1)
        .setMargin<Widget>(100,0,0,0)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube3);

    ui->rootContainer_ = container;
}

void TestUi::testStackContainer(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>();
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::White))
        .setPadding<StackContainer>(10,10,10,10);

    auto cube1 = std::make_shared<Widget>(200,200);
    cube1->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setLayoutGravity<Widget>(LayoutGravity::TopLeft)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube1);

    auto cube2 = std::make_shared<Widget>(200,200);
    cube2->setBackgroundColor<Widget>(ConverColorValue(Color::Green))
        .setLayoutGravity<Widget>(LayoutGravity::TopCenter)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube2);

    auto cube3 = std::make_shared<Widget>(200,200);
    cube3->setBackgroundColor<Widget>(ConverColorValue(Color::SkyBlue))
        .setLayoutGravity<Widget>(LayoutGravity::TopRight)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube3);


    auto cube4 = std::make_shared<Widget>(200,200);
    cube4->setBackgroundColor<Widget>(ConverColorValue(Color::Green))
        .setLayoutGravity<Widget>(LayoutGravity::CenterLeft)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube4);

    auto cube5 = std::make_shared<Widget>(200,200);
    cube5->setBackgroundColor<Widget>(ConverColorValue(Color::Blue))
        .setLayoutGravity<Widget>(LayoutGravity::Center)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube5);

    auto cube6 = std::make_shared<Widget>(200,200);
    cube6->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setLayoutGravity<Widget>(LayoutGravity::CenterRight)
        .setBackgroundConnerRadius<Widget>(8.0f);
    container->addChild(cube6);


    auto cube7 = std::make_shared<Widget>(200,200);
    cube7->setBackgroundColor<Widget>(ConverColorValue(Color::Red))
        .setLayoutGravity<Widget>(LayoutGravity::BottomLeft)
        .setBackgroundConnerRadius<Widget>(0.0f);
    container->addChild(cube7);

    auto cube8 = std::make_shared<Widget>(200,200);
    cube8->setBackgroundColor<Widget>(ConverColorValue(Color::Blue))
        .setLayoutGravity<Widget>(LayoutGravity::BottomCenter)
        .setBackgroundConnerRadius<Widget>(0.0f);
    container->addChild(cube8);

    auto cube9 = std::make_shared<Widget>(200,200);
    cube9->setBackgroundColor<Widget>(ConverColorValue(Color::Black))
        .setLayoutGravity<Widget>(LayoutGravity::BottomRight)
        .setBackgroundConnerRadius<Widget>(0.0f);
    container->addChild(cube9);

    ui->rootContainer_ = container;
}

void TestUi::testContainerCompose(){
    using namespace purple;

    auto container = std::make_shared<ColumContainer>();
    container->setBackgroundColor<ColumContainer>(ConverColorValue(Color::White))
        .setPadding<ColumContainer>(0,0,0,0);
    
    auto headContainer = std::make_shared<RowContainer>(LAYOUT_MATCH_PARENT,100);
    headContainer->setBackgroundColor<RowContainer>(ConverColorValue(Color::Blue));
    container->addChild(headContainer);

    auto contentContainer = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT,0);
    contentContainer->setBackgroundColor<StackContainer>(ConverColorValue(Color::Silver))
        .setLayoutWeight<StackContainer>(1);
    container->addChild(contentContainer);
    auto contentText = std::make_shared<Text>(L"我是内容",LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    contentText->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(64.0f)
        .setLayoutGravity<Text>(LayoutGravity::Center);
    contentContainer->addChild(contentText);

    auto footContainer = std::make_shared<RowContainer>(LAYOUT_MATCH_PARENT,150);
    footContainer->setBackgroundColor<RowContainer>(ConverColorValue(Color::SkyBlue));
    container->addChild(footContainer);

    auto tab1 = std::make_shared<Text>(L"Tab1",0,LAYOUT_MATCH_PARENT);
    tab1->setFontColor<Text>(ConverColorValue(Color::Black))
        .setBackgroundColor<Text>(glm::vec4(1.0f , 0.0f ,0.0f , 1.0f))
        .setTextGravity<Text>(TextGravity::Center)
        .setId<Text>("tab1")
        .setLayoutWeight<Text>(1);
    footContainer->addChild(tab1);
    // footContainer->setVisible(VisibleState::Gone);

    auto tab2 = std::make_shared<Text>(L"Tab2",0,LAYOUT_MATCH_PARENT);
    tab2->setFontColor<Text>(ConverColorValue(Color::Black))
        .setBackgroundColor<Text>(glm::vec4(0.0f , 1.0f ,0.0f , 0.3f))
        .setTextGravity<Text>(TextGravity::Center)
        .setId<Text>("tab2")
        .setLayoutWeight<Text>(1);
    footContainer->addChild(tab2);

    auto tab3 = std::make_shared<Text>(L"Tab3",0,LAYOUT_MATCH_PARENT);
    tab3->setFontColor<Text>(ConverColorValue(Color::Black))
        .setBackgroundColor<Text>(glm::vec4(0.0f , 0.0f ,1.0f , 0.3f))
        .setTextGravity<Text>(TextGravity::Center)
        .setId<Text>("tab3")
        .setLayoutWeight<Text>(1);
    footContainer->addChild(tab3);

    auto tab4 = std::make_shared<Text>(L"Tab4",0,LAYOUT_MATCH_PARENT);
    tab4->setFontColor<Text>(ConverColorValue(Color::Black))
        .setBackgroundColor<Text>(ConverColorValue(Color::White))
        .setTextGravity<Text>(TextGravity::Center)
        .setId<Text>("tab4")
        .setLayoutWeight<Text>(1);
    footContainer->addChild(tab4);


    auto headText = std::make_shared<Text>(L"我是标题",LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    headText->setMargin<Text>(20,0,0,0)
        .setTextGravity<Text>(TextGravity::CenterLeft)
        .setFontColor<Text>(ConverColorValue(Color::Black));
    headContainer->addChild(headText);

    ui->rootContainer_ = container;
}


void TestUi::onInit(){
    purple::Log::i("test_ui", "Test Ui init");

    this->ui = std::make_shared<purple::UiRoot>(purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight);

    // testContainer();
    // testColoumContainer();
    // testColumContainerGravity();
    // testColumContainerWeight();
    // testColumContainerComplex();
    // testRowContainer();
    // testRowContainerGravity();
    // testRowContainerWeight();
    // testRowContainerCompose();
    // testStackContainer();
    testContainerCompose();
}

void TestUi::onTick(){
    // purple::Log::i("test_ui", "Test Ui onTick");

    if(this->ui != nullptr){
        this->ui->startRenderUI();
    }
}

void TestUi::onDispose(){
    purple::Log::i("test_ui", "Test Ui onDispose");
}