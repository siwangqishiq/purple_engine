#pragma once

#include "render/cmd/command.h"

namespace purple{
    class CircleRenderCommand: public RenderCommand{
    public:
        CircleRenderCommand(RenderEngine *engine) 
            :RenderCommand(engine){
            shader_ = ShaderManager::getInstance()->loadAssetShader("circle",
                        "shader/shape/circle_vert.glsl", "shader/shape/circle_frag.glsl");
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