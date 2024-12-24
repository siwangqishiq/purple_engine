#pragma once

#include "ui/custom_widget.h"

namespace purple{
    class ProgressBar : public CustomWidget{
    public:
        ProgressBar(int reqW , int reqH) : CustomWidget(reqW, reqH){
        }

        virtual void renderContent(int widgetWidth , int widgetHeight) override;
    };
}
