#include "Parser.hpp"

#include <exception>
#include <fstream>

#include "QuaternionRotation.hpp"


namespace parser
{
    // very simple parser
    // 1. assumes that the material is defined before the objects
    std::vector<std::unique_ptr<Model>> parseScene(const std::string& fileName)
    {
        std::string line;
        std::string token;
        std::string materialFile;
        MaterialMap textures;
        std::vector<MeshInfo> meshes;
        std::vector<std::unique_ptr<Model>> models;
        std::ifstream file(fileName, std::ifstream::in);

        while(!file.eof())
        {
            std::getline(file, line);
            std::istringstream lineBuffer(line);
            lineBuffer >> token;
            if (token == "mtllib")
            {
                lineBuffer >> token;
                std::filesystem::path sceneFilePath(fileName);
                std::filesystem::path materialFileName(token);
                std::filesystem::path materialFilePath = sceneFilePath.parent_path() / materialFileName;
                textures = parseMaterial(materialFilePath);
            }
            else if (token == "o")
            {
                lineBuffer >> token;
                MeshInfo meshInfo = parseMesh(file, token);
                meshes.push_back(std::move(meshInfo));
            }
        }

        for (int i = 0; i < meshes.size(); i++)
        {
            MeshInfo& mesh = meshes[i];
            MaterialInfo& materialInfo = textures[mesh.material];
            models.push_back(std::make_unique<Model>(mesh.vertices, 
                                                     mesh.normals, 
                                                     mesh.textureCoords, 
                                                     mesh.vertexIndices, 
                                                     mesh.normalIndices,
                                                     mesh.textureIndices,
                                                     std::move(materialInfo.textureBuffer),
                                                     QuaternionRotation(1.f, 0.f, 0.f, 0.f),
                                                     materialInfo.material));
        }
        return std::move(models);
    }

    MaterialMap parseMaterial(const std::filesystem::path& materialFile)
    {
        std::ifstream file(materialFile.string());

        std::string line;
        std::string token;
        std::string materialName;
        MaterialMap materialInfoMap;
        while (!file.eof() && file.good())
        {
            std::getline(file, line);
            std::istringstream lineBuffer(line);
            lineBuffer >> token;
            Material material;
            std::unique_ptr<TextureBuffer> textureBuffer;
            if (token == "newmtl")
            {
                lineBuffer >> materialName;
                while (true)
                {
                    if (((unsigned char)file.peek() == 'n') || (file.eof()))       // new material or eof
                    {
                        break;
                    }

                    std::getline(file, line);
                    lineBuffer.str(line);
                    lineBuffer.clear();

                    lineBuffer >> token;
                    if (token == "map_Kd")
                    {
                        lineBuffer >> token;
                        std::filesystem::path textureFileName(token);
                        std::filesystem::path textureFilePath(materialFile.parent_path() / textureFileName);
                        textureBuffer = parseTexture(textureFilePath);
                    }
                    else if (token == "Ka")
                    {
                        lineBuffer >> token;
                        material.ambient = std::stof(token);
                    }
                    else if (token == "Kd")
                    {
                        lineBuffer >> token;
                        material.diffuse = std::stof(token);
                    }
                    else if (token == "Ks")
                    {
                        lineBuffer >> token;
                        material.specular = std::stof(token);
                    }
                    else if (token == "Ns")
                    {
                        lineBuffer >> token;
                        material.shininess = std::stof(token);
                    }
                }
                MaterialInfo materialInfo{material, std::move(textureBuffer)};
                materialInfoMap[materialName] = std::move(materialInfo);
            }

        }
        return std::move(materialInfoMap);
    }

    std::unique_ptr<TextureBuffer> parseTexture(const std::filesystem::path& textureFile)
    {
        std::ifstream file(textureFile.string());

        int imageIDLen              = getInt(file, 1);
        int colorMapType            = getInt(file, 1);
        int imageType               = getInt(file, 1);
        int colorMapFirstEntryIndex = getInt(file, 2);
        int colorMapSize            = getInt(file, 2);
        int colorMapEntrySize       = getInt(file, 1);
        int xOrigin                 = getInt(file, 2);
        int yOrigin                 = getInt(file, 2);
        int width                   = getInt(file, 2);
        int height                  = getInt(file, 2);
        int pixelDepth              = getInt(file, 1);
        int bytesPerPixel           = pixelDepth / 8;
        std::vector<uint32_t> data;
        // image descriptor shows what corner holds the first byte
        //                 4th bit      5th bit
        // bottom left -      0            0
        // bottom right -     1            0
        // top left -         0            1
        // top right -        1            1
        int imageDescriptor = getInt(file, 1);
        
        // additional header data
        std::vector<char> imageInfo = parseDataBlock(file, imageIDLen);
        
        // color map data (should not be needed for our textures)
        std::vector<char> colorMapData = parseDataBlock(file, colorMapSize * colorMapEntrySize / 8);

        // texture data that we will use
        std::vector<char> imageData = parseDataBlock(file, width * height * bytesPerPixel);

        // convert char -> uint8
        data.resize(width * height);

        // convert data to bottom left start
        bool topLeft = !(imageDescriptor & 16) && (imageDescriptor & 32);
        if (topLeft)
        {
            // convert uint8_t to uint32_t
            std::vector<uint32_t> imageDataCollapsed;
            imageDataCollapsed.resize(width * height);
            for (int i = 0; i < imageData.size(); i += bytesPerPixel)
            {
                uint32_t color = 0;
                color += reinterpret_cast<unsigned char&>(imageData[i + 0]) << 8;  // blue
                color += reinterpret_cast<unsigned char&>(imageData[i + 1]) << 16; // green
                color += reinterpret_cast<unsigned char&>(imageData[i + 2]) << 24; // red
                if (bytesPerPixel == 4)
                {
                    color += reinterpret_cast<unsigned char&>(imageData[i + 3]);
                }
                imageDataCollapsed[i / bytesPerPixel] = color;
            }

            // convert top left to bottom left
            for (int x = 0; x < width; x++)
            {
                for (int y = 0; y < height; y++)
                {
                    int dstIndex = (height - y - 1) * width + x;
                    int srcIndex = y * width + x;
                    data[dstIndex] = imageDataCollapsed[srcIndex];
                }
            }
        }
        else
        {
            // TODO: to implement
            std::cerr << "Parser can only convert from topLeft";
            std::terminate();
        }

        std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(width, height);

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                textureBuffer->set(x, y, data[y * width + x]);
            }
        }

        return std::move(textureBuffer);
    }

    MeshInfo parseMesh(std::ifstream& file, const std::string& name)
    {

        MeshInfo meshInfo;
        meshInfo.name = name;
        meshInfo.vertexIndices = std::vector<int>();
        meshInfo.normalIndices = std::vector<int>();
        meshInfo.textureIndices = std::vector<int>();
        meshInfo.vertices = std::vector<Vector4f>();
        meshInfo.normals = std::vector<Vector4f>();
        meshInfo.textureCoords = std::vector<Vector4f>();

        while (((unsigned char)file.peek() != 'o') && (!file.eof()))
        {
            std::string line;
            std::string token;
            std::string first;
            std::string second;
            std::string third;
            std::getline(file, line);
            std::istringstream lineBuffer(line);
            lineBuffer >> token;
            if (token == "v")
            {
                parseMeshAttribute(lineBuffer, meshInfo.vertices, 3);
            }
            else if (token == "vn")
            {
                parseMeshAttribute(lineBuffer, meshInfo.normals, 3);
            }
            else if (token == "vt")
            {
                parseMeshAttribute(lineBuffer, meshInfo.textureCoords, 2);
            }
            else if (token == "usemtl")
            {
                lineBuffer >> meshInfo.material;
            }
            else if (token == "f")
            {
                parseMeshFace(lineBuffer, meshInfo.vertexIndices, meshInfo.normalIndices, meshInfo.textureIndices);
            }
        }
        return std::move(meshInfo);
    }

    void parseMeshFace(std::istringstream& buffer, 
                               std::vector<int>& vertexIndices, 
                               std::vector<int>& normalIndices, 
                               std::vector<int>& textureIndices)
    {
        std::string block;
        std::string index;
        while (buffer >> block)
        {
            std::istringstream indicesBuffer(block);
            
            std::getline(indicesBuffer, index, '/');
            int v = std::stoi(index);
            
            std::getline(indicesBuffer, index, '/');
            int t = std::stoi(index);
            
            std::getline(indicesBuffer, index, '/');
            int n = std::stoi(index);
            
            vertexIndices.push_back(v - 1);
            textureIndices.push_back(t - 1);
            normalIndices.push_back(n - 1);
        }

    }

    int getInt(std::ifstream& buffer, int len)
    {
        // https://gist.github.com/rolfwr/e3e4223b887476bd9bbdab1ec29f30b4
        char storage[4];
        buffer.read(storage, len);
        int value = 0;
        for (int i = 0; i < len; ++i) {
            // casting from char (-127/127) to unsigned char (0, 255) for numbers
            unsigned char byteValue = reinterpret_cast<unsigned char&>(storage[i]);
            value += byteValue << (i*8);
        }
        return value;
    }

    std::vector<char> parseDataBlock(std::ifstream& file, int size)
    {
        std::vector<char> data;
        data.resize(size);
        file.read(data.data(), size);
        return data;
    }

    void parseMeshAttribute(std::istringstream& buffer, std::vector<Vector4f>& storage, unsigned int amount)
    {
        std::string first;
        std::string second;
        std::string third;
        buffer >> first >> second;
        float x = std::stof(first);
        float y = std::stof(second);
        float z = 0.f;
        if (amount == 3)
        {
            buffer >> third;
            z = std::stof(third);
        }
        storage.push_back(Vector4f(x, y, z, 1.f));
    }

}