#include "ui/seekbar.h"
#include "utils.h"
#include "purple.h"
#include <tuple>
#include <cmath>

namespace purple{
    void SeekBar::onMeasure(MeasureSpecMode widthSpecMode,
                                int widthValue, 
                                MeasureSpecMode heightSpecMode,
                                int heightValue){
        if(widthSpecMode == MeasureSpecMode::Exactly){
            this->width_ = widthValue;
        } else if(widthSpecMode == MeasureSpecMode::Atmost){
            if(isSizeValueLegal(widthValue)){
                this->width_ = widthValue;
            }else{
                this->width_ = 0;
            }
        } else {
            this->width_ = 0;
        }

        if(heightSpecMode == MeasureSpecMode::Exactly){
            this->height_ = heightValue;
        } else if(heightSpecMode == MeasureSpecMode::Atmost){
            if(isSizeValueLegal(height_)){
                this->height_ = heightValue;
            }else{
                this->height_ = 0;
            }
        }else {
            this->height_ = 0;
        }
        
        putSeekbarParams();
        buildVirtualTexture();
    }

    void SeekBar::putSeekbarParams(){
        if(width_ <= 0 || height_ <= 0){
            return;
        }

        indicatorRadius = (height_ - getPaddingVertial()) / 2.0f;
        barHeight = indicatorRadius * 0.5f;

        barWidth = width_ - indicatorRadius * 2.0f - getPaddingHorizontal();
        barOffsetX = indicatorRadius;
    }

    void SeekBar::renderContent(int widgetWidth , int widgetHeight){
        // CustomWidget::renderContent(widgetWidth, widgetHeight);
        auto render = purple::Engine::getRenderEngine();
        auto shapeBatch = render->getShapeBatch();
        
        shapeBatch->begin();
        Paint paint;
        paint.color = barColor;
        const float midY = getHeight() / 2.0f;
        float t = midY + barHeight / 2.0f;
        Rect barRect(barOffsetX , t , barWidth , barHeight);
        shapeBatch->renderRoundRect(barRect , barHeight / 2.0f, paint);

        paint.color = inidicatorColor;
        shapeBatch->renderCircle(barOffsetX + convertProgressToWidth(), midY, indicatorRadius, paint);
        shapeBatch->end();
    }

    float SeekBar::convertProgressToWidth(){
        const float progressTotal = progressMaxValue - progressMinValue;
        const float ratio = progress / progressTotal;
        return barWidth * ratio;
    }

    float SeekBar::convertLenToProgressValue(float lenValue){
        const float ratio = Clamp(lenValue / barWidth , 0.0f , 1.0f);
        return RoundToTwoDecimal(ratio * (progressMaxValue - progressMinValue));
    }

    float SeekBar::getProgress(){
        const float total = progressMaxValue - progressMinValue;
        return purple::RoundToTwoDecimal(total * (progress - progressMinValue));
    }

    void SeekBar::fireUpdateCallback(float curValue , float oldValue , bool isManual){
        if(seekbarUpdateFn != nullptr){
            seekbarUpdateFn(curValue , oldValue , isManual);
        }
    }

    void SeekBar::setProgress(float newProgress){
        setProgressInner(newProgress , false);
    }

    void SeekBar::setProgressInner(float newProgress , bool manual){
        float oldValue = progress;
        progress = Clamp(newProgress , progressMinValue , progressMaxValue);
        if(std::abs(oldValue - progress) >= 0.01f){
            fireUpdateCallback(progress , oldValue , manual);
        }
    }

    bool SeekBar::onInputEvent(InputEvent &event){
        const int action = event.action;
        auto xy = inputCoordsToLocal(event.x, event.y);
        const float x = std::get<0>(xy);
        const float y = std::get<1>(xy);
        
        if(action == EVENT_ACTION_BEGIN){
            const float indiCenterX = barOffsetX + convertProgressToWidth();
            const float indiCenterY = getHeight() / 2.0f;
            if(canManualUpdate && PointInCircle(x, y , indiCenterX , indiCenterY , indicatorRadius)){
                return true;
            }
            return false;
        }else if(action == EVENT_ACTION_MOVE
            || action == EVENT_ACTION_END){
            float progressSignLen = x - barOffsetX;
            float newProgress = convertLenToProgressValue(progressSignLen);
            setProgressInner(newProgress , true);
            // std::cout << "SeekBar action " << action << " " << x << "  " << y << std::endl;                
            return true;
        } else if(action == EVENT_ACTION_CANCEL){
            return true;
        }
        return false;
    }
}


