#pragma once

#include "render/cmd/command.h"

namespace purple{
    class RoundRectRenderCommand: public RenderCommand{
    public:
        RoundRectRenderCommand(RenderEngine *engine) 
            :RenderCommand(engine){
            shader_ = ShaderManager::getInstance()->loadAssetShader("round_rect",
                        "shader/shape/round_rect_vert.glsl", "shader/shape/round_rect_frag.glsl");
        }

        virtual void putParams(Rect &rect ,glm::mat4 &matrix
            ,Paint &paint);

        virtual void runCommands() override;
    private:
        Shader shader_;
        Rect rect_;
        Paint paint_;

        glm::mat4 modelMat_;
    };
}