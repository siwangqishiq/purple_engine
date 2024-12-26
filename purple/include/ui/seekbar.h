#pragma once

#include <functional>
#include "ui/custom_widget.h"

namespace purple{
    typedef std::function<void(float, float , bool)> SeekBarUpdateFunc;

    class SeekBar : public CustomWidget{
    public:
        SeekBar(int reqW , int reqH) : CustomWidget(reqW, reqH){
            barColor = ConverColorValue(Color::SkyBlue);
            inidicatorColor = ConverColorValue(Color::SkyBlue);
        }

        virtual void onMeasure(MeasureSpecMode widthSpecMode,
                        int widthValue, 
                        MeasureSpecMode heightSpecMode,
                        int heightValue) override;

        float getProgress();

        void setProgress(float newProgress);

        virtual void renderContent(int widgetWidth , int widgetHeight) override;
        
        virtual bool onInputEvent(InputEvent &event) override;

        template<typename T>
        T& setMinValue(float minValue){
            this->progressMinValue = minValue;
            return static_cast<T&>(*this);
        }

        template<typename T>
        T& setMaxValue(float maxValue){
            this->progressMaxValue = maxValue;
            return static_cast<T&>(*this);
        }

        template<typename T>
        T& setProgressUpdate(SeekBarUpdateFunc updateFn){
            this->seekbarUpdateFn = updateFn;
            return static_cast<T&>(*this);
        }

        template<typename T>
        T& setBarColor(ColorType color){
            this->barColor = color;
            return static_cast<T&>(*this);
        }

        template<typename T>
        T& setIndicatorColor(ColorType color){
            this->inidicatorColor = color;
            return static_cast<T&>(*this);
        }
        
    protected:
        bool canManualUpdate = true; //是否可以手动拖拽

        glm::vec4 barColor;
        glm::vec4 inidicatorColor;

        float progressMinValue = 0.0f;
        float progressMaxValue = 100.0f;
        float progress = 0.0f;

        float indicatorRadius = 0.0f;
        float barOffsetX = 0.0f;
        float barHeight = 0.0f;
        float barWidth = 0.01f;

        void putSeekbarParams();

        float convertProgressToWidth();

        float convertLenToProgressValue(float lenValue);
        
        void fireUpdateCallback(float curValue , float oldValue , bool isManual);
        
        void setProgressInner(float newProgress , bool manual);

        SeekBarUpdateFunc seekbarUpdateFn = nullptr;
    private:
    };
}