#include "ui/custom_widget.h"
#include "purple.h"
#include "utils.h"
#include "render/sprite.h"

namespace purple{
    void CustomWidget::regenerateTexId(){
        texId = std::string("CustomWidget_") + std::to_string(currentTimeMillis());
        Log::i("ui", "CustomWidget texId = %s" , texId);
    }

    void CustomWidget::onMeasure(MeasureSpecMode widthSpecMode,
                                int widthValue, 
                                MeasureSpecMode heightSpecMode,
                                int heightValue){
        if(widthSpecMode == MeasureSpecMode::Exactly
            || widthSpecMode == MeasureSpecMode::Atmost){
            this->width_ = widthValue;
        } else {
            this->width_ = 0;
        }

        if(heightSpecMode == MeasureSpecMode::Exactly
            || heightSpecMode == MeasureSpecMode::Atmost){
            this->height_ = heightValue;
        } else{
            this->height_ = 0;
        }
        
        buildVirtualTexture();
    } 

    void CustomWidget::buildVirtualTexture(){
        if(width_ > 0 && height_ > 0 && virtualTexture == nullptr){
            auto render = purple::Engine::getRenderEngine();
            virtualTexture = render->buildVirtualTexture(this->texId , width_ , height_ , nullptr);
        }
    }  

    void CustomWidget::onRender(){
        Widget::onRender();

        if(virtualTexture == nullptr){
           return;
        }

        auto render = purple::Engine::getRenderEngine();

        render->updateVirtualTexture(virtualTexture , [this](int texWidth , int texHeight){
            this->renderContent(texWidth , texHeight);
        });

        auto spriteBatch = render->getSpriteBatch();
        spriteBatch->begin();
        Rect src(0, virtualTexture->height , virtualTexture->width , virtualTexture->height);
        Rect dst(left , top , width_ , height_);
        // std::cout << "left = " << left << " top " << top << std::endl;
        TextureImage image(virtualTexture);
        spriteBatch->renderImage(image, src , dst);
        spriteBatch->end();
    }

    void CustomWidget::renderContent(int widgetWidth , int widgetHeight){
        // Log::i("ui", "CustomWidget::renderContent ...");
        auto render = purple::Engine::getRenderEngine();

        auto shapeBatch = render->getShapeBatch();
        shapeBatch->begin();
        Paint paint;
        paint.color = ConverColorValue(Color::Yellow);
        Rect rect(0, widgetHeight , widgetWidth , widgetHeight);
        shapeBatch->renderRect(rect, paint);
        shapeBatch->end();
    }
}