#pragma once

#include "ui/custom_widget.h"

namespace purple{

    class Switcher : public CustomWidget{
    public:
        Switcher(int reqW , int reqH) : CustomWidget(reqW, reqH){
        }

        virtual void renderContent(int widgetWidth , int widgetHeight) override;

        virtual void onMeasure(MeasureSpecMode widthSpecMode,
                                int widthValue, 
                                MeasureSpecMode heightSpecMode,
                                int heightValue) override;
    private:
        bool seleced = false;

        const int DefaultHeight = 100;
        const int DefaultPadding = 8;
    };
}

