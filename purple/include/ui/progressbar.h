#pragma once

#include "ui/seekbar.h"

namespace purple{
    class ProgressBar : public SeekBar{
    public:
        ProgressBar(int reqW , int reqH) : SeekBar(reqW, reqH){
            this->canManualUpdate = false;
            barColor = ConverColorValue(Color::Gray);
            inidicatorColor = ConverColorValue(Color::SkyBlue);
        }

        virtual void renderContent(int widgetWidth , int widgetHeight) override;
    };
}
