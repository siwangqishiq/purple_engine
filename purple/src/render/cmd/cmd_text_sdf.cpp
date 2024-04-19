#include "render/cmd/cmd_text_sdf.h"

namespace purple{
    std::shared_ptr<CharInfo> SdfTextRenderCommand::findCharInfo(wchar_t &ch , int index){
        return textRender_->findCharInfo(ch , index);
    }

    void SdfTextRenderCommand::putParams(
            std::wstring &text ,
            float left ,
            float bottom,
            TextPaint &paint){
        paint_ = paint;

        allocatorVRamForText(text.length());
        if(vbo_ <= 0){
            Log::e(TAG , "SdfTextRenderCommand -> vbo is < 0");
            return;
        }

        float x = left;
        float y = bottom;
        std::vector<float> buf(vertexCount_ * attrCount_);
        
        float depth = engine_->getAndChangeDepthValue();
        for(int i = 0 ; i < text.length() ;i++){
            std::shared_ptr<CharInfo> charInfoPtr = findCharInfo(text[i] , i);
            putVertexDataToBuf(buf , i , x , y ,depth, charInfoPtr , paint);
            x += (charInfoPtr->width + paint.gapSize) * paint.textSizeScale;

            fontTextureId_ = charInfoPtr->textureId;
        }//end for i

        buildGlCommands(buf);                 
    }

    void SdfTextRenderCommand::runCommands(){
        if(fontTextureId_ <= 0){
            return;
        }
        
        Shader shader = fetchSdfTextShader();
        shader.useShader();
        shader.setUniformMat3("transMat" , engine_->normalMatrix_);
        shader.setUniformVec4("textColor" , paint_.textColor);
        
        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER , vbo_);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, fontTextureId_);
        shader.setUniformInt("fontTexture" , 0);
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 6 * sizeof(float) , 
            reinterpret_cast<void *>(vboOffset_));
        glVertexAttribPointer(1 , 3 , GL_FLOAT , GL_FALSE , 6 * sizeof(float) , 
            reinterpret_cast<void *>(vboOffset_ + 3 * sizeof(float)));
        glDrawArrays(GL_TRIANGLES , 0 , vertexCount_);

        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        glBindBuffer(GL_ARRAY_BUFFER , 0);
        glBindVertexArray(0);
    }



    Shader SdfTextRenderCommand::fetchSdfTextShader(){
        return ShaderManager::getInstance()->loadAssetShader(SAHDER_NAME_SDF_TEXT, 
                    "shader/render_sdftext_vert.glsl", 
                    "shader/render_sdftext_frag.glsl");
    }
}