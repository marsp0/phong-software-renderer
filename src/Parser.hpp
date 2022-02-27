#pragma once

#include <sstream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdint.h>
#include <filesystem>

#include "Model.hpp"
#include "Vector.hpp"
#include "Material.hpp"

namespace parser
{
    // 
    // classes
    // 

    struct MeshInfo
    {
        std::string name;
        std::string material;
        std::vector<int> vertexIndices;
        std::vector<int> normalIndices;
        std::vector<int> textureIndices;
        std::vector<Vector4f> vertices;
        std::vector<Vector4f> normals;
        std::vector<Vector4f> textureCoords;
    };

    struct TextureInfo
    {
        int imageIDLen;
        int colorMapType;
        int imageType;
        int colorMapFirstEntryIndex;
        int colorMapSize;
        int colorMapEntrySize;
        int xOrigin;
        int yOrigin;
        int width;
        int height;
        int pixelDepth;
        int bytesPerPixel;
        Material material;
        std::vector<uint32_t> data;
    };

    typedef std::unordered_map<std::string, TextureInfo> MaterialMap;

    // 
    // functions
    // 

    std::vector<std::unique_ptr<Model>> parseScene(const std::string& fileName);
    MaterialMap parseMaterial(const std::filesystem::path& materialFile);
    TextureInfo parseTexture(const std::filesystem::path& textureFile);
    std::vector<char> parseDataBlock(std::ifstream& file, int size);
    MeshInfo parseMesh(std::ifstream& file, const std::string& name);
    void parseMeshAttribute(std::istringstream& buffer, std::vector<Vector4f>& storage, unsigned int amount);
    void parseMeshFace(std::istringstream& buffer, 
                       std::vector<int>& vertexIndices,
                       std::vector<int>& normalIndices,
                       std::vector<int>& textureIndices);
    int getInt(std::ifstream& buffer, int len);

};