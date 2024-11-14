#pragma once

#include "ui.h"
#include "color.h"
#include "render/common.h"

namespace purple{

    class Text :public Widget{
    public:
        Text(const wchar_t *chars,int w,int h):Widget(w, h),content_(chars){}

        Text(std::wstring content,int w,int h):Widget(w, h),content_(content){}

        virtual void measure(int parentRequestWidth , int parentRequestHeight);
        virtual void render();

        virtual ~Text();

        virtual void setText(std::wstring &content){
            content_ = content;
        }

        template<typename T>
        T& setFontColor(glm::vec4 fontColor){
            textPaint_.textColor = fontColor;
            return static_cast<T&>(*this);
        }

        template<typename T>
        T& setFontSize(float fontSize){
            textPaint_.setTextSize(fontSize);
            return static_cast<T&>(*this);
        }

        template<typename T>
        T& setTextGravity(TextGravity gravity){
            textPaint_.textGravity = gravity;
            return static_cast<T&>(*this);
        }
    private:
        std::wstring content_ = L"";
        TextPaint textPaint_;

        void preCalculateTextRectSize(Rect &outInfo,int maxWidth);
    };
}