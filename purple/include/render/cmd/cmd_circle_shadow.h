#pragma once

#include "render/cmd/command.h"

namespace purple{
    class CircleShadowRenderCommand: public RenderCommand{
    public:
        CircleShadowRenderCommand(RenderEngine *engine) 
            :RenderCommand(engine){
            shader_ = ShaderManager::getInstance()->loadAssetShader("shadow_circle",
                        "shader/shape/circle_shadow_vert.glsl", "shader/shape/circle_shadow_frag.glsl");
        }

        virtual void putParams(float cx , float cy , float radius
            ,Paint &paint);
        
        virtual void runCommands() override;
    private:
        Shader shader_;
        Rect rect_;
        Paint paint_;
        
        glm::mat4 modelMat_;

        void fillRect(float cx , float cy , float radius,Paint &paint);
    };
}