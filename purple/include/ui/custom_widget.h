#pragma once

#include "ui/widget.h"
#include "render/texture.h"
#include <memory>
#include <tuple>

namespace purple{
    class CustomWidget : public Widget {
    public:
        CustomWidget(int reqW , int reqH) : Widget(reqW , reqH){
            regenerateTexId();
        }

        virtual void onMeasure(MeasureSpecMode widthSpecMode,
                                int widthValue, 
                                MeasureSpecMode heightSpecMode,
                                int heightValue) override;

        virtual void onRender() override;

        virtual void renderContent(int widgetWidth , int widgetHeight);

        virtual ~CustomWidget();

        std::tuple<float , float> inputCoordsToLocal(float x , float y);
    protected:
        void buildVirtualTexture();
    
    private:
        std::shared_ptr<TextureInfo> virtualTexture = nullptr;
        std::string texId = "CustomWidget";

        void regenerateTexId();
    };
}