#include "test_ui_text.h"
#include "ui/img.h"
#include "purple_ui.h"
#include "input/input_manager.h"
#include "log.h"

void TestTextUi::onInit(){
    ui = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    purple::InputManager::getInstance()->addEventListener("ui",[this](purple::InputEvent &e){
        if(this->ui != nullptr){
            // std::cout << "rootui = " << this->ui << std::endl;
            return this->ui->dispatchInputEvent(e);
        }
        return false;
    });

    // testText();
    // testStackContainerWithText();
    // testColumContainer();
    testColumContainerInStack();
}

void TestTextUi::onResize(int w , int h){
    onInit();
}

void TestTextUi::testText(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::White))
        .setPadding<StackContainer>(0,0,0,0);

    auto text1 = std::make_shared<Text>(L"你好世界" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text1->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(30.0f)
        .setLayoutGravity<Text>(LayoutGravity::TopLeft)
        .setMargin<Text>(0,100,0,0)
        .setBackgroundColor<Text>(ConverColorValue(Color::Red))
        .setPadding<Text>(20,10,20,10);

    container->addChild(text1);

    ui->setRootContainer(container);
}

void TestTextUi::testStackContainerWithText(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::White))
        .setPadding<StackContainer>(0,0,0,0);

    auto text1 = std::make_shared<Text>(L"你好世界" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text1->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(30.0f)
        .setLayoutGravity<Text>(LayoutGravity::TopLeft)
        .setMargin<Text>(0,0,0,0)
        .setBackgroundColor<Text>(ConverColorValue(Color::Pink))
        .setPadding<Text>(20,10,20,10);
    container->addChild(text1);


    auto text2 = std::make_shared<Text>(L"大政奉还" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text2->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(30.0f)
        .setLayoutGravity<Text>(LayoutGravity::TopRight)
        .setBackgroundColor<Text>(ConverColorValue(Color::Yellow))
        .setPadding<Text>(20,10,20,10);
    container->addChild(text2);


    auto text3 = std::make_shared<Text>(L"天诛\n国贼" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text3->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(80.0f)
        .setLayoutGravity<Text>(LayoutGravity::Center)
        .setBackgroundConnerRadius<Text>(16.0f)
        .setBackgroundColor<Text>(ConverColorValue(Color::Red))
        .setPadding<Text>(20,20,20,20)
        .setFontWeight<Text>(100.0f);
    container->addChild(text3);

    auto text4 = std::make_shared<Text>(L"废刀令" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text4->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(30.0f)
        .setLayoutGravity<Text>(LayoutGravity::BottomLeft)
        .setBackgroundColor<Text>(ConverColorValue(Color::SkyBlue))
        .setPadding<Text>(20,10,20,10);
    container->addChild(text4);

    auto text5 = std::make_shared<Text>(L"黑船来袭" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text5->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(30.0f)
        .setLayoutGravity<Text>(LayoutGravity::BottomRight)
        .setBackgroundColor<Text>(ConverColorValue(Color::SkyBlue))
        .setPadding<Text>(20,10,20,10);
    container->addChild(text5);

    ui->setRootContainer(container);
}


void TestTextUi::testColumContainer(){
    using namespace purple;

    auto container = std::make_shared<ColumContainer>(LAYOUT_WRAP_CONTENT, LAYOUT_WRAP_CONTENT);
    container->setBackgroundColor<ColumContainer>(ConverColorValue(Color::SkyBlue))
        .setPadding<ColumContainer>(10,10,10,10);

    auto text1 = std::make_shared<Text>(L"你好" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text1->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(50.0f)
        .setMargin<Text>(0,0,0,0)
        .setBackgroundColor<Text>(ConverColorValue(Color::Pink))
        .setPadding<Text>(20,10,20,10);
    container->addChild(text1);

    auto text2 = std::make_shared<Text>(L"大政奉还" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text2->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(50.0f)
        .setMargin<Text>(0,0,0,0)
        .setBackgroundColor<Text>(ConverColorValue(Color::Silver))
        .setPadding<Text>(20,10,20,10);
    container->addChild(text2);

    ui->setRootContainer(container);
}

void TestTextUi::testColumContainerInStack(){
    using namespace purple;
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::White));

    auto columContainer = std::make_shared<ColumContainer>(LAYOUT_MATCH_PARENT, LAYOUT_WRAP_CONTENT);
    columContainer->setBackgroundColor<ColumContainer>(ConverColorValue(Color::SkyBlue))
        .setPadding<ColumContainer>(10,10,10,10)
        .setMargin<ColumContainer>(20,20,20,20)
        .setLayoutGravity<ColumContainer>(LayoutGravity::TopLeft);
    container->addChild(columContainer);

    auto text1 = std::make_shared<Text>(L"你好世界1你好世界2你好世界3你好世界4你好世界5你好世界6你好世界7你好世界8" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text1->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(50.0f)
        .setMargin<Text>(0,0,0,0)
        .setBackgroundColor<Text>(ConverColorValue(Color::Pink))
        .setId<Text>("error_col")
        .setPadding<Text>(10,10,10,10)
        .setClick<Text>([](purple::InputEvent &e){
            purple::Log::i("click","click HelloWorld!");
        });
    columContainer->addChild(text1);

    auto text2 = std::make_shared<Text>(L"奉还1奉还2奉还3奉还4" , LAYOUT_WRAP_CONTENT , LAYOUT_WRAP_CONTENT);
    text2->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(50.0f)
        .setFontWeight<Text>(75.0f)
        .setMargin<Text>(0,20,0,0)
        .setBackgroundColor<Text>(ConverColorValue(Color::Silver))
        .setPadding<Text>(10,10,10,10);
    columContainer->addChild(text2);

    ui->setRootContainer(container);
}

void TestTextUi::onTick(){
    if(ui != nullptr){
        ui->startRenderUI();
    }
}

void TestTextUi::onDispose(){
    purple::Log::i("TestImgUi","TestTextUi::onDispose");
}

