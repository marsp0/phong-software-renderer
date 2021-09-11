#pragma once

#include <sstream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdint.h>
#include "Model.hpp"
#include "Vector.hpp"

// width, height, bytes per pixel (RGB/RGBA) and data
typedef std::tuple<int, int, int, std::vector<uint8_t>> TextureInfo;
typedef std::unordered_map<std::string, TextureInfo> MaterialInfoMap;

class Parser
{
    public:

        static std::vector<std::unique_ptr<Model>> parseScene(const char* fileName);
        static MaterialInfoMap parseMaterialInfo(const std::string& fileName);
        static TextureInfo parseTexture(const std::string& fileName,const std::string& name);
    
    private:

        static std::stringstream getBuffer(const char* fileName);
        static int getInt(std::stringstream& buffer, int len);
        static std::string getBasePath(const std::string& path);
        static void fromBottom(std::vector<char>& srcBuffer, std::vector<uint8_t>& destBuffer, int step);
};