#pragma once

#include <sstream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdint.h>
#include "Model.hpp"
#include "Vector.hpp"

struct MeshInfo
{
    std::string name;
    std::string material;
    std::unique_ptr<std::vector<int>> vertexIndices;
    std::unique_ptr<std::vector<int>> normalIndices;
    std::unique_ptr<std::vector<int>> textureIndices;
    std::unique_ptr<std::vector<Vector4f>> vertices;
    std::unique_ptr<std::vector<Vector4f>> normals;
    std::unique_ptr<std::vector<Vector4f>> textureCoords;
};

// width, height, bytes per pixel (RGB/RGBA) and data
struct TextureInfo2
{
    int width;
    int height;
    int bytesPerPixel;
    std::vector<uint8_t> data;
};

typedef std::tuple<int, int, int, std::vector<uint8_t>> TextureInfo;
typedef std::unordered_map<std::string, TextureInfo> MaterialInfoMap;

class Parser
{
    public:

        static std::vector<std::unique_ptr<Model>> parseScene(const char* fileName);
        static MaterialInfoMap parseMaterialInfo(const std::string& fileName);
        static TextureInfo parseTexture(const std::string& fileName,const std::string& name);
    
    private:

        static std::unique_ptr<MeshInfo> parseMesh(std::ifstream& file, std::string& name);

        static std::stringstream getBuffer(const char* fileName);
        static int getInt(std::stringstream& buffer, int len);
        static std::string getBasePath(const std::string& path);
        static void fromBottom(std::vector<char>& srcBuffer, std::vector<uint8_t>& destBuffer, int step);
};