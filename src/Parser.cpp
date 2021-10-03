#include "Parser.hpp"

#include <exception>
#include <fstream>
#include <iostream>


std::vector<std::unique_ptr<Model>> Parser::parseScene(const char* fileName)
{
    std::vector<std::unique_ptr<Model>> models;
    MaterialInfoMap textures;
    std::stringstream buffer = Parser::getBuffer(fileName);
    std::string line;
    std::string materialFile;
    // iterates over every model
    while (std::getline(buffer, line))
    {
        std::string             name;
        std::string             material;
        std::string             entry;
        std::vector<int>        vertexIndices;
        std::vector<int>        normalIndices;
        std::vector<int>        textureIndices;
        std::vector<Vector4f>   vertices;
        std::vector<Vector4f>   normals;
        std::vector<Vector4f>   textureCoords;

        std::stringstream lineBuffer;
        lineBuffer << line;
        
        std::getline(lineBuffer, entry, ' ');
        if (entry == "mtllib")
        {
            std::getline(lineBuffer, materialFile, ' ');
            std::string filePath = Parser::getBasePath(fileName) + materialFile;
            textures = Parser::parseMaterialInfo(filePath);
        }
        else if (entry == "o")
        {
            std::getline(lineBuffer, name, ' ');
            // iterate over every attribute of the model
            while (std::getline(buffer, line))
            {
                std::stringstream attributeBuffer;
                attributeBuffer << line;

                std::string element;
                std::string attributeName;
                std::getline(attributeBuffer, attributeName, ' ');
                if (attributeName == "v" || attributeName == "vn")
                {
                    std::getline(attributeBuffer, element, ' ');
                    float x = std::stof(element);
                    
                    std::getline(attributeBuffer, element, ' ');
                    float y = std::stof(element);

                    std::getline(attributeBuffer, element, ' ');
                    float z = std::stof(element);
                    
                    if (attributeName == "v")
                    {
                        vertices.push_back(Vector4f(x, y, z, 1.f));
                    }
                    else
                    {
                        normals.push_back(Vector4f(x, y, z, 1.f));
                    }
                }
                else if (attributeName == "vt")
                {
                    std::getline(attributeBuffer, element, ' ');
                    float x = std::stof(element);
                    
                    std::getline(attributeBuffer, element, ' ');
                    float y = std::stof(element);
                    
                    textureCoords.push_back(Vector4f(x, y, 0.f, 1.f));
                }
                else if (attributeName == "usemtl")
                {
                    std::getline(attributeBuffer, material, ' ');
                }
                else if (attributeName == "f")
                {
                    std::string index;
                    while (std::getline(attributeBuffer, element, ' '))
                    {
                        std::stringstream indicesBuffer;
                        indicesBuffer << element;
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

                // peek to see if the next row is a new object
                if (buffer.peek() == 'o')
                {
                    break;
                }
            }
            TextureInfo textureTuple = textures[material];
            int width = std::get<0>(textureTuple);
            int height = std::get<1>(textureTuple);
            int bytesPerPixel = std::get<2>(textureTuple);
            std::vector<uint8_t>& data = std::get<3>(textureTuple);
            std::unique_ptr<TextureBuffer> textureBuffer = std::make_unique<TextureBuffer>(width, height);
            for (int i = 0; i < data.size(); i += bytesPerPixel)
            {
                uint32_t color = 0;
                color += data[i + 0] << 8;  // blue
                color += data[i + 1] << 16; // green
                color += data[i + 2] << 24; // red
                if (bytesPerPixel == 4)
                {
                    color += data[i + 3];
                }
                textureBuffer->set(i / bytesPerPixel, 0, color);
            }
            models.push_back(std::make_unique<Model>(vertices, normals, textureCoords, vertexIndices,
                                                     normalIndices, textureIndices, std::move(textureBuffer)));
        }
    }
    for (int i = 0; i < models.size(); i++)
    {
        models[i]->position.x = i * 5.f;
        models[i]->position.y = i * 5.f;
    }
    return std::move(models);
}

std::stringstream Parser::getBuffer(const char* fileName)
{
    std::ifstream sceneFile(fileName, std::ifstream::in);
    std::stringstream buffer;
    buffer << sceneFile.rdbuf();
    sceneFile.close();
    return buffer;
}

std::string Parser::getBasePath(const std::string& path)
{
  return path.substr(0, path.find_last_of("/\\") + 1);
}

MaterialInfoMap Parser::parseMaterialInfo(const std::string& fileName)
{
    std::string line;
    std::string materialName;
    std::string textureFileName;
    std::stringstream buffer = Parser::getBuffer(fileName.c_str());
    MaterialInfoMap materialInfoMap;
    while (std::getline(buffer, line))
    {
        // Note: c++20 has a starts_with function that is cleaner looking than this
        // https://en.cppreference.com/w/cpp/string/basic_string/starts_with
        if (line.substr(0, 6) == "newmtl")
        {
            materialName = line.substr(7);
            while (std::getline(buffer, line))
            {
                if (line.substr(0, 6) == "map_Kd")
                {
                    std::string filePath = Parser::getBasePath(fileName) + line.substr(7);
                    materialInfoMap[materialName] = Parser::parseTexture(filePath, materialName);
                }
                // peek if next line is a new material
                if (buffer.peek() == 'n')
                {
                    break;
                }
            }
        }
    }
    return std::move(materialInfoMap);
}

TextureInfo Parser::parseTexture(const std::string& fileName, const std::string& name)
{
    
    std::stringstream buffer = Parser::getBuffer(fileName.c_str());
    // header information
    int imageIDLen = Parser::getInt(buffer, 1);
    int colorMapType = Parser::getInt(buffer, 1);
    int imageType = Parser::getInt(buffer, 1);
    int colorMapFirstEntryIndex = Parser::getInt(buffer, 2);
    int colorMapSize = Parser::getInt(buffer, 2);
    int colorMapEntrySize = Parser::getInt(buffer, 1);
    int xOrigin = Parser::getInt(buffer, 2);
    int yOrigin = Parser::getInt(buffer, 2);
    int width = Parser::getInt(buffer, 2);
    int height = Parser::getInt(buffer, 2);
    int pixelDepth = Parser::getInt(buffer, 1);
    // image descriptor shows what corner holds the first byte
    //                 4th bith     5th bit
    // bottom left -      0            0
    // bottom right -     1            0
    // top left -         0            1
    // top right -        1            1
    int imageDescriptor = Parser::getInt(buffer, 1);
    
    // additional header data
    std::vector<char> imageInfo;
    imageInfo.resize(imageIDLen);
    buffer.read(imageInfo.data(), imageIDLen);
    
    // color map data (should not be needed for our textures)
    int colorMapBytes = colorMapSize * colorMapEntrySize / 8;
    std::vector<char> colorMapData;
    colorMapData.resize(colorMapBytes);
    buffer.read(colorMapData.data(), colorMapBytes);

    // texture data that we will use
    int bytesPerPixel = pixelDepth / 8;
    int imageDataBytes = width * height * bytesPerPixel;
    std::vector<char> imageData;
    imageData.resize(imageDataBytes);
    buffer.read(imageData.data(), imageDataBytes);

    // convert char -> uint8
    std::vector<uint8_t> data;
    data.resize(imageData.size());
    bool bottomLeft = !(imageDescriptor & 16) && !(imageDescriptor & 32);
    bool bottomRight = (imageDescriptor & 16) && !(imageDescriptor & 32);
    bool topLeft = !(imageDescriptor & 16) && (imageDescriptor & 32);
    if (bottomLeft)
    {
        Parser::fromBottom(imageData, data, bytesPerPixel * width);
    }
    else if (bottomRight)
    {
        Parser::fromBottom(imageData, data, bytesPerPixel);
    }
    else if (topLeft)
    {
        for (int i = 0; i < imageData.size(); i++)
        {
            data[i] = imageData[i];
        }
    }
    else
    {
        // TODO: to implement
        std::cerr << "Parser cannot convert topRight starting point";
        std::terminate();
    }
    return std::make_tuple(width, height, bytesPerPixel, data);
}

void Parser::fromBottom(std::vector<char>& srcBuffer, std::vector<uint8_t>& destBuffer, int step)
{
    int destIndex = 0;
    for (int i = srcBuffer.size() - step; i >= 0 ; i -= step)
    {
        for (int j = 0; j < step; j++)
        {
            destBuffer[destIndex + j] = reinterpret_cast<uint8_t&>(srcBuffer[i + j]);
        }
        destIndex += step;
    }
}

int Parser::getInt(std::stringstream& buffer, int len)
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