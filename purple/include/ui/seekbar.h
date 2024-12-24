#pragma once

#include "ui/custom_widget.h"

namespace purple{
    class SeekBar : public CustomWidget{
    public:
        SeekBar(int reqW , int reqH) : CustomWidget(reqW, reqH){
        }

        virtual void renderContent(int widgetWidth , int widgetHeight) override;
    };
}