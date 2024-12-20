#pragma once

#include "ui/widget.h"

namespace purple{
    class CustomWidget : public Widget {
    public:
        CustomWidget(int reqW , int reqH) : Widget(reqW , reqH){
        }

        virtual void onMeasure(MeasureSpecMode widthSpecMode,
                                int widthValue, 
                                MeasureSpecMode heightSpecMode,
                                int heightValue) override;

        virtual void renderContent(int widgetWidth , int widgetHeight);
    };
}