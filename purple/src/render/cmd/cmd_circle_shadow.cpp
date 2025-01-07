#include "render/cmd/cmd_circle_shadow.h"

namespace purple{
    void CircleShadowRenderCommand::putParams(float cx , 
            float cy , float radius, 
            Paint &paint){
        paint_ = paint;

        fillRect(cx , cy , radius , paint);

        vertexCount_ = 4; //4个顶点
        attrCount_ = 3 + 4;//每个顶点3个属性长度 + 4全局的矩形信息

        float depth = engine_->getAndChangeDepthValue();
        
        int requestSize = vertexCount_ * attrCount_ * sizeof(float);
        int allocateSize = 0;
        allocatorVRam(requestSize , allocateSize);
        std::vector<float> buf(vertexCount_ * attrCount_);

        const int attrC = attrCount_;

        Rect &rect = rect_;

        const float outterRadius = radius + paint_.shadowRadius;
        //v1
        buf[0 * attrC + 0] = rect.left;
        buf[0 * attrC + 1] = rect.top - rect.height;
        buf[0 * attrC + 2] = depth;

        buf[0 * attrC + 3] = cx;
        buf[0 * attrC + 4] = cy;
        buf[0 * attrC + 5] = radius;
        buf[0 * attrC + 6] = outterRadius;

        //v2
        buf[1 * attrC + 0] = rect.left + rect.width;
        buf[1 * attrC + 1] = rect.top - rect.height;
        buf[1 * attrC + 2] = depth;

        buf[1 * attrC + 3] = cx;
        buf[1 * attrC + 4] = cy;
        buf[1 * attrC + 5] = radius;
        buf[1 * attrC + 6] = outterRadius;

        //v3
        buf[2 * attrC + 0] = rect.left + rect.width;
        buf[2 * attrC + 1] = rect.top;
        buf[2 * attrC + 2] = depth;

        buf[2 * attrC + 3] = cx;
        buf[2 * attrC + 4] = cy;
        buf[2 * attrC + 5] = radius;
        buf[2 * attrC + 6] = outterRadius;

        //v4
        buf[3 * attrC + 0] = rect.left;
        buf[3 * attrC + 1] = rect.top;
        buf[3 * attrC + 2] = depth;

        buf[3 * attrC + 3] = cx;
        buf[3 * attrC + 4] = cy;
        buf[3 * attrC + 5] = radius;
        buf[3 * attrC + 6] = outterRadius;

        buildGlCommands(buf);
    }

    void CircleShadowRenderCommand::fillRect(float cx , float cy , float radius,Paint &paint){
        float addedRadius = 2.0f * paint.shadowRadius;
        if(paint.fillStyle == FillStyle::Stroken){
            addedRadius += paint.stokenWidth + 1.0f;
        }

        const float realRaidus = radius + addedRadius;
        // std::cout << "CircleShadow realRaidus " << realRaidus << std::endl;
        
        rect_.left = cx - realRaidus;
        rect_.top = cy + realRaidus;
        rect_.width = realRaidus + realRaidus;
        rect_.height = rect_.width;
    }

    void CircleShadowRenderCommand::runCommands(){
        if(shader_.programId <= 0){
            return;
        }
        
        shader_.useShader();
        // shader_.setUniformMat4("modelMat" , modelMat_);
        shader_.setUniformMat3("transMat" , engine_->normalMatrix_);
        shader_.setUniformVec4("uColor" , paint_.color);
        shader_.setUniformInt("uFillType",paint_.fillStyle);
        shader_.setUniformFloat("uStrokenWidth" , paint_.stokenWidth);
        shader_.setUniformFloat("uShadowSize" , paint_.shadowRadius);
        
        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER , vbo_);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 
            attrCount_ * sizeof(float) , 
            reinterpret_cast<void *>(vboOffset_));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1 , 4 , GL_FLOAT , GL_FALSE , 
            attrCount_ * sizeof(float) , 
            reinterpret_cast<void *>(vboOffset_ + 3 * sizeof(float)));
        
        glDrawArrays(GL_TRIANGLE_FAN , 0 , vertexCount_);
        glBindBuffer(GL_ARRAY_BUFFER , 0);
        glBindVertexArray(0);

        // std::cout << "gl error:" << glGetError() << std::endl;
    }
    
}