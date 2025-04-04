//
// Created by panyi on 2022/7/1.
//
#pragma once

#include "glheader.h"
#include <string>
#include "glm/glm.hpp"
#include <unordered_map>
#include <map>
#include <memory>

namespace purple{
        
    const std::string TAG_SHADER = "shader";

    const std::string SHADER_CACHE_DIR = "shadercache/";

    const std::string SUFFIX_BINARY_FILE = ".bin";

    // //读取asset 文本文件
    // std::string ReadAssetTextFile(std::string filename);

    //编译shader源码
    GLuint CompileShader(GLenum shaderType, const char* shaderSource);

    //创建完整Shader
    GLuint CreateGPUProgram(const char* vsShaderSource, const char* fsShaderSource);

    GLuint CreateGPUProgramByAsset(std::string vsFilePath , std::string fsFilePath);

    //创建一个计算shader
    GLuint CreateComputeProgremAsset(std::string shaderProgramPath);

    //读取文本文件
    std::string ReadFileAsText(std::string path);

    bool IsFileExists(std::string &name);

    class Shader{
    public:
        static Shader buildGPUProgram(std::string vtxSrc , std::string frgSrc);

        static Shader buildGPUProgramAssetFile(std::string vtxSrc , std::string frgSrc);

        static Shader buildGPUProgramFromBinaryFile(std::string shaderName);

        static Shader buildGPUComptuteShaderAssetFile(std::string srcFilePath);

        //使用shader
        void useShader();
        
        //调度计算着色器
        void dispathComputeShader(int groupX , int groupY, int groupZ);

        //
        void setUniformInt(std::string key , int value);

        void setUniformFloat(std::string key , float value);

        //
        void setUniformMat4(std::string key , glm::mat4 mat);

        void setUniformMat3(std::string key , glm::mat3 mat);

        //设置三维向量
        void setUniformVec3(std::string key , float x , float y , float z);

        //设置二维向量
        void setUniformVec2(std::string key , float x , float y);

        void setUniformVec2(std::string key , glm::vec2 vec);

        void setUniformIVec2(std::string key , int x , int y);

        //设置三维向量
        void setUniformVec3(std::string key ,glm::vec3 value);

        //设置四维向量
        void setUniformVec4(std::string key , glm::vec4 vec);

        void setUniformBool(std::string key , bool value);

        int findUniformLocation(std::string key);

        void deleteSelf();

        unsigned int programId = 0;
    protected:
        std::unordered_map<std::string , int> unifromLocs; //unifrom变量loccation
    };

    class ShaderManager{
    private:
        std::unordered_map<std::string , Shader> shaderMap;

        static std::shared_ptr<ShaderManager> instance_;
    public:
        static std::shared_ptr<ShaderManager> getInstance();

        std::string readShaderSrc(std::string shaderPath);

        Shader loadAssetShader(std::string shaderName , std::string vertexPath , std::string frgPath);

        Shader loadShader(std::string shaderName , std::string vertexSrc , std::string frgSrc);

        // Shader loadShaderByPath(std::string shaderName , std::string vertexPath , std::string fragPath);

        Shader getShaderByName(std::string shaderName);

        void cacheShaderProgram(GLuint programId ,std::string shaderName);

        void clear();

        static std::string ensureShaderCacheDir();
    };
}

