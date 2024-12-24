#pragma once

#include "ui/custom_widget.h"

namespace purple{
    class Switcher : public CustomWidget{
    public:
        Switcher(int reqW , int reqH) : CustomWidget(reqW, reqH){
        }

        virtual void renderContent(int widgetWidth , int widgetHeight) override;
    };
}

