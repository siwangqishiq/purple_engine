#include "test_ui_img.h"
#include "ui/img.h"
#include "purple_ui.h"
#include "log.h"
#include "input/input_common.h"
#include "input/input_manager.h"

void TestImgUi::onInit(){
    ui = std::make_shared<purple::UiRoot>(
        purple::Engine::ScreenWidth , 
        purple::Engine::ScreenHeight
    );

    purple::InputManager::getInstance()->addEventListener("ui",[this](purple::InputEvent &e){
        if(ui != nullptr){
            return ui->dispatchInputEvent(e);
        }
        return false;
    });

    // testImg();
    // testImgMatchParent();
    // testImgWrapContent();
    // testImgScaleMode();
    // testImgScaleMode2();
    // testImgScaleMode3();
    // testImgScaleMode4();
    // testImgScaleMode5();
    // testSeekbar();
    // testProgressBar();
    testSwitcher();
    playBgmMusic();
}

void TestImgUi::onResize(int w , int h){
    onInit();
}

void TestImgUi::testSeekbar(){
    using namespace purple;

    auto container = std::make_shared<ColumContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<ColumContainer>(ConverColorValue(Color::White));

    ui->setRootContainer(container);

    auto seekbar = std::make_shared<SeekBar>(LAYOUT_MATCH_PARENT,20);
    seekbar->setMargin<SeekBar>(30,100,30,0);
    container->addChild(seekbar);

    auto seekbar2 = std::make_shared<SeekBar>(purple::Engine::ScreenWidth / 2.0f,30);
    seekbar2->setMargin<SeekBar>(30,100,30,0)
        .setLayoutGravity<SeekBar>(LayoutGravity::Center)
        .setBarColor<SeekBar>(ConverColorValue(Color::Pink))
        .setIndicatorColor<SeekBar>(ConverColorValue(Color::Red));
    container->addChild(seekbar2);

    auto text1 = std::make_shared<Text>(L"0",LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    text1->setFontColor<Text>(ConverColorValue(Color::Black))
        .setFontSize<Text>(200.0f)
        .setLayoutGravity<SeekBar>(LayoutGravity::Center)
        .setMargin<Text>(0,100,0,0)
        .setFontWeight<Text>(90.0f);

    auto seekbar3 = std::make_shared<SeekBar>(LAYOUT_MATCH_PARENT,20);
    seekbar3->setMargin<SeekBar>(30,100,30,0)
        .setProgressUpdate<SeekBar>([seekbar , seekbar2 , text1](float value , float oldValue , bool isManual){
            seekbar2->setProgress(value);
            seekbar->setProgress(value);
            text1->setText(std::to_wstring(static_cast<int>(value)));
        });
    container->addChild(seekbar3);

    container->addChild(text1);
}

void TestImgUi::testProgressBar(){
    using namespace purple;

    auto container = std::make_shared<ColumContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<ColumContainer>(ConverColorValue(Color::White));

    ui->setRootContainer(container);

    auto progressBar = std::make_shared<ProgressBar>(LAYOUT_MATCH_PARENT,60);
    progressBar->setMargin<ProgressBar>(30,100,30,0);
    container->addChild(progressBar);

    auto seekbar3 = std::make_shared<ProgressBar>(purple::Engine::ScreenWidth / 2.0f,20);
    seekbar3->setMargin<ProgressBar>(30,100,30,0);
    container->addChild(seekbar3);

    purple::Engine::getTimer()->scheduleAtFixedRate([this, progressBar](void *params){
        this->progressValue = (this->progressValue + 1) % 100;
        progressBar->setProgress(static_cast<float>(this->progressValue));
    },20);
}

void TestImgUi::testSwitcher(){
    using namespace purple;
    
    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::White));
    ui->setRootContainer(container);

    auto switcher = std::make_shared<Switcher>(
        purple::Engine::vpTopx(100), 
        purple::Engine::vpTopx(50));
    switcher->setLayoutGravity<Switcher>(LayoutGravity::Center);
    container->addChild(switcher);
}

void TestImgUi::playBgmMusic(){
    if(bgm != nullptr){
        return;
    }
    
    std::string audioPath = "audio/heishenhua.mp3";
    bgm = purple::AudioManager::getInstance()->loadAudioEntity(audioPath,false);

    std::string audioPath2 = "audio/test.mp3";
    bgm2 = purple::AudioManager::getInstance()->loadAudioEntity(audioPath2,false);


    purple::AudioManager::getInstance()->setAudioPlayEndCallback(bgm, [this](std::string name){
        purple::AudioManager::getInstance()->playAudioEntity(this->bgm2);
    });

    purple::AudioManager::getInstance()->setAudioPlayEndCallback(bgm2, [this](std::string name){
        purple::AudioManager::getInstance()->playAudioEntity(this->bgm);
    });
    
    // // purple::AudioManager::getInstance()->playAudioEntity(bgm);
    purple::AudioManager::getInstance()->playAudioEntity(bgm);

    // purple::AudioManager::getInstance()->setAudioPlayProgressCallback(bgm2, [](unsigned long a, unsigned long b, double c){
    //     std::cout << "play callback" << std::endl;
    // });
}

void TestImgUi::testImg(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::SkyBlue));

    auto imgTexture = purple::ImageSource::fromAsset("img/t2.jpg");
    auto image = std::make_shared<Img>(imgTexture , 200,200);
    container->addChild(image);

    ui->setRootContainer(container);
}

void TestImgUi::testImgMatchParent(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::SkyBlue));

    auto imgTexture = purple::ImageSource::fromAsset("img/t2.jpg");
    auto image = std::make_shared<Img>(imgTexture , LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    container->addChild(image);

    ui->setRootContainer(container);
}

void TestImgUi::testImgWrapContent(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::SkyBlue));

    auto imgTexture = purple::ImageSource::fromAsset("img/small.png");
    auto image = std::make_shared<Img>(imgTexture , LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    image->setLayoutGravity<Img>(LayoutGravity::Center)
        .setBackgroundColor<Img>(ConverColorValue(Color::Pink))
        .setScaleMode<Img>(ImgScale::Mode::FitBottom);
    container->addChild(image);

    auto imgTexture2 = purple::ImageSource::fromAsset("img/t2.jpg");
    auto image2 = std::make_shared<Img>(imgTexture2 , 200,200);
    image2->setLayoutGravity<Img>(LayoutGravity::BottomRight);
    container->addChild(image2);

    auto imgTexture3 = purple::ImageSource::fromAsset("img/g2.jpg");
    auto image3 = std::make_shared<Img>(imgTexture3 , 200,200);
    image3->setLayoutGravity<Img>(LayoutGravity::TopRight);
    container->addChild(image3);

    ui->setRootContainer(container);
}

void TestImgUi::testImgScaleMode(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::White));

    auto imgTexture = purple::ImageSource::fromAsset("img/g2.jpg");

    auto imageBase = std::make_shared<Img>(imgTexture , LAYOUT_WRAP_CONTENT,LAYOUT_WRAP_CONTENT);
    imageBase->setLayoutGravity<Img>(LayoutGravity::Center)
        .setScaleMode<Img>(ImgScale::Mode::Center);
    container->addChild(imageBase);

    auto image = std::make_shared<Img>(300,300);
    image->setLayoutGravity<Img>(LayoutGravity::Center)
        .setBackgroundColor<Img>(ConverColorValue(Color::SkyBlue))
        .setScaleMode<Img>(ImgScale::Mode::Center);
    container->addChild(image);
    
    ui->setRootContainer(container);

    purple::Engine::getTimer()->schedule([image, imgTexture](void *){
        image->setImage<Img>(imgTexture);
    },4000);
}

void TestImgUi::testImgScaleMode2(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::White));

    auto imgTexture = purple::ImageSource::fromAsset("img/small.png");

    auto image = std::make_shared<Img>(imgTexture, 400,400);
    image->setLayoutGravity<Img>(LayoutGravity::Center)
        .setBackgroundColor<Img>(ConverColorValue(Color::SkyBlue))
        .setPadding<Img>(10,10,10,10)
        .setScaleMode<Img>(ImgScale::Mode::CenterCrop);
    container->addChild(image);
    
    ui->setRootContainer(container);
}

void TestImgUi::testImgScaleMode3(){
    using namespace purple;

    auto container = std::make_shared<RowContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);

    // auto imgTexture = purple::ImageSource::fromAsset("img/g2.jpg");
    // auto imgTexture = purple::ImageSource::fromAsset("img/small.png");

    auto imgTexture1 = purple::ImageSource::fromAsset("img/more_height.jpg");
    auto imgTexture2 = purple::ImageSource::fromAsset("img/g2.jpg");
    const int imageSizeWidth = 400;
    const int imageSizeHeight = 400;

    auto leftContainer = std::make_shared<StackContainer>(0,LAYOUT_MATCH_PARENT);
    leftContainer->setBackgroundColor<StackContainer>(ConverColorValue(Color::Silver))
        .setLayoutWeight<StackContainer>(1);
    container->addChild(leftContainer);
    auto leftImage = std::make_shared<Img>(imgTexture1 , imageSizeWidth,imageSizeHeight);
    leftImage->setLayoutGravity<Img>(LayoutGravity::Center)
        .setPadding<Img>(5,5,5,5)
        .setScaleMode<Img>(ImgScale::Mode::CenterCrop)
        .setBackgroundColor<Img>(ConverColorValue(Color::Pink));
    leftContainer->addChild(leftImage);

    auto rightContainer = std::make_shared<StackContainer>(0,LAYOUT_MATCH_PARENT);
    rightContainer->setBackgroundColor<StackContainer>(ConverColorValue(Color::SkyBlue))
        .setLayoutWeight<StackContainer>(1);
    container->addChild(rightContainer);
    auto rightImage = std::make_shared<Img>(imgTexture1 , imageSizeWidth,imageSizeHeight);
    rightImage->setLayoutGravity<Img>(LayoutGravity::Center)
        .setPadding<Img>(5,5,5,5)
        .setScaleMode<Img>(ImgScale::Mode::CenterInside)
        .setBackgroundColor<Img>(ConverColorValue(Color::Pink));
    rightContainer->addChild(rightImage);

    ui->setRootContainer(container);
}

void TestImgUi::testImgScaleMode4(){
    using namespace purple;

    auto container = std::make_shared<RowContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);

    // auto imgTexture = purple::ImageSource::fromAsset("img/g2.jpg");
    // auto imgTexture = purple::ImageSource::fromAsset("img/small.png");

    auto imgTexture2 = purple::ImageSource::fromAsset("img/g2.jpg");
    const int imageSizeWidth = 400;
    const int imageSizeHeight = 400;

    auto leftContainer = std::make_shared<StackContainer>(0,LAYOUT_MATCH_PARENT);
    leftContainer->setBackgroundColor<StackContainer>(ConverColorValue(Color::Silver))
        .setLayoutWeight<StackContainer>(1);
    container->addChild(leftContainer);
    auto leftImage = std::make_shared<Img>(imgTexture2 , imageSizeWidth,imageSizeHeight);
    leftImage->setLayoutGravity<Img>(LayoutGravity::Center)
        .setPadding<Img>(5,5,5,5)
        .setScaleMode<Img>(ImgScale::Mode::CenterCrop)
        .setBackgroundColor<Img>(ConverColorValue(Color::Pink));
    leftContainer->addChild(leftImage);

    auto rightContainer = std::make_shared<StackContainer>(0,LAYOUT_MATCH_PARENT);
    rightContainer->setBackgroundColor<StackContainer>(ConverColorValue(Color::SkyBlue))
        .setLayoutWeight<StackContainer>(1);
    container->addChild(rightContainer);
    auto rightImage = std::make_shared<Img>(imgTexture2 , imageSizeWidth,imageSizeHeight);
    rightImage->setLayoutGravity<Img>(LayoutGravity::Center)
        .setPadding<Img>(5,5,5,5)
        .setScaleMode<Img>(ImgScale::Mode::CenterInside)
        .setBackgroundColor<Img>(ConverColorValue(Color::Pink));
    rightContainer->addChild(rightImage);

    ui->setRootContainer(container);
}

void TestImgUi::testImgScaleMode5(){
    using namespace purple;

    auto container = std::make_shared<StackContainer>(LAYOUT_MATCH_PARENT, LAYOUT_MATCH_PARENT);
    container->setBackgroundColor<StackContainer>(ConverColorValue(Color::Black));

    // auto imgTexture = purple::ImageSource::fromAsset("img/g2.jpg");
    // auto imgTexture = purple::ImageSource::fromAsset("img/small.png");
    auto imgTexture = purple::ImageSource::fromAsset("img/more_height.jpg");
    // auto imgTexture = purple::ImageSource::fromAsset("img/more_width.png");
    // const int imageSizeWidth = 400;
    // const int imageSizeHeight = 400;

    auto image = std::make_shared<Img>(imgTexture , LAYOUT_MATCH_PARENT,LAYOUT_MATCH_PARENT);
    image->setLayoutGravity<Img>(LayoutGravity::Center)
        .setScaleMode<Img>(ImgScale::Mode::CenterCrop)
        .setBackgroundColor<Img>(ConverColorValue(Color::Pink));
    container->addChild(image);

    ui->setRootContainer(container);
}

void TestImgUi::onTick(){
    if(ui != nullptr){
        ui->startRenderUI();
    }
}

void TestImgUi::onDispose(){
    purple::Log::i("TestImgUi","TestImgUi::onDispose");
    purple::InputManager::getInstance()->removeEventListener("ui");

    if(bgm != nullptr){
        purple::AudioManager::getInstance()->releaseAudioEntity(bgm);
    }

    if(bgm2 != nullptr){
        purple::AudioManager::getInstance()->releaseAudioEntity(bgm2);
    }
}

