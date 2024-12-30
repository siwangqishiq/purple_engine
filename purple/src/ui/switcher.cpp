#include "ui/switcher.h"
#include <algorithm>
#include "purple.h"

namespace purple{

    void Switcher::onMeasure(MeasureSpecMode widthSpecMode,
                                int widthValue, 
                                MeasureSpecMode heightSpecMode,
                                int heightValue){
        if(heightSpecMode == MeasureSpecMode::Atmost){
            height_ = std::min(DefaultHeight , heightValue);
        }else if(heightSpecMode == MeasureSpecMode::Exactly){
            height_ = heightValue;
        }else{
            height_ = 0;
        }

        if(widthSpecMode == MeasureSpecMode::Atmost){
            width_ = height_ * 2;
        }else if(widthSpecMode == MeasureSpecMode::Exactly){
            width_ = widthValue;
        }else{
            width_ = 0;
        }

        buildVirtualTexture();
    }

    void Switcher::renderContent(int widgetWidth , int widgetHeight){
        // std::cout << "widgetWidth , widgetHeight = " << widgetWidth << "," <<
        //      widgetHeight << std::endl;

        Rect rect(0, widgetHeight, widgetWidth , widgetHeight);
        Paint paint;
        paint.fillStyle = FillStyle::Filled;
        paint.stokenWidth = DefaultPadding;
        paint.color = ConverColorValue(Color::Black);
        auto render = purple::Engine::getRenderEngine();
        auto shapeBatch = render->getShapeBatch();
        shapeBatch->begin();
        shapeBatch->renderRoundRect(rect , rect.height / 2.0f, paint);
        
        shapeBatch->end();
    }
}


