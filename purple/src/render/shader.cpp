//
// Created by panyi on 2022/7/1.
//

#include "render/shader.h"
#include <fstream>
#include "glm/gtc/type_ptr.hpp"
#include "log.h"
#include "resource/asset_manager.h"
#include "purple.h"

namespace purple{
    std::string ReadAssetTextFile(std::string filename) {
        return ShaderManager::getInstance()->readShaderSrc(filename);
    }   

    GLuint CreateGPUProgram(const char* vsShaderSource, const char* fsShaderSource) {
        GLuint vsShader = CompileShader(GL_VERTEX_SHADER, vsShaderSource);
        GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, fsShaderSource);
        // std::cout << "glCompileProgram e222:" << glGetError() <<std::endl;
        //Attach
        GLuint program = glCreateProgram();
        glAttachShader(program, vsShader);
        glAttachShader(program, fsShader);
        // std::cout << "glCompileProgram e111:" << glGetError() <<std::endl;
        
        // GLint compileResult = GL_TRUE;
        // glGetProgramiv(program, GL_COMPILE_STATUS, &compileResult);
        // std::cout << "glCompileProgram e0000:" << glGetError() <<std::endl;
        // if(compileResult == GL_FALSE){
        //     char szLog[1024] = { 0 };
        //     GLsizei logLen = 0;
        //     glGetProgramInfoLog(program, 1024, &logLen, szLog);
        //     Logi(TAG_SHADER, "Compile program fail error log: %s \nvs shader code:\n%s\nfs shader code:\n%s\n" , szLog , vsShaderSource , fsShaderSource);
        //     glDeleteShader(program);
        //     program = 0;
        // }

        //Link
        glLinkProgram(program);
        GLint linkResult = GL_TRUE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
        if(linkResult == GL_FALSE){
            char szLog[1024] = { 0 };
            GLsizei logLen = 0;
            glGetProgramInfoLog(program, 1024, &logLen, szLog);
            Log::e(TAG_SHADER, "Compile program fail error log: %s \nvs shader code:\n%s\nfs shader code:\n%s\n" , szLog , vsShaderSource , fsShaderSource);
            glDeleteShader(program);
            program = 0;
        }

        // std::cout << "glLinkProgram e000:" << glGetError() <<std::endl;

        //Clear
        glDetachShader(program, vsShader);
        glDetachShader(program, fsShader);
        glDeleteShader(vsShader);
        glDeleteShader(fsShader);

        // std::cout << "glDeleteShader e000:" << glGetError() <<std::endl;
        Log::w(TAG_SHADER , "program = %d" , program);
        // std::cout << "glCompileProgram error:" << glGetError() <<std::endl;
        return program;
    }

    // 创建一个用于GPU运算的compute shader
    GLuint CreateComputeShaderProgram(const char* src){
        GLuint shader = glCreateShader(GL_COMPUTE_SHADER);
        if(shader == 0){
            Log::e(TAG_SHADER, "glCreateComputeShader error");
            glDeleteShader(shader);
            return 0;
        }
        
        glShaderSource(shader, 1 , &src , nullptr);
        glCompileShader(shader);
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            Log::e(TAG_SHADER,"Compute Shader Compilation Failed:%s\n" , infoLog);
            return 0;
        }

        GLuint program = glCreateProgram();
        // std::cout << "Compute program: " << program << std::endl;
        glAttachShader(program , shader);
        GLint attachedCount;
        glGetProgramiv(program, GL_ATTACHED_SHADERS, &attachedCount);
        // std::cout << "Attached shaders: " << attachedCount << std::endl;

        glLinkProgram(program);
        GLint linkResult = GL_TRUE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
        if(linkResult == GL_FALSE){
            char szLog[512] = { 0 };
            GLsizei logLen = 0;
            glGetProgramInfoLog(program, 512, &logLen, szLog);
            Log::e(TAG_SHADER, 
                    "Compile compute program fail error log:\n %s \nsource code:\n%s\n logLen = %d" 
                    ,szLog , src , logLen);
            glDeleteShader(shader);
            glDeleteProgram(program);
            program = 0;
        }

        glDeleteShader(shader);
        return program;
    }

    bool IsFileExists(std::string& name){
        std::ifstream f(name.c_str());
        return f.good();
    }

    //读取文本文件
    std::string ReadFileAsText(std::string path){
        std::string content;
        std::ifstream infile(path);
        if(infile.is_open()){
            std::string line;
            while(std::getline(infile , line)){
                line += "\n";
                content += line;
            }//end while
        }else{
            Log::i(TAG_SHADER , "open file : %s error" , path.c_str());
        }
        infile.close();
        return content;
    }

    //从文件中创建shader
    GLuint CreateGPUProgramFromFile(std::string vertexShaderPath , std::string fragShaderPath){
        std::string vertexSrc = ReadFileAsText(vertexShaderPath);
        std::string fragSrc = ReadFileAsText(fragShaderPath);

        return CreateGPUProgram(vertexSrc.c_str() , fragSrc.c_str());
    }

    Shader Shader::buildGPUProgram(std::string vtxSrc , std::string frgSrc){
        Shader shader;
        auto pid = CreateGPUProgram(vtxSrc.c_str() , frgSrc.c_str());
        shader.programId = pid;
        return shader;
    }

    Shader Shader::buildGPUProgramAssetFile(std::string vtxPath , std::string frgPath){
        Shader shader;
        auto  pid = CreateGPUProgramByAsset(vtxPath , frgPath);
        shader.programId = pid;
        return shader;
    }

    Shader Shader::buildGPUComptuteShaderAssetFile(std::string srcFilePath){
        Shader shader;
        auto pid = CreateComputeProgremAsset(srcFilePath);
        shader.programId = pid;
        return shader;
    }

    Shader Shader::buildGPUProgramFromBinaryFile(std::string shaderName){
        Shader shader;
        if(isDebug){
            return shader;
        }

        GLint programBinaryFormats = GL_NONE;
        glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &programBinaryFormats);
        if(programBinaryFormats <= GL_NONE) {
            Log::e("Shader" , "GL_NUM_PROGRAM_BINARY_FORMATS = %d" , programBinaryFormats);
            return shader;
        }

        GLint binaryFormat = GL_NONE;
        glGetIntegerv(GL_PROGRAM_BINARY_FORMATS , &binaryFormat);
        if(binaryFormat <= GL_NONE){
            Log::e("Shader" , "GL_PROGRAM_BINARY_FORMATS = %d" , binaryFormat);
            return shader;
        }
        Log::w("Shader" , "Shader Program binary format : %d" , binaryFormat); 

        std::string cacheDir = ShaderManager::ensureShaderCacheDir();
        std::string binFile = cacheDir + shaderName + SUFFIX_BINARY_FILE;
        Log::i("Shader" , "load binary shader file : %s" , binFile.c_str());

        if(!IsFileExists(binFile)){
            Log::e("Shader" , "load binary shader %s file Not exist" , binFile.c_str());
            return shader;
        }

        int fileLength = 0;
        auto dataBuf = AssetManager::getInstance()->readFileAsBinRaw(binFile.c_str() , fileLength);
        if(dataBuf != nullptr && fileLength > 0){
            GLuint program = glCreateProgram();
            glProgramBinary(program , binaryFormat, dataBuf , fileLength);

            GLint linkResult;
            glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
            if(!linkResult){
                char szLog[1024] = { 0 };
                GLsizei logLen = 0;
                glGetProgramInfoLog(program, 1024, &logLen, szLog);
                Log::e(TAG_SHADER, "Compile program fail error log: %s" , szLog);
                glDeleteShader(program);
                program = 0;
            }

            Log::i("Shader" , "load program from binary success id = %d" , program);
            //success
            shader.programId = program;
        }
        return shader;
    }

    GLuint CompileShader(GLenum shaderType, const char* shaderSource) {
        GLuint shader = glCreateShader(shaderType);
        if (shader == 0) {
            Log::e(TAG_SHADER , "create shader failed : %s" , shaderSource);
            glDeleteShader(shader);
            return 0;
        }
        const char* shaderCode = shaderSource;
        if (shaderCode == nullptr) {
            Log::e(TAG_SHADER , "load shader code from %s failed" , shaderSource);
            glDeleteShader(shader);
            return 0;
        }

        glShaderSource(shader, 1, &shaderCode, nullptr);
        glCompileShader(shader);

        GLint compileResult = GL_TRUE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
        if (compileResult == GL_FALSE) {
            char szLog[1024] = { 0 };
            GLsizei logLen = 0;
            glGetShaderInfoLog(shader, 1024, &logLen, szLog);
            Log::e(TAG_SHADER , "Compile Shader fail error log: %s \nshader code:\n%s\n", szLog, shaderCode);
            glDeleteShader(shader);
            shader = 0;
        }
        return shader;
    }

    void Shader::useShader(){
        glUseProgram(this->programId);
    }

    void Shader::dispathComputeShader(int groupX, int groupY, int groupZ){
        glDispatchCompute(groupX, groupY, groupZ);
    }

    void Shader::setUniformInt(std::string key , int value){
        GLint loc = findUniformLocation(key);
        glUniform1i(loc , value);
    }

    void Shader::setUniformFloat(std::string key , float value){
        GLint loc = findUniformLocation(key);
        glUniform1f(loc , value);
    }

    void Shader::setUniformMat3(std::string key, glm::mat3 mat) {
        GLint loc = findUniformLocation(key);
        glUniformMatrix3fv(loc , 1 , GL_FALSE , glm::value_ptr(mat));
    }

    void Shader::setUniformMat4(std::string key , glm::mat4 mat){
        GLint loc = findUniformLocation(key);
        glUniformMatrix4fv(loc , 1 , GL_FALSE , glm::value_ptr(mat));
    }

    void Shader::setUniformVec4(std::string key , glm::vec4 vec){
        GLint loc = findUniformLocation(key);
        glUniform4fv(loc , 1 ,  (float *)(&vec[0]));
    }

    void Shader::setUniformVec2(std::string key , glm::vec2 vec){
        GLint loc = findUniformLocation(key);
        glUniform2fv(loc , 1 ,  (float *)(&vec[0]));
    }

    void Shader::setUniformVec3(std::string key , float x , float y , float z){
        GLint loc = findUniformLocation(key);
        glUniform3f(loc , x , y , z);
    }

    void Shader::setUniformVec3(std::string key ,glm::vec3 value){
        GLint loc = findUniformLocation(key);
        glUniform3fv(loc , 1 , (float *)(&value[0]));
    }

    void Shader::setUniformVec2(std::string key , float x , float y){
        GLint loc = findUniformLocation(key);
        glUniform2f(loc , x , y);
    }

    void Shader::setUniformIVec2(std::string key , int x , int y){
        GLint loc = findUniformLocation(key);
        glUniform2i(loc , x,  y);
    }

    void Shader::setUniformBool(std::string key , bool value){
        GLint loc = findUniformLocation(key);
        glUniform1i(loc , value);
    }

    int Shader::findUniformLocation(std::string key){
        if(unifromLocs.find(key) != unifromLocs.end()){
            return unifromLocs[key];
        }

        const int loc = glGetUniformLocation(this->programId , key.c_str());
        if(loc >= 0){
            unifromLocs[key] = loc;
        }
        return loc;
    }

    void Shader::deleteSelf(){
        if(programId != 0){
            glDeleteShader(programId);
        }
    }

    //获取 或 创建出一个shader
    Shader ShaderManager::loadShader(std::string shaderName , 
            std::string vtxSrc , std::string frgSrc) {
        if(shaderMap.find(shaderName) == shaderMap.end()){//not found shader create a new shader
            Log::i("Shader" , "create a new shader %s " , shaderName.c_str());
            //build shader from binary cache
            Shader shader = Shader::buildGPUProgramFromBinaryFile(shaderName);
            if(shader.programId == 0){
                shader = Shader::buildGPUProgram(vtxSrc , frgSrc);
                cacheShaderProgram(shader.programId , shaderName);
            }else{
                Log::w("Shader" , "create a new shader %s from cache" , shaderName.c_str());
            }

            if(shader.programId > 0){
                shaderMap[shaderName] = shader;
            }
        }
        return shaderMap[shaderName];
    }

    //获取 或 创建出一个shader
    // Shader ShaderManager::loadShaderByPath(std::string shaderName , std::string vertexPath , std::string fragPath) {
    //     if(shaderMap.find(shaderName) == shaderMap.end()){//not found shader create a new shader
    //         Log::i("no found %s , create a new shader" , shaderName.c_str());
    //         Shader shader = Shader::buildGPUProgramAssetFile(vertexPath , fragPath);
    //         shaderMap[shaderName] = shader;
    //         cacheShaderProgram(shader.programId , shaderName);
    //     }else{
    //         Log::i("has found %s , reuse shader" , shaderName.c_str());
    //     }
    //     return shaderMap[shaderName];
    // }

    Shader ShaderManager::getShaderByName(std::string shaderName){
        return shaderMap[shaderName];
    }
    
    //缓存已编译好的二进制shader程序
    void ShaderManager::cacheShaderProgram(GLuint programId , std::string shaderName){
        const int BinBufSize = 512 * 1024;
        int size;
        GLenum binaryFormat;
        // uint8_t *buf = new uint8_t[BinBufSize];
        std::vector<uint8_t> buf(BinBufSize);
        glGetProgramBinary(programId , BinBufSize ,&size , &binaryFormat , buf.data());
        Log::w("cache_shader" , "Get binary shader size : %d , binaryFormat : %d  , name : %s" , 
            size , binaryFormat, shaderName.c_str());
        
        std::string shaderCacheDir = ensureShaderCacheDir();
        Log::w("cache_shader" , "shaderCacheDir : %s" , shaderCacheDir.c_str());

        if(size <= 0){
            return;
        }
        
        std::string cacheFilePath = shaderCacheDir + shaderName + SUFFIX_BINARY_FILE;
        long writeSize = AssetManager::getInstance()->writeFileWithBin(cacheFilePath , 
                                size , buf.data());
        Log::w("cache_shader" , "cachefile %s writeSize : %ld" 
                    ,cacheFilePath.c_str() 
                    ,writeSize);
    }

    std::string ShaderManager::ensureShaderCacheDir(){
        std::string cacheDir = AssetManager::getInstance()->ensureCacheDir();
        std::string shaderCacheDir = cacheDir + SHADER_CACHE_DIR;
        AssetManager::getInstance()->makedir(shaderCacheDir);
        return shaderCacheDir;
    }

    void ShaderManager::clear() {
        Log::i(TAG_SHADER , "shader manager clear");
        for(auto pair : shaderMap){
            Shader shader = pair.second;
            if(glIsProgram(shader.programId)){
               glDeleteProgram(shader.programId);
            }else{
                Log::e(TAG_SHADER ,"%d is not a shader" , shader.programId);
            }
        }
        // std::cout << "shader clear glGetError -> "<< glGetError() << std::endl;

        Log::i(TAG_SHADER ,"shader map size %d" , shaderMap.size());
        shaderMap.clear();
        Log::i(TAG_SHADER ,"shader map size after clear %d" , shaderMap.size());
    }

    std::shared_ptr<ShaderManager> ShaderManager::getInstance() {
        static std::shared_ptr<ShaderManager> instance_;
        if(instance_ == nullptr){
            instance_ = std::make_shared<ShaderManager>();
        }
        return instance_;
    }

    //从Asset中读取shader
    GLuint CreateGPUProgramByAsset(std::string vsFilePath , std::string fsFilePath){
        return CreateGPUProgram(ReadAssetTextFile(vsFilePath).c_str() ,
                                ReadAssetTextFile(fsFilePath).c_str());
    }

    //创建compute shader
    GLuint CreateComputeProgremAsset(std::string shaderProgramPath){
        // std::string proSrc = AssetManager::getInstance()->readAssetTextFileAsString(shaderProgramPath);
        // std::cout << "proSrc:" << proSrc.c_str() << std::endl;
        auto proSrc = ShaderManager::getInstance()->readShaderSrc(shaderProgramPath);
        return CreateComputeShaderProgram(proSrc.c_str());
    }

    std::string ShaderManager::readShaderSrc(std::string shaderPath){
        std::string shadrHeadSrc =   
        #ifdef __ANDROID__
        "#version 310 es \n";
        #elif defined(__APPLE__) && defined(__arm64__)
        "#version 410 core \n";
        #elif __ARM_ARCH
        "#version 330 es \n";
        #else
        "#version 410 core \n";
        #endif
        
        std::string shaderBodySrc = AssetManager::getInstance()->readAssetTextFileAsString(shaderPath);
        return std::string(shadrHeadSrc + shaderBodySrc);
    }

    Shader ShaderManager::loadAssetShader(std::string shaderName , 
                std::string vertexPath , std::string frgPath){
        if(shaderMap.find(shaderName) != shaderMap.end()){ //found shader by shader name direct return
            return shaderMap[shaderName];
        }
        return loadShader(shaderName , readShaderSrc(vertexPath) , readShaderSrc(frgPath));
    }
}
