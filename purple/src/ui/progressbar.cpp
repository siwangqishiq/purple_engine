#include "ui/progressbar.h"
#include "purple.h"


namespace purple{
    void ProgressBar::renderContent(int widgetWidth , int widgetHeight){
        auto render = purple::Engine::getRenderEngine();
        auto shapeBatch = render->getShapeBatch();
        
        Paint paint;
        shapeBatch->begin();

        paint.color = barColor;
        const float midY = getHeight() / 2.0f;
        const float t = barHeight;
        const float rectRoundRadius = barHeight / 2.0f;
        Rect barRect(barOffsetX , t , barWidth , barHeight);
        shapeBatch->renderRoundRect(barRect , rectRoundRadius, paint);
        paint.color = inidicatorColor;
        Rect indicatorRect(barOffsetX , t , 
            convertProgressToWidth() , barHeight);
        shapeBatch->renderRoundRect(indicatorRect , rectRoundRadius, paint);
        shapeBatch->end();
    }
}

